
// OpenglExampleView.h : COpenglExampleView 类的接口
//

#pragma once

#include "gl\gl.h"
#include "gl\glu.h"
//#pragma comment(lib, "opengl32.lib")
//#pragma comment(lib, "glu32.lib")
class COpenglExampleView : public CView
{
protected: // 仅从序列化创建
	COpenglExampleView();
	DECLARE_DYNCREATE(COpenglExampleView)

// 特性
public:
	COpenglExampleDoc* GetDocument() const;

// 操作
public:
	HGLRC  m_hRC;
	HDC    m_hDC;
	int   m_angle;

	enum{ XX, YY, ZZ,  CYLINDER, NOROTATE }  m_rotate_axis;

	void draw_car();
	void draw_cylinder(GLfloat bottomx, GLfloat bottomy, GLfloat  bottomz,  GLfloat   r, GLfloat height);
	//void draw_sphere(GLfloat  x, GLfloat y, GLfloat z, GLfloat r);
	void draw_cube();
	void RenderScene();
	void RenderScene2();
	void GLInit();
	void GLRelease();
	void GLResize(int cx, int cy);
	void GLSetupRC(HDC hdc);

	void ChangeMaterial(CString &string,
		bool update = true);
// 重写
public:
	virtual void OnDraw(CDC* pDC);  // 重写以绘制该视图
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:

// 实现
public:
	virtual ~COpenglExampleView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 生成的消息映射函数
protected:
	//afx_msg void OnFilePrintPreview();
	//afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	DECLARE_MESSAGE_MAP()
public:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnDestroy();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnRotate();
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnStop();
	afx_msg void OnRotateX();
	afx_msg void OnRotateZ();
	afx_msg void On32780();
	afx_msg void OnNbX();
	afx_msg void OnNbY();
	afx_msg void OnNbZ();
	afx_msg void OnNbXyz();
	afx_msg void OnNbStop();
};

#ifndef _DEBUG  // OpenglExampleView.cpp 中的调试版本
inline COpenglExampleDoc* COpenglExampleView::GetDocument() const
   { return reinterpret_cast<COpenglExampleDoc*>(m_pDocument); }
#endif

