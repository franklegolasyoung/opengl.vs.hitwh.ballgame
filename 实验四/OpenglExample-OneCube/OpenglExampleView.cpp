
// OpenglExampleView.cpp : COpenglExampleView 类的实现
//

#include "stdafx.h"
// SHARED_HANDLERS 可以在实现预览、缩略图和搜索筛选器句柄的
// ATL 项目中进行定义，并允许与该项目共享文档代码。
#ifndef SHARED_HANDLERS
#include "OpenglExample.h"
#endif


#include "OpenglExampleDoc.h"
#include "OpenglExampleView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif
#include <vector>
using namespace std;
// COpenglExampleView

IMPLEMENT_DYNCREATE(COpenglExampleView, CView)

BEGIN_MESSAGE_MAP(COpenglExampleView, CView)
	ON_WM_CONTEXTMENU()
	ON_WM_CREATE()
	ON_WM_DESTROY()
	ON_WM_SIZE()
	ON_WM_ERASEBKGND()
	ON_COMMAND(ID_ROTATE, &COpenglExampleView::OnRotate)
	ON_WM_TIMER()
	ON_COMMAND(ID_Stop, &COpenglExampleView::OnStop)
	ON_COMMAND(ID_ROTATE_X, &COpenglExampleView::OnRotateX)
	ON_COMMAND(ID_ROTATE_Z, &COpenglExampleView::OnRotateZ)
	ON_COMMAND(ID_32780, &COpenglExampleView::On32780)
	ON_COMMAND(ID_NB_X, &COpenglExampleView::OnNbX)
	ON_COMMAND(ID_NB_Y, &COpenglExampleView::OnNbY)
	ON_COMMAND(ID_NB_Z, &COpenglExampleView::OnNbZ)
	ON_COMMAND(ID_NB_XYZ, &COpenglExampleView::OnNbXyz)
	ON_COMMAND(ID_NB_STOP, &COpenglExampleView::OnNbStop)
END_MESSAGE_MAP()

// COpenglExampleView 构造/析构

COpenglExampleView::COpenglExampleView()
{
	// TODO:  在此处添加构造代码
	m_angle = 0;
	m_rotate_axis = NOROTATE;
}

COpenglExampleView::~COpenglExampleView()
{
}

BOOL COpenglExampleView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO:  在此处通过修改
	//  CREATESTRUCT cs 来修改窗口类或样式

	return CView::PreCreateWindow(cs);
}

// COpenglExampleView 绘制

void COpenglExampleView::OnDraw(CDC* /*pDC*/)
{
	COpenglExampleDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;
	//wglMakeCurrent(m_hDC, m_hRC);
	RenderScene();
	SwapBuffers(m_hDC);
}

void COpenglExampleView::OnContextMenu(CWnd* /* pWnd */, CPoint point)
{
#ifndef SHARED_HANDLERS
	theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
#endif
}


// COpenglExampleView 诊断

#ifdef _DEBUG
void COpenglExampleView::AssertValid() const
{
	CView::AssertValid();
}

void COpenglExampleView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

COpenglExampleDoc* COpenglExampleView::GetDocument() const // 非调试版本是内联的
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(COpenglExampleDoc)));
	return (COpenglExampleDoc*)m_pDocument;
}
#endif //_DEBUG

void COpenglExampleView::RenderScene2()
{
	// clear color buffer and depth buffer
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glPushMatrix();
	glRotatef(30, 0, 1, 0); //glRotatef(angle,  rx, ry, rz);
	glRotatef(30, 1, 0, 0);
	glRotatef(30, 0, 0, 1);
	glBegin(GL_QUADS);
	// front
	glNormal3f(0, 0, -1);
	glVertex3f(0, 0, 0);
	glVertex3f(1, 0, 0);
	glVertex3f(1, 1, 0);
	glVertex3f(0, 1, 0);
	// bottom
	glNormal3f(0, -1, 0);
	glVertex3f(0, 0, 0);
	glVertex3f(0, 0, 1);
	glVertex3f(1, 0, 1);
	glVertex3f(1, 0, 0);

	//right
	glNormal3f(1, 0, 0);
	glVertex3f(1, 0, 0);
	glVertex3f(1, 0, 1);
	glVertex3f(1, 1, 1);
	glVertex3f(1, 1, 0);
	//left
	glNormal3f(-1, 0, 0);
	glVertex3f(0, 0, 0);
	glVertex3f(0, 1, 0);
	glVertex3f(0, 1, 1);
	glVertex3f(0, 0, 1);

	//top
	glNormal3f(0, 1, 0);
	glVertex3f(0, 1, 0);
	glVertex3f(1, 1, 0);
	glVertex3f(1, 1, 1);
	glVertex3f(0, 1, 1);


	//back
	glNormal3f(0, 0, 1);
	glVertex3f(0, 0, 1);
	glVertex3f(0, 1, 1);
	glVertex3f(1, 1, 1);
	glVertex3f(1, 0, 1);

	glEnd();
	glPopMatrix();

	glFlush();    //强制执行opengl语句

}

