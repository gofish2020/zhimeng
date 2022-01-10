#pragma once
/*
coder:nash
date:2022/1/8
desc:飘雪算法，生成guid
*/
#include "..\include\CriticalSection.h"
class Snowflake
{

public:
	static Snowflake* GetSnowflake(INT64 workid = 1);
private:
	Snowflake(INT64 workerid);//取值范围[0,0x3ff]占用CWorkerIdBits位（10位） //只能通过下面提供的外部函数接口，创建Snowflake对象
	virtual ~Snowflake();
public:
	INT64 NextId();
private:
	CriticalSection cs;
	int CWorkerIdBits; //workerid占的位数
	int CSenquenceBits ;//序列号占的位数
	
	int CWorkerIdShift;//workerid偏移量
	int CTimeStampShift;//时间戳偏移量

	INT64 CSequenceMask;// 序列号 最大值
	INT64 CMaxWorker; //workerid 最大值
	INT64 CTimeStampMax;

	INT64 c_Epoch;//起始时间戳
	INT64 c_workerid;
	INT64 c_sequence;
	INT64 lastTimeStamp;
};



