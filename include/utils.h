#pragma once
#include "..\include\XString.h"
#define Painc(err) ThrowError(err)


extern AFX_EXT_CLASS void ThrowError(UnicodeString err);
extern AFX_EXT_CLASS UnicodeString GetLastErrorStr(UnicodeString funcname, UnicodeString desc = L"");
extern AFX_EXT_CLASS bool FileExist(const UnicodeString& file);
extern AFX_EXT_CLASS bool CreateDir(const UnicodeString& dirpath);
extern AFX_EXT_CLASS bool RemoveEmptyDir(const UnicodeString& dirpath);
extern AFX_EXT_CLASS bool DeleteDir(const UnicodeString& dirpath);
extern AFX_EXT_CLASS bool DirectoryExist(const UnicodeString& dirpath);
extern AFX_EXT_CLASS void SearchDir(const UnicodeString& dirpath, vector<UnicodeString>& files,const UnicodeString& filter);
