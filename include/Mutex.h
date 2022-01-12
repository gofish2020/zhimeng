/*
coder:nash
date:2022/1/6
desc:跨进程互斥锁

https://docs.microsoft.com/en-us/windows/win32/api/synchapi/nf-synchapi-createmutexa

*/

#pragma once
#include "..\include\XString.h"

class AFX_EXT_CLASS Mutex
{
public:
	Mutex();
	virtual ~Mutex();
	int Create(UnicodeString name,bool isClosed = true); //0 失败 1 成功 2 已存在
	bool Wait(); //拥有mutex
	int Release();//释放拥有权
	int Close();
private:
	HANDLE c_mutex;
	bool c_isClose;
};