
// TestProjectDlg.h : ͷ�ļ�
//

#pragma once
#include "PrintThread.h"
#include "afxwin.h"

// CTestProjectDlg �Ի���
class CTestProjectDlg : public CDialogEx
{
// ����
public:
	CTestProjectDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_TESTPROJECT_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��

	PrintThread *pt;
// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
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

