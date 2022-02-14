#pragma once
#include "..\include\Stream.h"
#include "..\include\XString.h"

class AFX_EXT_CLASS StringList
{
public:
	StringList();
	virtual ~StringList();

	void SetSplit();

	void LoadFromStream(Stream& stream) ;
	void LoadFromFile(const UnicodeString& fileName);

	void SaveToStream(Stream& stream);
	void SaveToFile(const UnicodeString& fileName);

	void Clear();
	
	void SetText(const UnicodeString& wstr); //���� \n �ָ��ַ���,��������datas
	UnicodeString Text();

	void Add(const UnicodeString &wstr);
	int Update(int index, const UnicodeString &wstr);//�޸��ƶ�λ�õ�����
	int Delete(int index);
	int Insert(int index, const UnicodeString& wstr);

	UnicodeString Keys(int index);
	UnicodeString Values(int index);

	StringList& operator=(const StringList& data);
	UnicodeString operator[](int index);

	
	int Size();
private:

	struct stringData {
		UnicodeString str;
		UnicodeString key;
		UnicodeString value;
		
		stringData() //���캯��
		{
			str = L"";
			key = L"";
			value = L"";
		};
		stringData(const stringData &sd)//�������캯��
		{
			str = sd.str;
			key = sd.key;
			value = sd.value;
		};

		stringData(const UnicodeString& wstr)
		{
			str = wstr;

		};

		stringData& operator=(const stringData& sd)//��ֵ����
		{
			if (this != &sd)
			{
				str = sd.str;
				key = sd.key;
				value = sd.value;
			}
			return *this;
		};

		void Split()
		{
			size_t pos = str.find(L'=', 0);
			if (pos != wstring::npos)
			{
				key = str.SubString(0, pos);
				value = str.substr(pos + 1, str.Len() - pos - 1);
			}
		};
	};

	std::vector<stringData> datas;
	bool IsSplit;
};

