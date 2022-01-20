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

void XVariant::VrArrayToStream(vector<XVariant> &src, MemoryStream &dest)
{
	for (int i = 0; i < src.size();i++)
	{
		UINT16 tp = src[i].Type();
		switch (tp)
		{
		case VT_INT:
		{
			dest << tp;
			dest << V_INT(&src[i]);
			break;
		}
		case VT_UINT: 
		{
			dest << tp;
			dest << V_UINT(&src[i]);
			break;
		}
		case VT_I1:
		{
			dest << tp;
			dest << V_I1(&src[i]);
			break;
		}
		case VT_I2:
		{
			dest << tp;
			dest << V_I2(&src[i]);
			break;
		}
		case VT_I4:
		{
			dest << tp;
			dest << V_I4(&src[i]);
			break;
		}
		case VT_I8:
		{
			dest << tp;
			dest << V_I8(&src[i]);
			break;
		}
		case VT_BOOL:
		{
			dest << tp;
			dest << V_BOOL(&src[i]);
			break;
		}
		case VT_UI1:
		{
			dest << tp;
			dest << V_UI1(&src[i]);
			break;
		}
		case VT_UI2:
		{
			dest << tp;
			dest << V_UI2(&src[i]);
			break;
		}
		case VT_UI4:
		{
			dest << tp;
			dest << V_UI4(&src[i]);
			break;
		}
		case VT_UI8:
		{
			dest << tp;
			dest << V_UI8(&src[i]);
			break;
		}
		case VT_R4:
		{
			dest << tp;
			dest << V_R4(&src[i]);
			break;
		}
		case VT_R8:
		{
			dest << tp;
			dest << V_R8(&src[i]);
			break;
		}
		case VT_BSTR:
		{
			dest << tp;
			UnicodeString temp = UnicodeString(V_BSTR(&src[i]));
			dest << UINT32(temp.length());
			dest << temp;
			break;
		}
		case VT_DATE:
		{
			dest << tp;
			dest << V_DATE(&src[i]);
			break;
		}
		}
	}
}

void XVariant::StreamToVrArray(MemoryStream &src, vector<XVariant> &dest)
{
	XVariant temp;
	while (src.GetCursor() < src.GetSize())
	{
		UINT16 type = 0;
		src >> type; //读取类型
		
		switch (type)
		{
		case VT_INT:
		{
			temp.Clear();
			V_VT(&temp) = type;
			src >> V_INT(&temp);
			dest.push_back(temp);
			break;
		}
		case VT_UINT:
		{
			temp.Clear();
			V_VT(&temp) = type;
			src >> V_UINT(&temp);
			dest.push_back(temp);
			break;
		}
		case VT_BOOL:
		{
			temp.Clear();
			V_VT(&temp) = type;
			src >> V_BOOL(&temp);
			dest.push_back(temp);
			break;
		}
		case VT_I1:
		{
			temp.Clear();
			V_VT(&temp) = type;
			src >> V_I1(&temp);
			dest.push_back(temp);
			break;
		}
		case VT_I2:
		{
			temp.Clear();
			V_VT(&temp) = type;
			src >> V_I2(&temp);
			dest.push_back(temp);
			break;
		}
		case VT_I4:
		{
			temp.Clear();
			V_VT(&temp) = type;
			src >> V_I4(&temp);
			dest.push_back(temp);
			break;
		}
		case VT_I8:
		{
			temp.Clear();
			V_VT(&temp) = type;
			src >> V_I8(&temp);
			dest.push_back(temp);
			break;
		}
		case VT_UI1:
		{
			temp.Clear();
			V_VT(&temp) = type;
			src >> V_UI1(&temp);
			dest.push_back(temp);
			break;
		}
		case VT_UI2:
		{
			temp.Clear();
			V_VT(&temp) = type;
			src >> V_UI2(&temp);
			dest.push_back(temp);
			break;
		}
		case VT_UI4:
		{
			temp.Clear();
			V_VT(&temp) = type;
			src >> V_UI4(&temp);
			dest.push_back(temp);
			break;
		}
		case VT_UI8:
		{
			temp.Clear();
			V_VT(&temp) = type;
			src >> V_UI8(&temp);
			dest.push_back(temp);
			break;
		}
		case VT_R4:
		{
			temp.Clear();
			V_VT(&temp) = type;
			src >> V_R4(&temp);
			dest.push_back(temp);
			break;
		}

		case VT_R8:
		{
			temp.Clear();
			V_VT(&temp) = type;
			src >> V_R8(&temp);
			dest.push_back(temp);
			break;
		}
		case VT_DATE:
		{
			temp.Clear();
			V_VT(&temp) = type;
			src >> V_DATE(&temp);
			dest.push_back(temp);
			break;
		}
		case VT_BSTR:
		{
			temp.Clear();
			V_VT(&temp) = type;
			UINT32 size = 0;
			src >> size;
			UnicodeString tempStr(size,0);
			src >> tempStr;
			temp = tempStr;
			dest.push_back(temp);
			break;
		}
		}
	}
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
	UnicodeString result = Variant2UnicodeString();

	return result;
}


