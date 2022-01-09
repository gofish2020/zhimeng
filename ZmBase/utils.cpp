#include "stdafx.h"
#include "..\include\utils.h"
#include "..\include\Logger.h"
#include <exception>
#include <direct.h>
#include "..\include\Snowflake.h"


extern INT64 CreateGUID()
{
	return GetSnowflake()->NextId();
}

extern AFX_EXT_CLASS void ThrowError(UnicodeString err)
{
	throw std::exception(string(err).c_str());
}

extern AFX_EXT_CLASS UnicodeString GetLastErrorStr(UnicodeString funcname,UnicodeString desc)
{
	int codeError = GetLastError();
	if (codeError == 0)
		return L"";
	LPTSTR lpBuffer;
	FormatMessage(FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_ALLOCATE_BUFFER, NULL, codeError, 0, (LPTSTR)&lpBuffer, MAX_PATH, NULL);
	UnicodeString buffer(lpBuffer);
	LocalFree(lpBuffer);
	if (desc != L"")
		return funcname + L" failed with error:【" + UnicodeString(codeError) + L"|" + buffer + L"】 desc:"+desc;
	return funcname + L" failed with error :【" + UnicodeString(codeError) + L"|" + buffer +L"】" ;
}

extern AFX_EXT_CLASS bool FileExist(const UnicodeString& file)
{
	//return PathFileExists(file.c_str());

	if (file.Trim() == L"")
		return false;
	WIN32_FIND_DATA FindFileData;
	HANDLE hFind;
	hFind = FindFirstFile(file.c_str(), &FindFileData);
	if (hFind == INVALID_HANDLE_VALUE)
		return false;
	FindClose(hFind);
	return true;
}



extern AFX_EXT_CLASS bool CreateDir(const UnicodeString& dirpath)
{
	UnicodeString temp;
	UnicodeString path;
	if (dirpath[dirpath.Len() - 1] != L'/' || dirpath[dirpath.Len() -1 ] != L'\\')
		path = dirpath + L"\\";
	for (int i = 0; i < path.Len();i++)
	{
		if (path[i] == L'\\' || path[i] == L'/')
		{
			temp = path.SubString(0, i);
			if (temp[temp.Len()-1] != L':' && !DirExist(temp))
			{
				CreateDirectory(temp.c_str(), nullptr);
			}
		}
	}
	return true;
}

extern AFX_EXT_CLASS bool DirExist(const UnicodeString& dirpath)
{
	if (dirpath.Trim() == L"")
		return false;
	int Code = GetFileAttributes(dirpath.c_str());
	return (Code != -1) && ((FILE_ATTRIBUTE_DIRECTORY & Code) != 0);
}

extern AFX_EXT_CLASS void TraverselFiles(const UnicodeString& dirpath, vector<UnicodeString>& files, UnicodeString filter, bool issub /*= true*/)
{
	UnicodeString dir = dirpath + L"\\*.*";
	WIN32_FIND_DATA wfd;
	HANDLE hFind = FindFirstFile(dir.c_str(), &wfd);
	if (hFind == INVALID_HANDLE_VALUE)
		return;
	do
	{
		if (StrCmpW(wfd.cFileName, L".") == 0 || StrCmpW(wfd.cFileName, L"..") == 0)
			continue;

		if (issub && wfd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) //目录
		{
			TraverselFiles(dirpath + L"\\" + wfd.cFileName, files, filter, issub); //递归遍历子目录
		}
		//判断文件后缀
		if (filter.IsEmpty())
			files.push_back(dirpath + L"\\" + wfd.cFileName);
		else if (ExtractFileExt(wfd.cFileName).ToUpper() == filter.ToUpper())
			files.push_back(dirpath + L"\\" + wfd.cFileName);
	} while (FindNextFile(hFind, &wfd));
	FindClose(hFind);
}

extern AFX_EXT_CLASS UnicodeString ExtractFilePath(UnicodeString fileName)
{
	size_t pos = fileName.find_last_of(L"\\");
	if (pos == wstring::npos)
	{
		return L"";
	}
	else
		return fileName.SubString(0, pos);
}

