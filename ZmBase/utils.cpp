#include "stdafx.h"
#include "..\include\utils.h"
#include "..\include\Logger.h"
#include <exception>
extern AFX_EXT_CLASS void ThrowError(UnicodeString err)
{
	throw std::exception(string(err).c_str());
}

extern AFX_EXT_CLASS UnicodeString GetLastErrorStr(UnicodeString funcname,UnicodeString desc)
{
	int codeError = GetLastError();
	if (codeError == 0)
		return L"";
	LPTSTR lpBuffer;
	FormatMessage(FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_ALLOCATE_BUFFER, NULL, codeError, 0, (LPTSTR)&lpBuffer, MAX_PATH, NULL);
	UnicodeString buffer(lpBuffer);
	LocalFree(lpBuffer);
	if (desc != L"")
		return funcname + L" failed error:¡¾" + UnicodeString(codeError) + L"|" + buffer + L"¡¿ desc:"+desc;
	return funcname + L" failed error :¡¾" + UnicodeString(codeError) + L"|" + buffer +L"¡¿" ;
}
