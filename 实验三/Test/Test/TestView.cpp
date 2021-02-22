
// TestView.cpp: CTestView 类的实现
//

#include "stdafx.h"
// SHARED_HANDLERS 可以在实现预览、缩略图和搜索筛选器句柄的
// ATL 项目中进行定义，并允许与该项目共享文档代码。
#ifndef SHARED_HANDLERS
#include "Test.h"
#endif

#include "TestDoc.h"
#include "TestView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CTestView

IMPLEMENT_DYNCREATE(CTestView, CView)

BEGIN_MESSAGE_MAP(CTestView, CView)
	// 标准打印命令
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
	ON_WM_LBUTTONDOWN()
	ON_WM_MOUSEMOVE()
	ON_WM_RBUTTONDOWN()
END_MESSAGE_MAP()

// CTestView 构造/析构

CTestView::CTestView() noexcept
{
	// TODO: 在此处添加构造代码
	//窗口位置坐标
	wxl = 250; wxr = 850; wyb = 250; wyt = 450;
	m_Attatch = FALSE;
	m_i = 0;
	m_Draw = FALSE;
	RC0 = 0; RC1 = 0;
	drawing = false;

}

CTestView::~CTestView()
{
}

BOOL CTestView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: 在此处通过修改
	//  CREATESTRUCT cs 来修改窗口类或样式

	return CView::PreCreateWindow(cs);
}

// CTestView 绘图

void CTestView::OnDraw(CDC* /*pDC*/)
{
	CTestDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	//绘制窗口
	CClientDC dc(this);
	CPen* pen = new CPen;
	pen->CreatePen(PS_SOLID, 1, RGB(0, 0, 0));
	dc.SelectObject(pen);
	dc.Rectangle(wxl, wyt, wxr, wyb);//矩形
	if (!pDoc)
		return;
	// TODO: 在此处为本机数据添加绘制代码
}

void CTestView::OnMENUClip()//裁剪菜单函数 
{
	CClientDC dc(this);
	CPen* pen1 = new CPen;
	pen1->CreatePen(PS_SOLID, 1, RGB(255, 255, 255));
	dc.SelectObject(pen1);
	dc.MoveTo(round(Pointx[0]), round(Pointy[0]));
	dc.LineTo(round(Pointx[1]), round(Pointy[1]));
	//先清空原来的状态
	
	CohenSutherland();

	//重新绘制
	CPen* pen = new CPen;
	pen->CreatePen(PS_SOLID, 1, RGB(0, 0, 0));
	dc.SelectObject(pen);
	dc.Rectangle(wxl, wyt, wxr, wyb);//矩形
	dc.MoveTo(round(Pointx[0]), round(Pointy[0]));
	dc.LineTo(round(Pointx[1]), round(Pointy[1]));
	
}
unsigned int CTestView::codePoint(double LinePx, double LinePy)//端点编码函数
{//顺序左右下上

	RC = 0;
	if (LinePx < wxl)
	{
		RC = RC | 1;
	}
	if (LinePx > wxr)
	{
		RC = RC | 2;
	}
	if (LinePy < wyb)
	{
		RC = RC | 4;
	}
	if (LinePy > wyt)
	{
		RC = RC | 8;
	}
	return RC;
}


// CTestView 消息处理程序


void CTestView::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	m_i++;
	CClientDC dc(this);
	CPen* pen = new CPen;
	pen->CreatePen(PS_SOLID, 1, RGB(0, 0, 0));
	dc.SelectObject(pen);
	if (m_i ==1)//确定直线的两个端点
	{
		drawing = true;
		Pointx[0] = point.x;
		Pointy[0] = point.y;
		
	}
	else if (m_i == 2)
	{
		drawing = false;
		Pointx[1] = point.x;
		Pointy[1] = point.y;
		dc.MoveTo(round(Pointx[0]), round(Pointy[0]));
		dc.LineTo(round(Pointx[1]), round(Pointy[1]));
		m_i++;
	}

	CView::OnLButtonDown(nFlags, point);
}
void CTestView::OnRButtonDown(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	//按下右键则切割
	OnMENUClip();
	CView::OnRButtonDown(nFlags, point);
}

