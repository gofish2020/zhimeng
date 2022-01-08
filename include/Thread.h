#pragma once


class ThreadNotifition
{
public:
	virtual void OnTerminate() = 0;
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
	bool IsTerminate();
protected:
	virtual void OnExecute() = 0;
	static DWORD WINAPI ThreadProc(LPVOID lpvThreadParm);
private:
	HANDLE c_handle;
	unsigned int c_ThreadId;
	bool isTerminate;
	ThreadNotifition* c_ThreadNotifition;
};