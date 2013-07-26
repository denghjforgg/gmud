// ChildView.cpp : CChildView ���ʵ��
//

#include "stdafx.h"
#include "GmudApp.h"
#include "ChildView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CChildView
CChildView::CChildView()
{
	m_hDC = NULL;
	m_hRC = NULL;				//OpenGL��RC
	m_MoveOrigin.x = m_MoveOrigin.y = 0.0;		//ƽ�Ƶ�����ԭ��
	m_MouseCurPt.SetPoint(ERROR_COORD,ERROR_COORD);
	m_MouseLastPt = m_MouseCurPt;
	m_sizeWindows.cx = m_sizeWindows.cy = 0;
}

CChildView::~CChildView()
{
}

//////////////////////////////////////////////////////////////////////////
//˽��
void CChildView::Draw()
{

}

//////////////////////////////////////////////////////////////////////////
//�̳�

BOOL CChildView::PreCreateWindow(CREATESTRUCT& cs) 
{
	if (!CWnd::PreCreateWindow(cs))
	{	
		return FALSE;
	}

	cs.dwExStyle |= WS_EX_CLIENTEDGE;
	cs.style &= ~WS_BORDER;
	cs.lpszClass = AfxRegisterWndClass(CS_HREDRAW|CS_VREDRAW|CS_DBLCLKS, 
		::LoadCursor(NULL, IDC_ARROW), reinterpret_cast<HBRUSH>(COLOR_WINDOW+1), NULL);

	return TRUE;
}

// CChildView ��Ϣ�������
BEGIN_MESSAGE_MAP(CChildView, CWnd)
	ON_WM_CREATE()
	ON_WM_DESTROY()
	ON_WM_PAINT()
END_MESSAGE_MAP()

int CChildView::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if(CWnd::OnCreate(lpCreateStruct)==-1)
	{
		return -1;
	}

	PIXELFORMATDESCRIPTOR pfd =
	{
		sizeof(PIXELFORMATDESCRIPTOR),	// size of this pfd			pfd��С
		1,								// version number			�汾��
		PFD_DRAW_TO_WINDOW |			// support window			֧�ִ���
		PFD_SUPPORT_OPENGL |			// support OpenGL			֧��OpenGL
		PFD_DOUBLEBUFFER,				// double buffered			˫����
		PFD_TYPE_RGBA,					// RGBA type				RGBA����
		24,								// 24-bit color depth		24λ��ɫ���
		0, 0, 0, 0, 0, 0,				// color bits ignored		���Ե���ɫλ
		0,								// no alpha buffer			��alpha������
		0,								// shift bit ignored		�任λ����
		0,								// no accumulation buffer	�޶ѻ�����
		0, 0, 0, 0, 					// accum bits ignored		�ѻ�λ����
		32,								// 32-bit z-buffer			32λZ-����QQ
		0,								// no stencil buffer		���ɰ建��
		0,								// no auxiliary buffer		�޸�������
		PFD_MAIN_PLANE,					// main layer				����
		0,								// reserved					����
		0, 0, 0							// layer masks ignored		������

	};

	m_hDC = ::GetDC(m_hWnd);
	if (m_hDC == NULL)
	{
		return FALSE;
	}

	// get the device context's best-available-match pixel format����ȡDC������ƥ���ظ�ʽ
	int iPixelFormat = ::ChoosePixelFormat(m_hDC, &pfd);
	if (iPixelFormat==0)
	{
		::ReleaseDC(m_hWnd, m_hDC);
		return FALSE;
	}

	// make that the device context's current pixel format��ʹ֮��ΪDC�ĵ�ǰ���ظ�ʽ
	if (!::SetPixelFormat(m_hDC, iPixelFormat, &pfd))
	{
		::ReleaseDC(m_hWnd, m_hDC);
		return FALSE;
	}

	//����RC
	m_hRC = wglCreateContext(m_hDC);
	if (m_hRC==NULL)
	{
		::ReleaseDC(m_hWnd, m_hDC);
		return FALSE;
	}

	wglMakeCurrent(m_hDC, m_hRC);

	GLenum err = glewInit();
	if ( err != GLEW_OK)
	{
		AfxMessageBox(_T("glewInit:Error"));
	}

	glEnable(GL_TEXTURE_2D);