void  COpenglExampleView::draw_cube()
{
	glBegin(GL_QUADS);
	// back
	glNormal3f(0, 0, -1);
	glVertex3f(0, 0, 0);
	glVertex3f(0, 1, 0);
	glVertex3f(1, 1, 0);
	glVertex3f(1, 0, 0);

	// bottom
	glNormal3f(0, -1, 0);
	glVertex3f(0, 0, 0);
	glVertex3f(1, 0, 0);
	glVertex3f(1, 0, 1);
	glVertex3f(0, 0, 1);

	//right
	glNormal3f(1, 0, 0);
	glVertex3f(1, 0, 0);
	glVertex3f(1, 1, 0);
	glVertex3f(1, 1, 1);
	glVertex3f(1, 0, 1);

	//left
	glNormal3f(-1, 0, 0);
	glVertex3f(0, 0, 0);
	glVertex3f(0, 0, 1);
	glVertex3f(0, 1, 1);
	glVertex3f(0, 1, 0);

	//top
	glNormal3f(0, 1, 0);
	glVertex3f(0, 1, 0);
	glVertex3f(0, 1, 1);
	glVertex3f(1, 1, 1);
	glVertex3f(1, 1, 0);


	//front
	glNormal3f(0, 0, 1);
	glVertex3f(0, 0, 1);
	glVertex3f(1, 0, 1);
	glVertex3f(1, 1, 1);
	glVertex3f(0, 1, 1);

	glEnd();

	//glPopMatrix();
}
// COpenglExampleView 消息处理程序
void COpenglExampleView::RenderScene()
{
	// clear color buffer and depth buffer
	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
	if (m_rotate_axis == XX)
	{
		glRotatef(m_angle, 1, 0, 0);
	}
	else if (m_rotate_axis == YY)
	{
		glRotatef(m_angle, 0, 1, 0);
	}
	else if (m_rotate_axis == ZZ)
	{
		glRotatef(m_angle, 0, 0, 1);
	}
	else if (m_rotate_axis == NOROTATE)
	{
		glRotatef(315, 0, 1, 0);
		glRotatef(40, 0, 1, 1);
		glRotatef(310, 0, 1, -1);
		glRotatef(350, 1, 1, 0);
		glRotatef(355, 0, 0, 1);
	}

	glLineWidth(4.0f);
	glBegin(GL_LINES);

	glColor3f(0, 0, 1);
	glVertex3f(0, 0, 0);
	glVertex3f(2, 0, 0);
	glColor3f(1, 0, 0);
	glVertex3f(0, 0, 0);
	glVertex3f(0, 2, 0);
	glColor3f(0, 1, 0);
	glVertex3f(0, 0, 0);
	glVertex3f(0, 0, 2);
	glEnd();

	glPushMatrix();
	glTranslatef(0, 1, 0);
	glColor3f(1, 0, 0);
	if (m_rotate_axis == CYLINDER)
	{
		glRotatef(m_angle, 0, 1, 0);
	}
	draw_cube();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(1, 0, 0);
	glColor3f(0, 0, 1);
	if (m_rotate_axis == CYLINDER)
	{
		glRotatef(m_angle, 1, 0, 0);
	}
	draw_cube();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0, 0, 1);
	glColor3f(0, 1, 0);
	if (m_rotate_axis == CYLINDER)
	{
		glRotatef(m_angle, 0, 0, 1);
	}
	draw_cube();
	glPopMatrix();
	
	glFlush();
}
void COpenglExampleView::GLInit()
{
	m_hDC = ::GetDC(m_hWnd);
	static PIXELFORMATDESCRIPTOR  pfdWnd = {
		sizeof(PIXELFORMATDESCRIPTOR),
		1,
		PFD_DRAW_TO_WINDOW |
		PFD_SUPPORT_OPENGL|
		PFD_DOUBLEBUFFER,
		PFD_TYPE_RGBA,
		24,
		0,0,0,0,0,
		0,0,0,0,0,0,0,
		32,
		0,0,
		PFD_MAIN_PLANE,
		0,
		0,0,0
	};

	int pixelformat;
	pixelformat = ChoosePixelFormat(m_hDC, &pfdWnd);
	SetPixelFormat(m_hDC, pixelformat, &pfdWnd);

	m_hRC = wglCreateContext(m_hDC);
	wglMakeCurrent(m_hDC, m_hRC);

	GLSetupRC(m_hDC);
}
void COpenglExampleView::GLRelease()
{
	wglMakeCurrent(NULL, NULL);
	wglDeleteContext(m_hRC);
	::ReleaseDC(m_hWnd, m_hDC);
}

