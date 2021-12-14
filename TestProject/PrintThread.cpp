#include "stdafx.h"
#include "PrintThread.h"


PrintThread::PrintThread()
{
}

PrintThread::~PrintThread()
{
}

void PrintThread::OnExecute()
{
	while (1)
	{
		if (IsTerminate())
		{
			break;
		}
		Sleep(1000);
	}

	return;
}
