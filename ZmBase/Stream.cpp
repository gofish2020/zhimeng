#include "stdafx.h"
#include <exception>
#include "..\include\Stream.h"
#include "..\include\utils.h"
#include "..\include\Logger.h"
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
	size_t len = src.Len();//�洢�ռ�
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
	size_t maxSize = GetCursor() + count;//д������
	if (maxSize > GetSize())//����size
		SetSize(maxSize);
	memcpy(Memory() + GetCursor(), src, count);
	SetCursor(maxSize);
	return count;
}

size_t MemoryStream::Read(_Out_ void* dest, size_t count)
{
	size_t maxSize = GetCursor() + count; //��������
	if (maxSize > GetSize())
		count = GetSize() - GetCursor();
	memcpy(dest, Memory() + GetCursor(), count);
	SetCursor(GetCursor() + count);
	return count;
}

///////////////////�ļ���///////////////////
FileStream::FileStream()
{

}

FileStream::~FileStream()
{

}
///////////////////�����ڴ���///////////////////
ShareMemoryStream::ShareMemoryStream(UnicodeString Name, DWORD losize)
{
	//���������ڴ����
	SECURITY_ATTRIBUTES sa;
	SECURITY_DESCRIPTOR sd;
	InitializeSecurityDescriptor(&sd, SECURITY_DESCRIPTOR_REVISION);
	SetSecurityDescriptorDacl(&sd, TRUE, NULL, FALSE);
	sa.nLength = sizeof(SECURITY_ATTRIBUTES);
	sa.bInheritHandle = TRUE;
	sa.lpSecurityDescriptor = &sd;
	c_handle = CreateFileMapping(INVALID_HANDLE_VALUE, &sa, PAGE_READWRITE, 0, losize + 2*sizeof(UINT32), Name.c_str());
	if (c_handle == nullptr)
	{
		Painc(GetLastErrorStr(L"CreateFileMapping", Name));
	}
	pSize = (UINT32 *)MapViewOfFile(c_handle, FILE_MAP_WRITE | FILE_MAP_READ, 0, 0, 0); 
	if (pSize == nullptr)
	{
		Painc(GetLastErrorStr(L"MapViewOfFile", Name));
	}
	*pSize = losize;//��һ��4�ֽ�Ϊ�����ڴ�ռ��С(ʵ����Ч�Ŀռ��С)
	pCursor = pSize + 1;
	*pCursor = 0;//�ڶ���4�ֽ��趨�α�λ��
	pMemory = reinterpret_cast<char*>(pCursor + 1); //�ӵ�8�ֽڿ�ʼ�洢����
	c_IsCreator = true;
	c_ShareName = Name;
}

ShareMemoryStream::ShareMemoryStream(UnicodeString Name)
{
	//��ȡ�����ڴ����
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
	pMemory = reinterpret_cast<char*>(pCursor + 1); //�ӵ�8�ֽڿ�ʼ�洢����
	c_IsCreator = false;
	c_ShareName = Name;
}

ShareMemoryStream::~ShareMemoryStream()
{
	try
	{
		if (c_IsCreator)
		{
			//�����߸�������
			UnmapViewOfFile(pSize);
			CloseHandle(c_handle);
		}
	}
	catch (const std::exception& e)
	{
		LOGEXCEPTION(e);
	}
	catch (...)
	{
		LOGERROR("ShareMemoryStream::~ShareMemoryStream", "ϵͳδ֪����");
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