void COpenglExampleView::GLSetupRC(HDC hdc)
{

	//lighting
	GLfloat   ambientLight[] = {0.2f, 0.2f, 0.2f, 1.0f};
	GLfloat   diffuseLight[] = {0.6f, 0.6f, 0.6f, 1.0f };
	GLfloat   specular[] = { 1.0f, 1.0f, 1.0f, 1.0f };
	GLfloat   lightPos[] = { -10.0f, 10.0f, 10.0f, 1.0f };
	// light 0
	glEnable(GL_LIGHTING);
	glLightfv(GL_LIGHT0,  GL_AMBIENT, ambientLight);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuseLight);
	glLightfv(GL_LIGHT0, GL_SPECULAR, specular);
	glLightfv(GL_LIGHT0, GL_POSITION, lightPos);
	glEnable(GL_LIGHT0);
	// color material
	glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);
	glEnable(GL_COLOR_MATERIAL);
	// backgroud colr
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	// color
	glColor3f(1,0,0);

	glEnable(GL_DEPTH_TEST);
	glShadeModel(GL_SMOOTH);
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
}

int COpenglExampleView::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CView::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  在此添加您专用的创建代码
	GLInit();

	return 0;
}


void COpenglExampleView::OnDestroy()
{
	GLRelease();
	CView::OnDestroy();
}


void COpenglExampleView::OnSize(UINT nType, int cx, int cy)
{
	CView::OnSize(nType, cx, cy);
	GLResize(cx,cy);

}


void COpenglExampleView::GLResize(int cx, int cy)
{
	double nRange = 3;
	if (cy == 0)  cy = 1;
	glViewport(0,0, cx,cy);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(60, (double)cx / cy, 0.1, 50 * nRange);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	double eye[3], ref[3], up_dir[3];
	eye[0] = 0;  eye[1] = 0; eye[2] = 2*nRange;
	ref[0] = 0; ref[1] = 0; ref[2] = 0;
	up_dir[0] = 0; up_dir[1] = 1;  up_dir[2] = 0;
	gluLookAt(eye[0], eye[1], eye[2], ref[0], ref[1], ref[2], up_dir[0], up_dir[1], up_dir[2]);
}

BOOL COpenglExampleView::OnEraseBkgnd(CDC* pDC)
{
	// TODO:  在此添加消息处理程序代码和/或调用默认值

	//return CView::OnEraseBkgnd(pDC);
	return TRUE;
}

//rotate about y axis
void COpenglExampleView::OnRotate()
{
	// TODO:  在此添加命令处理程序代码
	//glRotatef(30, 0, 1, 0);
	SetTimer(1, 100, NULL);
	m_rotate_axis = YY;
	
}


void COpenglExampleView::OnTimer(UINT_PTR nIDEvent)
{
	// TODO:  在此添加消息处理程序代码和/或调用默认值

	if (m_rotate_axis == CYLINDER)
	{
		m_angle += 7;
		m_angle = m_angle % 360;
	}
	else
	{
		m_angle = 5;

	}

	CRect rect;
	GetClientRect(&rect);
	InvalidateRect(rect);

	CView::OnTimer(nIDEvent);
}


void COpenglExampleView::OnStop()
{
	// TODO:  在此添加命令处理程序代码
	KillTimer(1);
}


void COpenglExampleView::OnRotateX()
{
	//glRotatef(30, 1, 0, 0);
	SetTimer(1, 100, NULL);
	m_rotate_axis = XX;
}


void COpenglExampleView::OnRotateZ()
{
	// TODO:  在此添加命令处理程序代码	
	//glRotatef(30, 0, 0, 1);
	SetTimer(1, 100, NULL);
	m_rotate_axis = ZZ;
}


void COpenglExampleView::On32780()
{
	// TODO:  在此添加命令处理程序代码
	
	SetTimer(1, 100, NULL);
	m_rotate_axis = CYLINDER;

}


void COpenglExampleView::OnNbX()
{
	// TODO: 在此添加命令处理程序代码
	SetTimer(1, 100, NULL);
	m_rotate_axis = XX;
}


void COpenglExampleView::OnNbY()
{
	// TODO: 在此添加命令处理程序代码
	SetTimer(1, 100, NULL);
	m_rotate_axis = YY;

}


void COpenglExampleView::OnNbZ()
{
	// TODO: 在此添加命令处理程序代码
	SetTimer(1, 100, NULL);
	m_rotate_axis = ZZ;
}


void COpenglExampleView::OnNbXyz()
{
	// TODO: 在此添加命令处理程序代码
	SetTimer(1, 100, NULL);
	m_rotate_axis = CYLINDER;
}


void COpenglExampleView::OnNbStop()
{
	// TODO: 在此添加命令处理程序代码
	KillTimer(1);
}
