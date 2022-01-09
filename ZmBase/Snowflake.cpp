#include "stdafx.h"
#include "..\include\Snowflake.h"
#include "..\include\Logger.h"
#include "..\include\DateTime.h"
#include <map>
using namespace std;


Snowflake::Snowflake(INT64 workerid )
{
	c_Epoch = 1641630350369;
	CWorkerIdBits = 10;
	CSenquenceBits = 12;

	CWorkerIdShift = 12;
	CTimeStampShift = 22;

	CSequenceMask = 0xfff;
	CMaxWorker = 0x3ff;

	lastTimeStamp = -1;
	CTimeStampMax = (INT64(-1) << 41) ^ INT64(-1)  ;//最多占用41位

	c_workerid = workerid;
	c_sequence = 0;
}


Snowflake::~Snowflake()
{
}

INT64 Snowflake::NextId()
{
	cs.Locked();
	INT64 now = DateTime::NowUnixMSecond(); //毫秒
	if (now == lastTimeStamp)
	{
		c_sequence = (c_sequence + 1) & CSequenceMask;
		if (c_sequence == 0)
		{
			for (;;)
			{
				now = DateTime::NowUnixMSecond();
				if (now > lastTimeStamp)
				{
					break;
				}
			}
		}
	}
	else
		c_sequence = 0;

	if (now < lastTimeStamp)
	{
		LOGERROR("Snowflake::NextId", L"Clock moved backwards, Refuse gen id");
		return 0;
	}
	lastTimeStamp = now;

	if (now - c_Epoch > CTimeStampMax)
	{
		UnicodeString temp;
		temp.uprintf_s(L"时间戳越界，最大值 %d", CTimeStampMax);
		LOGERROR("Snowflake::NextId", temp);
		return 0;
	}

	//最高位不使用，为0
	now = (now - c_Epoch) << CTimeStampShift | c_workerid << CWorkerIdShift | c_sequence;
	cs.UnLocked();
	return now;
}


map<INT64, Snowflake*>snowMap;

extern Snowflake* GetSnowflake(INT64 workid)
{
	if (workid > 0x3ff || workid < 0 )
	{
		//随机一个
		srand(DateTime::NowDateTime().UnixTimeStamp());
		workid = rand() % 0x400;
	}
	map<INT64, Snowflake*>::iterator iter = snowMap.find(workid);
	if (iter == snowMap.end())//没找到
	{
		Snowflake *temp = new Snowflake(workid);
		snowMap.insert(make_pair(workid, temp));
		return temp;
	}
	else
		return iter->second;
}
