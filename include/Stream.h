#pragma once


class AFX_EXT_CLASS Stream
{
public:
	Stream();
	virtual ~Stream();
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
	void Seek(size_t offset, SeekDirection & direction);
	void SetCursor(size_t cursor); //设置游标位置
	size_t GetCursor();
	void SetSize(size_t size);
	size_t GetSize();
	char* Memory();

	size_t Write(_In_ void* src, size_t count);
	size_t Read(_Out_ void* dest, size_t count);
private:
	size_t _step;	//扩容步长
	size_t _size;	//数据大小
	size_t _cap;	//容量大小
	size_t _cursor;//游标
	void* _pMemory;	//头指针

};

class AFX_EXT_CLASS FileStream :public Stream
{
public:
	FileStream();
	virtual ~FileStream();
};

