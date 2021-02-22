
// TestView.h: CTestView 类的接口
//

#pragma once
#include "cmath"


class CTestView : public CView
{
protected: // 仅从序列化创建
	CTestView() noexcept;
	DECLARE_DYNCREATE(CTestView)
	
	double  Pointx[2], Pointy[2];//用户绘制的直线
	int		wxl, wxr, wyb, wyt;//左上与右下
	CDC	Picture;//内存(预存)DC,防止屏幕闪烁
	char	    m_i; //第一个点还是第二个点
	BOOL	m_Attatch;
	BOOL	m_Draw;
	unsigned int RC, RC0, RC1;
	bool drawing;    // 是否在绘图状态


// 特性
public:
	CTestDoc* GetDocument() const;

// 操作
public:

// 重写
public:
	virtual void OnDraw(CDC* pDC);  // 重写以绘制该视图
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	virtual void OnMENUClip();
	virtual unsigned int codePoint(double LinePx, double LinePy);
	virtual void CohenSutherland();
	//virtual void midLineClip();
	//virtual double findIntersection(double p1_x, double p1_y, double p2_x, double p2_y);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// 实现
public:
	virtual ~CTestView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 生成的消息映射函数
protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
};

#ifndef _DEBUG  // TestView.cpp 中的调试版本
inline CTestDoc* CTestView::GetDocument() const
   { return reinterpret_cast<CTestDoc*>(m_pDocument); }
#endif

