#include "stdafx.h"
#include "..\include\IniConfig.h"
#include "..\include\utils.h"

IniConfig::IniConfig():c_event(nullptr), c_IsModify(false), c_FileName(L"")
{
}


IniConfig::IniConfig(const UnicodeString& fileName): c_FileName(fileName),c_event(nullptr),c_IsModify(false)
{
	LoadFromFile(fileName);
}

IniConfig::IniConfig(Stream& stream):c_FileName(L""),c_event(nullptr),c_IsModify(false)
{

}

IniConfig::~IniConfig()
{
	if (c_IsModify && !c_FileName.IsEmpty())
	{
		SaveToFile(c_FileName);
	}
}

void IniConfig::LoadFromFile(const UnicodeString& fileName)
{
	Clear();
	if (FileExist(fileName))
	{
		FileStream fs(fileName, fmOpenRead);
		LoadFromStream(fs);
	}
	c_FileName = fileName;
	c_IsModify = false;
}

void IniConfig::LoadFromStream(Stream& stream)
{
	Clear();
	c_FileName = L"";
	c_IsModify = false;

	StringList sl;
	sl.LoadFromStream(stream);
	sl.SetSplit();//·Ö¸î
	ConfigData *cdata = nullptr;
	for (int i = 0;i < sl.Size();i++)
	{
		UnicodeString temp = sl[i];
		if (temp[0] == L'[' && temp[temp.Len()-1] == L']') //sections
		{
			map<CaseIString,ConfigData*>::iterator it = sections.find(CaseIString(temp));
			if (it != sections.end())
			{
				cdata = it->second;
			}
			else
			{
				cdata = new ConfigData;
				sections.insert(make_pair(CaseIString(temp), cdata));
			}
		}
		else if (temp[0] != L';')
		{
			if (cdata != nullptr)
			{
				map<CaseIString, UnicodeString>::iterator x = cdata->items.find(sl.Keys(i));
				if (x != cdata->items.end())
				{
					x->second = sl.Values(i);
				}
				else
				{
					cdata->items.insert(make_pair(sl.Keys(i), sl.Values(i)));
				}
			}
		}
	}
}

void IniConfig::SaveToFile(const UnicodeString& fileName)
{
	UnicodeString name = fileName;
	if (name == L"")
	{
		name = c_FileName;
		if (name == L"")
		{
			return;
		}
	}
	if (name == c_FileName && !c_IsModify )
	{
		return;
	}
	//±£´æ
	FileStream fs(fileName, fmOpenNew);//¸²¸Ç
	SaveToStream(fs);
}

void IniConfig::SaveToStream(Stream& stream)
{

	map<CaseIString, ConfigData*>::iterator it = sections.begin();
	while (it != sections.end())
	{

		string section = UnicodeString(it->first)+L"\n";
		stream.Write((char*)section.c_str(), section.length());

		map<CaseIString, UnicodeString>::iterator x = it->second->items.begin();
		while (x != it->second->items.end())
		{

			string item = UnicodeString(x->first) + L"=" + x->second+L"\n";
			stream.Write((char*)item.c_str(), item.length());
			x++;
		}
		it++;
	}
}

void IniConfig::EraseSection(const UnicodeString& section)
{
	if (section.IsEmpty())
	{
		return;
	}
	UnicodeString temp = L"[" + section + L"]";
	map<CaseIString, ConfigData*>::iterator it = sections.find(temp);
	if (it != sections.end())
	{
		delete it->second;
		sections.erase(it);
		c_IsModify = true;
	}
	return;
}

void IniConfig::ClearSectionValues(const UnicodeString section)
{
	if (section.IsEmpty())
	{
		return;
	}
	UnicodeString temp = L"[" + section + L"]";
	map<CaseIString, ConfigData*>::iterator it = sections.find(temp);
	if (it != sections.end())
	{
		if (it->second->items.size() != 0)
		{
			it->second->items.clear();
			c_IsModify = true;
		}
	}
	return;
}

void IniConfig::ReadSection(const UnicodeString section, StringList &strings)
{
	if (section.IsEmpty())
	{
		return;
	}
	UnicodeString temp = L"[" + section + L"]";
	map<CaseIString, ConfigData*>::iterator it = sections.find(temp);
	if (it != sections.end())
	{
		map<CaseIString,UnicodeString>::iterator x = it->second->items.begin();
		while (x != it->second->items.end())
		{
			UnicodeString temp = UnicodeString(x->first);
			strings.Add(temp);
			x++;
		}
	}
	return;
}

