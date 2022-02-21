#pragma once
#include "..\include\XString.h"
#include <winsock2.h>
#include "..\include\StringList.h"

extern AFX_EXT_CLASS void  InitSocket();
#define INITSOCK() InitSocket()

//Socket ����
struct AFX_EXT_CLASS SockSetting
{
	UnicodeString IpAddr;
	int Port;//!�˿ں�
	int ReadTimeOut;//!���ӳ�ʱ��(��λ΢��)Ĭ��10��,���ֵΪ-1��ϵͳ����
	int WriteTimeOut;//!д�ӳ�ʱ��(��λ΢��)Ĭ��10��,���ֵΪ-1��ϵͳ����
	int RecvBufferSize;//!�׽��ֽ��ջ��������ȣ�Ĭ��32768�ֽ�
	int SendBufferSize;//!�׽��ַ��ͻ��������ȣ�Ĭ��32768�ֽ�
	int ListenQueue;//!���Ӷ��У��趨�����ͬʱ�������Ӽ����ͻ��ˣ�Ĭ��15
	SockSetting();
	SockSetting& operator=(const SockSetting& sock);
};

//!Select Socket ģ�� https://blog.csdn.net/guo8113/article/details/26448011
class AFX_EXT_CLASS SelectSocket
{
public:
	SelectSocket();
	virtual ~SelectSocket();
	void Open(SockSetting& sockSetting);
	void Close();

	SelectSocket* Accept(); //���ؿͻ��˵�һ������
	SOCKET Handle();


	static UnicodeString GetHostName();
	static StringList GetHostByName(const UnicodeString& name);
	static StringList GetLocalAddr();
	static bool IsLocalIPAddr(const UnicodeString& ip);
	static UnicodeString Dns(const UnicodeString& domain);
private:
	//
	SelectSocket(SockSetting &s, SOCKET sock);
	//!����(δ�󶨵�ַ��)�׽��֣����������˺Ϳͻ��ˣ�
	void Create(); 
	

	//��������
	void RecvFrom(void *buf, size_t len);
	//��������
	void SendTo(void *buf, size_t len);
private:
	SOCKET c_socket;
	SockSetting c_socksetting;
};


