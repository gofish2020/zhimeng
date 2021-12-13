#pragma once

class AFX_EXT_CLASS Thread
{
public:
	Thread() ;
	virtual ~Thread() ;

	
	
	void Resume();
	void Suspend();
	void Terminate();
	

	bool IsTerminate();
protected:
	virtual void OnExecute() = 0;
	virtual void OnTerminate() {};

	static DWORD WINAPI ThreadProc(LPVOID lpvThreadParm);

private:
	HANDLE c_handle;
	unsigned int c_ThreadId;

	bool isTerminate;
};