#include "stdafx.h"
#include <exception>
#include "..\include\Stream.h"

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

template<typename T>
MemoryStream& MemoryStream::operator<<(const T data)
{
	size_t count = sizeof(data);
	Write(reinterpret_cast<BYTE*>(&data), count);
	return *this;
}

template<typename T>
MemoryStream& MemoryStream::operator>>(T &data)
{
	size_t count = sizeof(data);
	Read(reinterpret_cast<BYTE*>(&data), count);
	return *this;
}

MemoryStream& MemoryStream::operator<<(const UnicodeString& src)
{
	size_t count = src.Len() * 2;
	Write(reinterpret_cast<BYTE*>(const_cast<wchar_t*>(src.c_str())), count);
	return *this;
}

MemoryStream& MemoryStream::operator>>(UnicodeString& src)
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

}

FileStream::~FileStream()
{

}
///////////////////共享内存类///////////////////
ShareMemoryStream::ShareMemoryStream(DWORD losize,UnicodeString Name)
{
	SECURITY_ATTRIBUTES sa;
	SECURITY_DESCRIPTOR sd;
	InitializeSecurityDescriptor(&sd, SECURITY_DESCRIPTOR_REVISION);
	SetSecurityDescriptorDacl(&sd, TRUE, NULL, FALSE);
	sa.nLength = sizeof(SECURITY_ATTRIBUTES);
	sa.bInheritHandle = TRUE;
	sa.lpSecurityDescriptor = &sd;
	c_handle = CreateFileMapping(INVALID_HANDLE_VALUE, &sa, PAGE_READWRITE, 0, losize, Name.c_str());
	if (c_handle == nullptr)
	{
		UnicodeString err = "CreateFileMapping failed ";
		throw std::exception(string(err).c_str());
	}

	FSize = (UINT32 *)MapViewOfFile(c_handle, FILE_MAP_WRITE | FILE_MAP_READ, 0, 0, 0);
	if (FSize == NULL)
	{
		//错误处理
		UnicodeString msg = L"MapViewOfFile() failed with error :" + Name;
		throw std::exception(string(msg).c_str());
	}
}

ShareMemoryStream::~ShareMemoryStream()
{

}
