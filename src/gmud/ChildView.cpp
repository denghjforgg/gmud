// ChildView.cpp : CChildView 类的实现
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
	m_hRC = NULL;				//OpenGL的RC
	m_MoveOrigin.x = m_MoveOrigin.y = 0.0;		//平移的坐标原点
	m_MouseCurPt.SetPoint(ERROR_COORD,ERROR_COORD);
	m_MouseLastPt = m_MouseCurPt;
	m_sizeWindows.cx = m_sizeWindows.cy = 0;
}

CChildView::~CChildView()
{
}

//////////////////////////////////////////////////////////////////////////
//私有
void CChildView::Draw()
{

}

//////////////////////////////////////////////////////////////////////////
//继承

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

// CChildView 消息处理程序
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
		sizeof(PIXELFORMATDESCRIPTOR),	// size of this pfd			pfd大小
		1,								// version number			版本号
		PFD_DRAW_TO_WINDOW |			// support window			支持窗口
		PFD_SUPPORT_OPENGL |			// support OpenGL			支持OpenGL
		PFD_DOUBLEBUFFER,				// double buffered			双缓冲
		PFD_TYPE_RGBA,					// RGBA type				RGBA类型
		24,								// 24-bit color depth		24位颜色深度
		0, 0, 0, 0, 0, 0,				// color bits ignored		忽略的颜色位
		0,								// no alpha buffer			无alpha缓冲区
		0,								// shift bit ignored		变换位忽略
		0,								// no accumulation buffer	无堆积缓冲
		0, 0, 0, 0, 					// accum bits ignored		堆积位忽略
		32,								// 32-bit z-buffer			32位Z-缓冲QQ
		0,								// no stencil buffer		无蒙板缓冲
		0,								// no auxiliary buffer		无辅助缓冲
		PFD_MAIN_PLANE,					// main layer				主层
		0,								// reserved					保留
		0, 0, 0							// layer masks ignored		层掩码

	};

	m_hDC = ::GetDC(m_hWnd);
	if (m_hDC == NULL)
	{
		return FALSE;
	}

	// get the device context's best-available-match pixel format，获取DC的最配匹象素格式
	int iPixelFormat = ::ChoosePixelFormat(m_hDC, &pfd);
	if (iPixelFormat==0)
	{
		::ReleaseDC(m_hWnd, m_hDC);
		return FALSE;
	}

	// make that the device context's current pixel format，使之成为DC的当前象素格式
	if (!::SetPixelFormat(m_hDC, iPixelFormat, &pfd))
	{
		::ReleaseDC(m_hWnd, m_hDC);
		return FALSE;
	}

	//创建RC
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
	//深度测试
	glEnable( GL_DEPTH_TEST );
	//这里我们比较常用的深度测试函数有 GL_LESS 和 GL_LEQUAL 
	//两者的区别在于当深度相同时是显示新的象素 还是老的象素
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

	// 打开混合
	if (FALSE)
	{
	}

	//字体
//	m_rsFont.m_hDC = m_hDC;
//	m_rsFont.m_hRC = m_hRC;
//	m_rsFont.CreateFontEx( LPCTSTR("Courier New"),TRUE );//幼圆

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
	// 不要为绘制消息而调用 CWnd::OnPaint()
	CPaintDC dc(this); // 用于绘制的设备上下文

	// TODO: 在此处添加消息处理程序代码
	wglMakeCurrent(m_hDC, m_hRC);

	//设置刷新背景色 
	glClearColor(m_backColor.r / 255.0f, m_backColor.g / 255.0f, m_backColor.b / 255.0f, m_backColor.a / 255.0f);

	// 清除屏幕和深度缓存
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); 

	glPushMatrix();

	//当您调用glLoadIdentity()之后，您实际上讲当前点移到了屏幕中心，X坐标轴从左至右，
	//Y坐标轴从下至上，Z坐标轴从里至外。OpenGL屏幕中心的坐标值是X和Y轴上的0.0f点。
	// 中心左面的坐标值是负值，右面是正值。移向屏幕顶端是正值，移向屏幕底端是负值。
	// 移入屏幕深处是负值，移出屏幕则是正值。
	glLoadIdentity();	// 重置当前的模型观察矩阵

//	glScaled(m_dScale, m_dScale, m_dScale);

	//glTranslatef(x, y, z)沿着 X, Y 和 Z 轴移动。
	//根据前面的次序，下面的代码沿着X轴左移m_lfX0个单位，Y轴下移m_lfY0各单位，
	//Z如果为负值，则为移入屏幕深处
	//注意在glTranslatef(x, y, z)中当您移动的时候，您并不是相对屏幕中心移动，
	//而是相对与当前所在的屏幕位置。
	glTranslated(-m_MoveOrigin.x, -m_MoveOrigin.y, 0.0);

	//这里要注意的是存在两种不同的坐标变换方式，
	//glTranslatef(x, y, z)中的x, y, z是相对与您当前所在点的位移，
	//但glVertex(x,y,z)是相对于glTranslatef(x, y, z)移动后的新原点的位移。
	//因而这里可以认为glTranslate移动的是坐标原点，glVertex中的点是相对最新的坐标原点的坐标值。


//   几何图元类型和说明
//   类型   				 说明
//   GL_POINTS  			单个顶点集
//   GL_LINES   			多组双顶点线段
//   GL_POLYGON 			单个简单填充凸多边形
//   GL_TRAINGLES   		多组独立填充三角形
//   GL_QUADS   			多组独立填充四边形
//   GL_LINE_STRIP  		不闭合折线
//   GL_LINE_LOOP   		闭合折线
//   GL_TRAINGLE_STRIP  	线型连续填充三角形串
//   GL_TRAINGLE_FAN		扇形连续填充三角形串
//   GL_QUAD_STRIP  		连续填充四边形串

	//绘制四边形
	// 	for (int i=0 ; i<m_iLayerQuadNum ; i++)
	// 	{
	// 		if(m_LayerQuadR[i].IsShow()) m_LayerQuadR[i].QR_Draw();
	// 	}
	// 
	// 
	// 	//绘制点
	// 	for (int i=0 ; i<m_iLayerPointNum ; i++)
	// 	{
	// 		if(m_LayerPointR[i].IsShow()) m_LayerPointR[i].PR_Draw(m_dScale);
	// 	}
	// 
	// 	//绘制文字
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
		selectFont(48, GB2312_CHARSET, "楷体_GB2312");
		glColor3f(1.0f, 1.0f, 0.0f);
		glRasterPos2f(500.0f, 1000.0f);
		drawCNString("asdfsadf当代的中国汉字");
		selectFont(48, DEFAULT_CHARSET, "华文仿宋");
		glColor3f(0.0f, 1.0f, 0.0f);
		glRasterPos2f(40.0f, 150.0f);
		drawCNString("傳統的中國漢字");
	*/
	Draw();

	glPopMatrix();
	SwapBuffers(m_hDC);
//	glDisable(GL_BLEND);	
 	wglMakeCurrent( NULL,NULL );
}

//////////////////////////////////////////////////////////////////////////
//公共













