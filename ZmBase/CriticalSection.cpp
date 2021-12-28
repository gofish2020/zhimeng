#include "stdafx.h"
#include "CriticalSection.h"

CriticalSection::CriticalSection()
{
}


CriticalSection::~CriticalSection()
{
}

void CriticalSection::Locked()
{
	CCriticalSection::Lock();
}

void CriticalSection::UnLocked()
{
	CCriticalSection::Unlock();
}
