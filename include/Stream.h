#pragma once


class AFX_EXT_CLASS Stream
{
public:
	Stream();
	virtual ~Stream();
};




//һ�������Ĵ洢�ռ�
class AFX_EXT_CLASS MemoryStream :public Stream
{
public:
	MemoryStream();
	virtual ~MemoryStream();
};

class AFX_EXT_CLASS FileStream :public Stream
{
public:
	FileStream();
	virtual ~FileStream();
};

