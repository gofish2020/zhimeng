#include "stdafx.h"
#include "..\include\CriticalSection.h"

CriticalSection::CriticalSection()
{
}


CriticalSection::~CriticalSection()
{
}

void CriticalSection::Locked()
{
	Lock();
}

void CriticalSection::UnLocked()
{
	Unlock();
}
