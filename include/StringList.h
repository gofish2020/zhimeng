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
private:

	bool IsSplit;
	typedef struct _Data {
		UnicodeString str;
		UnicodeString key;
		UnicodeString value;
	} stringData;

	std::vector<stringData> datas;
};

