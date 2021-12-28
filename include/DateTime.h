#pragma once
#include "..\include\XString.h"

//https://blog.csdn.net/Louis_815/article/details/58594672
class AFX_EXT_CLASS DateTime :public COleDateTime
{
public:
	DateTime();
	DateTime(const DateTime& src);
	DateTime(DATE src);
	DateTime(__time32_t src);
	DateTime(__time64_t src);
	DateTime(const SYSTEMTIME& systimeSrc);
	DateTime(const FILETIME& filetimeSrc);
	DateTime( int nYear,int nMonth,int nDay,int nHour,int nMin,int nSec);
	DateTime(const int src);
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



	DateTime& operator=(const UnicodeString& Src) throw();
	DateTime& operator=(const int Src) throw();
	DateTime operator +(const DateTime& rhs) const;
	DateTime operator +(const double rhs) const;
	DateTime operator +(const int rhs) const;
	DateTime operator -(const DateTime& rhs) const;
	DateTime operator -(const double rhs) const;
	DateTime operator -(const int rhs) const;
	DateTime &operator+=(const DateTime& Src);
	DateTime &operator+=(const double Src);
	DateTime &operator+=(const int Src);
	DateTime &operator-=(const DateTime& Src);
	DateTime &operator-=(const double Src);
	DateTime &operator-=(const int Src);
	operator UnicodeString() const;
	operator int() const;
};