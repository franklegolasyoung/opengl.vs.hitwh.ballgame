
// BezierCurveView.h : interface of the CBezierCurveView class
//

#pragma once
#include <vector>
#include <utility>


class CBezierCurveView : public CView
{
private:
	bool isDrawing;  // �Ƿ��ڻ�ͼ״̬

	CPoint lastMovingPoint;  // ����ƶ��������ϴθով����ĵ㣬��������ƶ��е���
	std::vector<CPoint> startPoint;  // �洢�ѻ��Ƶĵ㣬���ڴ����ػ�
	int pointNumber;

	void DrawBezierCurve(std::vector<CPoint>& p, CPen& curvePen);

protected: // create from serialization only
	CBezierCurveView() noexcept;
	DECLARE_DYNCREATE(CBezierCurveView)

// Attributes
public:
	CBezierCurveDoc* GetDocument() const;

// Operations
public:

// Overrides
public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// Implementation
public:
	virtual ~CBezierCurveView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
};

#ifndef _DEBUG  // debug version in BezierCurveView.cpp
inline CBezierCurveDoc* CBezierCurveView::GetDocument() const
   { return reinterpret_cast<CBezierCurveDoc*>(m_pDocument); }
#endif