/*
	//��Ȳ���
	glEnable( GL_DEPTH_TEST );
	//�������ǱȽϳ��õ���Ȳ��Ժ����� GL_LESS �� GL_LEQUAL 
	//���ߵ��������ڵ������ͬʱ����ʾ�µ����� �����ϵ�����
	glDepthFunc( GL_LESS );
*/
	if (FALSE)
	{
		glEnable(GL_POINT_SMOOTH);
		glEnable(GL_LINE_SMOOTH);
		glEnable(GL_POLYGON_SMOOTH);
	}
	glShadeModel(GL_SMOOTH);
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
	if (FALSE)
	{
		glHint(GL_POINT_SMOOTH_HINT, GL_NICEST);
		glHint(GL_LINE_SMOOTH_HINT, GL_NICEST);
		glHint(GL_POLYGON_SMOOTH_HINT, GL_NICEST);
	}

	if (TRUE)
	{
		GLfloat mat_specular[3];
		GLfloat mat_emitted[3];
		GLfloat mat_shininess[1];
		GLfloat mat_ambient[3];
		GLfloat mat_diffuse[3];
		GLfloat light_specular[3];
		GLfloat light_cutoff[1];
		GLfloat light_linear[1];
		GLfloat light_position[4];

		mat_specular[0] = mat_specular[1] = mat_specular[2] = 0.1f;
		mat_emitted[0] = mat_emitted[1] = mat_emitted[2] = 0.2f;
		mat_shininess[0] = 0.5f;
		mat_ambient[0] = mat_ambient[1] = mat_ambient[2] = 0.1f;
		mat_diffuse[0] = mat_diffuse[1] = mat_diffuse[2] = 0.5f;
		light_specular[0] = light_specular[1] = light_specular[2] = 0.1f;
		light_cutoff[0] = 180.0f;
		light_linear[0] = 0.0f;
		light_position[0] = -800.0f;
		light_position[1] = 800.0f;
		light_position[2] = 800.0f;
		light_position[3] = 1.0f;

		glEnable(GL_LIGHTING);
		glMaterialfv(GL_FRONT, GL_EMISSION, mat_emitted);
		glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
		glMaterialf(GL_FRONT, GL_SHININESS, mat_shininess[0]);
		glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
		glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);

		glEnable(GL_LIGHT0);
		glLightfv(GL_LIGHT0, GL_POSITION, light_position);
		glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);
		glLightfv(GL_LIGHT0, GL_SPOT_CUTOFF, light_cutoff);
		glLightfv(GL_LIGHT0, GL_LINEAR_ATTENUATION, light_linear);
	}


	glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE);
	glEnable(GL_COLOR_MATERIAL);
	glEnable(GL_AUTO_NORMAL);
	glEnable(GL_NORMALIZE);

	// �򿪻��
	if (FALSE)
	{
	}

	//����
//	m_rsFont.m_hDC = m_hDC;
//	m_rsFont.m_hRC = m_hRC;
//	m_rsFont.CreateFontEx( LPCTSTR("Courier New"),TRUE );//��Բ

	wglMakeCurrent(NULL, NULL);

	return TRUE;
}

void CChildView::OnDestroy()
{
	wglDeleteContext(m_hRC);
	m_hRC = NULL;

	::ReleaseDC(m_hWnd, m_hDC);
	m_hDC = NULL;

	CWnd::OnDestroy();
}

