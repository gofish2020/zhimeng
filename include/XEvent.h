#pragma once

class AFX_EXT_CLASS XEvent
{
public:
	XEvent(); //默认无信号
	~XEvent();
	void Set();//有信号
	void UnSet();//无信号
	void Wait();//等待有信号，否则阻塞
private:
	HANDLE c_Event;
};