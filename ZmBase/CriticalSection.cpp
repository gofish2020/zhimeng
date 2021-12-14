#include "stdafx.h"
#include "CriticalSection.h"

CriticalSection::CriticalSection()
{
}


CriticalSection::~CriticalSection()
{
}

void CriticalSection::Enter()
{
	CCriticalSection::Lock();
}

void CriticalSection::Leave()
{
	CCriticalSection::Unlock();
}
