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
//一段连续的存储空间 https://blog.csdn.net/qq_38810767/article/details/85265541
class AFX_EXT_CLASS MemoryStream :public Stream
{
public:
	MemoryStream(size_t step = 1 << 12); // 步长:4KB递增
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
	//字符编码GB2312
	MemoryStream &operator <<(const string& src)
	{
		size_t count = src.length();//字节数
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
	//字符编码UTF-16
	MemoryStream& operator<<(const UnicodeString& src)
	{
		size_t count = src.Len() * 2;
		Write(reinterpret_cast<BYTE*>(const_cast<wchar_t*>(src.c_str())), count);
		return *this;
	}

	MemoryStream& operator>>(UnicodeString& src)
	{
		size_t len = src.Len();//存储空间
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

static const int fmOpenNew = Fileout; //创建新文件，游标位于首部
static const int fmOpenRead = Filein | Fileapp ;//不存在创建文件，存在直接打开文件，游标位于首部，【只能读取】
static const int fmOpenWrite = Fileout | Fileapp | Fileate; // 不存在创建文件，存在直接打开文件，游标位于尾部，【只能写入】
static const int fmOpenReadWrite = Filein | Fileout | Fileapp | Fileate; // 不存在创建、存在打开文件，游标位于尾部【可在任意的位置写入和读取】

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


	//字符编码UTF-8
	void WriteStringUTF8(const UnicodeString& wstr);
	void ReadStringUTF8(UnicodeString& wstr);
	//字符编码UTF-16
	FileStream& operator<< (const UnicodeString& wstr);
	FileStream& operator>> (UnicodeString& wstr);

	//字符编码GB2312
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
		这里的wstr必须要先分配存储空间 
		UnicodeString wstr(10,L'\0');//分配10字符的存储空间,表示读取10个字符
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
	UINT32* pRefCount; //引用计数
	char* pMemory;
	bool c_IsCreator;
	UnicodeString c_ShareName;

};