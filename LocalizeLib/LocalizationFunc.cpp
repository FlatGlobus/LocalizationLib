// Copyright (C) FlatGlobus(wtlbuilder@gmail.com) All rights reserved.
//
// This file is a part of the WTLBuilder.
// The use and distribution terms for this software are covered by the
// Microsoft Public License (http://opensource.org/licenses/MS-PL)
// which can be found in the file MS-PL.txt at the root folder.
#include "stdafx.h"
#include <algorithm>
#include "Ini.h"
#include "LocalizationFunc.h"
//////////////////////////////////////////////////////////////////////////
#define LANG_EXT _T("*.lng")
#define LANG_INFO_SECTION _T("langinfo")
#define CODE_PAGE_KEY _T("LanguageID")
#define LANGUAGE_KEY _T("Language")

typedef std::vector<CString> CStringVector;

static CString _locDirectory;
static LanguageInfoVector _languages;
static long _defLocIndex=-1;
static UINT _languageID;
static CIni langFile;
static BOOL initialized=FALSE;

void ReplaceSymbols(CString &str);
BOOL GetAllFilesFromFolder(LPCTSTR folder, BOOL bRecursively, StringVector &strList,LPCTSTR ext=NULL);
LANGID DetectLanguage(void);
//////////////////////////////////////////////////////////////////////////
LOC_API void SetLangFileDir(const CString &val)
{
	_locDirectory = val;
}
//////////////////////////////////////////////////////////////////////////
void SetDefaultLoc()
{
	for(unsigned long i=0; i < _languages.size(); i++)
	{
		if(_languages[i].languageID==_languageID)
		{
			_defLocIndex=i;
			langFile.SetPathName(_languages[i].file);
			initialized=TRUE;
			return;
		}
	}
	langFile.SetPathName(NULL);
	initialized=FALSE;
}
//////////////////////////////////////////////////////////////////////////
BOOL InitLocalization(LPCTSTR locDirectory)
{
	StringVector _files;
	_languageID=DetectLanguage();
	_locDirectory = locDirectory;
	if(GetAllFilesFromFolder(_locDirectory,FALSE,_files,LANG_EXT)==TRUE)
	{
		_languages.clear();
		for(unsigned int i=0; i < _files.size(); i++)
		{
			langFile.SetPathName(_files[i]);
			CString language=langFile.GetString(LANG_INFO_SECTION,LANGUAGE_KEY);
			unsigned int codepage=langFile.GetInt(LANG_INFO_SECTION,CODE_PAGE_KEY,0);
			if(language.IsEmpty()==FALSE && codepage!=0)
				_languages.push_back(CLanguageInfo(_files[i],language,codepage));
		}
	}

	if(_languages.size()==0)
		_languageID=MAKELANGID(LANG_ENGLISH, SUBLANG_ENGLISH_US);

	SetDefaultLoc();

	return _languages.empty()!=true;
}

const LanguageInfoVector & GetLanguageInfo()
{
	return _languages;
}

int GetCurrentLangIdx(void)
{
	return _defLocIndex;
}

void SetCurrentLangIdx(int val)
{
	_defLocIndex=val;
}

UINT GetCurrentLangID()
{
	return _languageID;
}

void SetCurrentLangID(UINT val)
{
	_languageID = val;
	SetDefaultLoc();
}

//////////////////////////////////////////////////////////////////////////
CString Translate(const CString &section,const CString &id,const CString & defStr)
{
	if(initialized==TRUE)
	{
		CString str=langFile.GetString(section,id,defStr);
		if(str.IsEmpty()==FALSE)
		{
			ReplaceSymbols(str);
			return str;
		}
	}
	return defStr;
}
//////////////////////////////////////////////////////////////////////////
CLocalization::CLocalization(LPCTSTR _section):section(_section)
{
}
//////////////////////////////////////////////////////////////////////////
void CLocalization::SetSection(const CString & _section)
{
	section = _section;
}
//////////////////////////////////////////////////////////////////////////
CString CLocalization::Translate(const CString &id,const CString & defStr) const
{
	return ::Translate(section,id,defStr);
}
//////////////////////////////////////////////////////////////////////////
CString CLocalization::Translate(const CString &_section,const CString &id,const CString & defStr)  const
{
	return ::Translate(_section,id,defStr);
}
//////////////////////////////////////////////////////////////////////////
CString CLocalization::Translate(const CString &_section,UINT id,HINSTANCE hInstance)const
{
	CString resStr;
	resStr.LoadString(hInstance,id);
	CString resID;
	resID.Format(_T("%u"),id);
	return ::Translate(_section,resID,resStr);
}
//////////////////////////////////////////////////////////////////////////
CString CLocalization::Translate(UINT id,HINSTANCE hInstance)const
{
	CString resStr;
	resStr.LoadString(hInstance,id);
	CString resID;
	resID.Format(_T("%u"),id);
	return ::Translate(section,resID,resStr);
}
//////////////////////////////////////////////////////////////////////////
void CLocalization::TranslateMenu(CMenuHandle &menu, BOOL reInit)  const
{
	if(menu.IsMenu() == FALSE)
		return;
	int count=menu.GetMenuItemCount();
	CString searchStr;
	static CMenuHandle popupMenu;
	static UINT  popupIndex = -1;

	if(reInit == TRUE)
	{
		popupMenu.m_hMenu = NULL;
		popupIndex=-1;
	}

	if(count)
	{
		for(int i=0; i <= count;i++)
		{
			UINT id=menu.GetMenuItemID(i);
			WORD mt = (WORD) menu.GetMenuState(i, MF_BYPOSITION);

			if(mt == -1)
				continue;

			if (id!=-1)
			{
				if(popupMenu.m_hMenu != NULL && popupIndex != -1)
				{
					searchStr.Format(_T("%u.p"),id);
					CString str=::Translate(section,searchStr,_T(""));
					if(!str.IsEmpty())
						popupMenu.ModifyMenu(popupIndex,MF_BYPOSITION|MF_STRING,(UINT_PTR)(HMENU)menu,str);
					popupMenu.m_hMenu = NULL;
					popupIndex = -1;
				}

				searchStr.Format(_T("%u.m"),id);
				CString str=::Translate(section,searchStr,_T(""));
				if(!str.IsEmpty())
					menu.ModifyMenu(id,MF_BYCOMMAND|MF_STRING,id,str);
			}
			if(mt & MF_POPUP)
			{
				popupMenu.m_hMenu = menu;
				popupIndex = i;
				TranslateMenu(menu.GetSubMenu(i),FALSE);
			}

		}
	}
}

