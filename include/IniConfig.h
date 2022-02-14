#pragma once

/*
coder:nash
date:2022/2/13
desc:读写INI配合文件

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





	//!在当前的Root下，删除section下所有配置值，包括sub-section和自身
	void EraseSection(const UnicodeString& section);

	//-------------------------------------------------------------------------
	//!在当前的Root下，删除section下所有配置值，不包括sub-section和自身
	void ClearSectionValues(const UnicodeString section);

	//-------------------------------------------------------------------------
	//!在当前的Root下，读出section下所有数据的名称key，放在strings中
	void ReadSection(const UnicodeString section, StringList &strings);

	//-------------------------------------------------------------------------
	//!在当前的Root下，读出section所有的名称，放在strings中。
 	void ReadSections(StringList &strings);
 
 	//-------------------------------------------------------------------------
 	//!在当前的Root下，删除section下名为ident的配置信息
 	void DeleteValue(const UnicodeString section, const UnicodeString ident);
 
 	//-------------------------------------------------------------------------
 	//!在当前的Root下，读取section下名为ident的配置信息的字符串型值，\n
 	//!如果配置信息不可访问或者为空或者不是字符串类型，则返回缺省值defVal
 	UnicodeString ReadString(const UnicodeString section, const UnicodeString ident, const UnicodeString defVal);
 
 	//-------------------------------------------------------------------------
 	//!在当前的Root下，读取section下名为ident的配置信息的字符串型值，\n
 	//!如果配置信息不可访问或者为空或者不是时间类型，则返回缺省值defVal
 	DateTime ReadDateTime(const UnicodeString Section, const UnicodeString ident, DateTime defVal);
 
 	//-------------------------------------------------------------------------
 	//!在当前的Root下，读取section下名为ident的配置信息的字符串型值，\n
 	//!如果配置信息不可访问或者为空或者不是浮点类型，则返回缺省值defVal
 	double ReadFloat(const UnicodeString Section, const UnicodeString ident, double defVal);
 
 	//-------------------------------------------------------------------------
 	//!在当前的Root下，读取section下名为ident的配置信息的整型值，\n
 	//!如果配置信息不可访问或者不是整数类型，则返回缺省值defVal
 	int ReadInteger(const UnicodeString section, const UnicodeString ident, int defVal);
 
 	//-------------------------------------------------------------------------
 	//!在当前的Root下，读取section下名为ident的配置信息的bool型值，\n
 	//!如果配置信息不可访问或者不是bool类型，则返回缺省值defVal
 	bool ReadBool(const UnicodeString section, const UnicodeString ident, bool defVal);
 
 	//-------------------------------------------------------------------------
 	//!在当前的Root下，设置section下名为ident的配置信息的字符串型值为value
 	void WriteString(const UnicodeString section, const UnicodeString ident, const UnicodeString value);
 
 	//-------------------------------------------------------------------------
 	//!在当前的Root下，设置section下名为ident的配置信息的时间型值为value
 	void WriteDateTime(const UnicodeString section, const UnicodeString ident, const DateTime value);
 
 	//-------------------------------------------------------------------------
 	//!在当前的Root下，设置section下名为ident的配置信息的浮点型值为value
 	void WriteFloat(const UnicodeString section, const UnicodeString ident, double value);
 
 	//-------------------------------------------------------------------------
 	//!在当前的Root下，设置section下名为ident的配置信息的整型值为value
 	void WriteInteger(const UnicodeString section, const UnicodeString ident, int value);
 
 	//-------------------------------------------------------------------------
 	//!在当前的Root下，设置section下名为ident的配置信息的bool型值为value
 	void WriteBool(const UnicodeString section, const UnicodeString ident, bool value);
	//-------------------------------------------------------------------------
	//!清除当前所有的修改操作
	void Clear();

	//-------------------------------------------------------------------------
	//!从一个源对象设置列表及其可能的相关的对象
	//void Assign(const IniConfig &data);
	//-------------------------------------------------------------------------
	//!把data指定的LIniFileConfig复制给这个LIniFileConfig
//	IniConfig & operator=(const IniConfig & data);

//	IniConfig & operator+=(const IniConfig & data);

	//-------------------------------------------------------------------------
	//!注册设置对象回调函数
	void RegisterNotifyEvent(ConfigNotifyEvent *event);

	//-------------------------------------------------------------------------
	//!指定对象是否为空内容
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

