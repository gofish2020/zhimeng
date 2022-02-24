#include "stdafx.h"
#include "..\include\DSPServer.h"


class HandleThread : public Thread
{
public:
	HandleThread(SelectSocket *clientSocket) { c_clientSocket = clientSocket;  };
	~HandleThread() {};

	void OnExecute() {};
	UnicodeString ClassName() { return L"HandleThread"; }

private:
	SelectSocket *c_clientSocket;
};




///////////////////////////////////////////////
// AcceptThread �����߳� 
class AcceptThread : public Thread
{
public:
	AcceptThread(SelectSocket *socket);
	~AcceptThread();

	void OnExecute();
	UnicodeString ClassName() { return L"AcceptThread"; }

private:
	std::vector<Thread*>threads;
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
			SelectSocket *clientSocket = c_socket->Accept(); //�����ͻ��˵�����
			if (clientSocket != nullptr)
			{
				//���ջ��ͣ����ݵ��߳�
				Thread *temp = new HandleThread(clientSocket);
				temp->Resume();
				threads.push_back(temp);
			}
		}
		catch (const std::exception&e)
		{

		}
		catch (...)
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
		//����socket
		c_socket = new SelectSocket;
		c_socket->Open(c_sockSetting);
		//���������߳�
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
		c_thread = nullptr;
	}
	if (c_socket != nullptr)
	{
		delete c_socket;
		c_socket = nullptr;
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
