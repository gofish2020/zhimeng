#pragma once

#include <afxmt.h>
class CriticalSection :public CCriticalSection
{
public:
	CriticalSection();
	virtual ~CriticalSection();
	void Locked();
	void UnLocked();
};

