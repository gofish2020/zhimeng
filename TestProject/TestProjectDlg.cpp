
// TestProjectDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "TestProject.h"
#include "TestProjectDlg.h"
#include "afxdialogex.h"
#include "..\include\XString.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// ����Ӧ�ó��򡰹��ڡ��˵���� CAboutDlg �Ի���

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

// ʵ��
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CTestProjectDlg �Ի���



CTestProjectDlg::CTestProjectDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_TESTPROJECT_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CTestProjectDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CTestProjectDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON1, &CTestProjectDlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, &CTestProjectDlg::OnBnClickedButton2)
	ON_BN_CLICKED(IDC_BUTTON3, &CTestProjectDlg::OnBnClickedButton3)
	ON_BN_CLICKED(IDC_BUTTON4, &CTestProjectDlg::OnBnClickedButton4)
END_MESSAGE_MAP()


// CTestProjectDlg ��Ϣ�������

BOOL CTestProjectDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// ��������...���˵�����ӵ�ϵͳ�˵��С�

	// IDM_ABOUTBOX ������ϵͳ���Χ�ڡ�
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// ���ô˶Ի����ͼ�ꡣ  ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	// TODO: �ڴ���Ӷ���ĳ�ʼ������

	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

void CTestProjectDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ  ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CTestProjectDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // ���ڻ��Ƶ��豸������

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ʹͼ���ڹ����������о���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// ����ͼ��
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
HCURSOR CTestProjectDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CTestProjectDlg::OnBnClickedButton1()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������

	pt = new PrintThread();
	pt->Resume();
}


void CTestProjectDlg::OnBnClickedButton2()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������

	pt->Terminate();
}


void CTestProjectDlg::OnBnClickedButton3()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	pt->Terminate();
}


void CTestProjectDlg::OnBnClickedButton4()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������

// 	UnicodeString(); //���ַ�
// 	UnicodeString(const char*);
// 	UnicodeString(const wchar_t*, int); //��ȡ�ַ�
// 	UnicodeString(const wchar_t*); //ֱ�ӽ�ȡ��null
// 	UnicodeString(const wchar_t); //ֻ�ظ�һ��
// 	UnicodeString(int, const wchar_t); //�ظ��ַ�
// 	UnicodeString(const wstring);
// 	UnicodeString(const string);
// 	UnicodeString(char);
// 	UnicodeString(short);
// 	UnicodeString(int);
// 	UnicodeString(unsigned int);
// 	UnicodeString(long);
// 	UnicodeString(unsigned long);
// 	UnicodeString(__int64);
// 	UnicodeString(unsigned __int64);
// 	UnicodeString(float);
// 	UnicodeString(double);
// 	UnicodeString(long double);


	char* cPoint = "123�й�abc";
	wchar_t *wPoint = L"123�й�abc";
	string str = "123�й�abc";
	wstring wstr = L"123�й�abc";


	UnicodeString a;
	UnicodeString b(cPoint);
	UnicodeString c(wPoint);
	UnicodeString d(wPoint,4);
	UnicodeString e(L'b');
	UnicodeString f(3,L'a');
	UnicodeString g(str);
	UnicodeString h(wstr);

	short si = 12;
	int i = 14;
	unsigned int ui = 15;
	long int li = 16;
	unsigned long int uli = 17;
	__int64 i64 = 18;
	unsigned __int64 ui64 = 19;
	float fl = 1.01;
	double db = 1.022211;
	long double ldb = 92.19293324234;

	
	a = UnicodeString(si);
	a = UnicodeString(i);
	a = UnicodeString(ui);
	a = UnicodeString(li);
	a = UnicodeString(uli);
	a = UnicodeString(i64);
	a = UnicodeString(ui64);
	a = UnicodeString(fl);
	a = UnicodeString(db);
	a = UnicodeString(ldb);
	a.uprintf_s(L"%lg", ldb);



// 	UnicodeString& operator=(const wstring);
// 	UnicodeString& operator=(const string);
// 	UnicodeString& operator=(const char*);
// 	UnicodeString& operator=(const wchar_t*);
// 	UnicodeString& operator=(const UnicodeString&);
// 	UnicodeString operator+(const wstring);
// 	UnicodeString operator+(const string);
// 	UnicodeString operator+(const char*);
// 	UnicodeString operator+(const wchar_t*);
// 	UnicodeString operator+(const UnicodeString &);



	a = wstr;
	a = str;
	a = cPoint;
	a = wPoint;
	a = b;
	a = b + f;
	a = b + wstr;
	a = b + str;
	a = b + cPoint;
	a = b + wPoint;

	a = "����&��&";
	vector<UnicodeString>result;
	a.Split(result, L"&");




	a = L"2001,sdkf";
	int ii = a.ToInt();

	a = L"40c3";
	ii = a.ToInt(16);
	a = L"-10010110001";
	ii = a.ToInt(2);
	unsigned int ssss = a.ToUInt(2);
	a = L"0x7f";
	ii = a.ToInt(16);

	a = L"1.2";
	double sssf = a.ToDouble();
}
