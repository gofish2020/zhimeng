#pragma once

class AFX_EXT_CLASS XEvent
{
public:
	XEvent(); //Ĭ�����ź�
	~XEvent();
	void Set();//���ź�
	void UnSet();//���ź�
	void Wait();//�ȴ����źţ���������
private:
	HANDLE c_Event;
};