#include "stdafx.h"
#include "..\include\utils.h"
#include "..\include\Logger.h"
#include <exception>
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
		return funcname + L" failed error:¡¾" + UnicodeString(codeError) + L"|" + buffer + L"¡¿ desc:"+desc;
	return funcname + L" failed error :¡¾" + UnicodeString(codeError) + L"|" + buffer +L"¡¿" ;
}

extern AFX_EXT_CLASS bool FileExist(const UnicodeString& file)
{
	return PathFileExists(file.c_str());
}



extern AFX_EXT_CLASS bool CreateDir(const UnicodeString& dirpath)
{
	if (GetFileAttributes(dirpath.c_str()) != FILE_ATTRIBUTE_DIRECTORY)
		return CreateDirectory(dirpath.c_str(), nullptr);
	return false;
}

extern AFX_EXT_CLASS bool DeleteDir(const UnicodeString& dirpath)
{
	SHFILEOPSTRUCT FileOp;
	FileOp.fFlags = FOF_NOCONFIRMATION;
	FileOp.hNameMappings = NULL;
	FileOp.hwnd = NULL;
	FileOp.lpszProgressTitle = NULL;
	FileOp.pFrom = dirpath.c_str();
	FileOp.pTo = NULL;
	FileOp.wFunc = FO_DELETE;
	return SHFileOperation(&FileOp) == 0;

}

extern AFX_EXT_CLASS bool DirectoryExist(const UnicodeString& dirpath)
{
	bool result = false;
	WIN32_FIND_DATA wfd;
	HANDLE hFind = FindFirstFile(dirpath.c_str(), &wfd);
	if (hFind != INVALID_HANDLE_VALUE && (wfd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY))
		result =  true;
	FindClose(hFind);
	return result;
}

extern AFX_EXT_CLASS void SearchDir(const UnicodeString& dirpath, vector<UnicodeString>& files, const UnicodeString& filter)
{

}

extern AFX_EXT_CLASS bool RemoveEmptyDir(const UnicodeString& dirpath)
{
	bool res = RemoveDirectory(dirpath.c_str());
	if (!res)
	{
		LOGWARN("RemoveDir", GetLastErrorStr("RemoveDirectory"));
	}
	return res;
}
