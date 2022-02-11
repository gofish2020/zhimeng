#include "stdafx.h"
#include "..\include\StringList.h"
#include "..\include\utils.h"

StringList::StringList()
{
}


StringList::~StringList()
{
	Clear();
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

void StringList::Clear()
{
	datas.clear();
}

void StringList::Add(const UnicodeString &wstr)
{
	stringData d(wstr);
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
