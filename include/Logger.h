#pragma once
#include <deque>
#include "..\include\CriticalSection.h"
#include "..\include\XString.h"
#include "..\include\DateTime.h"
using namespace std;

enum DebugLevel
{
	dlNoDebug = 0,
	dlGeneralDebug = 1,
	dlDetailDebug = 2,
	dlFullDebug = 3
};

enum LogLevel	{ LLINFO, LLERROR,LLWARN };

//! 日志数据结构
struct LogData
{
	LogLevel Level;  // 消息级别
	UnicodeString Time;   // 消息发生时间
	UnicodeString Source; // 消息源
	UnicodeString Message; // 事件内容
	DWORD ProcessId;//进程ID
	DWORD ThreadId;   // 线程ID
};

class AFX_EXT_CLASS Logger
{
public:
	static Logger* Instance();
	void LogEvent(LogLevel ll, UnicodeString src, UnicodeString msg);

	void SetDebugLevel(DebugLevel dLevel);
	DebugLevel GetDebugLevel();
private:
	void SaveLogs();
private:
	std::deque<LogData*>c_logs;
	CriticalSection cs;
	static Logger s_Logger; //static Logger *s_Logger 这种形式，否则析构函数在进程退出，不会自动调用 good job~~
	Logger();
	virtual ~Logger();
	UnicodeString logPath;
	DebugLevel c_DebugLevel;
};


extern AFX_EXT_CLASS void LogEvent(LogLevel ll, UnicodeString src, UnicodeString msg);
extern AFX_EXT_CLASS void LogException(const std::exception & e, const char * file = 0, int line = 0);
extern AFX_EXT_CLASS DebugLevel GetDebugLevel();
extern AFX_EXT_CLASS void SetDebugLevel(DebugLevel dlevel);

//外部实际调用函数
#define LOGEXCEPTION(e) LogException(e,__FILE__,__LINE__)
#define LOGINFO(src,msg) LogEvent(LLINFO,src,msg)
#define LOGERROR(src,msg) LogEvent(LLERROR,src,msg)
#define LOGWARN(src,msg) LogEvent(LLWARN,src,msg)