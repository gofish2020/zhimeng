#pragma once
#include<string>
using namespace std;


class AFX_EXT_CLASS UnicodeString :public wstring
{

public:
	virtual ~UnicodeString();
	UnicodeString(); //���ַ�
	UnicodeString(const char*);
	UnicodeString(const wchar_t*, int); //��ȡ�ַ�
	UnicodeString(const wchar_t*); //ֱ�ӽ�ȡ��null
	UnicodeString(const wchar_t); //ֻ�ظ�һ��
	UnicodeString(int, const wchar_t); //�ظ��ַ�
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