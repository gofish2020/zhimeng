#pragma once
/*
coder:nash
date:2022/1/8
desc:Ʈѩ�㷨������guid
*/
#include "..\include\CriticalSection.h"
class Snowflake
{

public:
	static Snowflake* GetSnowflake(INT64 workid = 1);
private:
	Snowflake(INT64 workerid);//ȡֵ��Χ[0,0x3ff]ռ��CWorkerIdBitsλ��10λ�� //ֻ��ͨ�������ṩ���ⲿ�����ӿڣ�����Snowflake����
	virtual ~Snowflake();
public:
	INT64 NextId();
private:
	CriticalSection cs;
	int CWorkerIdBits; //workeridռ��λ��
	int CSenquenceBits ;//���к�ռ��λ��
	
	int CWorkerIdShift;//workeridƫ����
	int CTimeStampShift;//ʱ���ƫ����

	INT64 CSequenceMask;// ���к� ���ֵ
	INT64 CMaxWorker; //workerid ���ֵ
	INT64 CTimeStampMax;

	INT64 c_Epoch;//��ʼʱ���
	INT64 c_workerid;
	INT64 c_sequence;
	INT64 lastTimeStamp;
};



