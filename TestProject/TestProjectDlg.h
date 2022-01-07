
// TestProjectDlg.h : 头文件
//

#pragma once
#include "PrintThread.h"
#include "afxwin.h"

// CTestProjectDlg 对话框
class CTestProjectDlg : public CDialogEx
{
// 构造
public:
	CTestProjectDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_TESTPROJECT_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持

	PrintThread *pt;
// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedButton2();
	afx_msg void OnBnClickedButton3();
	afx_msg void OnBnClickedButton4();
	afx_msg void OnBnClickedButton5();
	afx_msg void OnBnClickedButton6();
	CEdit m_edit1;
};



class A {
public:
	A();
	virtual ~A();

	virtual int sub()
	{
		return 1;
	}

	int  gg()
	{
		return 55;
	}
	virtual int Print()
	{
		gg();
		return sub();
	}

	int read()
	{
		return Print();
	}
};




class MyC :public A
{
public:
	MyC();
	~MyC();

	virtual int Print()
	{
		return A::Print();
	}

	virtual int sub()
	{
		return 2;
	}

	int  gg()
	{
		return 55;
	}
private:

};

