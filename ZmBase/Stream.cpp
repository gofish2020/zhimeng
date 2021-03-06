#include "stdafx.h"
#include <exception>
#include "..\include\Stream.h"
#include "..\include\utils.h"
#include "..\include\Logger.h"
////////////////抽象类/////////////////////
Stream::Stream()
{
}


Stream::~Stream()
{
}


//////////////////内存类////////////////////
MemoryStream::MemoryStream(size_t step):_cap(0),_size(0),_cursor(0),_pMemory(nullptr)
{
	_step = step;
}

MemoryStream::~MemoryStream()
{
	Free();
}



void MemoryStream::Free()
{
	if (_pMemory)
	{
		free(_pMemory);
		_pMemory = nullptr;
	}
	_cap = 0;
	_size = 0;
	_cursor = 0;
}

void MemoryStream::Zero()
{
	if (_pMemory)
		memset(_pMemory, 0, _size);
}

void MemoryStream::Seek(size_t offset, SeekDirection & direction)
{
	if (direction == SeekDirection::SeekBegin)
		SetCursor(offset);
	else if (direction == SeekDirection::SeekCurrent)
		SetCursor(GetCursor() + offset);
	else if (direction == SeekDirection::SeekEnd)
		SetCursor(GetSize() - offset);
}

void MemoryStream::Skip(size_t byteNums)
{
	SetCursor(GetCursor() + byteNums);
}

void MemoryStream::SetCursor(size_t cursor)
{
	if (cursor > GetSize())
		cursor = GetSize();
	else
		_cursor = cursor;
}

size_t MemoryStream::GetCursor()
{
	return _cursor;
}

void MemoryStream::SetSize(size_t size)
{
	if (size > _cap) //容量不够，扩容
	{
		int num = size / _step;
		if (size % _step != 0)
			num++;
		_cap = num * _step;//容量大小
		if (!_pMemory)
			_pMemory = malloc(_cap);
		else
			_pMemory = realloc(_pMemory, _cap);
		if (_pMemory == nullptr)
			throw std::exception("SetSize 内存分配错误");
	}
	_size = size;
	SetCursor(GetCursor());
}

size_t MemoryStream::GetSize()
{
	return _size;
}

char* MemoryStream::Memory()
{
	return (char*)_pMemory;
}


size_t MemoryStream::Write(_In_ void* src, size_t count)
{
	size_t maxSize = GetCursor() + count;//写入数据
	if (maxSize > GetSize())//超出size
		SetSize(maxSize);
	memcpy(Memory() + GetCursor(), src, count);
	SetCursor(maxSize);
	return count;
}

size_t MemoryStream::Read(_Out_ void* dest, size_t count)
{
	size_t maxSize = GetCursor() + count; //读出数据
	if (maxSize > GetSize())
		count = GetSize() - GetCursor();
	memcpy(dest, Memory() + GetCursor(), count);
	SetCursor(GetCursor() + count);
	return count;
}

///////////////////文件类///////////////////
FileStream::FileStream()
{
	pfstream = new fstream();
}

FileStream::FileStream(UnicodeString fileName, int mode, int prot)
{
	pfstream = new fstream(fileName.c_str(), mode, prot);
	if (!pfstream->is_open())
		Painc("new fstream failed");
	_mode = mode;
}

void FileStream::Open(UnicodeString fileName, int mode, int prot )
{
	pfstream->open(fileName.c_str(), mode, prot);
	if (!pfstream->is_open())
		Painc("pfstream->open failed");
	_mode = mode;
}

void FileStream::Close()
{
	if (pfstream)
	{
		pfstream->flush();
		pfstream->close();
		delete pfstream;
		pfstream = nullptr;
	}
		
}

void FileStream::Seek(size_t offset, SeekDirection direction)
{
	pfstream->seekp(offset,direction);
}

size_t FileStream::GetCursor()
{
	int a = pfstream->tellg();//读取
	int b = pfstream->tellp();
	return b; //写入
}

void FileStream::SetCursor(size_t Pos)
{
	Seek(Pos, SeekBegin);
}


