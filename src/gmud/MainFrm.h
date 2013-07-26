// MainFrm.h : CMainFrame 类的接口
//

#pragma once
#include "ChildView.h"

class CMainFrame : public CFrameWnd
{
	DECLARE_DYNAMIC(CMainFrame)
	//私有变量
private:

	//继承变量
protected:
	CStatusBar m_wndStatusBar;
	CChildView m_wndView;

	//公共变量
public:

	//构造函数
public:
	CMainFrame();
	virtual ~CMainFrame();

#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

	//私有函数
private:	

	//继承函数
protected:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	virtual BOOL OnCmdMsg(UINT nID, int nCode, void* pExtra, AFX_CMDHANDLERINFO* pHandlerInfo);
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnSetFocus(CWnd *pOldWnd);
	DECLARE_MESSAGE_MAP()

	//公共函数
public:

};