void CChildView::OnPaint() 
{
	// ��ҪΪ������Ϣ������ CWnd::OnPaint()
	CPaintDC dc(this); // ���ڻ��Ƶ��豸������

	// TODO: �ڴ˴������Ϣ����������
	wglMakeCurrent(m_hDC, m_hRC);

	//����ˢ�±���ɫ 
	glClearColor(m_backColor.r / 255.0f, m_backColor.g / 255.0f, m_backColor.b / 255.0f, m_backColor.a / 255.0f);

	// �����Ļ����Ȼ���
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); 

	glPushMatrix();

	//��������glLoadIdentity()֮����ʵ���Ͻ���ǰ���Ƶ�����Ļ���ģ�X������������ң�
	//Y������������ϣ�Z������������⡣OpenGL��Ļ���ĵ�����ֵ��X��Y���ϵ�0.0f�㡣
	// �������������ֵ�Ǹ�ֵ����������ֵ��������Ļ��������ֵ��������Ļ�׶��Ǹ�ֵ��
	// ������Ļ��Ǹ�ֵ���Ƴ���Ļ������ֵ��
	glLoadIdentity();	// ���õ�ǰ��ģ�͹۲����

//	glScaled(m_dScale, m_dScale, m_dScale);

	//glTranslatef(x, y, z)���� X, Y �� Z ���ƶ���
	//����ǰ��Ĵ�������Ĵ�������X������m_lfX0����λ��Y������m_lfY0����λ��
	//Z���Ϊ��ֵ����Ϊ������Ļ�
	//ע����glTranslatef(x, y, z)�е����ƶ���ʱ���������������Ļ�����ƶ���
	//��������뵱ǰ���ڵ���Ļλ�á�
	glTranslated(-m_MoveOrigin.x, -m_MoveOrigin.y, 0.0);

	//����Ҫע����Ǵ������ֲ�ͬ������任��ʽ��
	//glTranslatef(x, y, z)�е�x, y, z�����������ǰ���ڵ��λ�ƣ�
	//��glVertex(x,y,z)�������glTranslatef(x, y, z)�ƶ������ԭ���λ�ơ�
	//������������ΪglTranslate�ƶ���������ԭ�㣬glVertex�еĵ���������µ�����ԭ�������ֵ��


//   ����ͼԪ���ͺ�˵��
//   ����   				 ˵��
//   GL_POINTS  			�������㼯
//   GL_LINES   			����˫�����߶�
//   GL_POLYGON 			���������͹�����
//   GL_TRAINGLES   		����������������
//   GL_QUADS   			�����������ı���
//   GL_LINE_STRIP  		���պ�����
//   GL_LINE_LOOP   		�պ�����
//   GL_TRAINGLE_STRIP  	����������������δ�
//   GL_TRAINGLE_FAN		����������������δ�
//   GL_QUAD_STRIP  		��������ı��δ�

	//�����ı���
	// 	for (int i=0 ; i<m_iLayerQuadNum ; i++)
	// 	{
	// 		if(m_LayerQuadR[i].IsShow()) m_LayerQuadR[i].QR_Draw();
	// 	}
	// 
	// 
	// 	//���Ƶ�
	// 	for (int i=0 ; i<m_iLayerPointNum ; i++)
	// 	{
	// 		if(m_LayerPointR[i].IsShow()) m_LayerPointR[i].PR_Draw(m_dScale);
	// 	}
	// 
	// 	//��������
	// 	for (int i=0 ; i<m_iLayerFontNum ; i++)
	// 	{
	// 		if(m_LayerFontR[i].IsShow()) m_LayerFontR[i].FR_Draw();
	//	}

//	glEnable(GL_BLEND);
//	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	/*
		selectFont(16, ANSI_CHARSET, "Comic Sans MS");
		glColor3f(1.0f, 0.0f, 0.0f);
		glRasterPos2f(200.0f, 30.0f);
		drawString("Hello, World!");
		selectFont(48, GB2312_CHARSET, "����_GB2312");
		glColor3f(1.0f, 1.0f, 0.0f);
		glRasterPos2f(500.0f, 1000.0f);
		drawCNString("asdfsadf�������й�����");
		selectFont(48, DEFAULT_CHARSET, "���ķ���");
		glColor3f(0.0f, 1.0f, 0.0f);
		glRasterPos2f(40.0f, 150.0f);
		drawCNString("���y���Ї��h��");
	*/
	Draw();

	glPopMatrix();
	SwapBuffers(m_hDC);
//	glDisable(GL_BLEND);	
 	wglMakeCurrent( NULL,NULL );
}

//////////////////////////////////////////////////////////////////////////
//����













