#pragma once
/*
coder:nash
date:2022/1/14
desc:
*/
#include "..\include\XString.h"
#include "..\include\DateTime.h"
#include "..\include\Stream.h"

/* 

* VARENUM usage key,  各个类型的含义
*
* * [V] - may appear in a VARIANT
* * [T] - may appear in a TYPEDESC
* * [P] - may appear in an OLE property set
* * [S] - may appear in a Safe Array
*
*
*  VT_EMPTY            [V]   [P]     nothing
*  VT_NULL             [V]   [P]     SQL style Null
*  VT_I2               [V][T][P][S]  2 byte signed int
*  VT_I4               [V][T][P][S]  4 byte signed int
*  VT_R4               [V][T][P][S]  4 byte real
*  VT_R8               [V][T][P][S]  8 byte real
*  VT_CY               [V][T][P][S]  currency
*  VT_DATE             [V][T][P][S]  date
*  VT_BSTR             [V][T][P][S]  OLE Automation string
*  VT_DISPATCH         [V][T]   [S]  IDispatch *
*  VT_ERROR            [V][T][P][S]  SCODE
*  VT_BOOL             [V][T][P][S]  True=-1, False=0
*  VT_VARIANT          [V][T][P][S]  VARIANT *
*  VT_UNKNOWN          [V][T]   [S]  IUnknown *
*  VT_DECIMAL          [V][T]   [S]  16 byte fixed point
*  VT_RECORD           [V]   [P][S]  user defined type
*  VT_I1               [V][T][P][s]  signed char
*  VT_UI1              [V][T][P][S]  unsigned char
*  VT_UI2              [V][T][P][S]  unsigned short
*  VT_UI4              [V][T][P][S]  ULONG
*  VT_I8                  [T][P]     signed 64-bit int
*  VT_UI8                 [T][P]     unsigned 64-bit int
*  VT_INT              [V][T][P][S]  signed machine int
*  VT_UINT             [V][T]   [S]  unsigned machine int
*  VT_INT_PTR             [T]        signed machine register size width
*  VT_UINT_PTR            [T]        unsigned machine register size width
*  VT_VOID                [T]        C style void
*  VT_HRESULT             [T]        Standard return type
*  VT_PTR                 [T]        pointer type
*  VT_SAFEARRAY           [T]        (use VT_ARRAY in VARIANT)
*  VT_CARRAY              [T]        C style array
*  VT_USERDEFINED         [T]        user defined type
*  VT_LPSTR               [T][P]     null terminated string
*  VT_LPWSTR              [T][P]     wide null terminated string
*  VT_FILETIME               [P]     FILETIME
*  VT_BLOB                   [P]     Length prefixed bytes
*  VT_STREAM                 [P]     Name of the stream follows
*  VT_STORAGE                [P]     Name of the storage follows
*  VT_STREAMED_OBJECT        [P]     Stream contains an object
*  VT_STORED_OBJECT          [P]     Storage contains an object
*  VT_VERSIONED_STREAM       [P]     Stream with a GUID version
*  VT_BLOB_OBJECT            [P]     Blob contains an object
*  VT_CF                     [P]     Clipboard format
*  VT_CLSID                  [P]     A Class ID
*  VT_VECTOR                 [P]     simple counted array
*  VT_ARRAY            [V]           SAFEARRAY*
*  VT_BYREF            [V]           void* for local use
*  VT_BSTR_BLOB                      Reserved for system use

	VT_VECTOR	= 0x1000,
	VT_ARRAY	= 0x2000,
	VT_BYREF	= 0x4000,
	VT_RESERVED	= 0x8000,
	VT_ILLEGAL	= 0xffff,
	VT_ILLEGALMASKED	= 0xfff,
	VT_TYPEMASK	= 0xfff


VARIANT STRUCTURE  各个类型组合有的实际类型
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
*    CHAR           VT_I1    
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


*  }
*/

//!!!自定义类型
const VARTYPE VT_WCHAR = VT_RECORD | 0x00001; //wchar_t


class AFX_EXT_CLASS XVariant: public COleVariant
{
public:
	~XVariant();
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
	XVariant(int src);
	XVariant(unsigned int src);
	XVariant(BYTE nSrc);
	XVariant(char nSrc);
	XVariant(wchar_t nwStr);
	XVariant(short nSrc);
	XVariant(unsigned short nSrc);
	XVariant(long lSrc);
	XVariant(unsigned long src);
	XVariant(__int64 nSrc);
	XVariant(unsigned __int64 nSrc);
	XVariant(float fltSrc);
	XVariant(double dblSrc);
	//当做字符串处理，类型为 VT_BSTR
	XVariant(const wchar_t* lpszSrc);
	XVariant(const char* lpszSrc);
	//当做普通的对应类型的指针处理，类型为 VT_BYREF|VT_UI1
	XVariant(BYTE* src); 
	XVariant(short* src);
	XVariant(int* src);
	XVariant(unsigned int* src);
	XVariant(long* src);
	XVariant(unsigned long* src);
	XVariant(__int64 *src);
	XVariant(unsigned __int64 *src);
	XVariant(float* src);
	XVariant(double* src);
	XVariant(void* src);

	bool IsArray() const;
	bool IsEmpty() const;
	bool IsNull() const;
	VARTYPE Type() const;

	static void VrArrayToStream(vector<XVariant> &src, MemoryStream &dest);
	static void StreamToVrArray(MemoryStream &src,vector<XVariant> &dest );

	XVariant& operator =(const XVariant& src); //如果有自定义类型，需要修改该函数,负责数据的copy操作

	XVariant& operator =(const UnicodeString& src);
	XVariant& operator =(const string& src);
	XVariant& operator =(const DateTime& src);
	XVariant& operator=(char src);
	XVariant& operator=(BYTE src);
	XVariant& operator =(wchar_t src);
	XVariant& operator =(bool src);
	XVariant& operator =(int src);
	XVariant& operator =(short src);
	XVariant& operator =(long src);
	XVariant& operator =(__int64 src);
	XVariant& operator =(unsigned int src );
	XVariant& operator =(unsigned short src );
	XVariant& operator =(unsigned long src);
	XVariant& operator =(unsigned __int64 src);
	XVariant& operator =(float fltSrc);
	XVariant& operator =(double dblSrc);
	XVariant& operator = (const wchar_t* src);
	XVariant& operator =(const char* src);
	XVariant& operator =(BYTE* src);
	XVariant& operator =(int* src);
	XVariant& operator =(long* src);
	XVariant& operator =(float* src);
	XVariant& operator =(double* src);
	XVariant& operator =(void *src);

	operator UnicodeString() const;  //只转化了基本类型到UnicodeString
 	operator wchar_t*() ; //这里有修改内部变量，不用const进行限定
 	operator DateTime() const;
	operator bool() const;
	operator BYTE() const;
	operator char() const;
	operator double() const;
	operator float() const;
	operator int() const;
	operator short() const;
	operator long() const;
	operator unsigned int() const;
	operator unsigned short() const;
	operator unsigned long() const;
	operator void*();
private:
	UnicodeString Variant2UnicodeString() const;
private:

	VARTYPE _type;
	union {
		wchar_t wch;
	};

	UnicodeString c_UnicodeString;
};

