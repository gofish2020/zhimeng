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



SelectSocket::SelectSocket():c_socket(INVALID_SOCKET)
{
	INITSOCK();
}

SelectSocket::SelectSocket(SockSetting &s, SOCKET sock)
{
	c_socksetting = s;
	c_socket = sock;
}

SelectSocket::~SelectSocket()
{
}

void SelectSocket::Open(SockSetting& sockSetting)
{
	c_socksetting = sockSetting;
	c_socksetting.IpAddr = Dns(c_socksetting.IpAddr);
	//创建未绑定的socket
	Create();
	sockaddr_in serAddr;
	serAddr.sin_family = AF_INET;
	serAddr.sin_addr.s_addr = inet_addr(string(c_socksetting.IpAddr).c_str());
	serAddr.sin_port = htons(c_socksetting.Port);
	//将socket绑定到Ip地址上
	if (::bind(c_socket, (PSOCKADDR)&serAddr, sizeof(serAddr)) == SOCKET_ERROR)
	{
		UnicodeString msg;
		msg.uprintf_s(L"bind() occurs error: %s", SysErrorMessage(WSAGetLastError()));
		Close();
		Painc(msg);
	}
	if (c_socksetting.RecvBufferSize >0)
	{
		//设置接收缓冲区大小
		if (setsockopt(c_socket, SOL_SOCKET, SO_RCVBUF, (char*)& c_socksetting.RecvBufferSize, sizeof(c_socksetting.RecvBufferSize)) == SOCKET_ERROR)
		{
			//错误处理
			UnicodeString msg;
			msg.uprintf_s(L"setsockopt() occurs error: %s", SysErrorMessage(WSAGetLastError()).c_str());
			LOGERROR("SelectSocket::Open", msg);
		}
	}
	
	if (c_socksetting.SendBufferSize > 0)
	{
		//设置发送缓冲区大小
		if (setsockopt(c_socket, SOL_SOCKET, SO_SNDBUF, (char*)&c_socksetting.SendBufferSize, sizeof(c_socksetting.SendBufferSize)) == SOCKET_ERROR)
		{
			//错误处理
			UnicodeString msg;
			msg.uprintf_s(L"setsockopt() occurs error: %s", SysErrorMessage(WSAGetLastError()).c_str());
			LOGERROR("SelectSocket::Open", msg);
		}
	}
	//监听端口
	if (listen(c_socket, c_socksetting.ListenQueue) == SOCKET_ERROR)
	{
		UnicodeString msg;
		msg.uprintf_s(L"listen() occurs error: %s", SysErrorMessage(WSAGetLastError()));
		Close();
		Painc(msg);
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
	c_socket = INVALID_SOCKET;
}

SelectSocket* SelectSocket::Accept()
{
	sockaddr_in addr;
	int addrlen = sizeof(sockaddr_in);
	SOCKET clientSock = ::accept(c_socket, (sockaddr*)&addr, &addrlen);
	if (clientSock == INVALID_SOCKET)
	{
		UnicodeString msg;
		msg.uprintf_s(L"accept() occurs error %s", SysErrorMessage(WSAGetLastError()).c_str());
		LOGERROR("SelectSocket::Accept()", msg);
		return NULL;
	}
	SockSetting s = c_socksetting;
	s.IpAddr = inet_ntoa(addr.sin_addr);
	s.Port = ntohs(addr.sin_port);
	return new SelectSocket(s,clientSock);
}

SOCKET SelectSocket::Handle()
{
	return c_socket;
}

UnicodeString SelectSocket::GetHostName()
{
	INITSOCK();
	char cHostName[256];
	memset(cHostName, 0, 256);
	if (gethostname(cHostName, 255) == SOCKET_ERROR)
	{
		//错误处理
		UnicodeString msg;
		msg.uprintf_s(L"gethostname() occurs error %s", SysErrorMessage(WSAGetLastError()).c_str());
		LOGERROR("SelectSocket::GetHostName()", msg);
	}
	return UnicodeString(cHostName);
}

StringList SelectSocket::GetHostByName(const UnicodeString& name)
{
	StringList sRes;
	hostent *phe = gethostbyname(string(name).c_str());
	if (phe == nullptr)
	{
		//错误处理
		UnicodeString msg;
		msg.uprintf_s(L"gethostbyname() occurs error %s", SysErrorMessage(WSAGetLastError()).c_str());
		LOGERROR("SelectSocket::GetHostByName()", msg);
	}
	else
	{
		struct in_addr addr;
		if (phe->h_addrtype == AF_INET)
		{
			int i = 0;
			while (phe->h_addr_list[i] != 0) 
			{
				addr.s_addr = *(u_long *)phe->h_addr_list[i++];
				UnicodeString ip = inet_ntoa(addr);
				if (!sRes.IsExist(ip))
					sRes.Add(ip);
			}
		}
	}
	return sRes;
}

StringList SelectSocket::GetLocalAddr()
{
	return GetHostByName(GetHostName());
}

bool SelectSocket::IsLocalIPAddr(const UnicodeString& ip)
{
	if (ip == L"127.0.0.1")
	{
		return true;
	}
	UnicodeString cHostName = SelectSocket::GetHostName();
	StringList LocalIPList = SelectSocket::GetHostByName(cHostName);
	return LocalIPList.IsExist(ip);
}

UnicodeString SelectSocket::Dns(const UnicodeString& domain)
{
	PHOSTENT phe = gethostbyname(string(domain).c_str()); //如果domain就是ip4地址，这个返回的是ip4地址的二进制形式
	if (phe == NULL)
	{
		return L"";
	}
	else
	{
		struct in_addr addr;
		addr.s_addr = *(u_long *)phe->h_addr_list[0];
		UnicodeString IPAddr = inet_ntoa(addr);
		return IPAddr;
	}
}

void SelectSocket::Create() 
{
	if (c_socket != INVALID_SOCKET)
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

void SelectSocket::SendTo(void *buf, size_t len)
{
	fd_set fd;
	FD_ZERO(&fd);
	FD_SET(c_socket, &fd);
	timeval time;
	time.tv_sec = 1;
	time.tv_usec = 0;
	int nResult = ::select(c_socket + 1, NULL, &fd, NULL, &time);
	if (nResult == SOCKET_ERROR)
	{
		UnicodeString msg;
		msg.uprintf_s(L"SendTo select() occurs error %s", SysErrorMessage(WSAGetLastError()).c_str());
		Painc(msg);
	}
	else if (nResult == 0)//timeout
	{

	}
}