size_t FileStream::GetSize()
{
	int tempPos = pfstream->tellp();
	Seek(0, SeekEnd);
	int size = pfstream->tellp();
	Seek(tempPos, SeekBegin);
	return size;
}

void FileStream::SetSize(size_t size)
{
	//Seek(size, SeekBegin);
}

size_t FileStream::Write(_In_ void* src, size_t count)
{
	if (int(Fileout) == int(_mode & Fileout)) //包含写属性
	{
		pfstream->write((char*)src, count);
		return count;
	}
	return 0; //do nothing
}

size_t FileStream::Read(_Out_ void* dest, size_t count)
{
	if (int(Filein) == int(_mode & Filein)  ) //包含读属性
	{
		int res = pfstream->read((char*)dest, count).gcount();
		if (pfstream->eof())
			pfstream->clear();
		return res;
	}
	return count;
}

void FileStream::WriteStringUTF8(const UnicodeString& wstr)
{
	*pfstream << wstr.Toutf8().c_str();
}

void FileStream::ReadStringUTF8(UnicodeString& wstr)
{
	string temp;
	std::getline(*pfstream, temp);
	wstr.utf8(temp.c_str());
}

FileStream& FileStream::operator<<( const UnicodeString& wstr)
{
	Write((char*)wstr.c_str(), wstr.size() * 2);
	return *this;
}

FileStream& FileStream::operator>>(UnicodeString& wstr)
{
	if (wstr.size() == 0)
	{
		return *this;
	}
	Read((char*)wstr.c_str(), wstr.size() * 2);

	return *this;
}

FileStream& FileStream::operator >> (string& src)
{
	if (src.size() == 0)
	{
		return *this;
	}
	Read((char*)src.c_str(), src.size());
	return *this;
}

FileStream& FileStream::operator<<(const string& src)
{
	Write((char*)src.c_str(), src.size());
	return *this;
}

FileStream::~FileStream()
{
	Close();
}
///////////////////共享内存类///////////////////
ShareMemoryStream::ShareMemoryStream(UnicodeString Name, DWORD losize)
{
	//创建共享内存对象
	SECURITY_ATTRIBUTES sa;
	SECURITY_DESCRIPTOR sd;
	InitializeSecurityDescriptor(&sd, SECURITY_DESCRIPTOR_REVISION);
	SetSecurityDescriptorDacl(&sd, TRUE, NULL, FALSE);
	sa.nLength = sizeof(SECURITY_ATTRIBUTES);
	sa.bInheritHandle = TRUE;
	sa.lpSecurityDescriptor = &sd;
	c_handle = CreateFileMapping(INVALID_HANDLE_VALUE, &sa, PAGE_READWRITE, 0, losize + 3*sizeof(UINT32), Name.c_str());
	if (c_handle == nullptr)
	{
		Painc(GetLastErrorStr(L"CreateFileMapping", Name));
	}
	pSize = (UINT32 *)MapViewOfFile(c_handle, FILE_MAP_WRITE | FILE_MAP_READ, 0, 0, 0); 
	if (pSize == nullptr)
	{
		Painc(GetLastErrorStr(L"MapViewOfFile", Name));
	}
	*pSize = losize;//第一个4字节为共享内存空间大小(实际有效的空间大小)
	pCursor = pSize + 1;
	*pCursor = 0;//第二个4字节设定游标位置
	pRefCount = pSize + 2; //第三个4字节，引用计数，
	*pRefCount =  1;
	pMemory = reinterpret_cast<char*>(pSize + 3); //从第12字节开始存储数据
	c_IsCreator = true;
	c_ShareName = Name;
}