XVariant::operator wchar_t*() 
{
	c_UnicodeString = Variant2UnicodeString();
	return const_cast<wchar_t*>(c_UnicodeString.c_str());
}

XVariant::operator DateTime() const
{
	if (VT_DATE ==  V_VT(this))
	{
		return DateTime(V_DATE(this));
	}
	return DateTime();
}

XVariant::operator bool() const
{
	if (VT_BOOL == V_VT(this))
	{
		if (V_BOOL(this) == VARIANT_TRUE)
		{
			return true;
		}
	}
	return false;
}


XVariant::operator BYTE() const
{
	if (VT_UI1 == V_VT(this))
	{
		return V_UI1(this);
	}
	//强制类型转化
	XVariant varDest;
	varDest.ChangeType(VT_UI1, (COleVariant*)this);
	return V_UI1(&varDest);
}


XVariant::operator char() const
{
	if (VT_I1 == V_VT(this))
	{
		return V_I1(this);
	}
	XVariant varDest;
	varDest.ChangeType(VT_I1, (COleVariant*)this);
	return V_I1(&varDest);
}


XVariant::operator double() const
{
	switch (V_VT(this))
	{
	case VT_R8:
		return (double)V_R8(this);
	case VT_NULL:
		return 0;
	case VT_CY:
	{
		double x = this->cyVal.int64;
		x /= 10000;
		return x;
	}
	case VT_BOOL:
		return (V_BOOL(this) == VARIANT_TRUE) ? 1.0 : 0.0;
	case VT_I1:
		return (double)V_I1(this);
	case VT_I2:
		return (double)V_I2(this);
	case VT_I4:
		return (double)V_I4(this);
	case VT_I8:
		return (double)V_I8(this);
	case VT_UI1:
		return (double)V_UI1(this);
	case VT_UI2:
		return (double)V_UI2(this);
	case VT_UI4:
		return (double)V_UI4(this);
	case VT_UI8:
		return (double)V_UI8(this);
	case VT_INT:
		return (double)V_INT(this);
	case VT_UINT:
		return (double)V_UINT(this);
	case VT_R4:
		return (double)V_R4(this);
	case VT_BSTR:
		UnicodeString temp = V_BSTR(this);
		return temp.ToDouble();
	}

	XVariant varDest;
	varDest.ChangeType(VT_R8, (COleVariant*)this);
	return V_R8(&varDest);
}


XVariant::operator float() const
{
	switch (V_VT(this))
	{
	case VT_R4:
		return (double)V_R4(this);
	case VT_R8:
		return (double)V_R8(this);
	case VT_NULL:
		return 0;
	case VT_CY:
	{
		double x = this->cyVal.int64;
		x /= 10000;
		return x;
	}
	case VT_BOOL:
		return (V_BOOL(this) == VARIANT_TRUE) ? 1.0 : 0.0;
	case VT_I1:
		return (double)V_I1(this);
	case VT_I2:
		return (double)V_I2(this);
	case VT_I4:
		return (double)V_I4(this);
	case VT_I8:
		return (double)V_I8(this);
	case VT_UI1:
		return (double)V_UI1(this);
	case VT_UI2:
		return (double)V_UI2(this);
	case VT_UI4:
		return (double)V_UI4(this);
	case VT_UI8:
		return (double)V_UI8(this);
	case VT_INT:
		return (double)V_INT(this);
	case VT_UINT:
		return (double)V_UINT(this);
	case VT_BSTR:
		UnicodeString temp = V_BSTR(this);
		return temp.ToFloat();
	}
	XVariant varDest;
	varDest.ChangeType(VT_R4, (COleVariant*)this);
	return V_R4(&varDest);
}


