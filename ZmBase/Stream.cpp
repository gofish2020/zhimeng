#include "stdafx.h"
#include <exception>
#include "..\include\Stream.h"

////////////////������/////////////////////
Stream::Stream()
{
}


Stream::~Stream()
{
}


//////////////////�ڴ���////////////////////
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
	if (size > _cap) //��������������
	{
		int num = size / _step;
		if (size % _step != 0)
			num++;
		_cap = num * _step;//������С
		if (!_pMemory)
			_pMemory = malloc(_cap);
		else
			_pMemory = realloc(_pMemory, _cap);
		if (_pMemory == nullptr)
			throw std::exception("SetSize �ڴ�������");
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
	size_t maxCursor = _cursor + count;//д������
	if (maxCursor > GetSize())//����size
		SetSize(maxCursor);
	memcpy(Memory() + _cursor, src, count);
	SetCursor(maxCursor);
	return count;
}

size_t MemoryStream::Read(_Out_ void* dest, size_t count)
{
	size_t maxCursor = _cursor + count; //��������
	if (maxCursor > GetSize())
		count = GetSize() - _cursor;
	memcpy(dest, Memory() + _cursor, count);
	return count;
}

///////////////////�ļ���///////////////////
FileStream::FileStream()
{

}

FileStream::~FileStream()
{

}
