#include "stdafx.h"
#include "..\include\Thread.h"

typedef unsigned(__stdcall *PTHREAD_START) (void *);
#define chBEGINTHREADEX(psa,cbStack,pfnStartAddr,\
	pvParam,fdwCreate,pdwThreadID)\
	((HANDLE) _beginthreadex(\
	(void *)(psa),\
	(unsigned)(cbStack),\
	(PTHREAD_START)(pfnStartAddr),\
	(void *)(pvParam),\
	(unsigned)(fdwCreate),\
	(unsigned *)(pdwThreadID)))

Thread::Thread()
{
	c_handle = nullptr;
	isTerminate = false;
	//创建线程默认
	if ((c_handle = chBEGINTHREADEX(NULL, 0, ThreadProc, this, CREATE_SUSPENDED, &c_ThreadId)) == NULL)
	{
		
	}
}

Thread::~Thread() 
{
	Terminate();
}

void Thread::Resume()
{
	DWORD res =  ResumeThread(c_handle);
	if (res ==-1)
	{
// 		LPVOID lpMsgBuf;
// 		DWORD dw = GetLastError();
// 
// 		FormatMessage(
// 			FORMAT_MESSAGE_ALLOCATE_BUFFER |
// 			FORMAT_MESSAGE_FROM_SYSTEM |
// 			FORMAT_MESSAGE_IGNORE_INSERTS,
// 			NULL,
// 			dw,
// 			MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
// 			(LPTSTR)&lpMsgBuf,
// 			0, NULL);
// 
// 		LocalFree(lpMsgBuf);
	}
}

void Thread::Suspend()
{
	SuspendThread(c_handle);
}

void Thread::Terminate()
{
	isTerminate = true;
	DWORD result = WaitForSingleObject(c_handle, INFINITE);
	if (result == WAIT_OBJECT_0)
	{
		CloseHandle(c_handle);
		c_handle = nullptr;
		OnTerminate();
	}
}

bool Thread::IsTerminate()
{
	return isTerminate;
}

DWORD WINAPI Thread::ThreadProc(LPVOID lpvThreadParm)
{
	Thread *pThread = static_cast<Thread*>(lpvThreadParm);
	pThread->OnExecute();
	return 0;
}