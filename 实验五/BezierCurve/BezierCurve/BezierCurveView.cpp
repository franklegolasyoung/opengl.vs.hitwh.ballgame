
// BezierCurveView.cpp : implementation of the CBezierCurveView class
//

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS can be defined in an ATL project implementing preview, thumbnail
// and search filter handlers and allows sharing of document code with that project.
#ifndef SHARED_HANDLERS
#include "BezierCurve.h"
#endif

#include "BezierCurveDoc.h"
#include "BezierCurveView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CBezierCurveView

IMPLEMENT_DYNCREATE(CBezierCurveView, CView)

BEGIN_MESSAGE_MAP(CBezierCurveView, CView)
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
	ON_WM_LBUTTONDOWN()
	ON_WM_RBUTTONDOWN()
	ON_WM_MOUSEMOVE()
	ON_WM_ERASEBKGND()
END_MESSAGE_MAP()

// CBezierCurveView construction/destruction

CBezierCurveView::CBezierCurveView() noexcept
{
	isDrawing = false;  // ��ʼ״̬Ϊδ��ͼ״̬
	pointNumber = 0;
}

CBezierCurveView::~CBezierCurveView()
{
}

BOOL CBezierCurveView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

// CBezierCurveView drawing

void CBezierCurveView::OnDraw(CDC* pDC)
{
	CBezierCurveDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// �ػ�����ֱ�ߺͱ���������
	int n = 0;
	for (auto thisPoint = startPoint.begin(); thisPoint < startPoint.end(); ++thisPoint)
	{
		n++;
		// �ػ�ֱ��
		if (thisPoint == startPoint.begin())
		{
			pDC->MoveTo(*thisPoint);
			continue;
		}
		pDC->LineTo(*thisPoint);
		pDC->MoveTo(*thisPoint);
		// �ػ�����
		if (n % 3 == 1 && n != 1)
		{
			std::vector<CPoint> p(thisPoint - 3, thisPoint + 1);
			CPen penCil;
			// �����������ߣ�������
			if (n / 3 % 2)
			{
				penCil.CreatePen(PS_SOLID, 5, RGB(0, 255, 0));
			}
			// ��ż�������ߣ�������
			else
			{
				penCil.CreatePen(PS_SOLID, 5, RGB(0, 0, 255));
			}
			DrawBezierCurve(p, penCil);
		}
	}
}

// CBezierCurveView printing

BOOL CBezierCurveView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CBezierCurveView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CBezierCurveView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}


// CBezierCurveView diagnostics

#ifdef _DEBUG
void CBezierCurveView::AssertValid() const
{
	CView::AssertValid();
}

void CBezierCurveView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CBezierCurveDoc* CBezierCurveView::GetDocument() const // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CBezierCurveDoc)));
	return (CBezierCurveDoc*)m_pDocument;
}
#endif //_DEBUG


// ���Ʊ���������
void CBezierCurveView::DrawBezierCurve(std::vector<CPoint>& p, CPen& thisPen)
{
	CClientDC dc(this);
	dc.SelectObject(&thisPen);
	dc.MoveTo(p.front());
	for (double i = 0.0; i < 1.0; i += 0.01)
	{
		double points[4] = { (1 - i) * (1 - i) * (1 - i), 3 * i * (1 - i) * (1 - i), 3 * i * i * (1 - i), i * i * i };
		double p_x = points[0] * p[0].x + points[1] * p[1].x + points[2] * p[2].x + points[3] * p[3].x;
		double p_y = points[0] * p[0].y + points[1] * p[1].y + points[2] * p[2].y + points[3] * p[3].y;
		dc.LineTo(p_x, p_y);
		dc.MoveTo(p_x, p_y);
	}
	dc.LineTo(p.back());
}


// CBezierCurveView message handlers


// �������
void CBezierCurveView::OnLButtonDown(UINT nFlags, CPoint point)
{
	CClientDC dc(this);
	//CPen linePen(PS_DASH, 1, RGB(0, 0, 0));
	//dc.SelectObject(&linePen);

	CPoint poinT = point;
	// �����ڻ�ͼ״̬
	if (isDrawing)
	{
		// ��֤ G1 ����
		if (pointNumber % 3 == 1 && pointNumber != 1)
		{
			std::vector<CPoint> p(startPoint.end() - 2, startPoint.end());
			int x0 = point.x, y0 = point.y;
			int x1 = p[0].x, y1 = p[0].y;
			int a = p[0].x - p[1].x;
			int b = p[0].y - p[1].y;
			int x = (a * a * x0 + a * b * (y0 - y1) + b * b * x1) / (a * a + b * b);
			int y = (a * a * y1 + a * b * (x0 - x1) + b * b * y0) / (a * a + b * b);
			poinT = CPoint(x, y);
		}
	}
	// �������ڻ�ͼ״̬
	else
	{
		// ��ʼ��ͼ
		isDrawing = true;
	}

	// ��¼���ε��������
	lastMovingPoint = poinT;
	startPoint.emplace_back(poinT);
	++pointNumber;

	if (pointNumber % 3 == 1 && pointNumber != 1)
	{
		std::vector<CPoint> p(startPoint.end() - 4, startPoint.end());
		CPen thisPen;
		// �����������ߣ�������
		if (pointNumber / 3 % 2)
		{
			thisPen.CreatePen(PS_SOLID, 5, RGB(0, 255, 0));
		}
		// ��ż�������ߣ�������
		else
		{
			thisPen.CreatePen(PS_SOLID, 5, RGB(0, 0, 255));
		}
		DrawBezierCurve(p, thisPen);
	}
}


// �Ҽ�����
void CBezierCurveView::OnRButtonDown(UINT nFlags, CPoint point)
{
	// �����ڻ�ͼ״̬
	if (isDrawing)
	{
		// ֹͣ��ͼ
		isDrawing = false;
		// ȥ������ƶ������в������
		CClientDC dc(this);
		dc.SetROP2(R2_NOT);
		dc.MoveTo(startPoint.back());
		dc.LineTo(lastMovingPoint);
	}
}


// ����ƶ�
void CBezierCurveView::OnMouseMove(UINT nFlags, CPoint point)
{
	// �����ڻ�ͼ״̬
	if (isDrawing)
	{
		// ����ƶ����ϸ�״̬�������
		CClientDC dc(this);
		dc.SetROP2(R2_NOT);
		dc.MoveTo(startPoint.back());dc.LineTo(lastMovingPoint);

		CPoint myPoint = point;

		// ��֤ G1 ����
		if (pointNumber % 3 == 1 && pointNumber != 1)
		{
			std::vector<CPoint> p(startPoint.end() - 2, startPoint.end());
			int x0 = point.x, y0 = point.y;
			int x1 = p[0].x, y1 = p[0].y;
			int a = p[0].x - p[1].x;
			int b = p[0].y - p[1].y;
			int x = (a * a * x0 + a * b * (y0 - y1) + b * b * x1) / (a * a + b * b);
			int y = (a * a * y1 + a * b * (x0 - x1) + b * b * y0) / (a * a + b * b);
			myPoint = CPoint(x, y);
		}
		// �����ƶ������е���
		dc.MoveTo(startPoint.back());
		dc.LineTo(myPoint);
		lastMovingPoint = myPoint;
	}
}
