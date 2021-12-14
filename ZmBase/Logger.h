#pragma once
#include <string>
#include <deque>
#include <queue>
using namespace std;
#include "CriticalSection.h"


enum LogLevel	{ LLINFO, LLERROR,LLWARN };

//! ��־��Ϣ�ṹ
struct LogData
{
	LogLevel Level;  // ��Ϣ����
	string Time;   // ��Ϣ����ʱ��
	string Source; // ��ϢԴ
	string Message; // �¼�����
	DWORD ProcessId;//����ID
	DWORD ThreadId;   // �߳�ID
};

class AFX_EXT_CLASS Logger
{
public:
	static Logger* Instance();
	void LogEvent(LogLevel ll, string src, string msg);

private:
	void SaveLogs();
private:
	std::deque<LogData*>c_logs;
	CriticalSection cs;
	static Logger* s_Logger;
	Logger();
	virtual ~Logger();
};


extern AFX_EXT_CLASS void LogEvent(LogLevel ll,string src, string msg);
extern AFX_EXT_CLASS void LogException(const std::exception & e, const char * file = 0, int line = 0);

#define LOGEXCEPTION(e) LogException(e,__FILE__,__LINE__)
#define LOGINFO(src,msg) LogEvent(LLINFO,src,msg)
#define LOGERROR(src,msg) LogEvent(LLERROR,src,msg)
#define LOGWARN(src,msg) LogEvent(LLWARN,src,msg)