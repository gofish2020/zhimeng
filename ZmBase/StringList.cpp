#include "stdafx.h"
#include "..\include\StringList.h"
#include "..\include\utils.h"

StringList::StringList():IsSplit(false)
{
}


StringList::StringList(const StringList& s)
{
	datas.assign(s.datas.begin(), s.datas.end());
}

StringList::~StringList()
{
	Clear();
}

void StringList::SetSplit()
{
	IsSplit = true;
	for (int i = 0; i < datas.size(); i++)
	{
		datas[i].Split();
	}
}

void StringList::LoadFromStream(Stream& stream)
{
	string str;
	size_t size = stream.GetSize();
	if (size == 0)
		return;
	str.resize(size);
	stream.SetCursor(0);
	stream.Read((char*)str.c_str(), size);
	SetText(UnicodeString(str));
}

void StringList::LoadFromFile(const UnicodeString& fileName)
{
	if (!FileExist(fileName))
	{
		Clear();
		return;
	}
	FileStream fs(fileName, fmOpenRead);
	LoadFromStream(fs);
}

void StringList::SaveToStream(Stream& stream)
{
	for (int i =0;i<datas.size();i++)
	{
		string temp = string(datas[i].str+L"\n");
		stream.Write((char*)temp.c_str(), temp.size());
	}
}

void StringList::SaveToFile(const UnicodeString& fileName)
{
	FileStream fs(fileName, fmOpenReadWrite);
	SaveToStream(fs);
}

void StringList::Clear()
{
	datas.clear();
}

void StringList::Add(const UnicodeString &wstr)
{
	stringData d(wstr);
	if (IsSplit)
		d.Split();
	datas.push_back(d);
}

void StringList::SetText(const UnicodeString &wstr)
{
	Clear();
	//°´ÕÕ \n ·Ö¸î¼ÇÂ¼
	size_t first = 0;

	UnicodeString temp;
	while (1)
	{
		size_t pos = wstr.find(L'\n', first);
		if (pos == wstring::npos)
		{
			temp = wstr.SubString(first, wstr.length() - first).Trim();
			if (temp.Len() > 0)
			{
				Add(temp);
			}
			break;
		}
		else
		{
			size_t size = pos - first; // \n
			if (size == 0)
			{
				first++;
				continue;
			}
			else if (size == 1 ) 
			{
				if ( wstr[first] != L'\r') // 1\n
				{
					temp = wstr.SubString(first, pos - first);
					if (temp.Len() > 0)
						Add(temp);
				}
				// \r\n
				first += 2;
				continue;
			}

			if (wstr[pos-1] != L'\r') // 123\n
				temp = wstr.SubString(first, pos  - first);
			else // 123\r\n
				temp = wstr.SubString(first, pos - first - 1);

			if (temp.Len() > 0)
				Add(temp);
			first = pos + 1;
		}
	}
}

UnicodeString StringList::Text()
{
	UnicodeString result = L"";
	for (int i = 0;i<datas.size();i++)
	{
		result += datas[i].str+ L"\r\n";
	}
	return result;
}

int StringList::Update(int index, const UnicodeString &wstr)
{
	if (index >= datas.size())
	{
		return -1;
	}
	datas[index].str = wstr;
	if (IsSplit)
		datas[index].Split();

}

int StringList::Delete(int index)
{
	if (index >= datas.size())
	{
		return -1;
	}
	datas.erase(datas.begin() + index);
}

int StringList::Insert(int index, const UnicodeString& wstr)
{
	if (index >= datas.size())
	{
		return -1;
	}
	stringData d(wstr);
	if (IsSplit)
		d.Split();
	datas.insert(datas.begin() + index, d);
}

bool StringList::IsExist(const UnicodeString& wstr)
{
	for (int i = 0;i<datas.size();i++)
	{
		if (datas[i].str == wstr)
		{
			return true;
		}
	}
	return false;
}

UnicodeString StringList::Keys(int index)
{
	if (index >= datas.size())
	{
		return L"";
	}
	return datas[index].key;
}

UnicodeString StringList::Values(int index)
{
	if (index >= datas.size())
	{
		return L"";
	}
	return datas[index].value;
}

StringList& StringList::operator=(const StringList& data)
{
	if (this != &data)
	{
		datas.assign(data.datas.begin(), data.datas.end());
	}

	return *this;
}

UnicodeString StringList::operator[](int index)
{
	if (datas.size() == 0 || index >= datas.size())
	{
		return L"";
	}
	return datas[index].str;
}

int StringList::Size()
{
	return datas.size();
}
