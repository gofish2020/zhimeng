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
	//this->assign(1, src);
	 *this = UnicodeString(1,src);
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

UnicodeString::UnicodeString(unsigned int src)
{
	*this = to_wstring(src);
}

UnicodeString::UnicodeString(long src)
{
	*this = to_wstring(src);
}

UnicodeString::UnicodeString(unsigned long src)
{
	*this = to_wstring(src);
}

UnicodeString::UnicodeString(__int64 src)
{
	*this = to_wstring(src);
}

UnicodeString::UnicodeString(unsigned __int64 src)
{
	*this = to_wstring(src);
}

UnicodeString::UnicodeString(float src)
{
	//*this = to_wstring(src);
	uprintf_s(L"%g", src);
}

UnicodeString::UnicodeString(double src)
{
	//*this = to_wstring(src);
	uprintf_s(L"%g", src);  //%g 最多保留6位数字
}


UnicodeString::UnicodeString(long double src)
{
	//*this = to_wstring(src);
	uprintf_s(L"%Lg", src);
}

UnicodeString::UnicodeString(const string src)
{
	*this = UnicodeString(src.c_str());
}

UnicodeString& UnicodeString::operator=(const wstring src)
{
	this->assign(src);
	return *this;
}

UnicodeString& UnicodeString::operator=(const UnicodeString& src)
{
	this->assign(src.c_str());
	return *this;
}

UnicodeString& UnicodeString::operator=(const char* src)
{
	*this = UnicodeString(src);
	return *this;
}

UnicodeString& UnicodeString::operator=(const string src)
{
	*this = src.c_str();
	return *this;
}

UnicodeString& UnicodeString::operator=(const wchar_t* src)
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

UnicodeString UnicodeString::operator+(const wchar_t* src)
{
	UnicodeString temp = *this;
	temp.append(src);
	return temp;
}

UnicodeString UnicodeString::operator+(const UnicodeString & src)
{
	UnicodeString temp = *this;
	temp.append(src.c_str());
	return temp;
}


UnicodeString UnicodeString::operator+(const wstring src)
{
	UnicodeString temp = *this;
	temp.append(src);
	return temp;
}


UnicodeString UnicodeString::operator+(const string src)
{
	return *this + UnicodeString(src.c_str());
}
UnicodeString UnicodeString::operator+(const char* src)
{
	return *this + UnicodeString(src);
}

UnicodeString& UnicodeString::operator+=(const UnicodeString& src)
{
	*this = *this + src;
	return *this;
}
size_t UnicodeString::Len() const
{
	return length();
}

bool UnicodeString::IsEmpty() const
{
	return empty();
}

UnicodeString UnicodeString::ToUpper() const
{
	UnicodeString temp = *this;
	_wcsupr_s(const_cast<wchar_t*>(temp.c_str()),temp.Len());
	return temp;
}

UnicodeString UnicodeString::ToLower() const
{
	UnicodeString temp = *this;
	_wcslwr_s(const_cast<wchar_t*>(temp.c_str()),temp.Len());
	return temp;
}

size_t UnicodeString::Pos(const UnicodeString& subStr) const
{
	return find(subStr);
}

bool UnicodeString::Contain(const UnicodeString& subStr) const
{
	if (find(subStr) == -1)
		return false;
	return true;
}

void UnicodeString::Split(vector<UnicodeString> &value, UnicodeString sep) const
{
	int index = 0;
	int pos = 0;
	while (1)
	{
		pos = find_first_of(sep, index);
		if (pos == -1)
		{
			pos = Len();
			break;
		}
		value.push_back(SubString(index, pos - index));
		index  = pos + sep.Len();
	}
	if (index != pos)
		value.push_back(SubString(index, pos - index));
}

UnicodeString UnicodeString::SubString(int index, int count) const
{
	return UnicodeString(substr(index, count));
}

UnicodeString Join(vector<UnicodeString> elems, UnicodeString sep)
{
	UnicodeString temp;
	for (int i = 0; i < elems.size();i++)
	{
		if (temp.IsEmpty())
			temp = elems[i];
		else
		{
			temp += sep;
			temp += elems[i];
		}
	}
	return temp;
}

/////////////////////////////////////////////////////////

MultiString::MultiString()
{

}

MultiString::~MultiString()
{

 }
