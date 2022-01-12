/*
coder:nash
date:2022/1/6
desc:����̻�����

https://docs.microsoft.com/en-us/windows/win32/api/synchapi/nf-synchapi-createmutexa

*/

#pragma once
#include "..\include\XString.h"

class AFX_EXT_CLASS Mutex
{
public:
	Mutex();
	virtual ~Mutex();
	int Create(UnicodeString name,bool isClosed = true); //0 ʧ�� 1 �ɹ� 2 �Ѵ���
	bool Wait(); //ӵ��mutex
	int Release();//�ͷ�ӵ��Ȩ
	int Close();
private:
	HANDLE c_mutex;
	bool c_isClose;
};