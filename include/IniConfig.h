#pragma once

/*
coder:nash
date:2022/2/13
desc:��дINI����ļ�

*/

#include "..\include\XString.h"
#include "..\include\Stream.h"
#include "..\include\StringList.h"
#include "..\include\DateTime.h"
#include <map>
using namespace std;


class ConfigNotifyEvent
{
public:
	virtual void OnChange() = 0;
};

class AFX_EXT_CLASS IniConfig
{
public:
	IniConfig();
	IniConfig(const UnicodeString& fileName);
	IniConfig(Stream& stream);
	virtual ~IniConfig();

	void LoadFromFile(const UnicodeString& fileName);
	void LoadFromStream(Stream& stream);
	void SaveToFile(const UnicodeString& fileName);
	void SaveToStream(Stream& stream) ;





	//!�ڵ�ǰ��Root�£�ɾ��section����������ֵ������sub-section������
	void EraseSection(const UnicodeString& section);

	//-------------------------------------------------------------------------
	//!�ڵ�ǰ��Root�£�ɾ��section����������ֵ��������sub-section������
	void ClearSectionValues(const UnicodeString section);

	//-------------------------------------------------------------------------
	//!�ڵ�ǰ��Root�£�����section���������ݵ�����key������strings��
	void ReadSection(const UnicodeString section, StringList &strings);

	//-------------------------------------------------------------------------
	//!�ڵ�ǰ��Root�£�����section���е����ƣ�����strings�С�
 	void ReadSections(StringList &strings);
 
 	//-------------------------------------------------------------------------
 	//!�ڵ�ǰ��Root�£�ɾ��section����Ϊident��������Ϣ
 	void DeleteValue(const UnicodeString section, const UnicodeString ident);
 
 	//-------------------------------------------------------------------------
 	//!�ڵ�ǰ��Root�£���ȡsection����Ϊident��������Ϣ���ַ�����ֵ��\n
 	//!���������Ϣ���ɷ��ʻ���Ϊ�ջ��߲����ַ������ͣ��򷵻�ȱʡֵdefVal
 	UnicodeString ReadString(const UnicodeString section, const UnicodeString ident, const UnicodeString defVal);
 
 	//-------------------------------------------------------------------------
 	//!�ڵ�ǰ��Root�£���ȡsection����Ϊident��������Ϣ���ַ�����ֵ��\n
 	//!���������Ϣ���ɷ��ʻ���Ϊ�ջ��߲���ʱ�����ͣ��򷵻�ȱʡֵdefVal
 	DateTime ReadDateTime(const UnicodeString Section, const UnicodeString ident, DateTime defVal);
 
 	//-------------------------------------------------------------------------
 	//!�ڵ�ǰ��Root�£���ȡsection����Ϊident��������Ϣ���ַ�����ֵ��\n
 	//!���������Ϣ���ɷ��ʻ���Ϊ�ջ��߲��Ǹ������ͣ��򷵻�ȱʡֵdefVal
 	double ReadFloat(const UnicodeString Section, const UnicodeString ident, double defVal);
 
 	//-------------------------------------------------------------------------
 	//!�ڵ�ǰ��Root�£���ȡsection����Ϊident��������Ϣ������ֵ��\n
 	//!���������Ϣ���ɷ��ʻ��߲����������ͣ��򷵻�ȱʡֵdefVal
 	int ReadInteger(const UnicodeString section, const UnicodeString ident, int defVal);
 
 	//-------------------------------------------------------------------------
 	//!�ڵ�ǰ��Root�£���ȡsection����Ϊident��������Ϣ��bool��ֵ��\n
 	//!���������Ϣ���ɷ��ʻ��߲���bool���ͣ��򷵻�ȱʡֵdefVal
 	bool ReadBool(const UnicodeString section, const UnicodeString ident, bool defVal);
 
 	//-------------------------------------------------------------------------
 	//!�ڵ�ǰ��Root�£�����section����Ϊident��������Ϣ���ַ�����ֵΪvalue
 	void WriteString(const UnicodeString section, const UnicodeString ident, const UnicodeString value);
 
 	//-------------------------------------------------------------------------
 	//!�ڵ�ǰ��Root�£�����section����Ϊident��������Ϣ��ʱ����ֵΪvalue
 	void WriteDateTime(const UnicodeString section, const UnicodeString ident, const DateTime value);
 
 	//-------------------------------------------------------------------------
 	//!�ڵ�ǰ��Root�£�����section����Ϊident��������Ϣ�ĸ�����ֵΪvalue
 	void WriteFloat(const UnicodeString section, const UnicodeString ident, double value);
 
 	//-------------------------------------------------------------------------
 	//!�ڵ�ǰ��Root�£�����section����Ϊident��������Ϣ������ֵΪvalue
 	void WriteInteger(const UnicodeString section, const UnicodeString ident, int value);
 
 	//-------------------------------------------------------------------------
 	//!�ڵ�ǰ��Root�£�����section����Ϊident��������Ϣ��bool��ֵΪvalue
 	void WriteBool(const UnicodeString section, const UnicodeString ident, bool value);
	//-------------------------------------------------------------------------
	//!�����ǰ���е��޸Ĳ���
	void Clear();

	//-------------------------------------------------------------------------
	//!��һ��Դ���������б�����ܵ���صĶ���
	//void Assign(const IniConfig &data);
	//-------------------------------------------------------------------------
	//!��dataָ����LIniFileConfig���Ƹ����LIniFileConfig
//	IniConfig & operator=(const IniConfig & data);

//	IniConfig & operator+=(const IniConfig & data);

	//-------------------------------------------------------------------------
	//!ע�����ö���ص�����
	void RegisterNotifyEvent(ConfigNotifyEvent *event);

	//-------------------------------------------------------------------------
	//!ָ�������Ƿ�Ϊ������
	bool Empty();

private:
	UnicodeString c_FileName;
	bool c_IsModify;
	ConfigNotifyEvent *c_event;
	struct ConfigData
	{
		map<CaseIString, UnicodeString>items;
	};
	map<CaseIString, ConfigData*>sections;

};

