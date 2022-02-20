#pragma once
#include "..\include\XString.h"
#include <winsock2.h>


extern AFX_EXT_CLASS void  InitSocket();
#define INITSOCK() InitSocket()

//Socket 配置
struct AFX_EXT_CLASS SockSetting
{
	UnicodeString IpAddr;
	int Port;//!端口号
	int ReadTimeOut;//!读延迟时间(单位微秒)默认10秒,如果值为-1按系统配置
	int WriteTimeOut;//!写延迟时间(单位微秒)默认10秒,如果值为-1按系统配置
	int RecvBufferSize;//!套接字接收缓冲区长度，默认32768字节
	int SendBufferSize;//!套接字发送缓冲区长度，默认32768字节
	int ListenQueue;//!连接队列，设定服务端同时可以连接几个客户端，默认15
	SockSetting();
	SockSetting& operator=(const SockSetting& sock);
};

//!Select Socket 模型
class AFX_EXT_CLASS SelectSocket
{
public:
	SelectSocket();
	virtual ~SelectSocket();
	void Open(SockSetting& sockSetting);
	void Close();
	SelectSocket* Accept();

	SOCKET Handle();
private:
	SOCKET c_socket;
	SockSetting c_socksetting;
};


