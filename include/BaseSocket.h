#pragma once
#include "..\include\XString.h"
#include <winsock2.h>


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

//!Select Socket ģ��
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


