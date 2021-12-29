/*
date:2021/12/29
coder:nash
desc:���ڡ�ʱ����
*/

#pragma once
#include "..\include\XString.h"

//https://blog.csdn.net/Louis_815/article/details/58594672

class AFX_EXT_CLASS DateTime :public COleDateTime //����Ҳ���Ի���CTime ʵ��DateTime
{
public:
	DateTime();
	DateTime(const COleDateTime& src);
	DateTime(const UnicodeString& src);
	DateTime(const DateTime& Src);
	DateTime(DATE src);//����1899/12/30 ��DATE��ʾ���������������ֱ�ʾ�����죬С�����ֱ�ʾ24Сʱ�ļ���֮��������:1.25 =����1899/12/30 ��1��6Сʱ��  ��6Сʱ/24Сʱ=1/4 = 0.25��  
	DateTime(const int src); //����1899/12/30 ���˶�����
	DateTime(__time32_t src); // ʱ���(��)
	DateTime(__time64_t src); // ʱ���(��)
	DateTime(const SYSTEMTIME& systimeSrc);
	DateTime(const FILETIME& filetimeSrc);
	DateTime( int nYear,int nMonth,int nDay,int nHour,int nMin,int nSec);
	virtual ~DateTime();

	bool IsEmpty();
	int Year() const ;
	// Month of year (1 = January)
	int Month() const ;
	// Day of month (1-31)
	int Day() const ;
	// Hour in day (0-23)
	int Hour() const ;
	// Minute in hour (0-59)
	int Minute() const ;
	// Second in minute (0-59)
	int Second() const ;
	// Day of week (1 = Sunday, 2 = Monday, ..., 7 = Saturday)
	int DayOfWeek() const ;
	// Days since start of year (1 = January 1)
	int DayOfYear() const ;
	DateTime GetDate() const;
	DateTime GetTime() const;
	static DateTime NowDate();
	static DateTime NowDateTime();
	static DateTime NowTime();
	UnicodeString ToDateStr() const;
	UnicodeString ToDateTimeStr() const;
	UnicodeString ToTimeStr() const;
	UnicodeString ToDateInteger() const;
	UnicodeString ToDateTimeInteger() const;
	__time64_t UnixTimeStamp() const;

	DateTime& operator=(const UnicodeString& Src) throw();
	DateTime& operator=(const int Src) throw();
	DateTime operator +(const DateTime& rhs) const;
	DateTime operator +(const double rhs) const;
	DateTime operator +(const int rhs) const;
	DateTime operator-(const DateTime& rhs) const;
	DateTime operator-(const double rhs) const;
	DateTime operator-(const int rhs) const;
	DateTime &operator+=(const DateTime& Src);
	DateTime &operator+=(const double Src);
	DateTime &operator+=(const int Src);
	DateTime &operator-=(const DateTime& Src);
	DateTime &operator-=(const double Src);
	DateTime &operator-=(const int Src);

	operator UnicodeString() const;
	operator int() const;
};