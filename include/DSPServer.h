#pragma once
/*
author:nash
date:2022/2/24
desc:数据存储协议 Date Store Pro

*/

#include "..\include\BaseSocket.h"
#include "..\include\Logger.h"
#include "..\include\Thread.h"



class LNetServerNotifyEvent
{
public:
	//!当客户端与服务器建立连接时发出
	virtual void OnConnect(SelectSocket *Handle) {};
	//!当客户端与服务器进行数据交换时发生
	virtual void OnExecute(SelectSocket *Handle) = 0;
	//!当客户端与服务器断开连接时发生
	virtual void OnDisconnect(SelectSocket *Handle) {};
};


class AFX_EXT_CLASS DSPServer : public ThreadNotifition
{
public:
	DSPServer(const SockSetting& s);
	~DSPServer();
	
	bool Start();//启动服务
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



