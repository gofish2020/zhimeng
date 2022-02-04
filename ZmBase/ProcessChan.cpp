#include "stdafx.h"
#include "..\include\ProcessChan.h"
#include "..\include\utils.h"
#include <map>
#include "..\include\CriticalSection.h"

#define WM_PROCESS_INTEGER      WM_USER+1//发送命令
#define WM_PROCESS_STRING		WM_USER+2//发送字串
#define WM_PROCESS_STREAM		WM_USER+3//发送数据流
#define WM_PROCESS_LOGGER		WM_USER+4//发送日志
#define WM_PROCESS_COMMAND		WM_USER+5//

static const int gc_DataMaxSize = 0x4000; // 16*1024 = 16KB
static const int gc_DataMaxNum = 0x40; // 64个

struct DataPack
{
	bool IsLastPack;
	UINT64 datasize;
	char data[gc_DataMaxSize];//16KB
};
struct ProcData
{
	HWND handle;
	DataPack pack[gc_DataMaxNum];// 64个
};


//窗口类
class ProcessAcceptObject:public CWnd
{
public:
	ProcessAcceptObject(UnicodeString chanName, HWND handle, ProcessChanNotify *chan);
	~ProcessAcceptObject();
	afx_msg LRESULT OnProcInteger(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnProcString(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnProcStream(WPARAM wParam, LPARAM lParam);
//	afx_msg LRESULT OnProcLogger(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnProcCommand(WPARAM wParam, LPARAM lParam);
	DECLARE_MESSAGE_MAP()
private:
	ProcessChanNotify *c_chan;
	ShareMemoryStream* c_Share;
	ProcData *c_data;
};

BEGIN_MESSAGE_MAP(ProcessAcceptObject, CWnd)
	ON_MESSAGE(WM_PROCESS_INTEGER, OnProcInteger)
	ON_MESSAGE(WM_PROCESS_STRING, OnProcString)
	ON_MESSAGE(WM_PROCESS_STREAM, OnProcStream)
//	ON_MESSAGE(WM_PROCESS_LOGGER, OnProcLogger)
	ON_MESSAGE(WM_PROCESS_COMMAND, OnProcCommand)
END_MESSAGE_MAP()

ProcessAcceptObject::ProcessAcceptObject(UnicodeString chanName, HWND handle, ProcessChanNotify *chan):CWnd()
{
	if (chanName.IsEmpty())
		Painc("chanName 不能为空");
	if (chan == nullptr)
		Painc("ProcessChanNotify 不能为空");
	c_chan = chan;
	if (handle == nullptr) //如果没有指定窗口句柄，就使用当前应用程序的主窗口，作为父窗口
	{
		CWnd *Parent = AfxGetApp()->m_pMainWnd;
		Create(NULL, NULL, WS_CHILD, RECT{ 0, 0, 0, 0 }, Parent, 7777);
	}
	else
	{
		CWnd* parent = CWnd::FromHandle(handle);
		Create(nullptr, nullptr, WS_CHILD, RECT{ 0,0,0,0 }, parent, 7777);
	}
	//共享内存
	try
	{
		c_Share = new ShareMemoryStream(chanName.ToUpper(), sizeof(ProcData));
	}
	catch (...)
	{
		c_Share = new ShareMemoryStream(chanName.ToUpper());
	}
	c_data = (ProcData*)c_Share->Memory();
	memset(c_data, 0, sizeof(ProcData));
	c_data->handle = m_hWnd;
}

ProcessAcceptObject::~ProcessAcceptObject()
{
	c_data->handle = nullptr; //设置为空，让发送端不要再发送数据过来
	delete c_Share;
}

LRESULT ProcessAcceptObject::OnProcInteger(WPARAM wParam, LPARAM lParam)
{
	c_chan->OnProcessInteger(int(wParam), int(lParam));
	return 0;
}

LRESULT ProcessAcceptObject::OnProcString(WPARAM wParam, LPARAM lParam)
{
	//读取共享内存中的数据
	UnicodeString ustr(c_data->pack[lParam].datasize / 2,L'0');
	memcpy((char*)ustr.c_str(), c_data->pack[lParam].data, c_data->pack[lParam].datasize);
	c_data->pack[lParam].datasize = 0;
	c_chan->OnProcessString(int(wParam), ustr);
	return 0;
}

class Cache
{
public:
	Cache() {};
	~Cache() {};
	MemoryStream c_ms;
	bool IsLastPack;
	void WriteData(DataPack &dataPack)
	{
		IsLastPack = dataPack.IsLastPack;
		c_ms.Write(dataPack.data, dataPack.datasize);
	};
};
typedef Cache* pcacheData;

//负责缓存数据
class CacheMemory
{
public:
	pcacheData Get(int procId);
	void Del(int procId);
	static CacheMemory *Instance();
private:
	CriticalSection cs;
	CacheMemory();
	~CacheMemory();
	std::map<int, pcacheData> c_map;
	static CacheMemory CachM;
};

CacheMemory CacheMemory::CachM;
pcacheData CacheMemory::Get(int procId)
{
	cs.Locked();
	pcacheData temp = nullptr;
	std::map<int, pcacheData>::iterator it = c_map.find(procId);
	if (it != c_map.end())
	{
		temp =  it->second;
	}
	else
	{
		try
		{
			temp = new Cache();
			temp->IsLastPack = false;
			c_map.insert(make_pair(procId, temp));
		}
		catch (...)
		{

		}
	}
	cs.UnLocked();
	return temp;
}

void CacheMemory::Del(int procId)
{
	cs.Locked();
	try
	{
		map<int, pcacheData>::iterator it = c_map.find(procId);
		if (it != c_map.end())
		{
			delete it->second;
			c_map.erase(it);
		}
	}
	catch (...)
	{
	}
	cs.UnLocked();
}

CacheMemory *CacheMemory::Instance()
{
	return &CachM;
}

CacheMemory::CacheMemory()
{
}

CacheMemory::~CacheMemory()
{
	cs.Locked();
	map<int, pcacheData>::iterator it = c_map.begin();
	if (it != c_map.end())
	{
		delete it->second;
		it++;
	}
	c_map.clear();
	cs.UnLocked();
}

LRESULT ProcessAcceptObject::OnProcStream(WPARAM wParam, LPARAM lParam)
{
	
	CacheMemory::Instance()->Get(wParam)->WriteData(c_data->pack[lParam]);
	if (CacheMemory::Instance()->Get(wParam)->IsLastPack == true)
	{
		c_data->pack[lParam].datasize = 0;
		c_data->pack[lParam].IsLastPack = false;
		CacheMemory::Instance()->Get(wParam)->c_ms.SetCursor(0);
		c_chan->OnProcessStream(int(wParam), CacheMemory::Instance()->Get(wParam)->c_ms);
		CacheMemory::Instance()->Del(wParam);
	}
	
	return 0;
}

LRESULT ProcessAcceptObject::OnProcCommand(WPARAM wParam, LPARAM lParam)
{
	CacheMemory::Instance()->Get(wParam)->WriteData(c_data->pack[lParam]);
	if (CacheMemory::Instance()->Get(wParam)->IsLastPack == true)
	{
		c_data->pack[lParam].datasize = 0;
		c_data->pack[lParam].IsLastPack = false;
		CacheMemory::Instance()->Get(wParam)->c_ms.SetCursor(0);
		c_chan->OnProcessCommand(int(wParam), CacheMemory::Instance()->Get(wParam)->c_ms);
		CacheMemory::Instance()->Del(wParam);
	}

	return 0;
}

///////接收端对外包装的类/////
ProcessAccept::ProcessAccept(UnicodeString chanName, HWND handle, ProcessChanNotify *chan)
{
	c_Object = new ProcessAcceptObject(chanName, handle, chan);
}


ProcessAccept::~ProcessAccept()
{
	delete (ProcessAcceptObject*)c_Object;
}




























/////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////// ProcessSendObject 发送端 ////////////////////////////////////

class ProcessSendObject
{
public:
	ProcessSendObject(UnicodeString chanName);
	~ProcessSendObject();
	void SendInteger(int integer);
	void SendString(UnicodeString ustr);
	void SendStream(MemoryStream& stream);
	void SendCommand(int command, vector<XVariant>&data);
private:
	ShareMemoryStream *c_ShareMemory;
	ProcData* c_ProcData;
};

ProcessSendObject::ProcessSendObject(UnicodeString chanName)
{
	//打开共享内存
	try
	{
		c_ShareMemory = new ShareMemoryStream(chanName.ToUpper());
	}
	catch (...)
	{
		c_ShareMemory = new ShareMemoryStream(chanName.ToUpper(), sizeof(ProcData));
	}
	c_ProcData = (ProcData*)(c_ShareMemory->Memory());
}

ProcessSendObject::~ProcessSendObject()
{
	delete c_ShareMemory;
}

void ProcessSendObject::SendInteger(int integer)
{
	if (c_ProcData->handle != nullptr)
	{
		PostMessage(c_ProcData->handle, WM_PROCESS_INTEGER, GetCurrentProcessId(), integer);
	}
}

void ProcessSendObject::SendString(UnicodeString ustr)
{
	if (c_ProcData->handle != nullptr)
	{
		for (int i = 0; i < 3;i++)
		{
			for (int j = 0; j < gc_DataMaxNum;j++)
			{
				if (c_ProcData->pack[j].datasize == 0) //未被使用
				{
					//写入数据
					c_ProcData->pack[j].datasize = ustr.length() * 2;
					memcpy(c_ProcData->pack[j].data, (char*)ustr.c_str(), ustr.length() * 2);
					PostMessage(c_ProcData->handle, WM_PROCESS_STRING, GetCurrentProcessId(), j);
					return;
				}
			}
		}
	}
}

void ProcessSendObject::SendStream(MemoryStream& stream)
{
	if (c_ProcData->handle != nullptr)
	{
		for (int i = 0; i < 3;i++)
		{
			for (int j = 0; j < gc_DataMaxNum;j++)
			{
				if (c_ProcData->pack[j].datasize == 0)
				{
					stream.SetCursor(0);
					size_t size = stream.GetSize();
					while (1)
					{
						if (size > gc_DataMaxSize)
						{
							c_ProcData->pack[j].datasize = gc_DataMaxSize;
							c_ProcData->pack[j].IsLastPack = false;
							memcpy(c_ProcData->pack[j].data, stream.Memory(), gc_DataMaxSize);
							SendMessage(c_ProcData->handle, WM_PROCESS_STREAM, GetCurrentProcessId(), j);
						}
						else
						{
							c_ProcData->pack[j].datasize = size;
							c_ProcData->pack[j].IsLastPack = true;
							memcpy(c_ProcData->pack[j].data, stream.Memory(), size);
							PostMessage(c_ProcData->handle, WM_PROCESS_STREAM, GetCurrentProcessId(), j);
							return;
						}
						size -= gc_DataMaxSize;
					}
				}
			}
		}
	}
}

void ProcessSendObject::SendCommand(int command, vector<XVariant>&data)
{
	if (c_ProcData->handle != nullptr)
	{
		for (int i = 0; i <= 3; i++)
		{
			for (int j = 0; j < gc_DataMaxNum; j++)
			{
				if (c_ProcData->pack[j].datasize == 0)
				{
					MemoryStream stream;
					stream << command;
					XVariant::VrArrayToStream(data, stream);
					stream.SetCursor(0);
					size_t size = stream.GetSize();
					while (1)
					{
						if (size > gc_DataMaxSize)
						{
							c_ProcData->pack[j].datasize = gc_DataMaxSize;
							c_ProcData->pack[j].IsLastPack = false;
							memcpy(c_ProcData->pack[j].data, stream.Memory(), gc_DataMaxSize);
							SendMessage(c_ProcData->handle, WM_PROCESS_COMMAND, GetCurrentProcessId(), j);

						}
						else
						{
							c_ProcData->pack[j].datasize = size;
							c_ProcData->pack[j].IsLastPack = true;
							memcpy(c_ProcData->pack[j].data, stream.Memory(), size);
							PostMessage(c_ProcData->handle, WM_PROCESS_COMMAND, GetCurrentProcessId(), j);
							return;
						}
						size -= gc_DataMaxSize;
					}
				}
			}
		}
	}
}

////////发送端对外包装的类
ProcessSend::ProcessSend(UnicodeString chanName)
{
	c_SendObject = new ProcessSendObject(chanName);
}

ProcessSend::~ProcessSend()
{
	delete c_SendObject;
}

void ProcessSend::SendStream(MemoryStream &stream)
{
	((ProcessSendObject*)c_SendObject)->SendStream(stream);
}

void ProcessSend::SendInteger(int integer)
{
	((ProcessSendObject*)c_SendObject)->SendInteger(integer);
}

void ProcessSend::SendCommand(int command, vector<XVariant>&data)
{
	((ProcessSendObject*)c_SendObject)->SendCommand(command,data);
}

void ProcessSend::SendString(const UnicodeString& ustr)
{
	((ProcessSendObject*)c_SendObject)->SendString(ustr);
}
