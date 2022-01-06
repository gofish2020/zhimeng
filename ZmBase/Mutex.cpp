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
	UnLocked();
}

bool Mutex::Locked(UnicodeString name)
{
	try
	{
		c_mutex = CreateMutex(nullptr, false, name.c_str());
		if (c_mutex == nullptr)
		{
			LOGERROR(L"Mutex::Locked",GetLastErrorStr("CreateMutex"));
			return false;
		}
		else
		{
			if ( GetLastError() == ERROR_ALREADY_EXISTS )
			{
				return false;
			}
		}
		return true;
	}
	catch (const std::exception& e)
	{
		LOGEXCEPTION(e);
	}
	catch (...)
	{
		LOGERROR("Mutex::Locked", "Î´ÖªµÄÒì³£´íÎó");
	}
	return false;
}

void Mutex::UnLocked()
{
	if (c_mutex != nullptr)
	{
		CloseHandle(c_mutex);
		c_mutex = nullptr;
	}
}
