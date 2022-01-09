#pragma once
#include "..\include\XString.h"
#define Painc(err) ThrowError(err)


extern AFX_EXT_CLASS INT64 CreateGUID();

extern AFX_EXT_CLASS void ThrowError(UnicodeString err);
extern AFX_EXT_CLASS UnicodeString GetLastErrorStr(UnicodeString funcname, UnicodeString desc = L"");


//�ļ��Ƿ����
extern AFX_EXT_CLASS bool FileExist(const UnicodeString& file);
//����Ŀ¼
extern AFX_EXT_CLASS bool CreateDir(const UnicodeString& dirpath);
//ɾ����Ŀ¼
extern AFX_EXT_CLASS bool DeleteEmptyDir(const UnicodeString& dirpath);
//ɾ��Ŀ¼��������Ŀ¼���ļ�������dirpathĿ¼
extern AFX_EXT_CLASS bool DeleteDir(const UnicodeString& dirpath);
//Ŀ¼�Ƿ����
extern AFX_EXT_CLASS bool DirExist(const UnicodeString& dirpath);


//����Ŀ¼�����е��ļ�(Ĭ�ϰ�����Ŀ¼�µ��ļ������filter��Ϊ�գ�����ָ����׺���ļ�
extern AFX_EXT_CLASS void TraverselFiles(const UnicodeString& dirpath,vector<UnicodeString>& files,UnicodeString filter = L"", bool issub = true);



//��ȡ�ļ�����׺ �������� .��
extern AFX_EXT_CLASS UnicodeString ExtractFileExt(UnicodeString fileName);
//�޸��ļ�����׺ (log)
extern AFX_EXT_CLASS UnicodeString ChangeFileExt(const UnicodeString& fileName,const UnicodeString& ext);
//��ȡ�ļ���(������׺)
extern AFX_EXT_CLASS UnicodeString ExtractFileName(UnicodeString fileName,bool NotExt = false);
//��ȡ�ļ�·��
extern AFX_EXT_CLASS UnicodeString ExtractFilePath(UnicodeString fileName);
//��ȡ��ǰȫ·��
extern AFX_EXT_CLASS UnicodeString GetApplicationFullName();
