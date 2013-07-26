// MainFrm.h : CMainFrame ��Ľӿ�
//

#pragma once
#include "ChildView.h"

class CMainFrame : public CFrameWnd
{
	DECLARE_DYNAMIC(CMainFrame)
	//˽�б���
private:

	//�̳б���
protected:
	CStatusBar m_wndStatusBar;
	CChildView m_wndView;

	//��������
public:

	//���캯��
public:
	CMainFrame();
	virtual ~CMainFrame();

#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

	//˽�к���
private:	

	//�̳к���
protected:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	virtual BOOL OnCmdMsg(UINT nID, int nCode, void* pExtra, AFX_CMDHANDLERINFO* pHandlerInfo);
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnSetFocus(CWnd *pOldWnd);
	DECLARE_MESSAGE_MAP()

	//��������
public:

};


