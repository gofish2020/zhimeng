#pragma once

#include "..\include\Thread.h"

class PrintThread: public Thread
{
public:
	PrintThread();
	~PrintThread();

	void OnExecute();
	void OnTerminate() {};
private:
};

