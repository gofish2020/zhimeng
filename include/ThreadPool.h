#pragma once
/*
coder:nash
date:2022/2/8
desc:
线程池：创建线程池对象，将【任务】传递给线程池对象，由线程池对象【创建一个线程，执行任务】，任务执行完成后；
空闲线程可以再分配给其他任务复用

*/

#include "..\include\XString.h"
#include "..\include\CriticalSection.h"
#include "..\include\Thread.h"
class AFX_EXT_CLASS ThreadTask
{
public:
	virtual void OnExecute() = 0;
	virtual UnicodeString TaskName() = 0;
};


class AFX_EXT_CLASS ThreadPool
{

public:
	static ThreadPool* Instance();
private:
	ThreadPool(); 
	virtual ~ThreadPool();
	static ThreadPool pool;
public:
	void SetTask(ThreadTask *task,bool IsRelease, ThreadNotifition *event =  nullptr);
	
private:
	CriticalSection c_cris;
	std::vector<void*>threads;
};

