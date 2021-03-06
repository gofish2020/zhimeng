
// TestProjectDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "TestProject.h"
#include <xstring>
#include "TestProjectDlg.h"
#include "afxdialogex.h"
#include "..\include\XString.h"
#include "..\include\DateTime.h"
#include "..\include\Stream.h"
#include "..\include\utils.h"
#include "..\include\Logger.h"
#include "..\include\XVariant.h"
#include "..\include\ProcessChan.h"
#include "..\include\ThreadPool.h"
#include "..\include\StringList.h"
#include "..\include\IniConfig.h"
#include "..\include\BaseSocket.h"
using namespace std;
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
	DDX_Control(pDX, IDC_EDIT1, m_edit1);
}

BEGIN_MESSAGE_MAP(CTestProjectDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON1, &CTestProjectDlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, &CTestProjectDlg::OnBnClickedButton2)
	ON_BN_CLICKED(IDC_BUTTON3, &CTestProjectDlg::OnBnClickedButton3)
	ON_BN_CLICKED(IDC_BUTTON4, &CTestProjectDlg::OnBnClickedButton4)
	ON_BN_CLICKED(IDC_BUTTON5, &CTestProjectDlg::OnBnClickedButton5)
	ON_BN_CLICKED(IDC_BUTTON6, &CTestProjectDlg::OnBnClickedButton6)
	ON_BN_CLICKED(IDC_BUTTON9, &CTestProjectDlg::OnBnClickedButton9)
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

// 	pt = new PrintThread();
// 	pt->Resume();
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

	ProcessChanNotify *pcn = new ProcessChanNotify;
	ProcessAccept *pa = new ProcessAccept (L"nash", m_hWnd, pcn);




	delete pa;
// 	// TODO: 在此添加控件通知处理程序代码
// 
// 	UnicodeString msg = L"123中说的11ff";
// 	string  ssfdsf = string(msg);
// // 	UnicodeString(); //空字符
// // 	UnicodeString(const char*);
// // 	UnicodeString(const wchar_t*, int); //截取字符
// // 	UnicodeString(const wchar_t*); //直接截取到null
// // 	UnicodeString(const wchar_t); //只重复一次
// // 	UnicodeString(int, const wchar_t); //重复字符
// // 	UnicodeString(const wstring);
// // 	UnicodeString(const string);
// // 	UnicodeString(char);
// // 	UnicodeString(short);
// // 	UnicodeString(int);
// // 	UnicodeString(unsigned int);
// // 	UnicodeString(long);
// // 	UnicodeString(unsigned long);
// // 	UnicodeString(__int64);
// // 	UnicodeString(unsigned __int64);
// // 	UnicodeString(float);
// // 	UnicodeString(double);
// // 	UnicodeString(long double);
// 
// 
// 	char* cPoint = "123中国abc";
// 	wchar_t *wPoint = L"123中国abc";
// 	string str = "123中国abc";
// 	wstring wstr = L"123中国abc";
// 
// 
// 	UnicodeString a;
// 	UnicodeString b(cPoint);
// 	UnicodeString c(wPoint);
// 	UnicodeString d(wPoint,4);
// 	UnicodeString e(L'b');
// 	UnicodeString f(3,L'a');
// 	UnicodeString g(str);
// 	UnicodeString h(wstr);
// 
// 	short si = 12;
// 	int i = 14;
// 	unsigned int ui = 15;
// 	long int li = 16;
// 	unsigned long int uli = 17;
// 	__int64 i64 = 18;
// 	unsigned __int64 ui64 = 19;
// 	float fl = 1.01;
// 	double db = 1.022211;
// 	long double ldb = 92.19293324234;
// 
// 	
// 	a = UnicodeString(si);
// 	a = UnicodeString(i);
// 	a = UnicodeString(ui);
// 	a = UnicodeString(li);
// 	a = UnicodeString(uli);
// 	a = UnicodeString(i64);
// 	a = UnicodeString(ui64);
// 	a = UnicodeString(fl);
// 	a = UnicodeString(db);
// 	a = UnicodeString(ldb);
// 	a.uprintf_s(L"%lg", ldb);
// 
// 
// 
// // 	UnicodeString& operator=(const wstring);
// // 	UnicodeString& operator=(const string);
// // 	UnicodeString& operator=(const char*);
// // 	UnicodeString& operator=(const wchar_t*);
// // 	UnicodeString& operator=(const UnicodeString&);
// // 	UnicodeString operator+(const wstring);
// // 	UnicodeString operator+(const string);
// // 	UnicodeString operator+(const char*);
// // 	UnicodeString operator+(const wchar_t*);
// // 	UnicodeString operator+(const UnicodeString &);
// 
// 
// 
// 	a = wstr;
// 	a = str;
// 	a = cPoint;
// 	a = wPoint;
// 	a = b;
// 	a = b + f;
// 	a = b + wstr;
// 	a = b + str;
// 	a = b + cPoint;
// 	a = b + wPoint;
// 
// 	a = "人民&中&";
// 	vector<UnicodeString>result;
// 	a.Split(result, L"&");
// 
// 
// 
// 
// 	a = L"2001,sdkf";
// 	int ii = a.ToInt();
// 
// 	a = L"40c3";
// 	ii = a.ToInt(16);
// 	a = L"-10010110001";
// 	ii = a.ToInt(2);
// 	unsigned int ssss = a.ToUInt(2);
// 	a = L"0x7f";
// 	ii = a.ToInt(16);
// 
// 	a = L"1.2";
// 	double sssf = a.ToDouble();
// 
// 	a = L"123&中华&abc&GGG&";
// 	int len = a.Len();
// 	bool isempty = a.IsEmpty();
// 	int pos = a.Pos("&");
// 	vector<UnicodeString>res;
// 	a.Split(res, "&");
// 	UnicodeString upper = a.ToUpper();
// 	UnicodeString lower = a.ToLower();
// 	UnicodeString substr = a.SubString(4, 2);
// 	UnicodeString replacestr = a.Replace("&", "|");
// 	a = L"123&中华&abc&GGG&   ";
// 	a = a.Trim();
// 	UnicodeString leftstr = a.Left(3);
// 	UnicodeString rightstr = a.Right(4);
// 
// 
// 	vector<UnicodeString>eles;
// 	eles.push_back("123");
// 	eles.push_back("123");
// 	eles.push_back("123");
// 	eles.push_back("123");
// 	a = Join(eles, "^");
}

