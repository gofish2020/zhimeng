#include "stdafx.h"
#include "..\include\XVariant.h"

VARIANT_BOOL
// struct tagVARIANT
// {
// 	union
// 	{
// 		struct __tagVARIANT
// 		{
// 			VARTYPE vt;
// 			WORD wReserved1;
// 			WORD wReserved2;
// 			WORD wReserved3;
// 			union
// 			{
// 				LONGLONG llVal;
// 				LONG lVal;
// 				BYTE bVal;
// 				SHORT iVal;
// 				FLOAT fltVal;
// 				DOUBLE dblVal;
// 				VARIANT_BOOL boolVal;
// 				_VARIANT_BOOL bool;
// 				SCODE scode;
// 				CY cyVal;
// 				DATE date;
// 				BSTR bstrVal;
// 				IUnknown *punkVal;
// 				IDispatch *pdispVal;
// 				SAFEARRAY *parray;
// 				BYTE *pbVal;
// 				SHORT *piVal;
// 				LONG *plVal;
// 				LONGLONG *pllVal;
// 				FLOAT *pfltVal;
// 				DOUBLE *pdblVal;
// 				VARIANT_BOOL *pboolVal;
// 				_VARIANT_BOOL *pbool;
// 				SCODE *pscode;
// 				CY *pcyVal;
// 				DATE *pdate;
// 				BSTR *pbstrVal;
// 				IUnknown **ppunkVal;
// 				IDispatch **ppdispVal;
// 				SAFEARRAY **pparray;
// 				VARIANT *pvarVal;
// 				PVOID byref;
// 				CHAR cVal;
// 				USHORT uiVal;
// 				ULONG ulVal;
// 				ULONGLONG ullVal;
// 				INT intVal;
// 				UINT uintVal;
// 				DECIMAL *pdecVal;
// 				CHAR *pcVal;
// 				USHORT *puiVal;
// 				ULONG *pulVal;
// 				ULONGLONG *pullVal;
// 				INT *pintVal;
// 				UINT *puintVal;
// 				struct __tagBRECORD
// 				{
// 					PVOID pvRecord;
// 					IRecordInfo *pRecInfo;
// 				} 	__VARIANT_NAME_4;
// 			} 	__VARIANT_NAME_3;
// 		} 	__VARIANT_NAME_2;
// 		DECIMAL decVal;
// 	} 	__VARIANT_NAME_1;
// };

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

XVariant::XVariant(BYTE nSrc):COleVariant(nSrc)
{

}

XVariant::XVariant(short nSrc):COleVariant(nSrc)
{

}

XVariant::XVariant(long lSrc):COleVariant(lSrc)
{

}

XVariant::XVariant(__int64 nSrc):COleVariant(nSrc)
{

}

XVariant::XVariant(unsigned __int64 nSrc):COleVariant(nSrc)
{

}

XVariant::XVariant(float fltSrc):COleVariant(fltSrc)
{

}

XVariant::XVariant(double dblSrc):COleVariant(dblSrc)
{

}

XVariant::XVariant(bool src)
{
	vt = VT_BOOL;
	V_BOOL(this) = src ? AFX_OLE_TRUE : AFX_OLE_FALSE;
}

XVariant::XVariant(char nSrc)
{
	vt = VT_I1;
	V_I1(this) = nSrc;
}

XVariant::XVariant(unsigned short nSrc)
{
	vt = VT_UI2;
	V_UI2(this) = nSrc;
}

XVariant::~XVariant()
{
}
