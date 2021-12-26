#include "stdafx.h"
#include <stdarg.h>
#include "..\include\XString.h"

UnicodeString::~UnicodeString()
{

}

UnicodeString::UnicodeString():wstring()
{
}


UnicodeString::UnicodeString(const char* src)
{
	if (src == nullptr)
		return;
	int convertResult = MultiByteToWideChar(CP_ACP, 0, src, (int)strlen(src), nullptr, 0);
	if (convertResult > 0)
	{
		resize(convertResult);
		MultiByteToWideChar(CP_ACP, 0, src, (int)strlen(src),(wchar_t*)(this->c_str()), convertResult);
	}
}



UnicodeString::UnicodeString(const wchar_t* src, int count)
{
	this->assign(src, count);
}

UnicodeString::UnicodeString(const wchar_t* src)
{
	this->assign(src);
}


UnicodeString::UnicodeString(int count, const wchar_t src)
{
	this->assign(count, src);
}

UnicodeString::UnicodeString(const wchar_t src)
{
	UnicodeString(1, src);
}



UnicodeString::UnicodeString(const wstring src)
{
	this->assign(src);
}



UnicodeString::UnicodeString(char src)
{
	uprintf_s(L"%c", src);
}

UnicodeString::UnicodeString(short src)
{
	uprintf_s(L"%hd", src);
}

UnicodeString::UnicodeString(int src)
{
	*this = to_wstring(src);
}

UnicodeString::UnicodeString(unsigned int)
{

}

UnicodeString::UnicodeString(long)
{

}

UnicodeString& UnicodeString::operator=(const wstring src)
{
	this->assign(src);
	return *this;
}

int UnicodeString::uprintf_s(const wchar_t *fmt,...)
{
	va_list _val;
	va_start(_val, fmt);
	int _len = _scwprintf(fmt, _val);
	wstring wstr(_len + 1 ,L'\0');
	_vsnwprintf_s((wchar_t*)wstr.c_str(), _len + 1, _TRUNCATE, fmt, _val);
	va_end(_val);
	wstr.resize(_len);
	*this = wstr;
	return _len;
}

/////////////////////////////////////////////////////////

MultiString::MultiString()
{

}

MultiString::~MultiString()
{

 }
