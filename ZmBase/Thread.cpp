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
	//创建线程默认-不执行
	if ((c_handle = chBEGINTHREADEX(NULL, 0, ThreadProc, this, CREATE_SUSPENDED, &c_ThreadId)) == NULL)
	{
		
	}
}

Thread::~Thread() 
{

}

DWORD WINAPI Thread::ThreadProc(LPVOID lpvThreadParm)
{

}