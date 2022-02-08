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
class AFX_EXT_CLASS ThreadTask
{
public:
	virtual void OnExecute() = 0;
	virtual UnicodeString TaskName() = 0;
};


class AFX_EXT_CLASS ThreadPool
{

public:
	ThreadPool(int defaultNum = 3); //默认创建多个少空闲状态线程
	virtual ~ThreadPool();

	void Bind(ThreadTask *task);
	//void UnBind(ThreadTask *task);

private:
	CriticalSection c_cris;
	std::vector<void*>threads;
};

