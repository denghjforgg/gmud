// Gmud.h : Gmud 应用程序的主头文件
//
#pragma once

#ifndef __AFXWIN_H__
	#error "在包含此文件之前包含“stdafx.h”以生成 PCH 文件"
#endif

#include "resource.h"       // 主符号

// CGmudApp:
// 有关此类的实现，请参阅 Gmud.cpp
//
class CGmudApp : public CWinApp
{
	//私有变量
private:

	//继承变量
protected:

	//公共变量
public:

	//构造函数
public:
	CGmudApp();
	
	//私有函数
private:	

	//继承函数
protected:
	virtual BOOL InitInstance();
	virtual int ExitInstance();
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()

	//公共函数
public:

};

extern CGmudApp theApp;
