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
class AFX_EXT_CLASS ThreadTask
{
public:
	virtual void OnExecute() = 0;
	virtual UnicodeString TaskName() = 0;
};


class AFX_EXT_CLASS ThreadPool
{

public:
	ThreadPool(int defaultNum = 3); //Ĭ�ϴ�������ٿ���״̬�߳�
	virtual ~ThreadPool();

	void Bind(ThreadTask *task);
	//void UnBind(ThreadTask *task);

private:
	CriticalSection c_cris;
	std::vector<void*>threads;
};

