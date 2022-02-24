#pragma once
/*
author:nash
date:2022/2/24
desc:数据存储协议 Date Store Pro

*/

#include "..\include\BaseSocket.h"
#include "..\include\Logger.h"
#include "..\include\Thread.h"
class AFX_EXT_CLASS DSPServer : public ThreadNotifition
{
public:
	DSPServer(const SockSetting& s);
	~DSPServer();
	
	bool Start();//启动服务
	void Close();
	bool Running();
protected:
	void OnTerminate(Thread *thread);
private:
	SockSetting c_sockSetting;
	SelectSocket *c_socket;
	bool c_running;
	Thread *c_thread;
};

