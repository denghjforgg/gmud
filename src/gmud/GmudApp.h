// Gmud.h : Gmud Ӧ�ó������ͷ�ļ�
//
#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"       // ������

// CGmudApp:
// �йش����ʵ�֣������ Gmud.cpp
//
class CGmudApp : public CWinApp
{
	//˽�б���
private:

	//�̳б���
protected:

	//��������
public:

	//���캯��
public:
	CGmudApp();
	
	//˽�к���
private:	

	//�̳к���
protected:
	virtual BOOL InitInstance();
	virtual int ExitInstance();
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()

	//��������
public:

};

extern CGmudApp theApp;
