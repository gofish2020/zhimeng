#include "stdafx.h"
#include "..\include\DSPServer.h"




class AcceptThread : public Thread
{
public:
	AcceptThread(SelectSocket *socket);
	~AcceptThread();

	void OnExecute();
	UnicodeString ClassName() { return L"AcceptThread"; }

private:
	SelectSocket * c_socket;
};

AcceptThread::AcceptThread(SelectSocket *socket)
{
	c_socket = socket;
	
}

void AcceptThread::OnExecute()
{
	while (!IsTerminate())
	{
		try
		{
			SelectSocket *clientSocket = c_socket->Accept(); //监听客户端的连接
		}
		catch (const std::exception&)
		{

		}
	}
}

AcceptThread::~AcceptThread()
{

}


////////////////////////////////////
DSPServer::DSPServer(const SockSetting& s)
{
	c_sockSetting = s;
	c_socket = nullptr;
	c_running = false;
}

DSPServer::~DSPServer()
{
}

bool DSPServer::Start()
{
	if (c_running)
		return true;
	try
	{
		//启动socket
		c_socket = new SelectSocket;
		c_socket->Open(c_sockSetting);
		//启动监听线程
		c_thread = new AcceptThread(c_socket);
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
	if (c_socket != nullptr)
	{
		delete c_socket;
	}
	c_socket = nullptr;
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