ShareMemoryStream::ShareMemoryStream(UnicodeString Name)
{
	//获取共享内存对象
	c_handle = OpenFileMapping(FILE_MAP_WRITE | FILE_MAP_READ, true, Name.c_str());
	if (c_handle == nullptr)
	{
		Painc(GetLastErrorStr(L"OpenFileMapping", Name));
	}
	pSize = (UINT32 *)MapViewOfFile(c_handle, FILE_MAP_WRITE | FILE_MAP_READ, 0, 0, 0);
	if (pSize == nullptr)
	{
		Painc(GetLastErrorStr(L"MapViewOfFile", Name));
	}
	pCursor = pSize + 1;
	pRefCount = pSize + 2;
	*pRefCount = (*pRefCount) + 1;
	pMemory = reinterpret_cast<char*>(pSize + 3); //从第12字节开始存储数据
	c_IsCreator = false;
	c_ShareName = Name;
}

ShareMemoryStream::~ShareMemoryStream()
{
	try
	{
		UnmapViewOfFile(pSize);
		//*pRefCount -= 1;
		if (c_IsCreator)
		{
			//创建者负责销毁
			CloseHandle(c_handle);
		}
	}
	catch (const std::exception& e)
	{
		LOGEXCEPTION(e);
	}
	catch (...)
	{
		LOGERROR("ShareMemoryStream::~ShareMemoryStream", "系统未知错误");
	}
}

size_t ShareMemoryStream::Write(_In_ void* src, size_t count)
{
	int size = GetSize() - GetCursor();
	if (count > size)
		count = size;
	memcpy(Memory() + GetCursor(), src, count);
	SetCursor(GetCursor() + count);
	return count;
}

size_t ShareMemoryStream::Read(_Out_ void* dest, size_t count)
{
	int size = GetSize() - GetCursor();
	if (count > size)
		count = size;
	memcpy(dest, Memory() + GetCursor(), count);
	SetCursor(GetCursor() + count);
	return count;
}

ShareMemoryStream& ShareMemoryStream::operator<<(const UnicodeString& wstr)
{
	int count = wstr.Len()* sizeof(wchar_t);
	if (count > GetSize() - GetCursor())
		Painc(L"ShareMemoryStream write out of memory");
	Write(const_cast<wchar_t*>(wstr.c_str()), count);
	return *this;
}

ShareMemoryStream& ShareMemoryStream::operator>>(UnicodeString& wstr)
{
	int count = wstr.Len()* sizeof(wchar_t);
	if (count > GetSize() - GetCursor())
		Painc(L"ShareMemoryStream read out of memory");
	Read(const_cast<wchar_t*>(wstr.c_str()), count);
	return *this;
}

size_t ShareMemoryStream::GetCursor()
{
	return *pCursor;
}
void ShareMemoryStream::SetCursor(size_t cursor)
{
	if (cursor > GetSize())
		cursor = GetSize();
	*pCursor = cursor;
}

size_t ShareMemoryStream::GetSize()
{
	return *pSize;
}

void ShareMemoryStream::SetSize(size_t size)
{
	//do nothing
}

char* ShareMemoryStream::Memory()
{
	return pMemory;
}

UnicodeString ShareMemoryStream::ShareName()
{
	return c_ShareName;
}


void QueueStream::AddQueue()
{
	MemoryStream *temp = nullptr;
	if (!cache.empty())
	{
		temp = cache.front();
		cache.pop();
	}
	else
	{
		temp = new MemoryStream;
		temp->SetSize(gc_streamSize);
	}
	data.push(temp);
	tailPos = 0;
}

void QueueStream::SubQueue()
{
	MemoryStream* temp = data.front();
	data.pop();
	if (cache.size() < 4)
		cache.push(temp);
	else
		delete temp;
	headPos = 0;
}


QueueStream::QueueStream(int size)
{
	gc_streamSize = size;
	MemoryStream *temp = new MemoryStream;
	temp->SetSize(gc_streamSize);
	data.push(temp);
	headPos = 0;
	tailPos = 0;
	c_Size = 0;
}



QueueStream::~QueueStream()
{
	while (!cache.empty())
	{
		delete (MemoryStream*)(cache.front());
		cache.pop();
	}
	while (!data.empty())
	{
		delete (MemoryStream*)(data.front());
		data.pop();
	}
}

