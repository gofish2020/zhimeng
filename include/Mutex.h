/*
author:nash
date:2022/1/6
desc:¿ç½ø³Ì»¥³âËø

https://docs.microsoft.com/en-us/windows/win32/api/synchapi/nf-synchapi-createmutexa

https://blog.csdn.net/lwx309025167/article/details/78252015?spm=1001.2101.3001.6650.1&utm_medium=distribute.pc_relevant.none-task-blog-2%7Edefault%7ECTRLIST%7Edefault-1.no_search_link&depth_1-utm_source=distribute.pc_relevant.none-task-blog-2%7Edefault%7ECTRLIST%7Edefault-1.no_search_link&utm_relevant_index=2
*/

#pragma once
#include "..\include\XString.h"

class AFX_EXT_CLASS Mutex
{
public:
	Mutex();
	virtual ~Mutex();
	bool Open(UnicodeString name,bool );
	bool Wait();
	bool Release();
	void Close();
private:
	HANDLE c_mutex;
};