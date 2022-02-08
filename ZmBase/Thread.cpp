#include "stdafx.h"
#include "..\include\Thread.h"
#include "..\include\utils.h"
#include "..\include\Logger.h"
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
	c_WaitEvent = nullptr;
	isTerminate = false;
	c_ThreadNotifition = nullptr;
	c_IsActive = false;
	//�����߳�Ĭ��
	if ((c_handle = chBEGINTHREADEX(NULL, 0, ThreadProc, this, CREATE_SUSPENDED, &c_ThreadId)) == NULL)
	{
		Painc(GetLastErrorStr("Thread::Thread","chBEGINTHREADEX Failed"));
	}

	if ((c_WaitEvent = CreateEvent(nullptr, false, 0, nullptr)) == nullptr)
	{
		Painc(GetLastErrorStr("Thread::Thread", "CreateEvent Failed"));
	}
}

Thread::~Thread() 
{
	if (CloseHandle(c_handle) == false)
	{
		Painc(GetLastErrorStr("Thread::~Thread", "CloseHandle(c_handle) failed"));
	}
	if (CloseHandle(c_WaitEvent) == false)
	{
		Painc(GetLastErrorStr("Thread::~Thread", "CloseHandle(c_WaitEvent) failed"));
	}
}

void Thread::RegisterNotifition(ThreadNotifition *event)
{
	c_ThreadNotifition = event;
}

void Thread::Resume()
{
	if (c_IsActive)
	{
		return;
	}
	
	isTerminate = false;
	if (c_WaitEvent != nullptr)
		::ResetEvent(c_WaitEvent); //���ź�״̬
	ResumeThread(c_handle);
	c_IsActive = true;
}

void Thread::Suspend()
{
	SuspendThread(c_handle);
	c_IsActive = false;
}

void Thread::Terminate()
{
	isTerminate = true;
// 	if (c_WaitEvent != nullptr)
// 		::SetEvent(c_WaitEvent);//���ź�״̬
}

bool Thread::IsTerminate()
{
	return isTerminate;
}

bool Thread::IsActive()
{
	return c_IsActive;
}

void Thread::Wait()
{
	WaitForSingleObject(c_handle, INFINITE);
}

void Thread::WaitEvent()
{
	WaitForSingleObject(c_WaitEvent, INFINITE);
}

DWORD WINAPI Thread::ThreadProc(LPVOID lpvThreadParm)
{
	Thread *pThread = static_cast<Thread*>(lpvThreadParm);
	try
	{
		pThread->OnExecute();
	}
	catch (std::exception &e)
	{
		UnicodeString msg = UnicodeString(e.what()) + L":" + pThread->ClassName();
		LOGERROR("LThread::ThreadProc", msg);
		if (pThread->c_ThreadNotifition != nullptr)
			pThread->c_ThreadNotifition->OnException(e);
	}
	catch (...)
	{
		LOGERROR("Thread::ThreadProc", L"����δ֪���쳣����" + pThread->ClassName());
	}
	if (pThread->c_WaitEvent != nullptr)
		::SetEvent(pThread->c_WaitEvent); //���ź�״̬

	try
	{
		if (pThread->c_ThreadNotifition != nullptr)
			pThread->c_ThreadNotifition->OnTerminate(pThread);
		delete pThread;//�ͷ��̶߳���
	}
	catch (...)
	{

	}
	
	return 0;
}