
// TestProject.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CTestProjectApp: 
// �йش����ʵ�֣������ TestProject.cpp
//

class CTestProjectApp : public CWinApp
{
public:
	CTestProjectApp();

// ��д
public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CTestProjectApp theApp;