void IniConfig::ReadSections( StringList &strings)
{
	map<CaseIString, ConfigData*>::iterator it = sections.begin();
	while (it != sections.end())
	{
		UnicodeString temp = UnicodeString(it->first);
		strings.Add(temp.SubString(1,temp.Len()-2));
		it++;
	}
	return;
}


void IniConfig::DeleteValue(const UnicodeString section, const UnicodeString ident)
{
	if (section.IsEmpty())
	{
		return;
	}
	UnicodeString temp = L"[" + section + L"]";
	map<CaseIString, ConfigData*>::iterator it = sections.find(temp);
	if (it != sections.end())
	{
		map<CaseIString, UnicodeString>::iterator x = it->second->items.find(ident);
		if (x != it->second->items.end())
		{
			it->second->items.erase(x);//É¾³ý
			c_IsModify = true;
		}
	}
	return;
}

UnicodeString IniConfig::ReadString(const UnicodeString section, const UnicodeString ident, const UnicodeString defVal)
{
	if (section.IsEmpty() || ident.IsEmpty())
	{
		return defVal;
	}
	UnicodeString temp = L"[" + section + L"]";
	map<CaseIString, ConfigData*>::iterator it = sections.find(temp);
	if (it != sections.end())
	{
		map<CaseIString, UnicodeString>::iterator x = it->second->items.find(ident);
		if (x != it->second->items.end())
		{
			return x->second;
		}
	}
	return defVal;
}

DateTime IniConfig::ReadDateTime(const UnicodeString Section, const UnicodeString ident, DateTime defVal)
{
	try
	{
		return DateTime(ReadString(Section, ident, defVal));
	}
	catch (...)
	{

	}
	return defVal;
}

double IniConfig::ReadFloat(const UnicodeString Section, const UnicodeString ident, double defVal)
{
	try
	{
		return ReadString(Section, ident, defVal).ToDouble();
	}
	catch (...)
	{

	}
	return defVal;
}

int IniConfig::ReadInteger(const UnicodeString section, const UnicodeString ident, int defVal)
{
	try
	{
		return ReadString(section, ident, defVal).ToInt();
	}
	catch (...)
	{

	}
	return defVal;
}

bool IniConfig::ReadBool(const UnicodeString section, const UnicodeString ident, bool defVal)
{
	return (ReadString(section, ident, (defVal == true) ? "TRUE" : "FALSE").ToUpper() == L"TRUE") ? true : false;
}

void IniConfig::WriteString(const UnicodeString section, const UnicodeString ident, const UnicodeString value)
{
	if (section.IsEmpty() )
	{
		return;
	}
	map<CaseIString, ConfigData*>::iterator it = sections.find(section);
	if (it != sections.end())
	{
		//Ö±½Ó¸²¸Ç
		//it->second->items.insert(ident, value);

		map<CaseIString, UnicodeString>::iterator x = it->second->items.find(ident);
		if (x != it->second->items.end())
		{
			if (x->second == value)
			{
				return;
			}
			x->second = value;
		}
		else
		{
			std::pair<CaseIString, UnicodeString>p(ident, value);
			it->second->items.insert(p);
		}
	}
	else
	{
		ConfigData *d = new ConfigData;
		d->items.insert(make_pair(ident,value));
		sections.insert(make_pair(section, d));
	}
	c_IsModify = true;
}

void IniConfig::WriteDateTime(const UnicodeString section, const UnicodeString ident, const DateTime value)
{
	WriteString(section, ident, value.ToDateTimeStr());
}

void IniConfig::WriteFloat(const UnicodeString section, const UnicodeString ident, double value)
{
	WriteString(section, ident, UnicodeString(value));
}

void IniConfig::WriteInteger(const UnicodeString section, const UnicodeString ident, int value)
{
	WriteString(section, ident, UnicodeString(value));
}

void IniConfig::WriteBool(const UnicodeString section, const UnicodeString ident, bool value)
{

	WriteString(section, ident, (value == true) ? L"TRUE":L"FALSE");
}

void IniConfig::Clear()
{
	map<CaseIString, ConfigData*>::iterator it = sections.begin();
	while (it != sections.end())
	{
		delete it->second;
		it++;
	}
	sections.clear();
	c_IsModify = true;
}

void IniConfig::RegisterNotifyEvent(ConfigNotifyEvent *event)
{
	c_event = event;
}

bool IniConfig::Empty()
{
	return sections.size() == 0;
}
