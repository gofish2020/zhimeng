#pragma once

class AFX_EXT_CLASS Thread
{
public:
	Thread() ;
	virtual ~Thread() ;
protected:
	static DWORD WINAPI ThreadProc(LPVOID lpvThreadParm);

private:
	HANDLE c_handle;
	unsigned int c_ThreadId;
};