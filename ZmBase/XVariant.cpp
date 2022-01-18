#include "stdafx.h"
#include "..\include\XVariant.h"
//VARIANT_BOOL
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

XVariant::XVariant():_type(0),COleVariant()
{

}


XVariant::XVariant(const VARIANT& varSrc):_type(0),COleVariant(varSrc)
{

}

XVariant::XVariant(LPCVARIANT pSrc): _type(0), COleVariant(pSrc)
{

}

XVariant::XVariant(const COleVariant& varSrc): _type(0), COleVariant(varSrc)
{

}

XVariant::XVariant(CString& strSrc): _type(0), COleVariant(strSrc)
{

}

XVariant::XVariant(const UnicodeString& wstr) : _type(0), COleVariant(const_cast<WCHAR*>(wstr.c_str()))
{

}

XVariant::XVariant(const string &str): _type(0), COleVariant(UnicodeString(str).c_str())
{

}

XVariant::XVariant(const wchar_t* lpszSrc) : _type(0), COleVariant(lpszSrc)
{

}

XVariant::XVariant(const char* lpszSrc) : _type(0), COleVariant(UnicodeString(lpszSrc).c_str())
{

}

XVariant::XVariant(const DateTime& timeSrc): _type(0), COleVariant(timeSrc)
{

}

XVariant::XVariant(const COleCurrency& curSrc): _type(0), COleVariant(curSrc)
{

}

XVariant::XVariant(const CByteArray& arrSrc): _type(0), COleVariant(arrSrc)
{

}

XVariant::XVariant(const CLongBinary& lbSrc): _type(0), COleVariant(lbSrc)
{

}

XVariant::XVariant(LPCITEMIDLIST pidl): _type(0), COleVariant(pidl)
{

}

XVariant::XVariant(BYTE nSrc): _type(0), COleVariant(nSrc)
{

}

XVariant::XVariant(short nSrc): _type(0), COleVariant(nSrc)
{

}

XVariant::XVariant(long lSrc): _type(0), COleVariant(lSrc)
{

}

XVariant::XVariant(__int64 nSrc): _type(0), COleVariant(nSrc)
{

}

XVariant::XVariant(unsigned __int64 nSrc): _type(0), COleVariant(nSrc)
{

}

XVariant::XVariant(float fltSrc): _type(0), COleVariant(fltSrc)
{

}

XVariant::XVariant(double dblSrc): _type(0), COleVariant(dblSrc)
{

}

XVariant::XVariant(bool src): _type(0)
{
	V_VT(this) = VT_BOOL;
	V_BOOL(this) = src ? AFX_OLE_TRUE : AFX_OLE_FALSE;
}

XVariant::XVariant(char nSrc) : _type(0)
{
	V_VT(this) = VT_I1;
	V_I1(this) = nSrc;
}

XVariant::XVariant(unsigned short nSrc) : _type(0)
{
	V_VT(this) = VT_UI2;
	V_UI2(this) = nSrc;
}

XVariant::XVariant(unsigned long src) : _type(0)
{
	V_VT(this) = VT_UI4;
	V_UI4(this) = src;
}

XVariant::XVariant(int src) : _type(0)
{
	V_VT(this) = VT_INT;
	V_INT(this) = src;
}

XVariant::XVariant(unsigned int src) : _type(0)
{
	V_VT(this) = VT_UINT;
	V_UINT(this) = src;
}



XVariant::XVariant(short* src) : _type(0)
{
	V_VT(this) = VT_BYREF | VT_I2;
	V_I2REF(this) = src;
}

XVariant::XVariant(int* src) : _type(0)
{
	V_VT(this) = VT_BYREF | VT_INT;
	V_INTREF(this) = src;
}

XVariant::XVariant(long* src) : _type(0)
{
	V_VT(this) = VT_BYREF | VT_I4;
	V_I4REF(this) = src;
}

XVariant::XVariant(__int64 *src) : _type(0)
{
	V_VT(this) = VT_BYREF | VT_I8;
	V_I8REF(this) = src;
}

XVariant::XVariant(float* src) : _type(0)
{
	V_VT(this) = VT_BYREF | VT_R4;
	V_R4REF(this) = src;
}

XVariant::XVariant(double* src) : _type(0)
{
	V_VT(this) = VT_BYREF | VT_R8;
	V_R8REF(this) = src;
}

XVariant::XVariant(BYTE* src) : _type(0)
{
	V_VT(this) = VT_BYREF | VT_UI1;
	V_UI1REF(this) = src;
}

XVariant::XVariant(void* src) : _type(0)
{
	V_VT(this) = VT_BYREF;
	V_BYREF(this) = src;
}

XVariant::XVariant(wchar_t nwStr) : _type(VT_WCHAR)
{
	V_VT(this) = VT_RECORD;
	wch = nwStr;
}

XVariant::XVariant(unsigned int* src) : _type(0)
{
	V_VT(this) = VT_BYREF | VT_UINT;
	V_UINTREF(this) = src;
}

XVariant::XVariant(unsigned long* src) : _type(0)
{
	V_VT(this) = VT_BYREF | VT_UI4;
	V_UI4REF(this) = src;
}

