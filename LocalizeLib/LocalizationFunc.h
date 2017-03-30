// Copyright (C) FlatGlobus(wtlbuilder@gmail.com) All rights reserved.
//
// This file is a part of the WTLBuilder.
// The use and distribution terms for this software are covered by the
// Microsoft Public License (http://opensource.org/licenses/MS-PL)
// which can be found in the file MS-PL.txt at the root folder.
#ifndef __LOCALIZATION_FUNC_H
#define __LOCALIZATION_FUNC_H
//////////////////////////////////////////////////////////////////////////

#include <vector>

#pragma warning( disable : 4251)

#ifdef LOCALIZELIB_EXPORTS
#define LOC_API __declspec( dllexport )
#else
#define LOC_API __declspec (dllimport)
#pragma comment( lib,"LocalizeLib.lib")
#endif

class CLanguageInfo
{
public:
	CLanguageInfo()
	{}

	CLanguageInfo(const CString& _file,const CString& _language,UINT _languageID):
	file(_file),language(_language),languageID(_languageID)
	{}

	CString file;
	CString language;
	UINT	languageID;
};
typedef std::vector<CLanguageInfo> LanguageInfoVector;
//////////////////////////////////////////////////////////////////////////
class LOC_API CLocalization
{
public:  
	CLocalization(LPCTSTR section);
	void SetSection(const CString &);
	CString Translate(const CString &id,const CString & defStr) const;
	CString Translate(const CString &section,const CString &id,const CString & defStr)const;
	CString Translate(UINT id,HINSTANCE hInstance = ModuleHelper::GetResourceInstance())const;
	CString Translate(const CString &section,UINT id,HINSTANCE hInstance = ModuleHelper::GetResourceInstance())const;
	void TranslateMenu(CMenuHandle& menu,BOOL reInit = TRUE) const;

	BEGIN_MSG_MAP(CLocalization)
		NOTIFY_CODE_HANDLER(TTN_GETDISPINFO, OnToolTipText)
	END_MSG_MAP()

	LRESULT OnToolTipText(int idCtrl, LPNMHDR pnmh, BOOL& /*bHandled*/);

protected:
	CString section;
};
//////////////////////////////////////////////////////////////////////////
template <class T>
class CFrameWindowLocalization: public CLocalization
{
public:
	CFrameWindowLocalization(LPCTSTR _section):CLocalization(_section)
	{
	}

	BEGIN_MSG_MAP(CFrameWindowLocalization)
		MESSAGE_HANDLER(WM_MENUSELECT, OnMenuSelect)
		CHAIN_MSG_MAP(CLocalization)
	END_MSG_MAP()

	LRESULT OnMenuSelect(UINT /*uMsg*/, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		bHandled = TRUE;

		if(static_cast<T*>(this)->m_hWndStatusBar == NULL)
			return 1;

		WORD wFlags = HIWORD(wParam);
		if(wFlags == 0xFFFF && lParam == NULL)   // menu closing
		{
			::SendMessage(static_cast<T*>(this)->m_hWndStatusBar, SB_SIMPLE, FALSE, 0L);
		}
		else
		{
			CString buff;
			if(!(wFlags & MF_POPUP))
			{
				WORD wID = LOWORD(wParam);
				// check for special cases
				if(wID >= 0xF000 && wID < 0xF1F0)   // system menu IDs
					wID = (WORD)(((wID - 0xF000) >> 4) + ATL_IDS_SCFIRST);
				else if(wID >= ID_FILE_MRU_FIRST && wID <= ID_FILE_MRU_LAST)   // MRU items
					wID = ATL_IDS_MRU_FILE;
				else if(wID >= ATL_IDM_FIRST_MDICHILD && wID <= ATL_IDM_LAST_MDICHILD)   // MDI child windows
					wID = ATL_IDS_MDICHILD;

				buff = Translate(wID);
				if(buff.IsEmpty()==FALSE)
					buff = buff.Left(buff.Find(_T('\n'))+1);
			}
			::SendMessage(static_cast<T*>(this)->m_hWndStatusBar, SB_SIMPLE, TRUE, 0L);
			::SendMessage(static_cast<T*>(this)->m_hWndStatusBar, SB_SETTEXT, (255 | SBT_NOBORDERS), (LPARAM)(LPCTSTR)buff);
		}
		return 0;
	}
};
//////////////////////////////////////////////////////////////////////////
LOC_API BOOL InitLocalization(LPCTSTR locDirectory);
LOC_API const LanguageInfoVector & GetLanguageInfo();
LOC_API int GetCurrentLangIdx(void);
LOC_API void SetCurrentLangIdx(int);
LOC_API UINT GetCurrentLangID();
LOC_API void SetCurrentLangID(UINT);
LOC_API CString Translate(const CString &section,const CString &id,const CString & defStr=_T(""));
//////////////////////////////////////////////////////////////////////////
#endif