#pragma once
/*
coder:nash
date:2022/2/8
desc:
�̳߳أ������̳߳ض��󣬽������񡿴��ݸ��̳߳ض������̳߳ض��󡾴���һ���̣߳�ִ�����񡿣�����ִ����ɺ�
�����߳̿����ٷ��������������

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

//������̴߳���һֱ���е�״̬��ͨ��SetTask�����ص����󴫵ݸ������У��̣߳�ִ������
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

