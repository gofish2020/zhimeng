
// TestProjectDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "TestProject.h"
#include "TestProjectDlg.h"
#include "afxdialogex.h"
#include "..\include\XString.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
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


// CTestProjectDlg 对话框



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


// CTestProjectDlg 消息处理程序

BOOL CTestProjectDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
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

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
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

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CTestProjectDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CTestProjectDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CTestProjectDlg::OnBnClickedButton1()
{
	// TODO: 在此添加控件通知处理程序代码

	pt = new PrintThread();
	pt->Resume();
}


void CTestProjectDlg::OnBnClickedButton2()
{
	// TODO: 在此添加控件通知处理程序代码

	pt->Terminate();
}


void CTestProjectDlg::OnBnClickedButton3()
{
	// TODO: 在此添加控件通知处理程序代码
	pt->Terminate();
}


void CTestProjectDlg::OnBnClickedButton4()
{
	// TODO: 在此添加控件通知处理程序代码

// 	UnicodeString(); //空字符
// 	UnicodeString(const char*);
// 	UnicodeString(const wchar_t*, int); //截取字符
// 	UnicodeString(const wchar_t*); //直接截取到null
// 	UnicodeString(const wchar_t); //只重复一次
// 	UnicodeString(int, const wchar_t); //重复字符
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


	char* cPoint = "123中国abc";
	wchar_t *wPoint = L"123中国abc";
	string str = "123中国abc";
	wstring wstr = L"123中国abc";


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

	a = "人民&中&";
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
