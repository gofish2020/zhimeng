#pragma once
#include <exception>
#include "..\include\XString.h"
class Thread;
class AFX_EXT_CLASS ThreadNotifition
{
public:
	virtual void OnException(std::exception &e) {};
	virtual void OnTerminate(Thread *thread) {};
};



class AFX_EXT_CLASS Thread
{
public:
	Thread() ;
	virtual ~Thread() ;
	void RegisterNotifition(ThreadNotifition *event);
	void Resume();
	void Suspend();
	void Terminate();
	void Wait();
	void WaitEvent();
	bool IsTerminate();
	//!线程是否已经激活
	bool IsActive();
protected:
	virtual void OnExecute() = 0;
	virtual UnicodeString ClassName() = 0;

	static DWORD WINAPI ThreadProc(LPVOID lpvThreadParm);
private:
	HANDLE c_handle;
	HANDLE c_WaitEvent;
	unsigned int c_ThreadId;
	bool isTerminate;
	bool c_IsActive;
	ThreadNotifition* c_ThreadNotifition;
};