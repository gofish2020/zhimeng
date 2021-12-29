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
//һ�������Ĵ洢�ռ� https://blog.csdn.net/qq_38810767/article/details/85265541
class AFX_EXT_CLASS MemoryStream :public Stream
{
public:
	MemoryStream(size_t step = 1 << 12 ); // ����:4KB����
	virtual ~MemoryStream();

	void Free(); //�ͷſռ�
	void Zero(); //����Ŀռ��ʼ��Ϊ0
	void Seek(size_t offset, SeekDirection & direction);
	void SetCursor(size_t cursor); //�����α�λ��
	size_t GetCursor();
	void SetSize(size_t size);
	size_t GetSize();
	char* Memory();

	size_t Write(_In_ void* src, size_t count);
	size_t Read(_Out_ void* dest, size_t count);
private:
	size_t _step;	//���ݲ���
	size_t _size;	//���ݴ�С
	size_t _cap;	//������С
	size_t _cursor;//�α�
	void* _pMemory;	//ͷָ��

};

class AFX_EXT_CLASS FileStream :public Stream
{
public:
	FileStream();
	virtual ~FileStream();
};

