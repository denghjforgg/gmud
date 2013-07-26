#pragma once

#ifndef ERROR_COORD
#define ERROR_COORD -9999
#endif

#ifndef struct_tag_POINT2DH
#define struct_tag_POINT2DH
typedef struct _tag_POINT2DH
{
	double x;
	double y;
	_tag_POINT2DH()
	{
		Init();
	}
	_tag_POINT2DH(double *pX,double *pY)
	{
		x = *pX;
		y = *pY;
	}
	void Init()
	{
		x = ERROR_COORD;
		y = ERROR_COORD;
	}
}POINT2D_H,*PPOINT2D_H;
#endif

#ifndef DEFAULT_BACK_COLOR
#define DEFAULT_BACK_COLOR	RGB(42,42,42) | 0x00000000
#endif

#ifndef DEFAULT_COLOR
#define DEFAULT_COLOR		0x00000000
#endif

#ifndef GetAValue
#define GetAValue(rgb) (LOBYTE((rgb)>>24))
#endif


#ifndef struct_tag_GLCOLOR
#define struct_tag_GLCOLOR
//ÑÕÉ«
typedef struct _tag_GLCOLOR
{
	// 	GLfloat glR;
	// 	GLfloat glG;
	// 	GLfloat glB;
	// 	GLfloat glA;
	BYTE r;
	BYTE g;
	BYTE b;
	BYTE a;
	COLORREF v;
	BYTE bit;
	_tag_GLCOLOR()
	{
		SetRGB4(DEFAULT_COLOR);
	}
	_tag_GLCOLOR(BYTE rV,BYTE gV,BYTE bV)
	{
		SetRGB3(rV,gV,bV);
	}
	void SetRGB3(BYTE rV,BYTE gV,BYTE bV)
	{
		r = rV;
		g = gV;
		b = bV;

		// 		glR = r/255.0f;
		// 		glG = g/255.0f;
		// 		glB = b/255.0f;

		v = RGB(r,g,b);
		bit = 24;
	}
	void SetRGB3(COLORREF cV)
	{
		r = GetRValue(cV);
		g = GetGValue(cV);
		b = GetBValue(cV);

		// 		glR = r/255.0f;
		// 		glG = g/255.0f;
		// 		glB = b/255.0f;

		v = cV;
		bit = 24;
	}
	BOOL GetRGB3(BYTE &rV,BYTE &gV,BYTE &bV)
	{
		if(bit<24) return FALSE;
		rV = r;
		gV = g;
		bV = b;
		return TRUE;
	}
	void SetRGB4(BYTE rV,BYTE gV,BYTE bV,BYTE aV)
	{
		r = rV;
		g = gV;
		b = bV;
		a = aV;
		v = RGB(r,g,b) | aV<<24;

		// 		glR = r/255.0f;
		// 		glG = g/255.0f;
		// 		glB = b/255.0f;
		// 		glA = a/255.0f;

		bit = 32;
	}
	void SetRGB4(COLORREF cV)
	{
		r = GetRValue(cV);
		g = GetGValue(cV);
		b = GetBValue(cV);
		a = GetAValue(cV);

		// 		glR = r/255.0f;
		// 		glG = g/255.0f;
		// 		glB = b/255.0f;
		// 		glA = a/255.0f;

		v = cV;
		bit = 32;
	}
	BOOL GetRGB4(BYTE &rV,BYTE &gV,BYTE &bV,BYTE &aV)
	{
		if(bit<32) return FALSE;
		rV = r;
		gV = g;
		bV = b;
		aV = a;
		return TRUE;
	}
	COLORREF GetColor()
	{
		return v;
	}
}GLCOLOR,*P_GLCOLOR;
#endif