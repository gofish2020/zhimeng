#include "stdafx.h"
#include "Logger.h"

namespace
{
	static size_t gc_logsbuffersize = 300;
	static size_t gc_LoggerIndex = 0;
	static const size_t gc_LoggerDataCount = 500;
	static LogData gc_LoggerData[gc_LoggerDataCount];
};


void Logger::SaveLogs()
{
	for (size_t i = 0; i < c_logs.size();i++)
	{
		LogData *d = c_logs[i]; //����־�ļ���д������
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

	//COleDateTime t = COleDateTime(DATE(GetCurrentTime()));
	LogData *data = &gc_LoggerData[gc_LoggerIndex]; //��־����ռ� -- �ظ�����
	data->Level = ll;
	data->Time = "";
	data->Source = src;
	data->Message = msg;
	data->ThreadId = ::GetCurrentThreadId();
	data->ProcessId = ::GetCurrentProcessId();

	c_logs.push_back(data);//˫�˶����б���ָ��
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
	if (file == "")
		LogEvent(LLERROR, "Exception", e.what());
	else
		LogEvent(LLERROR, "Exception", string(file) + ":"  + to_string(line) +  e.what());
}