LRESULT CLocalization::OnToolTipText(int idCtrl, LPNMHDR pnmh, BOOL& /*bHandled*/)
{
	LPNMTTDISPINFO pDispInfo = (LPNMTTDISPINFO)pnmh;
	pDispInfo->szText[0] = _T('\0');

	if((idCtrl != 0) && !(pDispInfo->uFlags & TTF_IDISHWND))
	{
		CString buff = Translate(idCtrl);
		if(buff.IsEmpty()==FALSE)
		{
			buff = buff.Right((buff.GetLength() - buff.Find(_T('\n')))-1);
			_tcscpy_s(pDispInfo->szText,(LPCTSTR)buff);
		}
#if (_WIN32_IE >= 0x0300)
		if(buff.GetLength() > 0)   // string was loaded, save it
			pDispInfo->uFlags |= TTF_DI_SETITEM;
#endif // (_WIN32_IE >= 0x0300)
	}

	return 0;
}

//////////////////////////////////////////////////////////////////////////
void ReplaceSymbols(CString &str)
{
	str.Replace(_T("\\\'"),_T("\'"));
	str.Replace(_T("\\\""),_T("\""));
	str.Replace(_T("\\?"),_T("\?"));
	str.Replace(_T("\\a"),_T("\a"));
	str.Replace(_T("\\b"),_T("\b"));
	str.Replace(_T("\\f"),_T("\f"));
	str.Replace(_T("\\n"),_T("\n"));
	str.Replace(_T("\\r"),_T("\r"));
	str.Replace(_T("\\t"),_T("\t"));
	str.Replace(_T("\\v"),_T("\v"));
}
//////////////////////////////////////////////////////////////////////////
BOOL IsDots(WIN32_FIND_DATA * pFindData)
{
	BOOL bResult = FALSE;
	if (pFindData != NULL && pFindData->dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
	{
		if (pFindData->cFileName[0] == _T('.'))
		{
			if (pFindData->cFileName[1] == _T('\0') ||
				(pFindData->cFileName[1] == _T('.') &&
				pFindData->cFileName[2] == _T('\0')))
			{
				bResult = TRUE;
			}
		}
	}
	return bResult;
}
//////////////////////////////////////////////////////////////////////////
BOOL GetAllFilesFromFolder(LPCTSTR folder, BOOL bRecursively, StringVector &strList,LPCTSTR ext)
{
	CString strSourceFolder(folder);
	if(strSourceFolder[strSourceFolder.GetLength()-1]!=_T('\\'))
		strSourceFolder=strSourceFolder+_T('\\');

	CString strExt(ext== NULL ? _T("*.*") : ext);
	WIN32_FIND_DATA FindFileData;
	HANDLE hFind = FindFirstFile((strSourceFolder + strExt), &FindFileData);
	if (hFind == INVALID_HANDLE_VALUE)
		return FALSE;
	do
	{
		if(IsDots(&FindFileData))
			continue;

		if(FindFileData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
		{
			if(bRecursively)
				GetAllFilesFromFolder(CString(strSourceFolder + FindFileData.cFileName + _T("\\")), bRecursively, strList);
		}
		else
			strList.push_back(strSourceFolder + FindFileData.cFileName);
	}
	while (FindNextFile(hFind, &FindFileData));
	FindClose(hFind);
	return strList.empty()!=true;
}

