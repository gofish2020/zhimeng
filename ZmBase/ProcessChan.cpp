#include "stdafx.h"
#include "..\include\ProcessChan.h"
#include "..\include\utils.h"


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
	c_chan->OnProcessString(int(wParam), ustr);
	return 0;
}

LRESULT ProcessAcceptObject::OnProcStream(WPARAM wParam, LPARAM lParam)
{
	MemoryStream ms;

	c_chan->OnProcessStream(int(wParam), ms);
	return 0;
}

LRESULT ProcessAcceptObject::OnProcCommand(WPARAM wParam, LPARAM lParam)
{
	vector<XVariant>value;
	value.push_back(123);
	value.push_back(L"123");
	c_chan->OnProcessCommand(int(wParam), value);
	return 0;
}

///////接收端对外包装的类
ProcessAccept::ProcessAccept(UnicodeString chanName, HWND handle, ProcessChanNotify *chan)
{
	c_Object = new ProcessAcceptObject(chanName, handle, chan);
}


ProcessAccept::~ProcessAccept()
{
	delete (ProcessAcceptObject*)c_Object;
}


//////////////////////////// ProcessSendObject 发送端 ////////////////////////////////////

class ProcessSendObject
{
public:
	ProcessSendObject(UnicodeString chanName);
	~ProcessSendObject();
	void SendInteger(int integer);
	void SendString(UnicodeString ustr);
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
			for (int j = 0; j < gc_DataMaxSize;j++)
			{
				if (c_ProcData->pack[j].datasize == 0) //未被使用
				{
					//写入数据
					c_ProcData->pack[j].datasize = ustr.length() * 2;
					memcpy(c_ProcData->pack[j].data, (char*)ustr.c_str(), ustr.length() * 2);
					PostMessage(c_ProcData->handle, WM_PROCESS_STRING, GetCurrentProcessId(), j);
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

}

void ProcessSend::SendInteger(int integer)
{
	((ProcessSendObject*)c_SendObject)->SendInteger(integer);
}

void ProcessSend::SendString(const UnicodeString& ustr)
{
	((ProcessSendObject*)c_SendObject)->SendString(ustr);
}