XVariant::XVariant(unsigned __int64 *src) : _type(0)
{
	V_VT(this) = VT_BYREF | VT_UI8;
	V_UI8REF(this) = src;
}

bool XVariant::IsArray() const
{
	if (vt == VT_ARRAY)
	{
		return true;
	}
	return false;
}

bool XVariant::IsEmpty() const
{
	if (vt == VT_EMPTY)
	{
		return true;
	}
	return false;
}

bool XVariant::IsNull() const
{
	if (vt == VT_NULL)
	{
		return true;
	}
	return false;
}

VARTYPE XVariant::Type() const
{
	return vt;
}

XVariant& XVariant::operator=(const wchar_t* src)
{
	*this = XVariant(src);
	return *this;
}

XVariant& XVariant::operator=(void *src)
{
	*this = XVariant(src);
	return *this;
}

XVariant& XVariant::operator=(double* src)
{
	*this = XVariant(src);
	return *this;
}

XVariant& XVariant::operator=(float* src)
{
	*this = XVariant(src);
	return *this;
}

XVariant& XVariant::operator=(long* src)
{
	*this = XVariant(src);
	return *this;
}

XVariant& XVariant::operator=(int* src)
{
	*this = XVariant(src);
	return *this;
}

XVariant& XVariant::operator=(BYTE* src)
{
	*this = XVariant(src);
	return *this;
}

XVariant& XVariant::operator=(const char* src)
{
	*this = XVariant(src);
	return *this;
}

XVariant& XVariant::operator=(double dblSrc)
{
	*this = XVariant(dblSrc);
	return *this;
}

XVariant& XVariant::operator=(float fltSrc)
{
	*this = XVariant(fltSrc);
	return *this;
}

XVariant& XVariant::operator=(BYTE src)
{
	*this = XVariant(src);
	return *this;
}

XVariant& XVariant::operator=(unsigned __int64 src)
{
	*this = XVariant(src);
	return *this;
}

XVariant& XVariant::operator=(unsigned long src)
{
	*this = XVariant(src);
	return *this;
}

XVariant& XVariant::operator=(unsigned short src)
{
	*this = XVariant(src);
	return *this;
}

XVariant& XVariant::operator=(long src)
{
	*this = XVariant(src);
	return *this;
}

XVariant& XVariant::operator=(short src)
{
	*this = XVariant(src);
	return *this;
}

XVariant& XVariant::operator=(int src)
{
	*this = XVariant(src);
	return *this;
}

XVariant& XVariant::operator=(char src)
{
	*this = XVariant(src);
	return *this;
}

XVariant& XVariant::operator=(unsigned int src)
{
	*this = XVariant(src);
	return *this;
}

XVariant& XVariant::operator=(wchar_t src)
{
	*this = XVariant(src);
	return *this;
}

XVariant& XVariant::operator=(__int64 src)
{
	*this = XVariant(src);
	return *this;
}

XVariant& XVariant::operator=(const XVariant& src)
{
	if (static_cast<XVariant*>(this) != &src)
	{
		AfxCheckError(::VariantCopy(this, (LPVARIANT)&src));

		//自定义类型
		if (src._type == VT_WCHAR) 
		{
			this->wch = src.wch;
		}
	}
	return *this;
}

XVariant& XVariant::operator=(bool src)
{
	*this = XVariant(src);
	return *this;
}

XVariant& XVariant::operator=(const DateTime& src)
{
	*this = XVariant(src);
	return *this;
}

XVariant& XVariant::operator=(const string& src)
{
	*this = XVariant(src);
	return *this;
}

XVariant& XVariant::operator=(const UnicodeString& src)
{
	*this = XVariant(src);
	return *this;
}

XVariant::~XVariant()
{
	::VariantClear(this);
}


XVariant::operator UnicodeString() const
{
	VARTYPE vt = V_VT(this);
	UnicodeString result = L"";
	switch (vt)
	{
	case VT_RECORD:
		if (_type == VT_WCHAR)
		{
			result = wch;
		}
		break;
	case VT_INT:
		result = V_INT(this);
		break;
	case VT_UINT:
		result = V_UINT(this);
		break;
	case VT_I1:
		result = V_I1(this);
		break;
	case VT_I2:
		result = V_I2(this);
		break;
	case VT_I4:
		result = V_I4(this);
		break;
	case VT_I8:
		result = V_I8(this);
		break;
	case VT_UI1:
		result = V_UI1(this);
		break;
	case VT_UI2:
		result = V_UI2(this);
		break;
	case VT_UI4:
		result = V_UI4(this);
		break;
	case VT_UI8:
		result = V_UI8(this);
		break;
	case VT_R8:
		result = V_R8(this);
		break;
	case VT_R4:
		result = V_R4(this);
		break;
	case VT_DATE:
		result = DateTime(V_DATE(this)).ToDateTimeStr();
		break;
	case  VT_BOOL:
	{
		if (V_BOOL(this) == VARIANT_TRUE)
			return "true";
		else
			return "false";
		break;
	}
	case VT_BSTR:
		result = UnicodeString(V_BSTR(this));
		break;
	default:
		break;
	}

	return result;
}