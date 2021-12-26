#pragma once
#include<string>
using namespace std;


class AFX_EXT_CLASS UnicodeString :public wstring
{

public:
	virtual ~UnicodeString();
	UnicodeString(); //空字符
	UnicodeString(const char*);
	UnicodeString(const wchar_t*, int); //截取字符
	UnicodeString(const wchar_t*); //直接截取到null
	UnicodeString(const wchar_t); //只重复一次
	UnicodeString(int, const wchar_t); //重复字符
	UnicodeString(const wstring);

	/*
		wstring to_wstring (int val);
		wstring to_wstring (long val);
		wstring to_wstring (long long val);
		wstring to_wstring (unsigned val);
		wstring to_wstring (unsigned long val);
		wstring to_wstring (unsigned long long val);
		wstring to_wstring (float val);
		wstring to_wstring (double val);
		wstring to_wstring (long double val);
	*/
	UnicodeString(char);
	UnicodeString(short);
	UnicodeString(int);
	UnicodeString(unsigned int);
	UnicodeString(long);
	UnicodeString(unsigned long);
	UnicodeString(__int64);
	UnicodeString(unsigned __int64);
	UnicodeString(float);
	UnicodeString(double);
	UnicodeString(long double);

	int uprintf_s(const wchar_t *fmt, ...);
	



	UnicodeString& operator=(const wstring);
};




class AFX_EXT_CLASS MultiString :public string
{

public:
	MultiString();
	virtual ~MultiString();
};