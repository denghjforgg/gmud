// ChildView.h : CChildView ��Ľӿ�
//
#pragma once
#include "glew.h"

// CChildView ����
class CChildView : public CWnd
{
	//˽�б���
private:
	HDC m_hDC;					//�ڴ�DC
	HGLRC m_hRC;				//OpenGL��RC
	POINT2D_H m_MoveOrigin;		//ƽ�Ƶ�����ԭ��
	GLCOLOR m_backColor;		//������ɫ
	CPoint m_MouseCurPt;		//��ǰ�����Ļ����
	CPoint m_MouseLastPt;		//��һ�ε���Ļ����
	SIZE m_sizeWindows;			//���ڴ�С

	//�̳б���
protected:

	//��������
public:

	//���캯��
public:
	CChildView();
	virtual ~CChildView();

	//˽�к���
private:	
	void Draw();

	//�̳к���
protected:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnDestroy();
	afx_msg void OnPaint();
	DECLARE_MESSAGE_MAP()

	//��������
public:

};

