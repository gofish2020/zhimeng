#include "stdafx.h"
#include "..\include\ThreadPool.h"
#include "..\include\Thread.h"
#include "..\include\Logger.h"

//单个线程
class ThreadObject :public Thread
{

public:
	ThreadObject();
	~ThreadObject();
public:
	virtual void OnExecute();
	virtual UnicodeString ClassName() 
	{
		return L"ThreadObject";
	};
	bool IsWorking();
	void SetTask(ThreadTask *task,bool IsRelease, ThreadNotifition *event = nullptr);
private:
	ThreadNotifition *c_event;
	bool c_IsWork;
	bool c_IsRelease;
	ThreadTask *c_task;
};

ThreadObject::ThreadObject():Thread()
{
	c_IsWork = false;
	c_IsRelease = false;
	c_event = nullptr;
	c_task = nullptr;
	Resume();
}

ThreadObject::~ThreadObject()
{

}

void ThreadObject::OnExecute()
{
	while (!IsTerminate()) //保持线程一直处于运行状态
	{
		while (1)
		{
			if (IsTerminate())
				return;
			if (c_IsWork)
				break;
			Sleep(50);
		}

		if (c_task != nullptr)
		{
			try
			{
				c_task->OnExecute();
			}
			catch (const std::exception&e)
			{
				UnicodeString msg = UnicodeString(e.what()) + ":" + c_task->TaskName();
				LOGERROR("ThreadObject::OnExecute", msg);
			}
			catch (...)
			{
				UnicodeString msg = "发生未知的异常错误！"  + c_task->TaskName();
				LOGERROR("ThreadObject::OnExecute", msg);
			}
		}
		if (c_event)
			c_event->OnTerminate(this);
		if (c_IsRelease)
			delete c_task;
		//任务执行完成
		c_task = nullptr;
		c_IsWork = false;
		c_IsRelease = false;
	}
	
}

bool ThreadObject::IsWorking()
{
	return c_IsWork;
}

void ThreadObject::SetTask(ThreadTask *task,bool IsRelease, ThreadNotifition *event)
{
	if (!c_IsWork)
	{
		c_event = event;
		c_task = task;
		c_IsWork = true;
		c_IsRelease = IsRelease;
	}
}



// struct ThreadData 
// {
// 	ThreadObject *obj;
// 	ThreadTask *task;
// };
// 
// typedef ThreadData pThreadData;


//线程池
ThreadPool::ThreadPool(int defaultNum /*= 3*/)
{
	for (int i = 0; i < defaultNum;i++)
	{
		threads.push_back(new ThreadObject());
	}
}

ThreadPool::~ThreadPool()
{
	std::vector<void*>::iterator it = threads.begin();
	while (it != threads.end())
	{
		ThreadObject *temp = static_cast<ThreadObject*>(*it);
		temp->Terminate();
		temp->WaitEvent();
	}
	threads.clear();
}

void ThreadPool::Bind(ThreadTask *task)
{
	c_cris.Locked();
	std::vector<void*>::iterator it = threads.begin();
	while (it != threads.end())
	{
		ThreadObject *temp = static_cast<ThreadObject*>(*it);
		if (!temp->IsWorking())
		{
			temp->SetTask(task, false, nullptr);
			return;
		}
	}

	ThreadObject *temp = new ThreadObject();
	temp->SetTask(task, false, nullptr);
	threads.push_back(temp);
	c_cris.UnLocked();
}

// void ThreadPool::UnBind(ThreadTask *task)
// {
// 
// }
