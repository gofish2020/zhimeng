#pragma once
#include "..\include\XString.h"
#define Painc(err) ThrowError(err)


extern AFX_EXT_CLASS void ThrowError(UnicodeString err);

extern AFX_EXT_CLASS UnicodeString GetLastErrorStr(UnicodeString funcname, UnicodeString desc = L"");