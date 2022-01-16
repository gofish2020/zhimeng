#pragma once

/*
coder:nash
date:2022/1/13
desc: 定义一个动态类型，主要是基于Union结构存储实际的数据
*/


class AFX_EXT_CLASS Variant: public COleVariant
{
public:
	Variant();
	virtual ~Variant();

	Variant(const VARIANT& varSrc);
	Variant(LPCVARIANT pSrc);
	Variant(const COleVariant& varSrc);

	Variant(LPCTSTR lpszSrc);
	Variant(LPCTSTR lpszSrc, VARTYPE vtSrc); // used to set to ANSI string
	Variant(CString& strSrc);

	Variant(BYTE nSrc);
	Variant(short nSrc, VARTYPE vtSrc = VT_I2);
	Variant(long lSrc, VARTYPE vtSrc = VT_I4);
	Variant(const COleCurrency& curSrc);

	Variant(LONGLONG nSrc);
	Variant(ULONGLONG nSrc);

	Variant(float fltSrc);
	Variant(double dblSrc);
	Variant(const COleDateTime& timeSrc);

	Variant(const CByteArray& arrSrc);
	Variant(const CLongBinary& lbSrc);

	Variant(LPCITEMIDLIST pidl);
};

