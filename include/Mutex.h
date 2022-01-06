/*
author:nash
date:2022/1/6
desc:¿ç½ø³Ì»¥³âËø

https://docs.microsoft.com/en-us/windows/win32/api/synchapi/nf-synchapi-createmutexa
*/

#pragma once
#include "..\include\XString.h"

class AFX_EXT_CLASS Mutex
{
public:
	Mutex();
	virtual ~Mutex();
	bool Locked(UnicodeString name);
	void UnLocked();
private:
	HANDLE c_mutex;
};