struct MyStruct
{
	int a;
	MemoryStream ms;

};

void AddData(MyStruct *mystruct)
{
	char cchars[] = { 1,2,3 };
	mystruct->a = 1;
	mystruct->ms.Write(cchars, 3);
}
void CTestProjectDlg::OnBnClickedButton5()
{

	
	MyStruct *mystruct = new MyStruct;
	AddData(mystruct);


	ProcessSend *ps = new ProcessSend(L"nash");
	ps->SendInteger(22);
	ps->SendString(L"中国人112abc");
	// TODO: 在此添加控件通知处理程序代码
// 	UpdateData(true);
// 	if (mu.Create(L"xiaobaitu", false)) {
// 		mu.Wait();
// 		SetDlgItemText(IDC_EDIT1, L"your text");
// 		mu.Release();
// 	}
// 	UpdateData(FALSE);
// 	return;
// 	UnicodeString a = DateTime::NowDate().ToDateTimeStr();
// 	UnicodeString b = DateTime::NowDateTime().ToDateTimeStr();
// 
// 	DateTime c = DateTime(1990, 1, 1, 8, 0, 0);
// 	DateTime ss = c + DateTime(0, 0, 0, 1, 0, 0);
// 	a = ss.ToDateTimeStr();

// 
// 	UnicodeString curNow = DateTime::NowDateTime().ToDateStr();
// 	UnicodeString curNowInteger = DateTime::NowDateTime().ToDateTimeInteger();
// 
// 	DateTime a;
// 	DateTime b(L"2021-02-01");
// 	DateTime c(b);
// 	DateTime d(__time64_t(1640743993)); //2021-12-29 10:13:13
// 	DateTime e(2021, 2, 2, 1, 1, 1);
// 
// 	__time64_t ssss = d.UnixTimeStamp();
// 
// 	int year = d.Year();
// 	int month = d.Month();
// 	int day = d.Day();
// 	int hour = d.Hour();
// 	int minu = d.Minute();
// 	int second = d.Second();
// 	int dayofweek = d.DayOfWeek();
// 	int dayofyear = d.DayOfYear();
// 
// 
// 	UnicodeString res;
// 
// 	DateTime r = d + 1;
// 	res = r.ToDateTimeStr();
// 	DateTime r1 = d + 10.25;
// 	res = r1.ToDateTimeStr();
// 	DateTime r2 = d + e;
// 	res = r2.ToDateTimeStr();
// 
// 
// 	res = UnicodeString(d);
// 	/*
// 	DateTime();
// 	DateTime(const DateTime& src);
// 	DateTime(DATE src);
// 	DateTime(__time32_t src);
// 	DateTime(__time64_t src);
// 	DateTime(const SYSTEMTIME& systimeSrc);
// 	DateTime(const FILETIME& filetimeSrc);
// 	DateTime( int nYear,int nMonth,int nDay,int nHour,int nMin,int nSec);
// 	DateTime(const int src);
// 	virtual ~DateTime();
// 
// 	bool IsEmpty();
// 	int Year() const ;
// 	// Month of year (1 = January)
// 	int Month() const ;
// 	// Day of month (1-31)
// 	int Day() const ;
// 	// Hour in day (0-23)
// 	int Hour() const ;
// 	// Minute in hour (0-59)
// 	int Minute() const ;
// 	// Second in minute (0-59)
// 	int Second() const ;
// 	// Day of week (1 = Sunday, 2 = Monday, ..., 7 = Saturday)
// 	int DayOfWeek() const ;
// 	// Days since start of year (1 = January 1)
// 	int DayOfYear() const ;
// 	DateTime GetDate() const;
// 	DateTime GetTime() const;
// 	static DateTime NowDate();
// 	static DateTime NowDateTime();
// 	static DateTime NowTime();
// 	UnicodeString ToDateStr() const;
// 	UnicodeString ToDateTimeStr() const;
// 	UnicodeString ToTimeStr() const;
// 	UnicodeString ToDateInteger() const;
// 	UnicodeString ToDateTimeInteger() const;
// 
// 	DateTime& operator=(const UnicodeString& Src) throw();
// 	DateTime& operator=(const int Src) throw();
// 	DateTime operator +(const DateTime& rhs) const;
// 	DateTime operator +(const double rhs) const;
// 	DateTime operator +(const int rhs) const;
// 	DateTime operator-(const DateTime& rhs) const;
// 	DateTime operator-(const double rhs) const;
// 	DateTime operator-(const int rhs) const;
// 	DateTime &operator+=(const DateTime& Src);
// 	DateTime &operator+=(const double Src);
// 	DateTime &operator+=(const int Src);
// 	DateTime &operator-=(const DateTime& Src);
// 	DateTime &operator-=(const double Src);
// 	DateTime &operator-=(const int Src);
// 
// 	operator UnicodeString() const;
// 	operator int() const;
// 	
// 	*/
}