void CTestView::CohenSutherland()//Cohen－Sutherland算法
{
	BOOL isChanged;
	double x, y;
	RC0 = codePoint(Pointx[0], Pointy[0]);
	RC1 = codePoint(Pointx[1], Pointy[1]);
	while (TRUE)
	{
		isChanged = FALSE;
		if (0 == (RC0 | RC1))
		{
			return;
		}
		else if (0 != (RC0 & RC1))
		{
			Pointx[0] = Pointy[0] = Pointx[1] = Pointy[1] = 0;
			return;
		}
		else
		{
			if (0 == RC0)
			//如果P0点在窗口内，交换P0和P1,保证p0点在窗口外
			{
				//交换点的坐标值
				double cPointx, cPointy;
				cPointx = Pointx[0]; cPointy = Pointy[0];
				Pointx[0] = Pointx[1]; Pointy[0] = Pointy[1];
				Pointx[1] = cPointx; Pointy[1] = cPointy;
				//交换点的编码值
				unsigned int TRC;
				TRC = RC0; RC0 = RC1; RC1 = TRC;
			}
			//按左、右、下、上的顺序裁剪
			if (RC0 & 1)//P0点位于窗口的左侧
			{
				x = wxl;//求交点y
				y = Pointy[0] + (Pointy[1] - Pointy[0])*(x - Pointx[0]) / (Pointx[1] - Pointx[0]);
				Pointx[0] = x; Pointy[0] = y;
				isChanged = TRUE;
				RC0 = codePoint(Pointx[0], Pointy[0]); RC1 = codePoint(Pointx[1], Pointy[1]);
			}
			if (RC0 & 2)//P0点位于窗口的右侧
			{
				x = wxr;//求交点y
				y = Pointy[0] + (Pointy[1] - Pointy[0])*(x - Pointx[0]) / (Pointx[1] - Pointx[0]);
				Pointx[0] = x; Pointy[0] = y;
				isChanged = TRUE;
				RC0 = codePoint(Pointx[0], Pointy[0]); RC1 = codePoint(Pointx[1], Pointy[1]);
			}
			if (RC0 & 4)//P0点位于窗口的下侧
			{
				y = wyb;//求交点x
				x = Pointx[0] + (Pointx[1] - Pointx[0])*(y - Pointy[0]) / (Pointy[1] - Pointy[0]);
				Pointx[0] = x; Pointy[0] = y;
				isChanged = TRUE;
				RC0 = codePoint(Pointx[0], Pointy[0]); RC1 = codePoint(Pointx[1], Pointy[1]);
			}
			if (RC0 & 8)//P0点位于窗口的上侧
			{
				y = wyt;//求交点x
				x = Pointx[0] + (Pointx[1] - Pointx[0])*(y - Pointy[0]) / (Pointy[1] - Pointy[0]);
				Pointx[0] = x; Pointy[0] = y;
				isChanged = TRUE;
				RC0 = codePoint(Pointx[0], Pointy[0]); RC1 = codePoint(Pointx[1], Pointy[1]);
			}
			if (FALSE == isChanged)
			{
				return;
			}
		}
	}
}

/*

void CTestView::midLineClip()
{
	RC0 = codePoint(Pointx[0], Pointy[0]);
	RC1 = codePoint(Pointx[1], Pointy[1]);
	double p1_x, p1_y, p2_x, p2_y;
	p1_x = Pointx[0];
	p1_y = Pointy[0];
	p2_x = Pointx[1];
	p2_y = Pointy[1];
	if (0 == (RC0 | RC1))
	{
		return;
	}
	//存在一个点在裁剪框内
	else if (0 != (RC0 & RC1))
	{
		Pointx[0] = Pointy[0] = Pointx[1] = Pointy[1] = 0;
		return;
	}
	else
	{
		if (RC0 == 0)
			findIntersection(p1_x, p1_y, p2_x, p2_y);
		else if (RC1 == 0)
			findIntersection(p1_x, p1_y, p2_x, p2_y);
		else
		{
			Pointx[0] = (p1_x + p2_x) / 2;
			Pointy[0] = (p1_y + p2_y) / 2;
			midLineClip();
		}
	}
}


//找出p1和p2之间边界的交点
double CTestView::findIntersection(double p1_x, double p1_y, double p2_x, double p2_y)
{
	double p_x, p_y;
	p_x = (p1_x + p2_x) / 2;
	p_y = (p1_y + p2_y) / 2;
	if (distance(p_x, p_y, p1_x, p1_y) < 1.5)
		return p_x;
	RC0 = codePoint(Pointx[0], Pointy[0]);
	RC1 = codePoint(Pointx[1], Pointy[1]);
	RC = codePoint(p_x, p_y);
	if (RC0 == 0)
		if (p_x == 0)
			return findIntersection(p_x, p_y, p2_x, p2_y);
		else
			return findIntersection(p1_x, p1_y, p_x, p_y);
	if (RC1 == 0)
		if (p_x == 0)
			return findIntersection(p_x, p_y, p1_x, p1_y);
		else
			return findIntersection(p2_x, p2_y, p_x, p_y);
	return p_x;
}

double distance(double p1_x, double p1_y, double p2_x, double p2_y)
{
	double result;
	result = sqrt((p1_x - p2_x) * (p1_x - p2_x) + (p1_y - p2_y) * (p1_y - p2_y));
	return result;
}





// CTestView 打印

BOOL CTestView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 默认准备
	return DoPreparePrinting(pInfo);
}

void CTestView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 添加额外的打印前进行的初始化过程
}

void CTestView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 添加打印后进行的清理过程
}


// CTestView 诊断

#ifdef _DEBUG
void CTestView::AssertValid() const
{
	CView::AssertValid();
}

void CTestView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CTestDoc* CTestView::GetDocument() const // 非调试版本是内联的
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CTestDoc)));
	return (CTestDoc*)m_pDocument;
}
#endif //_DEBUG


void CTestView::OnMouseMove(UINT nFlags, CPoint point)
{
	if (!drawing)//判断是否在绘画状态，即是否未按下左键
		return;

	CClientDC   ClientDC(this);
	ClientDC.DPtoLP(&point);
	ClientDC.SelectStockObject(NULL_BRUSH);
	CPen pen, *Pen1;
	pen.CreatePen(PS_SOLID, 1, RGB(0, 0, 0));
	Pen1 = ClientDC.SelectObject(&pen);
	ClientDC.SetROP2(R2_NOT);
	ClientDC.MoveTo(Pointx[0],Pointy[0]);
	ClientDC.LineTo(Pointx[1], Pointy[1]);
	Pointx[1] = point.x;
	Pointy[1] = point.y;
	ClientDC.MoveTo(round(Pointx[0]), round(Pointy[0]));
	ClientDC.LineTo(round(Pointx[1]), round(Pointy[1]));

	ClientDC.SelectObject(Pen1);
	CView::OnMouseMove(nFlags, point);
}
