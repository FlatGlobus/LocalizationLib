// LocalizeAppDemoView.h : interface of the CLocalizeAppDemoView class
//
/////////////////////////////////////////////////////////////////////////////

#pragma once

#include "LayoutMgr.h"
#include <atlscrl.h>

//{{WTLBUILDER_INCLUDE_DECLARATION
//}}WTLBUILDER_INCLUDE_DECLARATION

//{{WTLBUILDER_CONTROL_ID_DECLARATION
#define	IDC_CLOCALIZEAPPDEMOVIEW_BUTTON16	1016
#define	IDC_CLOCALIZEAPPDEMOVIEW_LISTBOX17	1017
#define	IDC_CLOCALIZEAPPDEMOVIEW_STATIC18	1018
//}}WTLBUILDER_CONTROL_ID_DECLARATION

//{{WTLBUILDER_WINDOW_STYLE
typedef CWinTraits<WS_CHILD|WS_BORDER|WS_VISIBLE|WS_GROUP|WS_TABSTOP,WS_EX_WINDOWEDGE>	CLocalizeAppDemoViewWinTraits;
//}}WTLBUILDER_WINDOW_STYLE

class CLocalizeAppDemoView : public CWindowImpl<CLocalizeAppDemoView, CWindow, CLocalizeAppDemoViewWinTraits>,
	public CScrollImpl<CLocalizeAppDemoView>,public LayoutMgr<CLocalizeAppDemoView>, public CLocalization
{
	CToolTipCtrl	m_toolTip;
//{{WTLBUILDER_MEMBER_DECLARATION
	CFont	m_formFont;
	CButton	m_button16;
	CListBox	m_listbox17;
	CStatic	m_static18;
//}}WTLBUILDER_MEMBER_DECLARATION
	void InitLayout(void);
	virtual void DefineLayout();
public:
	virtual void GetDialogRect(LPRECT r);
	virtual void GetOffset(LPPOINT offset);
	virtual void DoPaint(CDCHandle /*dc*/);
	static const UINT _controlsToClip[];
	typedef CWindowImpl<CLocalizeAppDemoView, CWindow, CLocalizeAppDemoViewWinTraits> baseClass;

//{{WTLBUILDER_WINCLASS_DECLARATION
	DECLARE_WND_CLASS_EX(NULL,CS_VREDRAW|CS_HREDRAW|CS_DBLCLKS,COLOR_WINDOW)
//}}WTLBUILDER_WINCLASS_DECLARATION

	BOOL PreTranslateMessage(MSG* pMsg);
	BEGIN_MSG_MAP(CLocalizeAppDemoView)
		MESSAGE_HANDLER(WM_SIZE, LayoutMgr<CLocalizeAppDemoView>::OnSize)
		MESSAGE_HANDLER(WM_ERASEBKGND, LayoutMgr<CLocalizeAppDemoView>::OnEraseBackground)
		MESSAGE_HANDLER(WM_CREATE, OnCreate)
		MESSAGE_HANDLER(WM_DESTROY, OnDestroy)
		MESSAGE_HANDLER(WM_PAINT, OnPaint)
		//localization support
		CHAIN_MSG_MAP(CLocalization)
		//
		REFLECT_NOTIFICATIONS_EX()
	END_MSG_MAP()

	CLocalizeAppDemoView(void);

// Handler prototypes (uncomment arguments if needed):
//	LRESULT MessageHandler(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/)
//	LRESULT CommandHandler(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
//	LRESULT NotifyHandler(int /*idCtrl*/, LPNMHDR /*pnmh*/, BOOL& /*bHandled*/)

	LRESULT OnCreate(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/);
	LRESULT OnDestroy(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/);
	LRESULT OnPaint(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/);
};