void TestError()
{
	
	Painc("1111");
	
}
/*
extern AFX_EXT_CLASS bool FileExist(const UnicodeString& file);
extern AFX_EXT_CLASS bool CreateDir(const UnicodeString& dirpath);
extern AFX_EXT_CLASS bool RemoveEmptyDir(const UnicodeString& dirpath);
extern AFX_EXT_CLASS bool DeleteDir(const UnicodeString& dirpath);
extern AFX_EXT_CLASS bool DirectoryExist(const UnicodeString& dirpath);
*/



// XVariant& operator =(const XVariant& src); //如果有自定义类型，需要修改该函数
// XVariant& operator =(const UnicodeString& src);
// XVariant& operator =(const string& src);
// XVariant& operator =(const DateTime& src);
// XVariant& operator=(char src);
// XVariant& operator=(BYTE src);
// XVariant& operator =(wchar_t src);
// XVariant& operator =(bool src);
// XVariant& operator =(int src);
// XVariant& operator =(short src);
// XVariant& operator =(long src);
// XVariant& operator =(__int64 src);
// XVariant& operator =(unsigned int src);
// XVariant& operator =(unsigned short src);
// XVariant& operator =(unsigned long src);
// XVariant& operator =(unsigned __int64 src);
// XVariant& operator =(float fltSrc);
// XVariant& operator =(double dblSrc);
// XVariant& operator =(char* src);
// XVariant& operator =(BYTE* src);
// XVariant& operator =(int* src);
// XVariant& operator =(long* src);
// XVariant& operator =(float* src);
// XVariant& operator =(double* src);
// XVariant& operator =(void *src);



