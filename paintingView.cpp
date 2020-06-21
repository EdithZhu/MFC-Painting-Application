
// paintingView.cpp : CpaintingView 类的实现
//

#include "stdafx.h"
// SHARED_HANDLERS 可以在实现预览、缩略图和搜索筛选器句柄的
// ATL 项目中进行定义，并允许与该项目共享文档代码。
#ifndef SHARED_HANDLERS
#include "painting.h"
#endif

#include "paintingDoc.h"
#include "paintingView.h"
#include "SettingDlg.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CpaintingView

IMPLEMENT_DYNCREATE(CpaintingView, CView)

BEGIN_MESSAGE_MAP(CpaintingView, CView)
	// 标准打印命令
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
	ON_COMMAND(ID_32772, &CpaintingView::sline)
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_MOUSEMOVE()
	ON_COMMAND(ID_32773, &CpaintingView::cline)
	ON_WM_LBUTTONDBLCLK()
	ON_COMMAND(ID_32776, &CpaintingView::nosector)
//	ON_COMMAND(ID_32775, &CpaintingView::On32775)
	ON_COMMAND(ID_32775, &CpaintingView::sector)
	ON_COMMAND(ID_32774, &CpaintingView::rect)
	ON_COMMAND(ID_32777, &CpaintingView::ecllipse)
	ON_COMMAND(ID_32778, &CpaintingView::DrawColor)
	ON_COMMAND(ID_32779, &CpaintingView::DrawFont)
	ON_COMMAND(ID_32780, &CpaintingView::OnSetting)
END_MESSAGE_MAP()

// CpaintingView 构造/析构

CpaintingView::CpaintingView()
	: m_strFontName(_T(""))
{
	// TODO: 在此处添加构造代码
    m_bDraw=FALSE;
	m_nLineWidth = 1;
	m_nLineStyle = 0;
}

CpaintingView::~CpaintingView()
{
}

BOOL CpaintingView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: 在此处通过修改
	//  CREATESTRUCT cs 来修改窗口类或样式

	return CView::PreCreateWindow(cs);
}

// CpaintingView 绘制

void CpaintingView::OnDraw(CDC* pDC)
{
	CpaintingDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	CFont *pOldFont=pDC->SelectObject(&m_font);
	pDC->TextOut(0,0,m_strFontName);
	pDC->SelectObject(pOldFont);
	if (!pDoc)
		return;
	//CpaintingDoc* pDoc = GetDocument();
 ASSERT_VALID(pDoc);
 if (!pDoc)
  return;
 CRect rect;
 GetClientRect(&rect);
 CDC dcMem;//以下是输出位图的标准操作
 CBitmap *pOldBitmap = NULL;
 dcMem.CreateCompatibleDC(NULL);
 pOldBitmap = dcMem.SelectObject(&pDoc->m_bmpBuf);
 
 pDC->BitBlt(0,0,rect.Width(),rect.Height(),&dcMem,0,0,SRCCOPY);
 dcMem.SelectObject(pOldBitmap); //将dcMeM中的bitmap拷贝到当前客户区
 dcMem.DeleteDC();
	// TODO: 在此处为本机数据添加绘制代码
}


// CpaintingView 打印

BOOL CpaintingView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 默认准备
	return DoPreparePrinting(pInfo);
}

void CpaintingView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 添加额外的打印前进行的初始化过程
}

void CpaintingView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 添加打印后进行的清理过程
}


// CpaintingView 诊断

#ifdef _DEBUG
void CpaintingView::AssertValid() const
{
	CView::AssertValid();
}

void CpaintingView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CpaintingDoc* CpaintingView::GetDocument() const // 非调试版本是内联的
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CpaintingDoc)));
	return (CpaintingDoc*)m_pDocument;
}
#endif //_DEBUG


// CpaintingView 消息处理程序


void CpaintingView::sline()
{
	//MessageBox(_T("现在可以绘制直线！"));
	dType=SLine;// TODO: 在此添加命令处理程序代码
}


int CpaintingView::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	
	if (CView::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	// TODO: Add your specialized creation code here
	btn.Create(_T("按钮"),WS_CHILD|WS_VISIBLE|BS_DEFPUSHBUTTON,CRect(20,20,100,100),this,123);
	
	return 0;
}


void CpaintingView::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	// TODO: Add your message handler code here and/or call default
	//MessageBox("View Clicked!");
   switch (dType)
	   
  {
   case SLine:
	          m_bDraw=TRUE;
	          m_ptOrigin=point;
			  break;
   case CLine:
	          m_bDraw=TRUE;
	          m_ptOrigin=point;
			  break;
   case NoSector:
              m_bDraw=TRUE;
	          m_ptOrigin=point;
			  break;
   case Sector:
              m_bDraw=TRUE;
	          m_ptOrigin=point;
			  m_ptNext=point;

			  break;
   case Recta:
              m_bDraw=TRUE;
	          m_ptOrigin=point;
			  break;
   case Ecllipse:
              m_bDraw=TRUE;
	          m_ptOrigin=point;
			  break;
   default:
	          break;
   }
	CView::OnLButtonDown(nFlags, point);
}


