#pragma once
/*
author:nash
date:2022/2/24
desc:���ݴ洢Э�� Date Store Pro

*/

#include "..\include\BaseSocket.h"
#include "..\include\Logger.h"
#include "..\include\Thread.h"
#include "..\include\MsgHeader.h"
#include "..\include\XVariant.h"
class AFX_EXT_CLASS LNetServerNotifyEvent
{
public:
	//!���ͻ������������������ʱ����
	virtual void OnConnect(SelectSocket *Handle) {};
	//!���ͻ�����������������ݽ���ʱ����
	virtual void OnExecute(SelectSocket *Handle) = 0;
	//!���ͻ�����������Ͽ�����ʱ����
	virtual void OnDisconnect(SelectSocket *Handle) {};
};

class AFX_EXT_CLASS DSPServer : public ThreadNotifition , public LNetServerNotifyEvent
{
public:
	DSPServer(const SockSetting& s);
	~DSPServer();
	bool Start();//��������
	void Close();
	bool Running();

protected:
	void OnTerminate(Thread *thread);

	//!���ͻ������������������ʱ����
	virtual void OnConnect(SelectSocket *Handle);
	//!���ͻ�����������������ݽ���ʱ����
	virtual void OnExecute(SelectSocket *Handle);
	//!���ͻ�����������Ͽ�����ʱ����
	virtual void OnDisconnect(SelectSocket *Handle);
private:
	SockSetting c_sockSetting;
	bool c_running;
	Thread *c_thread;
};


//һ������socket�ģ������Զ����Э�飩���ݴ���ͨ�����շ�����
class AFX_EXT_CLASS ServerChannle 
{
public:
	ServerChannle(SelectSocket *handle);
	~ServerChannle();

	void OnExecute();
protected:
	void ReadHeader(unsigned char &type, unsigned char &code, unsigned char &error);
	void SendHeader(unsigned char type, unsigned char code, unsigned char error = 0);

	void ReadParams(int &Command,char& Accessory,std::vector<XVariant>&value);
	void SendParams();

private:

	void DoGetFile();
	void DoPutFile();
	void Upload();
	SelectSocket *c_socket;
	MemoryStream mstream;

};



