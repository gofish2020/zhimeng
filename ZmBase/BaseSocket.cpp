#include "stdafx.h"
#include "..\include\BaseSocket.h"
#include <mutex>
#include "..\include\utils.h"


SockSetting::SockSetting()
{
	IpAddr = L"";
	Port = 0;
	ReadTimeOut = 10000;
	WriteTimeOut = 10000;
	RecvBufferSize = 65535;
	SendBufferSize = 65535;
	ListenQueue = 15;
}

SockSetting& SockSetting::operator=(const SockSetting& sock)
{
	if (this != &sock)
	{
		IpAddr = sock.IpAddr;
		Port = sock.Port;
		ReadTimeOut = sock.ReadTimeOut;
		WriteTimeOut = sock.WriteTimeOut;
		RecvBufferSize = sock.RecvBufferSize;
		SendBufferSize = sock.SendBufferSize;
		ListenQueue = sock.ListenQueue;
	}
	return *this;
}

std::once_flag flag;
extern AFX_EXT_CLASS void InitSocket()
{
	std::call_once(flag, []() {

		WSADATA wsaData;
		WORD wVersionRequested = MAKEWORD(2, 2);
		int err = WSAStartup(wVersionRequested, &wsaData);
		if (err != 0)
		{
			UnicodeString msg;
			msg.uprintf_s(L"WSAStartup() failed with error %s", SysErrorMessage(WSAGetLastError()).c_str());
			Painc(msg);
		}
	});
}



SelectSocket::SelectSocket():c_socket(0)
{
	INITSOCK();
}

SelectSocket::~SelectSocket()
{
}

void SelectSocket::Open(SockSetting& sockSetting)
{
	c_socksetting = sockSetting;
}