class TaskJob : public ThreadTask
{
public:
	TaskJob() {};
	~TaskJob() {};
public:
	UnicodeString TaskName() { return L"1111"; };
	void OnExecute() {
		LOGINFO("11111", "1123213");
	};
};

void CTestProjectDlg::OnBnClickedButton6()
{



	bool ipIsOk = SelectSocket::IsLocalIPAddr(L"");
	return;
	char ns[3] = { 'a','b','c' };
	char ns22[3] = { 'c','d','e' };

	char nbbb[4] = {};
	char nbb1b[4] = {};
	char nbb2b[4] = {};
	QueueStream qs;
	qs.Write(ns, 1);
	qs.Write(ns22, 1);
	qs.Read(nbbb, 1);
	qs.Read(nbb1b, 1);
	qs.Read(nbb2b, 1);
	return;
	IniConfig ini(L"D:\\hh.ini");

	bool v2 = ini.ReadBool(L"Version", L"v2", false);
	double v1 = ini.ReadFloat(L"Version", L"v1", 0);
	UnicodeString v3 = ini.ReadString(L"Version", L"v3", false);

	ini.SaveToFile(L"D:\\12.ini");
	//FileStream fs(L"D:\\hh.ini", fmOpenNew);

	return;
	StringList sl;
	sl.LoadFromFile(L"D:\\HL7Config.ini");

	sl.SaveToFile(L"D:\\hh.ini");
// 	string sstr = "a1中国";
// 	int ssize = sstr.length();

	UnicodeString ustring;
	ustring = L"a1中国";
	UnicodeString sssdfsdf = ustring.SubString(9, -1);
	size_t pos = ustring.find(L'a',6);
	if ( pos == -1)
	{
		ustring = L"a1中国";
	}
	//int si = ustring.Len();
	return;
// 	UnicodeString ressss(4, L' ');
// 	FileStream ffs(L"d:\\1.txt", fmOpenReadWrite);
// 	ffs << L"a1中国";
// 	ffs.SetCursor(0);
// 	ffs >> ressss;
// 	ffs.Close();

	FileStream fstr(L"D:\\2.txt", fmOpenReadWrite);
	fstr << string("a1中国");
	fstr.SetCursor(0);
	string ressss1(fstr.GetSize(),'\0');
	fstr >> ressss1;
	return;


// 	Base * ba = new product();
// 	ba->real();


	

	ThreadPool::Instance()->SetTask(new TaskJob(), true, nullptr);


	return;
// 	BYTE by = 256;
// 	stoi(L"a", nullptr, 10);

	int iii =  atoi("a");


	XVariant a;
	UnicodeString tempStr = L"中国人呢";
	a.Clear();
	V_VT(&a) = VT_BSTR;
	a = tempStr;
	UnicodeString ustr = L"123中";
	a = ustr;


	vector<XVariant>li;

	li.push_back((int)12);
	li.push_back((float)2.0);
	li.push_back(L"中国人呢");
	li.push_back(DateTime(L"2012-02-01"));
	li.push_back(true);
	li.push_back(char(97));
	li.push_back((BYTE)128);

	MemoryStream ms;
	XVariant::VrArrayToStream(li, ms);
	ms.SetCursor(0);
	vector<XVariant>ree;
	XVariant::StreamToVrArray(ms, ree);

	UnicodeString dest;
	XVariant::VrArrayToString(li, dest);
	vector<XVariant>vvv;
	XVariant::StringToVrArray(dest, vvv);



// 	char ccc = -1;
// 	BYTE bbbb = 0xff;
// 	BYTE ffdf = ccc;
// 	unsigned long llll = (unsigned long)ccc;
// 	long lll2l = (long)bbbb;
// 	return;
// 	UnicodeString usss1(char(64));
// 	UnicodeString usss2(short(-1));
// 	UnicodeString usss(BYTE(-1));
// 	UnicodeString sdf(unsigned short(-1));
// 
// 
// 	return;
// 	DateTime dd = DateTime::NowDateTime();
// 	XVariant a;
// 	a = dd;
// 	
// 	string sstr = "重点123";
// 	a = sstr;
// 	char c = 'z';
// 	a = c;
// 
// 	BYTE b = 0x89;
// 	a = b;
// 
// 	wchar_t wc = L'中';
// 	a = wc;
// 	bool bl = true;
// 	a = bl;
// 	int i = 90;
// 	a = i;
// 	short si = 88;
// 	a = si;
// 
// 	long ll = 888;
// 	a = ll;
// 	__int64 _i = 123;
// 	a = _i;
// 	unsigned int ui = 123;
// 	a = ui;
// 	unsigned short us = 14343;
// 	a = us;
// 	unsigned long ul = 34343;
// 	a = ul;
// 	unsigned __int64 u_i = 234324;
// 	a = u_i;
// 	float ff = 1.002;
// 	a = ff;
// 	double db = 1.2201;
// 	a = db;
// 
// 	a = &ff;
// 	a = ustr.c_str();
// 	a = sstr.c_str();
	// XVariant& operator =(int src);
	// XVariant& operator =(short src);
	// XVariant& operator =(long src);
	// XVariant& operator =(__int64 src);
	// XVariant& operator =(unsigned int src);
	// XVariant& operator =(unsigned short src);
	// XVariant& operator =(unsigned long src);
	// XVariant& operator =(unsigned __int64 src);
	// XVariant& operator =(float fltSrc);
	// XVariant& operator =(double dblSrc);

	return;
// 	COleVariant csa;

// 
// 	MyC1 fd;
// 	fd.c = 1;
// 	fd.a = 2;
// 	fd.b = 3;
// 	fd.m = 4;
// 	fd.Init();
// 	return;
// 	
// 	if (mu.Create(L"xiaobaitu"))
// 	{
// 		mu.Wait();
// 		Sleep(5000);
// 		mu.Release();
// 	}
// 	
// 
// 
// 
// 
// 	return;
// 	INT64 GUID = CreateGUID();
// 	return;
// 	for (int i = 0; i < 500; i++)
// 	{
// 		LOGINFO("中国", "dsfjlsjflsdjflsdl好浪费是代理发号施令 色调分离123123123");
// 	}
// 
// 	return;
// 
// // 	UnicodeString path = GetApplicationFullName();
// // 	return;
// 	bool adfasdf = CreateDir(L"D:\\hello\\hello");
// 	DeleteDir(L"D:\\hello");
// 	vector<UnicodeString> res;
// 	TraverselFiles(L"D:\\hello",res,L"exe",true);
// 	TraverselFiles(L"D:\\hello", res, L"exe", false);
// 	TraverselFiles(L"D:\\hello", res,L"",false);
// 
// 	UnicodeString filePaht = L"D:\\1.log";
// 	bool isOk = FileExist(filePaht);
// 
// 	
// 
// 
// 	return;
// 	// TODO: 在此添加控件通知处理程序代码
// 
// 	FileStream fs1;
// 	fs1.Open("d:\\20220106.log", fmOpenRead);
// 	fs1.SetCursor(0);
// 	UnicodeString aa;
// 	fs1 >> aa;
// 
// 
// 	
// 
// 	char aaa[20] = { 0 };
// 	FileStream fs;
// 	fs.Open("d:\\2.log", fmOpenReadWrite | Filebinary, _SH_DENYNO);
// 	int pos = fs.GetCursor();
// 	fs.Read(aaa, 2);
// 	fs.Seek(0, SeekBegin);
// 	pos = fs.GetCursor();
// 	fs.Read(aaa, 2);
// 	pos = fs.GetCursor();
// 	fs.Write("aa", 2);
// 	fs.Seek(0, SeekBegin);
// 	pos = fs.GetCursor();
// 	fs.Read(aaa, 2);
// 	pos = fs.GetCursor();
// 	fs.Close();
// 	//fs.SetCursor(1);
// 	//int pos1 = fs.GetCursor();
// 	//fs.Write("aa", 2);
// 	//fs.Close();
// 
// 	//int size = fs.GetSize();
// 	//int pos = fs.GetCursor();
// 	fs.SetCursor(2);
// 	
// 	pos = fs.GetCursor();
// 	pos = fs.GetCursor();
// 	fs.Read(aaa, 2);
// 	fs.SetCursor(5 );
// 	pos = fs.GetCursor();
// 	pos = fs.GetCursor();
// 	fs.Read(aaa, 2);
// 	//fs.Seek(0, SeekEnd);
// 	fs.Write("aa", 2);
// 	pos = fs.GetCursor();
// 	pos = fs.GetCursor();
// 	fs.Close();
// 	fs.Read(aaa, 20);
// 	return;
// 
// 	ShareMemoryStream sms("nash-share", 2);
// 	sms << L"a";
// 
// 
// 	UnicodeString result(1, L'\0');
// 	sms.SetCursor(0);
// 	sms >> result;
// 
// 
// 
// 	UnicodeString sss(1, L'\0');
// 	ShareMemoryStream copyShare("nash-share");
// 	copyShare.SetCursor(0);
// 	copyShare >> sss;
// 
// // 	UINT32 c[10];
// // 	for (int i = 0; i < 10;i++)
// // 	{
// // 		*(c + i) = i;
// // 	}
// // 	UINT32 *ss = c + sizeof(UINT32);
// // 	UINT32 a = *(c + sizeof(UINT32));
// // 	int aaa = sizeof(wchar_t);
// // 	char str[7] = { 'a','b','d','&','1','2','3' };
// // 
// // 	UnicodeString us = L"abd&123";
// // 	MemoryStream ms;
// // 	ms.Write((void*)us.c_str(),us.Len() *2 );
// // 	ms.SetCursor(0);
// // 	wchar_t sss[10] = {'\0'};
// // 	ms.Read(sss, 10);
// // 
// // 	MyC mc;
// // 	mc.read();
// // 	int aaaa = mc.Print();
// 
// 	try
// 	{
// 		TestError();
// 	}
// 	catch (const std::exception& e)
// 	{
// 		LOGEXCEPTION(e);
// 	}
// 	catch (...)
// 	{
// 	}
// 
// 	UnicodeString err = GetLastErrorStr("GetLastErrorStr","sdefsdfds");
	
}


