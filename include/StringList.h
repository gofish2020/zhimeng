#pragma once
#include "..\include\Stream.h"
#include "..\include\XString.h"

class AFX_EXT_CLASS StringList
{
public:
	StringList();
	virtual ~StringList();


	void LoadFromStream(Stream& stream) ;
	void LoadFromFile(const UnicodeString& fileName);

	void Clear();
	void Add(const UnicodeString &wstr);
	void SetText(const UnicodeString &wstr); //°´ÕÕ \n ·Ö¸î×Ö·û´®
private:

	struct stringData {
		UnicodeString str;
		UnicodeString key;
		UnicodeString value;
		bool Splited;

		stringData(const UnicodeString& wstr)
		{
			str = wstr;
			Splited = false;
		};

		void Split()
		{
			size_t pos = str.find(L'=', 0);
			if (pos != wstring::npos)
			{
				key = str.SubString(0, pos);
				value = str.substr(pos + 1, str.Len() - pos - 1);
			}
			Splited = true;
		};
	};

	std::vector<stringData> datas;
};