XVariant::operator int() const
{
	switch (V_VT(this))
	{
	case VT_INT:
		return V_INT(this);
	case VT_R4:
		return (int)V_R4(this);
	case VT_R8:
		return (int)V_R8(this);
	case VT_NULL:
		return 0;
	case VT_CY:
	{
		double x = this->cyVal.int64;
		x /= 10000;
		return x;
	}
	case VT_BOOL:
		return (V_BOOL(this) == VARIANT_TRUE) ? 1 : 0;
	case VT_I1:
		return (int)V_I1(this);
	case VT_I2:
		return (int)V_I2(this);
	case VT_I4:
		return (int)V_I4(this);
	case VT_I8:
		return (int)V_I8(this);
	case VT_UI1:
		return (int)V_UI1(this);
	case VT_UI2:
		return (int)V_UI2(this);
	case VT_UI4:
		return (int)V_UI4(this);
	case VT_UI8:
		return (int)V_UI8(this);
	case VT_UINT:
		return (int)V_UINT(this);
	case VT_BSTR:
		UnicodeString temp = V_BSTR(this);
		return temp.ToInt();
	}
	XVariant varDest;
	varDest.ChangeType(VT_I4, (COleVariant*)this);
	return V_I4(&varDest);
}


XVariant::operator short() const
{
	switch (V_VT(this))
	{
	case VT_INT:
		return (short)V_INT(this);
	case VT_R4:
		return (short)V_R4(this);
	case VT_R8:
		return (short)V_R8(this);
	case VT_NULL:
		return 0;
	case VT_CY:
	{
		double x = this->cyVal.int64;
		x /= 10000;
		return x;
	}
	case VT_BOOL:
		return (V_BOOL(this) == VARIANT_TRUE) ? 1 : 0;
	case VT_I1:
		return (short)V_I1(this);
	case VT_I2:
		return V_I2(this);
	case VT_I4:
		return (short)V_I4(this);
	case VT_I8:
		return (short)V_I8(this);
	case VT_UI1:
		return (short)V_UI1(this);
	case VT_UI2:
		return (short)V_UI2(this);
	case VT_UI4:
		return (short)V_UI4(this);
	case VT_UI8:
		return (short)V_UI8(this);
	case VT_UINT:
		return (short)V_UINT(this);
	case VT_BSTR:
		UnicodeString temp = V_BSTR(this);
		return temp.ToInt();
	}
	XVariant varDest;
	varDest.ChangeType(VT_INT, (COleVariant*)this);
	return V_INT(&varDest);
}


XVariant::operator long() const
{
	switch (V_VT(this))
	{
	case VT_I4:
		return V_I4(this);
	case VT_INT:
		return (long)V_INT(this);
	case VT_R4:
		return (long)V_R4(this);
	case VT_R8:
		return (long)V_R8(this);
	case VT_NULL:
		return 0;
	case VT_CY:
	{
		double x = this->cyVal.int64;
		x /= 10000;
		return x;
	}
	case VT_BOOL:
		return (V_BOOL(this) == VARIANT_TRUE) ? 1 : 0;
	case VT_I1:
		return (long)V_I1(this);
	case VT_I2:
		return (long)V_I2(this);
	case VT_I8:
		return (long)V_I8(this);
	case VT_UI1:
		return (long)V_UI1(this);
	case VT_UI2:
		return (long)V_UI2(this);
	case VT_UI4:
		return (long)V_UI4(this);
	case VT_UI8:
		return (long)V_UI8(this);
	case VT_UINT:
		return (long)V_UINT(this);
	case VT_BSTR:
		UnicodeString temp = V_BSTR(this);
		return temp.ToInt();
	}
	XVariant varDest;
	varDest.ChangeType(VT_INT, (COleVariant*)this);
	return V_INT(&varDest);
}