class XAcceptThread :public Thread
{
public:
	XAcceptThread(SelectSocket *handle);
	~XAcceptThread() {};

	void OnExecute();
	virtual UnicodeString ClassName() { return L""; };
private:
	SelectSocket * c_handle;
};

XAcceptThread::XAcceptThread(SelectSocket *handle)
{
	c_handle = handle;
}

void XAcceptThread::OnExecute()
{
	while(!IsTerminate())
	{ 
		MemoryStream ms;
		ms.SetSize(10);
		c_handle->RecvStream(ms, 10);
		Sleep(20);
	}
}


class XListerThread :public Thread
{
public:
	XListerThread(const SockSetting& s);
	~XListerThread() {};

	void OnExecute();
	virtual UnicodeString ClassName() { return L""; };
private:
	SockSetting c_s;
	SelectSocket sock;
};

XListerThread::XListerThread(const SockSetting& s)
{
	c_s = s;
	sock.Open(c_s);
}

void XListerThread::OnExecute()
{
	while (!IsTerminate())
	{
		SelectSocket*handle = sock.Accept();
		Thread * temp = new XAcceptThread(handle);
		temp->Resume();
	}
}

XListerThread * listen1 = nullptr;
void CTestProjectDlg::OnBnClickedButton9()
{

	UnicodeString dfd = UnicodeString::Int2FormatStr(UnicodeString(1233297893127));

	UnicodeString dfd1 = UnicodeString::Int2FormatStr(UnicodeString(-123456));
	// TODO: 在此添加控件通知处理程序代码
	SockSetting s;
	s.IpAddr = L"127.0.0.1";
	s.Port = 3000;
	if (listen1 == nullptr)
	{
		listen1 = new XListerThread(s);
		listen1->Resume();
	}
		
}
