// ZmBase.h : ZmBase DLL ����ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CZmBaseApp
// �йش���ʵ�ֵ���Ϣ������� ZmBase.cpp
//

class CZmBaseApp : public CWinApp
{
public:
	CZmBaseApp();

// ��д
public:
	virtual BOOL InitInstance();

	DECLARE_MESSAGE_MAP()
};
