#include "stdafx.h"
#include "..\include\Logger.h"
#include "..\include\Stream.h"
#include "..\include\utils.h"
namespace
{
	static size_t gc_logsbuffersize = 300;
	static size_t gc_LoggerIndex = 0;
	static const size_t gc_LoggerDataCount = 500;
	static LogData gc_LoggerData[gc_LoggerDataCount];
};


void Logger::SaveLogs()
{
	DateTime d = DateTime::NowDate();
	UnicodeString fileName;
	fileName.uprintf_s(L"%s%04d%02d%02d.log",logPath.c_str(),d.Year(),d.Month(),d.Day());
	FileStream fs;
	fs.Open(fileName, fmOpenWrite,_SH_DENYNO);
	for (size_t i = 0; i < c_logs.size();i++)
	{
		LogData *d = c_logs[i]; //打开日志文件，写入数据
		UnicodeString temp = UnicodeString(d->Level) + L"," + d->Time + L"," + UnicodeString(d->ProcessId) + L"," + UnicodeString(d->ThreadId) + L"," + d->Source + L"," + d->Message + L"\n";
		fs << temp;
	}
	c_logs.clear();
}

Logger Logger::s_Logger;
Logger* Logger::Instance()
{
	return &s_Logger;
}


void Logger::LogEvent(LogLevel ll, UnicodeString src, UnicodeString msg)
{
	cs.Locked();

	LogData *data = &gc_LoggerData[gc_LoggerIndex]; //日志缓存空间 -- 重复利用
	data->Level = ll;
	data->Time = DateTime::NowDateTime().ToDateTimeStr();
	data->Source = src;
	data->Message = msg;
	data->ThreadId = ::GetCurrentThreadId();
	data->ProcessId = ::GetCurrentProcessId();
	c_logs.push_back(data);//双端队列中保存指针
	if (c_logs.size() >= gc_logsbuffersize)
	{
		SaveLogs();
	}
	gc_LoggerIndex++;
	if (gc_LoggerIndex >= gc_LoggerDataCount)
	{
		gc_LoggerIndex = 0;
	}
	cs.UnLocked();
}


Logger::Logger()
{
	UnicodeString fileName = ExtractFileName(GetApplicationFullName(), true);
	logPath = ExtractFilePath(GetApplicationFullName()) + L"\\logs\\";
	CreateDir(logPath);
	logPath = logPath + fileName;
}

Logger::~Logger()
{
	try
	{
		SaveLogs();
	}
	catch (const std::exception&)
	{

	}
	
}

//---------------------
void LogEvent(LogLevel ll, UnicodeString src, UnicodeString msg)
{
	Logger::Instance()->LogEvent(ll, src, msg);
}

void LogException(const std::exception & e, const char * file /*= 0*/, int line /*= 0*/)
{
	if (file == "")
		LogEvent(LLERROR, "Exception", e.what());
	else
		LogEvent(LLERROR, "Exception", UnicodeString(file) + ":"  + UnicodeString(line) +  e.what());
}
