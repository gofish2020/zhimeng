#include "stdafx.h"
#include "..\include\XEvent.h"
#include "..\include\utils.h"

XEvent::XEvent()
{
	if ((c_Event = CreateEvent(nullptr, true, 0, nullptr)) == nullptr)
		Painc(GetLastErrorStr(L"CreateEvent()"));
}


XEvent::~XEvent()
{
	if (CloseHandle(c_Event) != TRUE)
		Painc(GetLastErrorStr(L"CloseHandle()"));
}

void XEvent::Set()
{
	SetEvent(c_Event);
}

void XEvent::UnSet()
{
	ResetEvent(c_Event);
}

void XEvent::Wait()
{
	WaitForSingleObject(c_Event, INFINITE);
}
