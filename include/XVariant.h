#pragma once

/*
coder:nash

date:2022/1/14
desc:
*/
#include "..\include\XString.h"
#include "..\include\DateTime.h"
class AFX_EXT_CLASS XVariant: public COleVariant
{
public:
	virtual ~XVariant();

	XVariant();
	XVariant(const VARIANT& varSrc);
	XVariant(LPCVARIANT pSrc);
	XVariant(const COleVariant& varSrc);
	XVariant(CString& strSrc);
	XVariant(const UnicodeString& wstr);
	XVariant(const string &str);

	XVariant(const COleCurrency& curSrc);
	XVariant(const CByteArray& arrSrc);
	XVariant(const CLongBinary& lbSrc);
	XVariant(const DateTime& timeSrc);
	XVariant(LPCITEMIDLIST pidl);


	XVariant(BYTE nSrc);
	XVariant(short nSrc, VARTYPE vtSrc = VT_I2);
	XVariant(long lSrc, VARTYPE vtSrc = VT_I4);
	

	XVariant(LONGLONG nSrc);
	XVariant(ULONGLONG nSrc);

	XVariant(float fltSrc);
	XVariant(double dblSrc);
	

	

	
};

