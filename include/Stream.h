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
//一段连续的存储空间 https://blog.csdn.net/qq_38810767/article/details/85265541
class AFX_EXT_CLASS MemoryStream :public Stream
{
public:
	MemoryStream(size_t step = 1 << 12 ); // 步长:4KB递增
	virtual ~MemoryStream();

	void Free(); //释放空间
	void Zero(); //分配的空间初始化为0
	void Seek(size_t offset, SeekDirection& direction);
	void Skip(size_t byteNums); //游标跳跃byteNums字节
	void SetCursor(size_t cursor); //设置游标位置
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
	size_t _step;	//扩容步长
	size_t _size;	//数据大小
	size_t _cap;	//容量大小
	size_t _cursor;//游标
	void* _pMemory;	//头指针
};

enum FileMode
{	
	Filein = 0x01, //文件以输入模式打开，磁盘-->>内存
	Fileout = 0x02,//文件以输出模式打开，内存-->>磁盘
	Fileate = 0x04,//文件打开后，定位到文件尾
	Fileapp = 0x08,//追加模式打开文件
	Filetrunc = 0x10,//如果文件存在，把文件长度设置为0
	File_Nocreate = _IOS_Nocreate,//不创建文件，如果文件不存在，打开失败
	File_Noreplace = _IOS_Noreplace,//不覆盖文件，如果文件存在，打开失败
	Filebinary = _IOSbinary//二进制打开文件
};

static const int fmCreate = Fileout; //创建（新）文件，如果已存在文件，原文件将被清空，不存在文件（创建新文件）
static const int fmOpenRead = Filein;//只读方式打开文件 -- 文件必须存在（通过指定游标，读取对应位置的数据）
static const int fmOpenWrite = Fileout | File_Nocreate ; // 在原文件的尾部写入数据（如果原文件不存在，报错）（只能在文件尾部写入，不能写入到指定的位置）
static const int fmOpenReadWriteBeg = Filein | Fileout  ; // 文件必须存在，否则报错,游标位于文件头（可在任意的位置写入和读取）
static const int fmOpenReadWriteEnd = Filein | Fileout | Fileapp; // 文件必须存在，否则报错，游标位于文件尾（可在任意的位置写入和读取）

//int prot 属性设定
#define _SH_DENYRW      0x10    //!其他的应用程序不能打开该文件
#define _SH_DENYWR      0x20    //!其他的应用程序只能以只读方式打开文件
#define _SH_DENYRD      0x30    //!其他的应用程序只能以只写方式打开文件
#define _SH_DENYNO      0x40    //!其他的应用程序可以以任何方式打开文件
#define _SH_SECURE      0x80    //!共享读取,独占写入(两个进程可以共同读，如果有一个写，另外一个不能打开)


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
		这里的wstr必须要先分配存储空间 
		UnicodeString wstr(10,L'\0');//分配10字符的存储空间
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