void CpaintingView::OnLButtonUp(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	// TODO: Add your message handler code here and/or call default
	CPen pen(m_nLineStyle,m_nLineWidth,m_clr);
	CClientDC dc(this);

	CPen *pOldPen=dc.SelectObject(&pen);
    CBitmap bitmap;
	bitmap.LoadBitmap(IDB_BITMAP1);
	CBrush brush(&bitmap);

	CBrush *pBrush=CBrush::FromHandle((HBRUSH)GetStockObject(NULL_BRUSH));
	CBrush *pOldBrush=dc.SelectObject(pBrush);
	switch (dType)
	   
	{
        case SLine:
	         dc.MoveTo(m_ptOrigin);
	         dc.LineTo(point);
	         break;
		case Recta:
             dc.FillRect(CRect(m_ptOrigin,point),&brush);
	         
			  break;
		case Ecllipse:
			 dc.Ellipse(CRect(m_ptOrigin,point));
			  break;
       default:
	         break;
	 }
    m_bDraw=FALSE;
	dc.SelectObject(pOldPen);
	dc.SelectObject(pOldBrush);
	CView::OnLButtonUp(nFlags, point);
	CDC *pDC = GetDC();
 CpaintingDoc *pDoc = GetDocument();
 CDC dcMem;
dcMem.CreateCompatibleDC(NULL);
 CRect rect;
 GetClientRect(&rect); //获取客户区域
 pDoc->m_bmpBuf.DeleteObject();
 pDoc->m_bmpBuf.CreateCompatibleBitmap(pDC,rect.Width(),rect.Height());
 CBitmap *pOldBitmap = dcMem.SelectObject(&pDoc->m_bmpBuf);//将创建好的m_bmpBuf添加到临时的CDC的Object中，类似于在墙上先糊上墙纸^_^，先在墙纸上作画，最后将最终形成的画拷贝到墙上。
 CPoint m_ptEnd = point;

 dcMem.BitBlt(0,0,rect.Width(),rect.Height(),pDC,0,0,SRCCOPY);
 dcMem.SelectObject(pOldBitmap); //将pDC即当前客户区里面的内容拷贝到临时的MEM中，MEM虽然过后会被delete掉，但是它更新了CDocument类中的m_bmpBuf
 m_bDraw = false;
 dcMem.DeleteDC();
}


void CpaintingView::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	// TODO: Add your message handler code here and/or call default
	CPen pen(m_nLineStyle,m_nLineWidth,m_clr);
	CClientDC dc(this);
	CPen *pOldPen=dc.SelectObject(&pen);
	if(m_bDraw)
	{
	switch (dType)
	   
	{
        case CLine:
	         dc.MoveTo(m_ptOrigin);
	         dc.LineTo(point);
			 m_ptOrigin=point;
	         break;
	    case NoSector:
	         dc.MoveTo(m_ptOrigin);
	         dc.LineTo(point);
			 
	         break;
		case Sector:
			 dc.MoveTo(m_ptOrigin);
	         dc.LineTo(point);
			 dc.LineTo(m_ptNext);
			 m_ptNext=point;
			 break;
       default:
	         break;
	 }
	}
	dc.SelectObject(pOldPen);
	CView::OnMouseMove(nFlags, point);
}


void CpaintingView::cline()
{
	// TODO: 在此添加命令处理程序代码
	// TODO: Add your command handler code here
	
	//MessageBox("开始绘制连续的线!");
	dType=CLine;
}


void CpaintingView::OnLButtonDblClk(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	// TODO: Add your message handler code here and/or call default
	dType=NoDraw;
	CView::OnLButtonDblClk(nFlags, point);
}


void CpaintingView::nosector()
{
	// TODO: 在此添加命令处理程序代码
	// TODO: Add your command handler code here
		dType=NoSector;
}


//void CpaintingView::On32775()
//{
//	// TODO: 在此添加命令处理程序代码
//}


void CpaintingView::sector()
{
	// TODO: 在此添加命令处理程序代码
	// TODO: Add your command handler code here
	dType=Sector;
}


void CpaintingView::rect()
{
	// TODO: 在此添加命令处理程序代码
	// TODO: Add your command handler code here
	dType=Recta;
}


void CpaintingView::ecllipse()
{
	// TODO: 在此添加命令处理程序代码
	// TODO: Add your command handler code here
	dType=Ecllipse;
}


//void CpaintingView::OnDrawColor()
//{
//	// TODO: Add your command handler code here
//	CColorDialog dlg;
//	dlg.DoModal();
//}


void CpaintingView::DrawColor()
{
	CColorDialog dlg;
	dlg.m_cc.Flags |=CC_RGBINIT|CC_FULLOPEN;
	dlg.m_cc.rgbResult=m_clr;
	if(IDOK==dlg.DoModal())
	{
		m_clr=dlg.m_cc.rgbResult;
	}
	// TODO: 在此添加命令处理程序代码
}


void CpaintingView::DrawFont()
{
	// TODO: 在此添加命令处理程序代码
	// TODO: Add your command handler code here
	CFontDialog dlg;
	if(IDOK==dlg.DoModal())
	{
		m_font.CreateFontIndirect(dlg.m_cf.lpLogFont);
		m_strFontName=dlg.m_cf.lpLogFont->lfFaceName;

	}
	//Invalidate();
	CClientDC dc(this);
	CFont *pOldFont=dc.SelectObject(&m_font);
	dc.TextOut(0,0,m_strFontName);
	dc.SelectObject(pOldFont);
	if (m_font.m_hObject)
			m_font.DeleteObject();
}


void CpaintingView::OnSetting()
{
	// TODO: 在此添加命令处理程序代码
	CSettingDlg dlg;
	dlg.m_nLineWidth=m_nLineWidth;
	dlg.m_nLineStyle=m_nLineStyle;
	if(IDOK==dlg.DoModal())
	{
		m_nLineWidth=dlg.m_nLineWidth;
		m_nLineStyle=dlg.m_nLineStyle;
	
	}
}