XVariant::operator unsigned int() const
{
	switch (V_VT(this))
	{
	case VT_UINT:
		return V_UINT(this);
	case VT_I4:
		return (unsigned int)V_I4(this);
	case VT_INT:
		return (unsigned int)V_INT(this);
	case VT_R4:
		return (unsigned int)V_R4(this);
	case VT_R8:
		return (unsigned int)V_R8(this);
	case VT_NULL:
		return 0;
	case VT_CY:
	{
		double x = this->cyVal.int64;
		x /= 10000;
		return x;
	}
	case VT_BOOL:
		return (V_BOOL(this) == VARIANT_TRUE) ? 1 : 0;
	case VT_I1:
		return (unsigned int)V_I1(this);
	case VT_I2:
		return (unsigned int)V_I2(this);
	case VT_I8:
		return (unsigned int)V_I8(this);
	case VT_UI1:
		return (unsigned int)V_UI1(this);
	case VT_UI2:
		return (unsigned int)V_UI2(this);
	case VT_UI4:
		return (unsigned int)V_UI4(this);
	case VT_UI8:
		return (unsigned int)V_UI8(this);
	case VT_BSTR:
		UnicodeString temp = V_BSTR(this);
		return temp.ToUInt();
	}

	XVariant varDest;
	varDest.ChangeType(VT_UINT, (COleVariant*)this);
	return V_UINT(&varDest);
}


XVariant::operator unsigned short() const
{
	switch (V_VT(this))
	{
	case VT_UI2:
		return V_UI2(this);
	case VT_UINT:
		return (unsigned short)V_UINT(this);
	case VT_I4:
		return (unsigned short)V_I4(this);
	case VT_INT:
		return (unsigned short)V_INT(this);
	case VT_R4:
		return (unsigned short)V_R4(this);
	case VT_R8:
		return (unsigned short)V_R8(this);
	case VT_NULL:
		return 0;
	case VT_CY:
	{
		double x = this->cyVal.int64;
		x /= 10000;
		return x;
	}
	case VT_BOOL:
		return (V_BOOL(this) == VARIANT_TRUE) ? 1 : 0;
	case VT_I1:
		return (unsigned short)V_I1(this);
	case VT_I2:
		return (unsigned short)V_I2(this);
	case VT_I8:
		return (unsigned short)V_I8(this);
	case VT_UI1:
		return (unsigned short)V_UI1(this);
	
	case VT_UI4:
		return (unsigned short)V_UI4(this);
	case VT_UI8:
		return (unsigned short)V_UI8(this);
	case VT_BSTR:
		UnicodeString temp = V_BSTR(this);
		return temp.ToUInt();
	}

	XVariant varDest;
	varDest.ChangeType(VT_UI2, (COleVariant*)this);
	return V_UI2(&varDest);
}

XVariant::operator unsigned long() const
{
	switch (V_VT(this))
	{
	case VT_UI4:
		return V_UI4(this);
	case VT_UI2:
		return (unsigned long)V_UI2(this);
	case VT_UINT:
		return (unsigned long)V_UINT(this);
	case VT_I4:
		return (unsigned long)V_I4(this);
	case VT_INT:
		return (unsigned long)V_INT(this);
	case VT_R4:
		return (unsigned long)V_R4(this);
	case VT_R8:
		return (unsigned long)V_R8(this);
	case VT_NULL:
		return 0;
	case VT_CY:
	{
		double x = this->cyVal.int64;
		x /= 10000;
		return x;
	}
	case VT_BOOL:
		return (V_BOOL(this) == VARIANT_TRUE) ? 1 : 0;
	case VT_I1:
		return (unsigned long)V_I1(this);
	case VT_I2:
		return (unsigned long)V_I2(this);
	case VT_I8:
		return (unsigned long)V_I8(this);
	case VT_UI1:
		return (unsigned long)V_UI1(this);
	case VT_UI8:
		return (unsigned long)V_UI8(this);
	case VT_BSTR:
		UnicodeString temp = V_BSTR(this);
		return temp.ToUInt64();
	}
	XVariant varDest;
	varDest.ChangeType(VT_UI4, (COleVariant*)this);
	return V_UI4(&varDest);
}

XVariant::operator void*()
{
	return this->byref;
}

UnicodeString XVariant::Variant2UnicodeString() const
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
	case VT_BOOL:
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
	case VT_ERROR:
		result = L"Error:" + UnicodeString((LONG)V_ERROR(this));
		break;
	default:
		break;
	}
	return result;
}