//
size_t QueueStream::Write(_In_ void* src, size_t count)
{
	size_t size = count;
	size_t pos = 0;
	while (1)
	{
		if (size > (gc_streamSize - tailPos))
		{
			memcpy(WriteMemory(), (char*)src + pos, gc_streamSize - tailPos);
			size = size - gc_streamSize + tailPos; //剩余的待copy的数据量
			pos = pos + gc_streamSize - tailPos;//待copy数据指针位置
			AddQueue();
		}
		else
		{
			memcpy(WriteMemory(), (char*)src + pos, size);
			tailPos += size;
			if (tailPos >= gc_streamSize)
			{
				AddQueue();
			}
			break;
		}
	}
	c_Size += count;
	return count;
}

size_t QueueStream::Read(_Out_ void* dest, size_t count)
{
	if (count > c_Size)
	{
		Painc("out of stream size");
	}
	size_t size = count;
	size_t pos = 0;
	while (1)
	{
		if (data.size() == 1)
		{
			memcpy((char*)dest + pos, ReadMemory(), size);
			pos += size;//已经写入的数据偏移
			c_Size -= size; //剩余数据量
			headPos += size;//头指针偏移量
// 			if (headPos >= gc_streamSize)
// 			{
// 				SubQueue();
// 			}
			break;
		}
		else
		{
			size_t tempSize = gc_streamSize - headPos;
			if (size > tempSize) //不够,全部读完
			{
				memcpy((char*)dest + pos, ReadMemory(), tempSize);
				size -= tempSize;//还需要读取的数量
				c_Size -= tempSize;
				pos += tempSize;
				SubQueue();//这个块读完了，不要了
			}
			else //够了、正好读取
			{
				//size < = tempSize
				memcpy((char*)dest + pos, ReadMemory(), size);
				pos += size;//已经写入的数据偏移
				c_Size -= size; //剩余数据量
				headPos += size;//头指针偏移量
				if (headPos >= gc_streamSize)
				{
					SubQueue();
				}
				break;
			}
		}
	}
	return count;
}

size_t QueueStream::GetSize()
{
	return c_Size;
}

char* QueueStream::AllocateSize(size_t &count)
{
	if (gc_streamSize - tailPos < count)
	{
		count = gc_streamSize - tailPos;
	}
	return WriteMemory();
}

void QueueStream::UpdateSize(size_t count)
{
	c_Size += count;
	tailPos += count;
	if (tailPos >= gc_streamSize)
	{
		AddQueue();
	}
}

void QueueStream::SaveToStream(Stream& stream, int count)
{
	if (count > c_Size)
	{
		Painc("QueueStream::SaveToStream -->> out of stream size");
	}
	size_t size = count;
	
	while (1)
	{
		if (data.size() == 1)//只有一个，说明没有填充满 也就四tailPos不会>=gc_streamSize
		{
			stream.Write(ReadMemory(), size);
			c_Size -= size; //剩余数据量
			headPos += size;//头指针偏移量
// 			if (headPos >= gc_streamSize) //这里不会执行到
// 			{
// 				SubQueue();
// 			}
			break;
		}
		else
		{
			size_t tempSize = gc_streamSize - headPos;
			if (size > tempSize) //不够,全部读完
			{
				stream.Write(ReadMemory(), tempSize);
				size -= tempSize;//还需要读取的数量
				c_Size -= tempSize;
				SubQueue();//这个块读完了，不要了
			}
			else //够了、正好读取
			{
				//size < = tempSize
				stream.Write(ReadMemory(), size);
				c_Size -= size; //剩余数据量
				headPos += size;//头指针偏移量
				if (headPos >= gc_streamSize)
				{
					SubQueue();
				}
				break;
			}
		}
	}
}

QueueStream& QueueStream::operator>>(string& str)
{
	Read((char*)str.c_str(), str.length());
	return *this;
}

char* QueueStream::ReadMemory()
{
	return (char*)((MemoryStream*)(data.front())->Memory()) + headPos;
}

char* QueueStream::WriteMemory()
{
	return (char*)((MemoryStream*)(data.back())->Memory()) + tailPos;
}
