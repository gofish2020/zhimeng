#include "stdafx.h"
#include "..\include\DateTime.h"


DateTime::DateTime():COleDateTime()
{
}


DateTime::DateTime(const DateTime& src):COleDateTime(src)
{

}

DateTime::DateTime(DATE src):COleDateTime(src)
{

}

DateTime::DateTime(__time32_t src):COleDateTime(src)
{

}

DateTime::DateTime(__time64_t src):COleDateTime(src)
{

}

DateTime::DateTime(const SYSTEMTIME& systimeSrc):COleDateTime(systimeSrc)
{

}

DateTime::DateTime(const FILETIME& filetimeSrc):COleDateTime(filetimeSrc)
{

}

DateTime::DateTime(int nYear,
	int nMonth,
	int nDay,
	int nHour,
	int nMin,
	int nSec):COleDateTime(nYear,nMonth,nDay,nHour,nMin,nSec)
{

}

DateTime::DateTime(const int src):COleDateTime((DATE)src)
{

}

DateTime::~DateTime()
{
}

int DateTime::Year() const
{
	return GetYear();
}

int DateTime::Month() const
{
	return GetMonth();
}

int DateTime::Day() const
{
	return GetDay();
}

int DateTime::Hour() const
{
	return GetHour();
}

int DateTime::Minute() const
{
	return GetMinute();
}

int DateTime::Second() const
{
	return GetSecond();
}

int DateTime::DayOfWeek() const
{
	return GetDayOfWeek();
}

int DateTime::DayOfYear() const
{
	return GetDayOfYear();
}

DateTime DateTime::GetDate()
{
	int d = m_dt;
	return DateTime(d);
}

DateTime DateTime::GetTime()
{
	int d = m_dt;
	DATE time = m_dt - d;
	return DateTime(time);
}

DateTime DateTime::NowDate()
{
	GetCurrentTime();
}

DateTime DateTime::NowDateTime()
{
	return DateTime(GetCurrentTime());
}

UnicodeString DateTime::ToDateStr() const
{

}

UnicodeString DateTime::ToDateTimeStr() const
{

}
