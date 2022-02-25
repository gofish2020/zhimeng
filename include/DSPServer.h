#pragma once
/*
author:nash
date:2022/2/24
desc:���ݴ洢Э�� Date Store Pro

*/

#include "..\include\BaseSocket.h"
#include "..\include\Logger.h"
#include "..\include\Thread.h"



class LNetServerNotifyEvent
{
public:
	//!���ͻ������������������ʱ����
	virtual void OnConnect(SelectSocket *Handle) {};
	//!���ͻ�����������������ݽ���ʱ����
	virtual void OnExecute(SelectSocket *Handle) = 0;
	//!���ͻ�����������Ͽ�����ʱ����
	virtual void OnDisconnect(SelectSocket *Handle) {};
};


class AFX_EXT_CLASS DSPServer : public ThreadNotifition
{
public:
	DSPServer(const SockSetting& s);
	~DSPServer();
	
	bool Start();//��������
	void Close();
	bool Running();

	void RegisterNetServerNotifyEvent(LNetServerNotifyEvent *event);
protected:
	void OnTerminate(Thread *thread);
private:
	SockSetting c_sockSetting;
	bool c_running;
	Thread *c_thread;
	LNetServerNotifyEvent *c_event;
};



