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

DateTime::DateTime(const UnicodeString& Src)
{
	if (Src.Trim() == L"")
	{
		*this = DateTime();
	}
	if (!ParseDateTime(Src.c_str()))
	{
		if (Src.ToInt() > 0 && Src.Len() == 8)
		{
			
			*this = DateTime(Src.SubString(0, 4).ToInt(), Src.SubString(4, 2).ToInt(), Src.SubString(6, 2).ToInt(), 0, 0, 0);
		}
		else
		{
			*this = DateTime();
		}
	}
}

DateTime::DateTime(const COleDateTime& src):COleDateTime(src)
{
	
}

DateTime::~DateTime()
{
}

bool DateTime::IsEmpty()
{
	return m_dt == 0;
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

DateTime DateTime::GetDate() const
{
	int d = m_dt;
	return DateTime(d);
}

DateTime DateTime::GetTime() const
{
	int d = m_dt;
	DATE time = m_dt - d;
	return DateTime(time);
}

DateTime DateTime::NowDate()
{
	DATE d = COleDateTime::GetCurrentTime().m_dt;
	int t = (int)d;
	return t;
}

DateTime DateTime::NowDateTime()
{
	return COleDateTime::GetCurrentTime();
}

DateTime DateTime::NowTime()
{
	DATE d = COleDateTime::GetCurrentTime().m_dt;
	int t = (int)d;
	return d-t;
}

UnicodeString DateTime::ToDateStr() const
{
	if ( m_dt == 0)
	{
		return L"";
	}
	return Format(L"%Y-%m-%d").GetString();
}

UnicodeString DateTime::ToDateTimeStr() const
{
	if (m_dt == 0)
	{
		return L"";
	}
	return Format(L"%Y-%m-%d %H:%M:%S").GetString();
}

UnicodeString DateTime::ToTimeStr() const
{
	if (m_dt == 0)
	{
		return L"";
	}
	return Format(L"%H:%M:%S").GetString();
}

UnicodeString DateTime::ToDateInteger() const
{
	UnicodeString temp;
	temp.uprintf_s(L"%04d%02d%02d", Year(), Month(), Day());
	return temp;
}

UnicodeString DateTime::ToDateTimeInteger() const
{
	UnicodeString temp;
	temp.uprintf_s(L"%04d%02d%02d%02d%02d%02d", Year(), Month(), Day(),Hour(),Minute(),Second());
	return temp;
}

__time64_t DateTime::UnixTimeStamp() const
{
	SYSTEMTIME stLocal;
	GetAsSystemTime(stLocal);
	CTime cTime(stLocal);
	return cTime.GetTime();
}

DateTime DateTime::operator-(const DateTime& rhs) const
{
	return m_dt - rhs.m_dt;
}

DateTime DateTime::operator-(const int rhs) const
{
	return m_dt - rhs;
}

DateTime & DateTime::operator-=(const DateTime& Src)
{
	m_dt -= Src.m_dt;
	return *this;
}

DateTime & DateTime::operator-=(const double Src)
{
	m_dt -= Src;
	return *this;
}

DateTime & DateTime::operator-=(const int Src)
{
	m_dt -= Src;
	return *this;
}

DateTime & DateTime::operator+=(const int Src)
{
	m_dt += Src;
	return *this;
}

DateTime & DateTime::operator+=(const double Src)
{
	m_dt += Src;
	return *this;
}

DateTime& DateTime::operator+=(const DateTime& Src)
{
	m_dt += Src.m_dt;
	return *this;
}

DateTime DateTime::operator+(const int rhs) const
{
	return this->m_dt + rhs;
}

DateTime DateTime::operator-(const double rhs) const
{
	return m_dt - rhs;
}

DateTime DateTime::operator+(const double rhs) const
{
	return this->m_dt + rhs;
}

DateTime DateTime::operator+(const DateTime& rhs) const
{
	return this->m_dt + rhs.m_dt;
}

DateTime& DateTime::operator=(const int Src) throw()
{
	m_dt = Src;
	return *this;
}

DateTime::operator UnicodeString() const
{
	return this->ToDateTimeStr();
}

DateTime::operator int() const
{
	return (int)m_dt;
}

DateTime& DateTime::operator=(const UnicodeString& Src) throw()
{
	if (Src.Trim() == L"")
	{
		*this = DateTime();
		return *this;
	}
	if (!ParseDateTime(Src.c_str()))
	{
		if (Src.ToInt() > 0 && Src.Len() == 8)
		{
			DateTime temp(Src.SubString(0, 4).ToInt(), Src.SubString(4, 2).ToInt(), Src.SubString(6, 2).ToInt(), 0, 0, 0);
			*this = temp;
		}
		else 
		{
			*this = DateTime();
		}
	}
	return *this;
}
