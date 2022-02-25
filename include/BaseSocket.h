#pragma once
#include "..\include\XString.h"
#include <winsock2.h>
#include "..\include\StringList.h"
#include "..\include\Stream.h"
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

//!Select Socket 模型 https://blog.csdn.net/guo8113/article/details/26448011
class AFX_EXT_CLASS SelectSocket
{
public:
	SelectSocket(bool needBuf = false);
	virtual ~SelectSocket();
	void Open(SockSetting& sockSetting);
	void Close();

	SelectSocket* Accept(); //返回客户端的一个连接
	SOCKET Handle();
	bool IsNull();

	//通用的函数
	static UnicodeString GetHostName();
	static StringList GetHostByName(const UnicodeString& name);
	static StringList GetLocalAddr();
	static bool IsLocalIPAddr(const UnicodeString& ip);
	static UnicodeString Dns(const UnicodeString& domain);

	//发送数据 
	void SendTo(void *buf, size_t len);
	void SendString(const string& wstr);
	void SendInteger(int& integer);
	void SendChar(char c);
	void SendStream(Stream& stream);
	
	//接收数据
	void RecvFrom(void* buf, int len);
	char RecvChar();
	string RecvString(size_t len);
	int RecvInteger();
	void RecvStream(Stream& stream, int len = 0);

private:
	//内部调用，生成socket
	SelectSocket(SockSetting &s, SOCKET sock);
	//!创建(未绑定地址的)套接字：（服务器端和客户端）
	void Create(); 

	//接收数据
	void RecvByLen(size_t len);
	void sendPacket(void *buf, size_t len); //send
	void recvPacket(void *buf, size_t& len);//recv
private:
	SOCKET c_socket;
	SockSetting c_socksetting;

	QueueStream *qstream;
};


