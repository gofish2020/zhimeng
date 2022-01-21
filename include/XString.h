#pragma once
#include<string>
#include <vector>
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
	UnicodeString(const string);
	UnicodeString(char);
	UnicodeString(BYTE b);
	UnicodeString(short);
	UnicodeString(unsigned short us);
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
	UnicodeString& operator=(const string);
	UnicodeString& operator=(const wchar_t src);
	UnicodeString& operator=(const char*);
	UnicodeString& operator=(const wchar_t*);
	UnicodeString& operator=(const char&);
	UnicodeString& operator=(const BYTE&);
	UnicodeString& operator=(const short&);
	UnicodeString& operator=(const unsigned short&);
	UnicodeString& operator=(const int&);
	UnicodeString& operator=(const unsigned int&);
	UnicodeString& operator=(const long&);
	UnicodeString& operator=(const unsigned long&);
	UnicodeString& operator=(const __int64&);
	UnicodeString& operator=(const unsigned __int64&);
	UnicodeString& operator=(const float&);
	UnicodeString& operator=(const double&);
	

	UnicodeString& operator=(const UnicodeString&);
	UnicodeString& operator+=(const UnicodeString&);
	UnicodeString operator+(const wstring);
	UnicodeString operator+(const string);
	UnicodeString operator+(const char*);
	UnicodeString operator+(const wchar_t*);
	UnicodeString operator+(const UnicodeString &);

	//�ַ���ת��
	operator char();
	operator string(); //unicode 2 mutil-byte
	string Toutf8() const;// unicode 2 utf8
	void utf8(const char * str); //utf8 2 unicode


	size_t Len() const;
	bool IsEmpty() const;
	bool Contain(const UnicodeString& subStr) const;
	size_t Pos(const UnicodeString& subStr) const;
	void Split(vector<UnicodeString> &value, UnicodeString sep) const;
	UnicodeString ToUpper() const;
	UnicodeString ToLower() const;
	UnicodeString SubString(int index, int count) const;
	UnicodeString Replace(UnicodeString fromstr, UnicodeString tostr) const;
	UnicodeString Trim(wchar_t marker = L' ') const;
	UnicodeString Left(int count) const;
	UnicodeString Right(int count) const;

	int ToInt(int _Base = 10) const;
 	unsigned int ToUInt(int _Base = 10) const;
 	__int64 ToInt64(int _Base = 10) const;
	unsigned __int64 ToUInt64(int _Base = 10) const;
 	double ToDouble() const;
	double ToFloat() const;
	long double ToLongDouble() const;
	
};

//��ָ���ָ���ƴ��
extern AFX_EXT_CLASS UnicodeString Join(vector<UnicodeString> elems, UnicodeString sep);

//��������أ�֧�֡�ָ���UnicodeString����ƴ��
extern AFX_EXT_CLASS UnicodeString operator+(const char* src,const UnicodeString& dest);
extern AFX_EXT_CLASS UnicodeString operator+(const wchar_t* src, const UnicodeString& dest);

class AFX_EXT_CLASS MultiString :public string
{

public:
	MultiString();
	virtual ~MultiString();
};