// 得到当前执行的exe的全路径文件名，如果失败返回""
extern AFX_EXT_CLASS UnicodeString GetApplicationFullName()
{
	wchar_t FileAppName[MAX_PATH];
	wmemset(FileAppName, 0, MAX_PATH);
	GetModuleFileName(::GetModuleHandle(NULL), FileAppName, MAX_PATH - 1);
	wchar_t FileDllName[MAX_PATH];
	wmemset(FileDllName, 0, MAX_PATH);
	// 只有欲获取的模块已映射到调用该函数的进程内，才会正确得到模块句柄。常用模块映射函数：LoadLibrary
#ifdef _DEBUG
	::GetModuleFileName(::GetModuleHandle(L"ZmBase_d.dll"), FileDllName, MAX_PATH - 1);
#else
	::GetModuleFileName(::GetModuleHandle(L"ZmBase.dll"), FileDllName, MAX_PATH - 1);
#endif
	UnicodeString AppPath = ExtractFilePath(FileAppName);
	UnicodeString DllPath = ExtractFilePath(FileDllName);
	DllPath = DllPath.Replace(L"\\\\?\\", L"");

	if (AppPath == DllPath)
		return FileAppName;
	else
		return DllPath + L"\\" + ExtractFileName(FileAppName);
}

extern AFX_EXT_CLASS UnicodeString ExtractFileExt(UnicodeString fileName)
{
	size_t pos= fileName.find_last_of(L".");
	if (pos == wstring::npos)
	{
		return L"";
	}
	else
		return fileName.SubString(pos+1,fileName.Len() - pos -1);
}

extern AFX_EXT_CLASS UnicodeString ChangeFileExt(const UnicodeString& fileName, const UnicodeString& ext)
{
	if (fileName.Trim().IsEmpty())
	{
		return L"";
	}
	size_t pos = fileName.find_last_of(L".");
	if (pos == wstring::npos)
	{
		return L"";
	}
	return fileName.SubString(0,pos + 1) + ext;
}

extern AFX_EXT_CLASS UnicodeString ExtractFileName(UnicodeString fileName, bool NotExt)
{
	size_t pos = fileName.find_last_of(L"\\");
	if (pos == wstring::npos)
	{
		return L"";
	}
	else
	{
		if (NotExt)
		{
			size_t pos1 = fileName.find_last_of(L".");
			if (pos1 == wstring::npos)
				return fileName.SubString(pos + 1, fileName.Len() - pos - 1);
			else
				return fileName.SubString(pos + 1, pos1 - pos - 1);
		}
		else
			return fileName.SubString(pos + 1, fileName.Len() - pos - 1);
	}
	return L"";
}

extern AFX_EXT_CLASS void TraverselAll(const UnicodeString& dirpath, vector<UnicodeString>& files,  bool issub)
{
	UnicodeString dir = dirpath + L"\\*.*" ;
	WIN32_FIND_DATA wfd;
	HANDLE hFind = FindFirstFile(dir.c_str(), &wfd);
	if (hFind == INVALID_HANDLE_VALUE)
		return;
	do 
	{
		if (StrCmpW(wfd.cFileName, L"." ) == 0 || StrCmpW(wfd.cFileName,L"..") == 0)
			continue;

		if (issub && wfd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) //目录
		{
			TraverselAll(dirpath + L"\\" + wfd.cFileName, files, issub); //递归遍历子目录
		}
		files.push_back(dirpath + L"\\" + wfd.cFileName);
	}
	while (FindNextFile(hFind, &wfd));
	FindClose(hFind);
}

extern AFX_EXT_CLASS bool DeleteEmptyDir(const UnicodeString& dirpath)
{
	bool res = RemoveDirectory(dirpath.c_str());
	if (!res)
	{
		LOGWARN("RemoveDir", GetLastErrorStr("RemoveDirectory"));
	}
	return res;
}

extern AFX_EXT_CLASS bool DeleteDir(const UnicodeString& dirpath)
{
	UnicodeString dir = dirpath + L"\\*.*";
	WIN32_FIND_DATA wfd;
	HANDLE hFind = FindFirstFile(dir.c_str(), &wfd);
	if (hFind == INVALID_HANDLE_VALUE)
		return false;
	do 
	{
		if (StrCmpW(wfd.cFileName,L".") == 0 || StrCmpW(wfd.cFileName,L"..") == 0)
			continue;
		if (wfd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
			DeleteDir(UnicodeString(dirpath + L"\\" + wfd.cFileName).c_str());
		else
			DeleteFile(UnicodeString(dirpath + L"\\" + wfd.cFileName).c_str());
	} 
	while (FindNextFile(hFind,&wfd));
	FindClose(hFind);
	DeleteEmptyDir(dirpath);
	return true;
}
