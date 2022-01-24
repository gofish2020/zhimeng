#include "stdafx.h"
#include "..\include\ProcessChan.h"
#include "..\include\utils.h"


#define WM_PROCESS_INTEGER      WM_USER+1//��������
#define WM_PROCESS_STRING		WM_USER+2//�����ִ�
#define WM_PROCESS_STREAM		WM_USER+3//����������
#define WM_PROCESS_LOGGER		WM_USER+4//������־
#define WM_PROCESS_COMMAND		WM_USER+5//

static const int gc_DataMaxSize = 0x4000; // 16*1024 = 16KB
static const int gc_DataMaxNum = 0x40; // 64��

struct DataPack
{
	bool IsLastPack;
	UINT64 datasize;
	char data[gc_DataMaxSize];//16KB
};
struct ProcData
{
	HWND handle;
	DataPack pack[gc_DataMaxNum];// 64��
};


//������
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
		Painc("chanName ����Ϊ��");
	if (chan == nullptr)
		Painc("ProcessChanNotify ����Ϊ��");
	c_chan = chan;
	if (handle == nullptr) //���û��ָ�����ھ������ʹ�õ�ǰӦ�ó���������ڣ���Ϊ������
	{
		CWnd *Parent = AfxGetApp()->m_pMainWnd;
		Create(NULL, NULL, WS_CHILD, RECT{ 0, 0, 0, 0 }, Parent, 7777);
	}
	else
	{
		CWnd* parent = CWnd::FromHandle(handle);
		Create(nullptr, nullptr, WS_CHILD, RECT{ 0,0,0,0 }, parent, 7777);
	}
	//�����ڴ�
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
	c_data->handle = nullptr; //����Ϊ�գ��÷��Ͷ˲�Ҫ�ٷ������ݹ���
	delete c_Share;
}

LRESULT ProcessAcceptObject::OnProcInteger(WPARAM wParam, LPARAM lParam)
{
	c_chan->OnProcessInteger(int(wParam), int(lParam));

	return 0;
}

LRESULT ProcessAcceptObject::OnProcString(WPARAM wParam, LPARAM lParam)
{
	//��ȡ�����ڴ��е�����
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

///////���ն˶����װ����
ProcessAccept::ProcessAccept(UnicodeString chanName, HWND handle, ProcessChanNotify *chan)
{
	c_Object = new ProcessAcceptObject(chanName, handle, chan);
}


ProcessAccept::~ProcessAccept()
{
	delete (ProcessAcceptObject*)c_Object;
}


//////////////////////////// ProcessSendObject ���Ͷ� ////////////////////////////////////

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
	//�򿪹����ڴ�
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
				if (c_ProcData->pack[j].datasize == 0) //δ��ʹ��
				{
					//д������
					c_ProcData->pack[j].datasize = ustr.length() * 2;
					memcpy(c_ProcData->pack[j].data, (char*)ustr.c_str(), ustr.length() * 2);
					PostMessage(c_ProcData->handle, WM_PROCESS_STRING, GetCurrentProcessId(), j);
				}
			}
		}
	}
}

////////���Ͷ˶����װ����
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
