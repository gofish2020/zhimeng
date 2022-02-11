#pragma once
#include "..\include\XString.h"
#include <fstream>
using namespace std;

class AFX_EXT_CLASS Stream
{
public:
	Stream();
	virtual ~Stream();
	virtual size_t Write(_In_ void* src, size_t count) = 0;
	virtual size_t Read(_Out_ void* dest, size_t count)= 0;
	virtual size_t GetSize() = 0;
	virtual void SetCursor(size_t Pos) = 0;
};



enum SeekDirection
{
	SeekBegin = 0, SeekCurrent = 1, SeekEnd = 2
};
//һ�������Ĵ洢�ռ� https://blog.csdn.net/qq_38810767/article/details/85265541
class AFX_EXT_CLASS MemoryStream :public Stream
{
public:
	MemoryStream(size_t step = 1 << 12); // ����:4KB����
	virtual ~MemoryStream();

	void Free(); //�ͷſռ�
	void Zero(); //����Ŀռ��ʼ��Ϊ0
	void Seek(size_t offset, SeekDirection& direction);
	void Skip(size_t byteNums); //�α���ԾbyteNums�ֽ�
	void SetCursor(size_t cursor); //�����α�λ��
	size_t GetCursor();
	void SetSize(size_t size);
	size_t GetSize();
	char* Memory();

	size_t Write(_In_ void* src, size_t count);
	size_t Read(_Out_ void* dest, size_t count);
	//�ַ�����GB2312
	MemoryStream &operator <<(const string& src)
	{
		size_t count = src.length();//�ֽ���
		Write((char*)src.c_str(), count);
		return *this;
	};

	MemoryStream &operator >> (string& src)
	{
		size_t count = src.length();
		if (count == 0)
		{
			src = "";
			return *this;
		}
		Read((char*)src.c_str(), count);
		return *this;
	};
	//�ַ�����UTF-16
	MemoryStream& operator<<(const UnicodeString& src)
	{
		size_t count = src.Len() * 2;
		Write(reinterpret_cast<BYTE*>(const_cast<wchar_t*>(src.c_str())), count);
		return *this;
	}

	MemoryStream& operator>>(UnicodeString& src)
	{
		size_t len = src.Len();//�洢�ռ�
		if (len == 0)
		{
			src = L"";
			return *this;
		}
		Read(reinterpret_cast<BYTE*>(const_cast<wchar_t*>(src.c_str())), len * 2);
		return *this;
	}

	template<typename T>
	MemoryStream& operator<<(T data)
	{
		size_t count = sizeof(data);
		Write(reinterpret_cast<BYTE*>(&data), count);
		return *this;
	}

	template<typename T>
	MemoryStream& operator>>(T &data)
	{
		size_t count = sizeof(data);
		Read(reinterpret_cast<BYTE*>(&data), count);
		return *this;
	}
private:
	size_t _step;	//���ݲ���
	size_t _size;	//���ݴ�С
	size_t _cap;	//������С
	size_t _cursor;//�α�
	void* _pMemory;	//ͷָ��
};

enum FileMode
{	
	Filein = 0x01, //�ļ�������ģʽ�򿪣�����-->>�ڴ�
	Fileout = 0x02,//�ļ������ģʽ�򿪣��ڴ�-->>����
	Fileate = 0x04,//�ļ��򿪺󣬶�λ���ļ�β
	Fileapp = 0x08,//׷��ģʽ���ļ�
	Filetrunc = 0x10,//����ļ����ڣ����ļ���������Ϊ0
	File_Nocreate = _IOS_Nocreate,//�������ļ�������ļ������ڣ���ʧ��
	File_Noreplace = _IOS_Noreplace,//�������ļ�������ļ����ڣ���ʧ��
	Filebinary = _IOSbinary//�����ƴ��ļ�
};

static const int fmOpenNew = Fileout; //�������ļ����α�λ���ײ�
static const int fmOpenRead = Filein | Fileapp ;//�����ڴ����ļ�������ֱ�Ӵ��ļ����α�λ���ײ�����ֻ�ܶ�ȡ��
static const int fmOpenWrite = Fileout | Fileapp | Fileate; // �����ڴ����ļ�������ֱ�Ӵ��ļ����α�λ��β������ֻ��д�롿
static const int fmOpenReadWrite = Filein | Fileout | Fileapp | Fileate; // �����ڴ��������ڴ��ļ����α�λ��β�������������λ��д��Ͷ�ȡ��

//int prot �����趨
#define _SH_DENYRW      0x10    //!������Ӧ�ó����ܴ򿪸��ļ�
#define _SH_DENYWR      0x20    //!������Ӧ�ó���ֻ����ֻ����ʽ���ļ�
#define _SH_DENYRD      0x30    //!������Ӧ�ó���ֻ����ֻд��ʽ���ļ�
#define _SH_DENYNO      0x40    //!������Ӧ�ó���������κη�ʽ���ļ�
#define _SH_SECURE      0x80    //!�����ȡ,��ռд��(�������̿��Թ�ͬ���������һ��д������һ�����ܴ�)


class AFX_EXT_CLASS FileStream :public Stream
{
public:
	FileStream();
	FileStream(UnicodeString fileName, int mode,int prot = _SH_DENYNO);
	virtual ~FileStream();

	void Open(UnicodeString fileName, int mode, int prot = _SH_DENYNO);
	void Close();
	void Seek(size_t offset, SeekDirection direction);
	virtual size_t GetCursor();
	virtual void SetCursor(size_t Pos);
	virtual size_t GetSize();
	virtual void SetSize(size_t size);

	virtual size_t Write(_In_ void* src, size_t count);
	virtual size_t Read(_Out_ void* dest, size_t count);


	//�ַ�����UTF-8
	void WriteStringUTF8(const UnicodeString& wstr);
	void ReadStringUTF8(UnicodeString& wstr);
	//�ַ�����UTF-16
	FileStream& operator<< (const UnicodeString& wstr);
	FileStream& operator>> (UnicodeString& wstr);

	//�ַ�����GB2312
	FileStream& operator <<(const string& src);
	FileStream& operator >>(string& src);

private:
	fstream* pfstream;
	int _mode;
	size_t _cursor;
};


class AFX_EXT_CLASS ShareMemoryStream : public Stream
{
public:
	ShareMemoryStream(UnicodeString Name, DWORD losize);
	ShareMemoryStream(UnicodeString Name);
	virtual ~ShareMemoryStream();

	virtual size_t Write(_In_ void* src, size_t count);
	virtual size_t Read(_Out_ void* dest, size_t count);


	ShareMemoryStream& operator<<(const UnicodeString& wstr);
	/*
		�����wstr����Ҫ�ȷ���洢�ռ� 
		UnicodeString wstr(10,L'\0');//����10�ַ��Ĵ洢�ռ�,��ʾ��ȡ10���ַ�
	*/
	ShareMemoryStream& operator>>(UnicodeString& wstr);

	size_t GetCursor();
	void SetCursor(size_t cursor);
	size_t GetSize();
	void SetSize(size_t size);

	char* Memory();
	UnicodeString ShareName();
private:
	HANDLE c_handle;
	UINT32* pSize;
	UINT32* pCursor;
	UINT32* pRefCount; //���ü���
	char* pMemory;
	bool c_IsCreator;
	UnicodeString c_ShareName;

};