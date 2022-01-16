#pragma once

/*
coder:nash
date:2022/1/14
desc:
*/



/* VARIANT STRUCTURE
*
*  VARTYPE vt;
*  WORD wReserved1;
*  WORD wReserved2;
*  WORD wReserved3;
*  union {
*    LONGLONG       VT_I8
*    LONG           VT_I4
*    BYTE           VT_UI1
*    SHORT          VT_I2
*    FLOAT          VT_R4
*    DOUBLE         VT_R8
*    VARIANT_BOOL   VT_BOOL
*    SCODE          VT_ERROR
*    CY             VT_CY
*    DATE           VT_DATE
*    BSTR           VT_BSTR
*    IUnknown *     VT_UNKNOWN
*    IDispatch *    VT_DISPATCH
*    SAFEARRAY *    VT_ARRAY
*    BYTE *         VT_BYREF|VT_UI1
*    SHORT *        VT_BYREF|VT_I2
*    LONG *         VT_BYREF|VT_I4
*    LONGLONG *     VT_BYREF|VT_I8
*    FLOAT *        VT_BYREF|VT_R4
*    DOUBLE *       VT_BYREF|VT_R8
*    VARIANT_BOOL * VT_BYREF|VT_BOOL
*    SCODE *        VT_BYREF|VT_ERROR
*    CY *           VT_BYREF|VT_CY
*    DATE *         VT_BYREF|VT_DATE
*    BSTR *         VT_BYREF|VT_BSTR
*    IUnknown **    VT_BYREF|VT_UNKNOWN
*    IDispatch **   VT_BYREF|VT_DISPATCH
*    SAFEARRAY **   VT_BYREF|VT_ARRAY
*    VARIANT *      VT_BYREF|VT_VARIANT
*    PVOID          VT_BYREF (Generic ByRef)
*    CHAR           VT_I1    #define V_I1(X)          V_UNION(X, cVal)
*    USHORT         VT_UI2
*    ULONG          VT_UI4
*    ULONGLONG      VT_UI8
*    INT            VT_INT
*    UINT           VT_UINT
*    DECIMAL *      VT_BYREF|VT_DECIMAL
*    CHAR *         VT_BYREF|VT_I1
*    USHORT *       VT_BYREF|VT_UI2
*    ULONG *        VT_BYREF|VT_UI4
*    ULONGLONG *    VT_BYREF|VT_UI8
*    INT *          VT_BYREF|VT_INT
*    UINT *         VT_BYREF|VT_UINT
*  }
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


	XVariant(bool src);
	XVariant(BYTE nSrc);
	XVariant(char nSrc);

	XVariant(short nSrc);
	XVariant(unsigned short nSrc);
	XVariant(long lSrc);
	XVariant(__int64 nSrc);
	XVariant(unsigned __int64 nSrc);
	XVariant(float fltSrc);
	XVariant(double dblSrc);




	LVariant(float fltSrc);
	LVariant(double dblSrc);
	LVariant(bool src);
	LVariant(BYTE nSrc);
	LVariant(short nSrc);
	LVariant(int src);
	LVariant(long lSrc);
	LVariant(__int64 src);
	LVariant(unsigned short src);
	LVariant(unsigned int src);
	LVariant(unsigned long src);
	LVariant(unsigned __int64 src);
	

	

	
};

