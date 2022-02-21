#include "stdafx.h"
#include "..\include\BaseSocket.h"
#include <mutex>
#include "..\include\utils.h"
#include "..\include\Logger.h"

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
	Create();
	sockaddr_in serAddr;
	serAddr.sin_family = AF_INET;
	serAddr.sin_addr.s_addr = inet_addr(string(c_socksetting.IpAddr).c_str());
	serAddr.sin_port = htons(c_socksetting.Port);
	if (::bind(c_socket, (PSOCKADDR)&serAddr, sizeof(serAddr)) == SOCKET_ERROR)
	{
		UnicodeString msg;
		msg.uprintf_s(L"bind() occurs error: %s", SysErrorMessage(WSAGetLastError()));
		Close();
		Painc(msg);
	}
	
	if (setsockopt(c_socket, SOL_SOCKET, SO_RCVBUF,(char*)& c_socksetting.RecvBufferSize, sizeof(c_socksetting.RecvBufferSize)) == SOCKET_ERROR)
	{
		//错误处理
		UnicodeString msg;
		msg.uprintf_s(L"setsockopt() occurs error: %s", SysErrorMessage(WSAGetLastError()).c_str());
		LOGERROR("SocketHandle", msg);
		return false;
	}

}

void SelectSocket::Close()
{
	try
	{
		if (closesocket(c_socket) == SOCKET_ERROR)
		{
			UnicodeString msg;
			msg.uprintf_s(L"closesocket() occurs error:%s", SysErrorMessage(WSAGetLastError()));
			LOGERROR(L"SelectSocket::Close()", msg);
		}
	}
	catch (const std::exception &e)
	{
		LOGERROR(L"SelectSocket::Close()", e.what());
	}
	catch (...)
	{
		LOGERROR(L"SelectSocket::Close()", L"发生未知的错误");
	}
	c_socket = 0;
}

void SelectSocket::Create() 
{
	if (c_socket != 0)
	{
		return;
	}
	c_socket = socket(AF_INET, SOCK_STREAM, IPPROTO_IP); //当protocol为0时，会自动选择type类型对应的默认协议。
	if (c_socket  == INVALID_SOCKET)
	{
		UnicodeString msg;
		msg.uprintf_s(L"socket() occurs error:%s", SysErrorMessage(WSAGetLastError()));
		Painc(msg);
	}
}
