#pragma once
/*
coder:nash
date:2022/1/21
desc:�����ͨ�ţ�����������֮�䷢�����ݰ�),���ڹ����ڴ��wins��ϵͳ��Ϣ
*/

#include "..\include\XVariant.h"
#include "..\include\Stream.h"


class AFX_EXT_CLASS ProcessChanNotify
{
public:
	virtual void OnProcessInteger(int procId, int integer) {};
	virtual void OnProcessString(int procId, UnicodeString ustr) {};
	virtual void OnProcessStream(int procId, MemoryStream &stream) {};
	virtual void OnProcessCommand(int procId,int command, vector<XVariant>& value) {};
};



//ProcessAccept ��Ϣ���ն�
class AFX_EXT_CLASS ProcessAccept
{
public:
	ProcessAccept(UnicodeString chanName, HWND handle, ProcessChanNotify *Chan);
	virtual ~ProcessAccept();
private:
	void *c_Object;
};



//ProcessSend ��Ϣ���Ͷ�
class AFX_EXT_CLASS ProcessSend
{
public:
	ProcessSend(UnicodeString chanName);
	virtual ~ProcessSend();
	void SendStream(MemoryStream &stream);
	void SendInteger(int integer) ;
	void SendCommand(int command, vector<XVariant>&data);
	void SendString(const UnicodeString& ustr) ;
private:
	void *c_SendObject;
};
