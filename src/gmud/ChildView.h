// ChildView.h : CChildView 类的接口
//
#pragma once
#include "glew.h"

// CChildView 窗口
class CChildView : public CWnd
{
	//私有变量
private:
	HDC m_hDC;					//内存DC
	HGLRC m_hRC;				//OpenGL的RC
	POINT2D_H m_MoveOrigin;		//平移的坐标原点
	GLCOLOR m_backColor;		//背景颜色
	CPoint m_MouseCurPt;		//当前鼠标屏幕坐标
	CPoint m_MouseLastPt;		//上一次的屏幕坐标
	SIZE m_sizeWindows;			//窗口大小

	//继承变量
protected:

	//公共变量
public:

	//构造函数
public:
	CChildView();
	virtual ~CChildView();

	//私有函数
private:	
	void Draw();

	//继承函数
protected:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnDestroy();
	afx_msg void OnPaint();
	DECLARE_MESSAGE_MAP()

	//公共函数
public:

};

