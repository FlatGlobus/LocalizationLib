// Copyright (C) FlatGlobus(wtlbuilder@gmail.com) All rights reserved.
//
// This file is a part of the WTLBuilder.
// The use and distribution terms for this software are covered by the
// Microsoft Public License (http://opensource.org/licenses/MS-PL)
// which can be found in the file MS-PL.txt at the root folder.

#pragma once

#include "LayoutMgr.h"
#include <atlscrl.h>

//{{WTLBUILDER_INCLUDE_DECLARATION
//}}WTLBUILDER_INCLUDE_DECLARATION

//{{WTLBUILDER_CONTROL_ID_DECLARATION
//}}WTLBUILDER_CONTROL_ID_DECLARATION

//{{WTLBUILDER_WINDOW_STYLE
typedef CWinTraits<WS_OVERLAPPED|WS_THICKFRAME|WS_CLIPSIBLINGS|WS_CAPTION|WS_SYSMENU|WS_MINIMIZEBOX|WS_MAXIMIZEBOX,WS_EX_WINDOWEDGE>	CMainFrameWinTraits;
//}}WTLBUILDER_WINDOW_STYLE

class CMainFrame : public CFrameWindowImpl<CMainFrame,CWindow ,CMainFrameWinTraits>, public CUpdateUI<CMainFrame>,
		public CScrollImpl<CMainFrame>,public LayoutMgr<CMainFrame>,
		public CMessageFilter, public CIdleHandler, 
		public CFrameWindowLocalization<CMainFrame>//localization support
{
	CToolTipCtrl	m_toolTip;
//{{WTLBUILDER_MEMBER_DECLARATION
	CFont	m_formFont;
//}}WTLBUILDER_MEMBER_DECLARATION

	void InitLayout(void);
	virtual void DefineLayout();
	virtual void DoPaint(CDCHandle /*dc*/);
public:
	virtual void GetOffset(LPPOINT offset);
	virtual void GetDialogRect(LPRECT r);
	static const UINT _controlsToClip[];
	typedef CFrameWindowImpl<CMainFrame, CWindow, CMainFrameWinTraits>	baseClass;

//{{WTLBUILDER_WINCLASS_DECLARATION
	DECLARE_FRAME_WND_CLASS(NULL,IDR_MAINFRAME)
//}}WTLBUILDER_WINCLASS_DECLARATION

	CLocalizeAppDemoView m_view;

	CCommandBarCtrl m_CmdBar;

	virtual BOOL PreTranslateMessage(MSG* pMsg);
	virtual BOOL OnIdle();

	BEGIN_UPDATE_UI_MAP(CMainFrame)
		UPDATE_ELEMENT(ID_VIEW_TOOLBAR, UPDUI_MENUPOPUP)
		UPDATE_ELEMENT(ID_VIEW_STATUS_BAR, UPDUI_MENUPOPUP)
	END_UPDATE_UI_MAP()

	BEGIN_MSG_MAP(CMainFrame)
		MESSAGE_HANDLER(WM_SIZE, LayoutMgr<CMainFrame>::OnSize)
		MESSAGE_HANDLER(WM_ERASEBKGND, LayoutMgr<CMainFrame>::OnEraseBackground)
		MESSAGE_HANDLER(WM_CREATE, OnCreate)
		MESSAGE_HANDLER(WM_DESTROY, OnDestroy)
		COMMAND_ID_HANDLER(ID_APP_EXIT, OnFileExit)
		COMMAND_ID_HANDLER(ID_FILE_NEW, OnFileNew)
		COMMAND_ID_HANDLER(ID_VIEW_TOOLBAR, OnViewToolBar)
		COMMAND_ID_HANDLER(ID_VIEW_STATUS_BAR, OnViewStatusBar)
		COMMAND_ID_HANDLER(ID_APP_ABOUT, OnAppAbout)
		//localization support
		CHAIN_MSG_MAP(CFrameWindowLocalization<CMainFrame>)
		//
		CHAIN_MSG_MAP(CUpdateUI<CMainFrame>)
		CHAIN_MSG_MAP(baseClass)
		//REFLECT_NOTIFICATIONS_EX()
	END_MSG_MAP()

	CMainFrame(void);

// Handler prototypes (uncomment arguments if needed):
//	LRESULT MessageHandler(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/)
//	LRESULT CommandHandler(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
//	LRESULT NotifyHandler(int /*idCtrl*/, LPNMHDR /*pnmh*/, BOOL& /*bHandled*/)

	LRESULT OnCreate(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/);
	LRESULT OnDestroy(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/);
	LRESULT OnFileExit(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/);
	LRESULT OnFileNew(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/);
	LRESULT OnViewToolBar(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/);
	LRESULT OnViewStatusBar(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/);
	LRESULT OnAppAbout(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/);
};
