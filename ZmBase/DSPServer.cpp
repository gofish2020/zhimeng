#include "stdafx.h"
#include "..\include\DSPServer.h"


class HandleThread : public Thread
{
public:
	HandleThread(SelectSocket *clientSocket, LNetServerNotifyEvent *event);
	~HandleThread();

	void OnExecute();
	UnicodeString ClassName() { return L"HandleThread"; }

private:
	SelectSocket *c_clientSocket;
	LNetServerNotifyEvent *c_event;
};

HandleThread::HandleThread(SelectSocket *clientSocket, LNetServerNotifyEvent *event)
{
	try
	{
		c_clientSocket = clientSocket;
		c_event = event;
		if (c_event != nullptr && c_clientSocket != nullptr)
		{
			c_event->OnConnect(c_clientSocket);
		}
	}
	catch (...)
	{

	}
	
}

HandleThread::~HandleThread()
{
	try
	{
		if (c_event != nullptr && c_clientSocket != nullptr)
		{
			c_event->OnDisconnect(c_clientSocket);
		}
		if (c_clientSocket != nullptr)
			delete c_clientSocket;
		c_clientSocket = nullptr;
	}
	catch (...)
	{

	}
	
}

void HandleThread::OnExecute()
{
	while (!IsTerminate())
	{
		try
		{
			if (c_event != nullptr && c_clientSocket != nullptr && !c_clientSocket->IsNull() )
			{
				c_event->OnExecute(c_clientSocket);
			}
		}
		catch (const std::exception& e)
		{
			Terminate();
		}
		catch (...)
		{
			Terminate();
		}
		if (c_clientSocket->IsNull())
		{
			break;
		}
	}
}

///////////////////////////////////////////////
// ListenThread �����߳� 
///////////////////////////////////////////////
class ListenThread : public Thread, public ThreadNotifition
{
public:
	ListenThread(SockSetting &setting,LNetServerNotifyEvent *event);
	~ListenThread();

	void OnExecute();
	UnicodeString ClassName() { return L"ListenThread"; }
	virtual void OnTerminate(Thread *thread) ;
private:
	CriticalSection c_Section;
	std::vector<Thread*>childThreads;
	SockSetting  c_setting;
	SelectSocket *c_socket;
	bool IsAccepting;
	LNetServerNotifyEvent *c_event;
};

ListenThread::ListenThread(SockSetting &setting, LNetServerNotifyEvent *event)
{
	c_socket = nullptr;
	c_setting = setting;
	c_socket = new SelectSocket;
	c_socket->Open(c_setting);
	IsAccepting = false;
	c_event = event;
}

void ListenThread::OnExecute()
{
	while (!IsTerminate())
	{
		IsAccepting = true;
		try
		{
			SelectSocket *clientSocket = c_socket->Accept(); //�����ͻ��˵�����
			IsAccepting = false;
			if (clientSocket != nullptr)
			{
				c_Section.Locked();
				try
				{
					//���ջ��ͣ����ݵ��߳�
					Thread *child = new HandleThread(clientSocket,c_event);
					child->RegisterNotifition(this);
					child->Resume();
					childThreads.push_back(child);
				}
				catch (...)
				{}
				c_Section.UnLocked();
			}
		}
		catch (const std::exception&e)
		{
			LOGEXCEPTION(e);
		}
		catch (...)
		{
			LOGERROR(L"ListenThread::OnExecute()", L"����δ֪���쳣����");
		}
	}
}

void ListenThread::OnTerminate(Thread *thread)
{
	c_Section.Locked();
	try
	{
		for (int i = 0; i < childThreads.size(); i++)
		{
			if (childThreads[i] == thread)
			{
				childThreads.erase(childThreads.begin() + i);
				break;
			}
		}
	}
	catch (...)
	{}
	c_Section.UnLocked();
}

ListenThread::~ListenThread()
{
	c_Section.Locked();
	try 
	{
		for (int i = 0; i < (int)childThreads.size(); i++)
		{
			childThreads[i]->RegisterNotifition(nullptr); //��Ҫ��֪ͨ�ˣ��ص��Է���
			childThreads[i]->Terminate();
		}
	}
	catch (...) {}
	c_Section.UnLocked();
	Terminate();
	if (IsAccepting == true)
		Suspend();
	if (c_socket != nullptr)
		delete c_socket;
	c_socket = nullptr;
}


////////////////////////////////////
DSPServer::DSPServer(const SockSetting& s)
{
	c_sockSetting = s;
	c_running = false;
	c_thread = nullptr;
}

DSPServer::~DSPServer()
{
	Close();
}

bool DSPServer::Start()
{
	if (c_running)
		return true;
	try
	{
		//���������߳�
		c_thread = new ListenThread(c_sockSetting,this); 
		c_thread->RegisterNotifition(this); //�߳�֪ͨ
		c_thread->Resume();
		c_running = true;
		return true;
	}
	catch (const std::exception& e)
	{
		LOGEXCEPTION(e);
	}
	catch (...)
	{
		LOGERROR(L"DSPServer::Start", L"����δ֪���쳣����");
	}
	Close();
	return false;
}

