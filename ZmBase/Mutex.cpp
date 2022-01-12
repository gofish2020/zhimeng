#include "stdafx.h"
#include "..\include\Mutex.h"
#include "..\include\Logger.h"
#include "..\include\utils.h"

Mutex::Mutex()
{
	c_mutex = nullptr;
}


Mutex::~Mutex()
{
	Close();
}

int Mutex::Create(UnicodeString name, bool isClosed /*= true */)
{
	try
	{
		c_mutex = CreateMutex(nullptr, false, name.c_str());
		if (c_mutex == nullptr)
		{
			LOGERROR(L"Mutex::Open",GetLastErrorStr("CreateMutex"));
			return 0;
		}
		else
		{
			if ( GetLastError() == ERROR_ALREADY_EXISTS )
			{
				return 2;
			}
		}
		c_isClose = isClosed;
		return 1;
	}
	catch (const std::exception& e)
	{
		LOGEXCEPTION(e);
	}
	catch (...)
	{
		LOGERROR("Mutex::Open", "Î´ÖªµÄÒì³£´íÎó");
	}
	return 0;
}

bool Mutex::Wait()
{
	DWORD d = WaitForSingleObject(c_mutex, INFINITE);
	if (WAIT_OBJECT_0 == d)
	{
		return true;
	}
	return false;
}

int Mutex::Release()
{
	return ReleaseMutex(c_mutex);
}

int Mutex::Close()
{
	int ret = 1;
	if (c_mutex != nullptr && c_isClose)
	{
		ret = CloseHandle(c_mutex);
		c_mutex = nullptr;
	}
	return ret;
}
