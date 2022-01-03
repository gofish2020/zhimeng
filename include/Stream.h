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
};



enum SeekDirection
{
	SeekBegin = 0, SeekCurrent = 1, SeekEnd = 2
};
//һ�������Ĵ洢�ռ� https://blog.csdn.net/qq_38810767/article/details/85265541
class AFX_EXT_CLASS MemoryStream :public Stream
{
public:
	MemoryStream(size_t step = 1 << 12 ); // ����:4KB����
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

	MemoryStream& operator<<(const UnicodeString& src);
	MemoryStream& operator>>(UnicodeString& src);

	template<typename T> 
	MemoryStream& operator<< (const T data);
	template<typename T>
	MemoryStream& operator>>(T &data);
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

static const int fmCreate = Fileout; //�������£��ļ�������Ѵ����ļ���ԭ�ļ�������գ��������ļ����������ļ���
static const int fmOpenRead = Filein;//ֻ����ʽ���ļ� -- �ļ�������ڣ�ͨ��ָ���α꣬��ȡ��Ӧλ�õ����ݣ�
static const int fmOpenWrite = Fileout | File_Nocreate ; // ��ԭ�ļ���β��д�����ݣ����ԭ�ļ������ڣ�������ֻ�����ļ�β��д�룬����д�뵽ָ����λ�ã�
static const int fmOpenReadWriteBeg = Filein | Fileout  ; // �ļ�������ڣ����򱨴�,�α�λ���ļ�ͷ�����������λ��д��Ͷ�ȡ��
static const int fmOpenReadWriteEnd = Filein | Fileout | Fileapp; // �ļ�������ڣ����򱨴��α�λ���ļ�β�����������λ��д��Ͷ�ȡ��

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
private:
	fstream* pfstream;

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
		UnicodeString wstr(10,L'\0');//����10�ַ��Ĵ洢�ռ�
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
	char* pMemory;
	bool c_IsCreator;
	UnicodeString c_ShareName;

};