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
