
// test1View.cpp: Ctest1View 类的实现
//

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS 可以在实现预览、缩略图和搜索筛选器句柄的
// ATL 项目中进行定义，并允许与该项目共享文档代码。
#ifndef SHARED_HANDLERS
#include "test1.h"
#endif

#include "test1Doc.h"
#include "test1View.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// Ctest1View

IMPLEMENT_DYNCREATE(Ctest1View, CView)

BEGIN_MESSAGE_MAP(Ctest1View, CView)
	// 标准打印命令
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &Ctest1View::OnFilePrintPreview)
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()
	ON_WM_LBUTTONDOWN()
	//	ON_WM_LBUTTONUP()
	ON_WM_MOUSEMOVE()
	ON_WM_RBUTTONDOWN()
END_MESSAGE_MAP()

// Ctest1View 构造/析构

Ctest1View::Ctest1View() noexcept
{
	// TODO: 在此处添加构造代码

}

Ctest1View::~Ctest1View()
{
}

BOOL Ctest1View::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: 在此处通过修改
	//  CREATESTRUCT cs 来修改窗口类或样式

	return CView::PreCreateWindow(cs);
}

// Ctest1View 绘图

void Ctest1View::OnDraw(CDC* pDC)
{
	Ctest1Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: 在此处为本机数据添加绘制代码
	for (auto line : lines)
	{
		//起点
		pDC->MoveTo(line.first);
		//划线，终点
		pDC->LineTo(line.second);
	}
}


// Ctest1View 打印


void Ctest1View::OnFilePrintPreview()
{
#ifndef SHARED_HANDLERS
	AFXPrintPreview(this);
#endif
}

BOOL Ctest1View::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 默认准备
	return DoPreparePrinting(pInfo);
}

void Ctest1View::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 添加额外的打印前进行的初始化过程
}

void Ctest1View::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 添加打印后进行的清理过程
}

void Ctest1View::OnRButtonUp(UINT /* nFlags */, CPoint point)
{
	/*ClientToScreen(&point);
	OnContextMenu(this, point);*/
}

void Ctest1View::OnContextMenu(CWnd* /* pWnd */, CPoint point)
{
#ifndef SHARED_HANDLERS
	theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
#endif
}


// Ctest1View 诊断

#ifdef _DEBUG
void Ctest1View::AssertValid() const
{
	CView::AssertValid();
}

void Ctest1View::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

Ctest1Doc* Ctest1View::GetDocument() const // 非调试版本是内联的
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(Ctest1Doc)));
	return (Ctest1Doc*)m_pDocument;
}
#endif //_DEBUG


// Ctest1View 消息处理程序


void Ctest1View::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值

	if (isDrawing) {
		CDC* pDC = GetDC();
		//起点
		pDC->MoveTo(startPoint);
		//划线，终点
		pDC->LineTo(point);
		ReleaseDC(pDC);
		lines.push_back(std::make_pair(startPoint, point));
	}
	else {
		isDrawing = TRUE;
	}
	startPoint = point;
	oldPoint = point;

	CView::OnLButtonDown(nFlags, point);
}

void Ctest1View::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值

	if (isDrawing) {
		CDC* pDC = GetDC();
		//起点
		pDC->SetROP2(R2_NOT);
		pDC->MoveTo(startPoint);
		pDC->LineTo(oldPoint);
		pDC->MoveTo(startPoint);
		//划线，终点
		pDC->LineTo(point);
		oldPoint = point;
		ReleaseDC(pDC);
	}

	CView::OnMouseMove(nFlags, point);
}


void Ctest1View::OnRButtonDown(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	CPoint pt;
	GetCursorPos(&pt);
	lines.push_back(std::make_pair(startPoint, point));
	isDrawing = FALSE;
	CView::OnRButtonDown(nFlags, point);
}
