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
	c_clientSocket = clientSocket;
	c_event = event;
	if (c_event != nullptr)
	{
		c_event->OnConnect(c_clientSocket);
	}
}

HandleThread::~HandleThread()
{
	if (c_event != nullptr)
	{
		c_event->OnDisconnect(c_clientSocket);
	}
	if (c_clientSocket != nullptr)
		delete c_clientSocket;
	c_clientSocket = nullptr;
}

void HandleThread::OnExecute()
{
	while (!IsTerminate())
	{
		try
		{
			if (c_event != nullptr && c_clientSocket != nullptr)
			{
				c_event->OnExecute(c_clientSocket);
			}
		}
		catch (const std::exception&)
		{
			Terminate();
		}
		catch (...)
		{
			Terminate();
		}
	}
}

///////////////////////////////////////////////
// ListenThread 监听线程 
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
			SelectSocket *clientSocket = c_socket->Accept(); //监听客户端的连接
			IsAccepting = false;
			if (clientSocket != nullptr)
			{
				c_Section.Locked();
				try
				{
					//接收或发送，数据的线程
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
			LOGERROR(L"ListenThread::OnExecute()", L"发生未知的异常错误");
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
			childThreads[i]->RegisterNotifition(nullptr); //不要再通知了，回调对方了
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
		//启动监听线程
		c_thread = new ListenThread(c_sockSetting,c_event);
		c_thread->RegisterNotifition(this);
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
		LOGERROR(L"DSPServer::Start", L"发生未知的异常错误");
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
			delete c_thread; //避免重复释放对象
		c_thread = nullptr;
	}
	c_running = false;
}

bool DSPServer::Running()
{
	return c_running;
}

void DSPServer::RegisterNetServerNotifyEvent(LNetServerNotifyEvent *event)
{
	c_event = event;
}

void DSPServer::OnTerminate(Thread *thread)
{
	Close();
}
