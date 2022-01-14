#include "stdafx.h"
#include "..\include\XVariant.h"


XVariant::XVariant():COleVariant()
{

}


XVariant::XVariant(const VARIANT& varSrc):COleVariant(varSrc)
{

}

XVariant::XVariant(LPCVARIANT pSrc):COleVariant(pSrc)
{

}

XVariant::XVariant(const COleVariant& varSrc):COleVariant(varSrc)
{

}

XVariant::XVariant(CString& strSrc):COleVariant(strSrc)
{

}

XVariant::XVariant(const UnicodeString& wstr) : COleVariant(const_cast<WCHAR*>(wstr.c_str()))
{

}

XVariant::XVariant(const string &str): XVariant(UnicodeString(str))
{

}

XVariant::XVariant(const DateTime& timeSrc):COleVariant(timeSrc)
{

}

XVariant::XVariant(const COleCurrency& curSrc):COleVariant(curSrc)
{

}

XVariant::XVariant(const CByteArray& arrSrc):COleVariant(arrSrc)
{

}

XVariant::XVariant(const CLongBinary& lbSrc):COleVariant(lbSrc)
{

}

XVariant::XVariant(LPCITEMIDLIST pidl):COleVariant(pidl)
{

}

XVariant::~XVariant()
{
}
