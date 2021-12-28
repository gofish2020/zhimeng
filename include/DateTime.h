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
	DateTime GetDate();
	DateTime GetTime();
	static DateTime NowDate();
	static DateTime NowDateTime();
	UnicodeString ToDateStr() const;
	UnicodeString ToDateTimeStr() const;
};



/*

COleDateTime() throw();

COleDateTime(_In_ const VARIANT& varSrc) throw();
COleDateTime(_In_ DATE dtSrc) throw();

COleDateTime(_In_ __time32_t timeSrc) throw();
COleDateTime(_In_ __time64_t timeSrc) throw();

COleDateTime(_In_ const SYSTEMTIME& systimeSrc) throw();
COleDateTime(_In_ const FILETIME& filetimeSrc) throw();

COleDateTime(
_In_ int nYear,
_In_ int nMonth,
_In_ int nDay,
_In_ int nHour,
_In_ int nMin,
_In_ int nSec) throw();
COleDateTime(_In_ WORD wDosDate, _In_ WORD wDosTime) throw();
*/