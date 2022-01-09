#pragma once
#include "..\include\XString.h"
#define Painc(err) ThrowError(err)


extern AFX_EXT_CLASS INT64 CreateGUID();

extern AFX_EXT_CLASS void ThrowError(UnicodeString err);
extern AFX_EXT_CLASS UnicodeString GetLastErrorStr(UnicodeString funcname, UnicodeString desc = L"");


//文件是否存在
extern AFX_EXT_CLASS bool FileExist(const UnicodeString& file);
//创建目录
extern AFX_EXT_CLASS bool CreateDir(const UnicodeString& dirpath);
//删除空目录
extern AFX_EXT_CLASS bool DeleteEmptyDir(const UnicodeString& dirpath);
//删除目录（所有子目录和文件）包括dirpath目录
extern AFX_EXT_CLASS bool DeleteDir(const UnicodeString& dirpath);
//目录是否存在
extern AFX_EXT_CLASS bool DirExist(const UnicodeString& dirpath);


//遍历目录下所有的文件(默认包括子目录下的文件）如果filter不为空，遍历指定后缀的文件
extern AFX_EXT_CLASS void TraverselFiles(const UnicodeString& dirpath,vector<UnicodeString>& files,UnicodeString filter = L"", bool issub = true);



//提取文件名后缀 （不包括 .）
extern AFX_EXT_CLASS UnicodeString ExtractFileExt(UnicodeString fileName);
//修改文件名后缀 (log)
extern AFX_EXT_CLASS UnicodeString ChangeFileExt(const UnicodeString& fileName,const UnicodeString& ext);
//提取文件名(包括后缀)
extern AFX_EXT_CLASS UnicodeString ExtractFileName(UnicodeString fileName,bool NotExt = false);
//提取文件路径
extern AFX_EXT_CLASS UnicodeString ExtractFilePath(UnicodeString fileName);
//获取当前全路径
extern AFX_EXT_CLASS UnicodeString GetApplicationFullName();
