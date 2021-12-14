#include "stdafx.h"
#include "Logger.h"

namespace
{
	static int gc_logsbuffersize = 300;
	static int gc_LoggerIndex = 0;
	static const int gc_LoggerDataCount = 500;
	static LogData gc_LoggerData[gc_LoggerDataCount];
};


void Logger::SaveLogs()
{
	for (int i = 0; i < c_logs.size();i++)
	{
		LogData *d = c_logs[i];
	}
	c_logs.clear();
}

Logger* Logger::s_Logger = nullptr;
Logger* Logger::Instance()
{
	if (s_Logger == nullptr)
		s_Logger = new Logger();
	return s_Logger;
}


void Logger::LogEvent(LogLevel ll, string src, string msg)
{
	cs.Enter();

	LogData *data = &gc_LoggerData[gc_LoggerIndex]; //ÈÕÖ¾»º´æ¿Õ¼ä
	data->Level = ll;
	data->Source = src;
	data->Message = msg;
	data->ThreadId = ::GetCurrentThreadId();
	data->ProcessId = ::GetCurrentProcessId();

	c_logs.push_back(data);
	if (c_logs.size() > gc_logsbuffersize)
	{
		SaveLogs();
		
	}

	gc_LoggerIndex++;
	if (gc_LoggerIndex >= gc_LoggerDataCount)
	{
		gc_LoggerIndex = 0;
	}
	cs.Leave();
}


Logger::Logger()
{
}

Logger::~Logger()
{
	SaveLogs();
}

//---------------------
void LogEvent(LogLevel ll, string src, string msg)
{
	Logger::Instance()->LogEvent(ll, src, msg);
}

void LogException(const std::exception & e, const char * file /*= 0*/, int line /*= 0*/)
{
	//LogEvent(LLERROR, "LogException", e.what() + "sss");
}
