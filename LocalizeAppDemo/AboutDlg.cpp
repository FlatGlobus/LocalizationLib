// aboutdlg.cpp : implementation of the CAboutDlg class
//
/////////////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "resource.h"

#include "aboutdlg.h"

CAboutDlg::CAboutDlg(void):CLocalization(_T("CAboutDlg"))
//{{WTLBUILDER_CONSTRUCTOR
//}}WTLBUILDER_CONSTRUCTOR
{
}

LRESULT CAboutDlg::OnInitDialog(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/)
{
	m_toolTip.Create(m_hWnd);
//{{WTLBUILDER_MEMBER_CREATION
	m_formFont.CreateFont(-12,0,0,0,FW_NORMAL,false,false,false,DEFAULT_CHARSET,OUT_DEFAULT_PRECIS,CLIP_DEFAULT_PRECIS,DEFAULT_QUALITY,DEFAULT_PITCH|FF_DONTCARE,_T("MS Sans Serif"));
	SetFont((HFONT)m_formFont);
	ModifyStyle(GetStyle(),WS_POPUP|WS_CAPTION);
	ModifyStyleEx(GetExStyle(),WS_EX_WINDOWEDGE);
	ResizeClient(367,140);
	SetWindowText(Translate(_T("Caption"),_T("About")));

	m_button0.Create(m_hWnd,CRect(146,102,220,124),Translate(_T("1"),_T("OK")),WS_CHILD|WS_VISIBLE|WS_TABSTOP|BS_TEXT|BS_CENTER|BS_VCENTER,0,IDOK);
	m_button0.SetFont((HFONT)m_formFont);

	m_static1.Create(m_hWnd,CRect(69,15,297,29),Translate(_T("1001"),_T("LocalizationLib demo")),WS_CHILD|WS_VISIBLE|WS_TABSTOP|SS_LEFT,0,IDC_CABOUTDLG_STATIC1);
	m_static1Font.CreateFont(-12,0,0,0,FW_BOLD,false,false,false,DEFAULT_CHARSET,OUT_DEFAULT_PRECIS,CLIP_DEFAULT_PRECIS,DEFAULT_QUALITY,DEFAULT_PITCH|FF_DONTCARE,_T("MS Sans Serif"));
	m_static1.SetFont((HFONT)m_static1Font);

	m_hyperlink2.Create(m_hWnd,CRect(118,48,248,68),NULL,WS_CHILD|WS_VISIBLE|WS_TABSTOP,0,IDC_CABOUTDLG_HYPERLINK2);
	m_hyperlink2.SetLabel(_T("www.wtlbuilder.com"));
	m_hyperlink2.SetHyperLink(_T("http://www.wtlbuilder.com"));
	m_hyperlink2.m_bPaintLabel=true;
	m_hyperlink2.m_clrLink=RGB(0x00,0x00,0xFF);
	m_hyperlink2.m_clrVisited=RGB(0x80,0x00,0x80);

//}}WTLBUILDER_MEMBER_CREATION

//{{WTLBUILDER_POST_CREATION
//}}WTLBUILDER_POST_CREATION

//{{WTLBUILDER_TABSTOP
	m_hyperlink2.SetWindowPos(m_button0,0,0,0,0,SWP_NOMOVE|SWP_NOSIZE);
//}}WTLBUILDER_TABSTOP

	CenterWindow(GetParent());
	return TRUE;
}

LRESULT CAboutDlg::OnCloseCmd(WORD /*wNotifyCode*/, WORD wID, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
{
//{{WTLBUILDER_MEMBER_DESTRUCTION
//}}WTLBUILDER_MEMBER_DESTRUCTION

	EndDialog(wID);
	return 0;
}
