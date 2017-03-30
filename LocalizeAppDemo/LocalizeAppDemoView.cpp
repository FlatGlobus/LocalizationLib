// LocalizeAppDemoView.cpp : implementation of the CLocalizeAppDemoView class
//
/////////////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "resource.h"

#include "LocalizeAppDemoView.h"

const UINT CLocalizeAppDemoView::_controlsToClip[] =
{
//{{WTLBUILDER_CTRLTOCLIP
//}}WTLBUILDER_CTRLTOCLIP
	0
};

CLocalizeAppDemoView::CLocalizeAppDemoView(void):CLocalization(_T("CLocalizeAppDemoView"))
//{{WTLBUILDER_CONSTRUCTOR
//}}WTLBUILDER_CONSTRUCTOR
{
}

BOOL CLocalizeAppDemoView::PreTranslateMessage(MSG* pMsg)
{
	if(m_toolTip.IsWindow())
		m_toolTip.RelayEvent(pMsg);
	return FALSE;
}

LRESULT CLocalizeAppDemoView::OnCreate(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/)
{
	m_toolTip.Create(m_hWnd);

//{{WTLBUILDER_MEMBER_CREATION
	m_formFont.CreateFont(-12,0,0,0,FW_NORMAL,false,false,false,DEFAULT_CHARSET,OUT_DEFAULT_PRECIS,CLIP_DEFAULT_PRECIS,DEFAULT_QUALITY,DEFAULT_PITCH|FF_DONTCARE,_T("MS Sans Serif"));
	SetFont((HFONT)m_formFont);
	ResizeClient(563,414);

	m_button16.Create(m_hWnd,CRect(6,12,158,34),Translate(_T("1016"),_T("button")),WS_CHILD|WS_VISIBLE|WS_TABSTOP|BS_TEXT|BS_CENTER|BS_VCENTER,0,IDC_CLOCALIZEAPPDEMOVIEW_BUTTON16);
	m_button16.SetFont((HFONT)m_formFont);
	m_toolTip.AddTool((HWND)m_button16,(LPCTSTR)Translate(_T("1016.t"),_T("button tooltip")));

	m_listbox17.Create(m_hWnd,CRect(186,12,318,153),NULL,WS_CHILD|WS_VISIBLE|WS_TABSTOP,WS_EX_CLIENTEDGE,IDC_CLOCALIZEAPPDEMOVIEW_LISTBOX17);
	m_listbox17.SetFont((HFONT)m_formFont);
	m_listbox17.AddString(Translate(_T("1017.0"),_T("Item1")));
	m_listbox17.AddString(Translate(_T("1017.1"),_T("Item2")));
	m_listbox17.AddString(Translate(_T("1017.2"),_T("Item3")));
	m_listbox17.AddString(Translate(_T("1017.3"),_T("Item4")));
	m_listbox17.SetItemHeight(0,13);
	m_listbox17.SetHorizontalExtent(40);
	m_toolTip.AddTool((HWND)m_listbox17,(LPCTSTR)Translate(_T("1017.t"),_T("listbox tooltip")));

	m_static18.Create(m_hWnd,CRect(12,162,234,176),Translate(_T("1018"),_T("Text")),WS_CHILD|WS_VISIBLE|WS_TABSTOP|SS_LEFT|SS_NOTIFY,0,IDC_CLOCALIZEAPPDEMOVIEW_STATIC18);
	m_static18.SetFont((HFONT)m_formFont);
	m_toolTip.AddTool((HWND)m_static18,(LPCTSTR)Translate(_T("1018.t"),_T("static tooltip")));

//}}WTLBUILDER_MEMBER_CREATION

//{{WTLBUILDER_POST_CREATION
//}}WTLBUILDER_POST_CREATION

//{{WTLBUILDER_TABSTOP
	m_listbox17.SetWindowPos(m_button16,0,0,0,0,SWP_NOMOVE|SWP_NOSIZE);
//}}WTLBUILDER_TABSTOP

	InitLayout();
	
	return 0;
}

LRESULT CLocalizeAppDemoView::OnDestroy(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/)
{
//{{WTLBUILDER_MEMBER_DESTRUCTION
//}}WTLBUILDER_MEMBER_DESTRUCTION

	return 0;
}

LRESULT CLocalizeAppDemoView::OnPaint(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/)
{
	CPaintDC dc(m_hWnd);

	//TODO: Add your drawing code here

	return 0;
}

void CLocalizeAppDemoView::DefineLayout()
{
//{{WTLBUILDER_ATTACH_CONTROLS
//}}WTLBUILDER_ATTACH_CONTROLS
}

void CLocalizeAppDemoView::InitLayout()
{
//{{WTLBUILDER_INITLAYOUT
	_minClientSize.cx = 563;
	_minClientSize.cy = 414;
	_prevClientSize = _minClientSize;

	_minWindowSize.cx = 571;
	_minWindowSize.cy = 448;

	SetNPositions(1);
	DefineLayout();
//}}WTLBUILDER_INITLAYOUT
	//SetScrollSize(_minClientSize);
}

void CLocalizeAppDemoView::GetDialogRect(LPRECT r)
{
	GetClientRect(r);	
	if (r->right < m_sizeAll.cx)
	{
		r->right = m_sizeAll.cx;
	}
	if (r->bottom < m_sizeAll.cy)
	{
		r->bottom = m_sizeAll.cy;
	}
}

void CLocalizeAppDemoView::GetOffset(LPPOINT offset)
{
	*offset = m_ptOffset;
}

void CLocalizeAppDemoView::DoPaint(CDCHandle /*dc*/)
{
}