void DSPServer::Close()
{
	if (c_thread != nullptr)
	{
		c_thread->Terminate();
		if (!c_thread->IsActive())
			delete c_thread; //�����ظ��ͷŶ���
		c_thread = nullptr;
	}
	c_running = false;
}

bool DSPServer::Running()
{
	return c_running;
}

void DSPServer::OnTerminate(Thread *thread)
{
	Close();
}


void DSPServer::OnConnect(SelectSocket *Handle)
{
	UnicodeString ip = Handle->SocketInfo()->IpAddr;
	int port = Handle->SocketInfo()->Port;
	LOGINFO(L"ServerChannel::OnConnect", L"Connecting Ip <" + ip + L":" + UnicodeString(port) + L">");
}

void DSPServer::OnExecute(SelectSocket *Handle) //��handle �л�ȡ����
{
	ServerChannle ch(Handle);
	ch.OnExecute();
}

void DSPServer::OnDisconnect(SelectSocket *Handle)
{
	UnicodeString ip = Handle->SocketInfo()->IpAddr;
	int port = Handle->SocketInfo()->Port;
	LOGINFO(L"ServerChannel::OnDisconnect", L"Disconnect Ip <" + ip + L":" + UnicodeString(port) + L">");
}

ServerChannle::ServerChannle(SelectSocket *handle)
{
	c_socket = handle;
}

ServerChannle::~ServerChannle()
{

}

void ServerChannle::OnExecute()
{
	Upload();
	BYTE type = 0, code = 0, error = 0;
	ReadHeader(type, code, error);
	if (error != 0x00)
	{
		SendHeader(MSG_HEADER_TYPE_CONTROL, MSG_HEADER_CODE_FAIL,error);
		Upload();
		return;
	}
	switch (type)
	{
	case MSG_HEADER_TYPE_CONTROL:
	{
		switch (code)
		{
		case MSG_HEADER_CODE_TEST:
			SendHeader(MSG_HEADER_TYPE_CONTROL, MSG_HEADER_CODE_TEST_OK);
			break;
		case MSG_HEADER_CODE_DISCONNECT://�Ͽ�����
			c_socket->Close();
			break;
		case MSG_HEADER_CODE_CONNECT:
			SendHeader(MSG_HEADER_TYPE_CONTROL, MSG_HEADER_CODE_ACCEPT);
			break;
		}
		break;
	}
	case MSG_HEADER_TYPE_GET_FILE:
	{

		break;
	}
	case MSG_HEADER_TYPE_PUT_FILE:
	{
		break;
	}

	}
	Upload();
}

void ServerChannle::ReadHeader(unsigned char &type, unsigned char &code, unsigned char &error)
{
	MsgHeader mHeader;
	c_socket->RecvFrom(&mHeader, sizeof(mHeader));
	if (mHeader.Flag != MSG_HEADER_FLAG)
	{
		error = MSG_HEADER_ERROR_FLAG;
		LOGERROR(L"ServerChannle::ReadHeader()", L"��Ϣͷ��Ǵ���");
		return;
	}
	type = mHeader.Type;
	code = mHeader.MsgCode;
	if (mHeader.Version != MSG_HEADER_VERSION)
	{
		error = MSG_HEADER_ERROR_VERSION;
		LOGERROR(L"ServerChannle::ReadHeader()", L"��Ϣ�汾����");
		return;
	}
	error = mHeader.ErrorCode;
	return;
}

void ServerChannle::SendHeader(unsigned char type, unsigned char code, unsigned char error)
{
	MsgHeader mHeader;
	mHeader.MsgCode = code;
	mHeader.Type = type;
	mHeader.ErrorCode = error;
	mstream.Write(&mHeader, sizeof(mHeader));
}

void ServerChannle::ReadParams(int &Command, char& Accessory, std::vector<XVariant>&value)
{
	MsgParameter mParameter;
	c_socket->RecvFrom(&mParameter, sizeof(mParameter));
	Command = mParameter.Command;
	Accessory = mParameter.Accessory;
	int paramSize = mParameter.ParameterSize;
	if (paramSize != 0)
	{
		MemoryStream stream;
		stream.SetSize(paramSize);
		c_socket->RecvFrom(stream.Memory(), paramSize);
		XVariant::StreamToVrArray(stream, value);
	}
}

void ServerChannle::DoGetFile()
{

}

void ServerChannle::Upload()
{
	try
	{
		clock_t begin = clock();
		int size = mstream.GetSize();
		if (size != 0)
		{
			mstream.SetCursor(0);
			c_socket->SendStream(mstream);
			if (GetDebugLevel() > DebugLevel::dlGeneralDebug)
			{
				clock_t diff = clock() - begin;
				UnicodeString logs;
				logs.uprintf_s(L"���ݴ���ʱ��(����):%d,��С(�ֽ�):%s", diff, UnicodeString::Int2FormatStr(size));
				LOGINFO(L"ServerChannle::Upload()", logs);
			}
		}
		mstream.Free();
	}
	catch (const std::exception& e)
	{
		LOGEXCEPTION(e);
	}
	catch (...)
	{
		LOGERROR(L"ServerChannle::Upload()", L"����δ֪���쳣����");
	}
}
