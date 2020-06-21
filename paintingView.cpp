
// paintingView.cpp : CpaintingView ���ʵ��
//

#include "stdafx.h"
// SHARED_HANDLERS ������ʵ��Ԥ��������ͼ������ɸѡ�������
// ATL ��Ŀ�н��ж��壬�����������Ŀ�����ĵ����롣
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
	// ��׼��ӡ����
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

// CpaintingView ����/����

CpaintingView::CpaintingView()
	: m_strFontName(_T(""))
{
	// TODO: �ڴ˴���ӹ������
    m_bDraw=FALSE;
	m_nLineWidth = 1;
	m_nLineStyle = 0;
}

CpaintingView::~CpaintingView()
{
}

BOOL CpaintingView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: �ڴ˴�ͨ���޸�
	//  CREATESTRUCT cs ���޸Ĵ��������ʽ

	return CView::PreCreateWindow(cs);
}

// CpaintingView ����

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
 CDC dcMem;//���������λͼ�ı�׼����
 CBitmap *pOldBitmap = NULL;
 dcMem.CreateCompatibleDC(NULL);
 pOldBitmap = dcMem.SelectObject(&pDoc->m_bmpBuf);
 
 pDC->BitBlt(0,0,rect.Width(),rect.Height(),&dcMem,0,0,SRCCOPY);
 dcMem.SelectObject(pOldBitmap); //��dcMeM�е�bitmap��������ǰ�ͻ���
 dcMem.DeleteDC();
	// TODO: �ڴ˴�Ϊ����������ӻ��ƴ���
}


// CpaintingView ��ӡ

BOOL CpaintingView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// Ĭ��׼��
	return DoPreparePrinting(pInfo);
}

void CpaintingView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: ��Ӷ���Ĵ�ӡǰ���еĳ�ʼ������
}

void CpaintingView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: ��Ӵ�ӡ����е��������
}


// CpaintingView ���

#ifdef _DEBUG
void CpaintingView::AssertValid() const
{
	CView::AssertValid();
}

void CpaintingView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CpaintingDoc* CpaintingView::GetDocument() const // �ǵ��԰汾��������
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CpaintingDoc)));
	return (CpaintingDoc*)m_pDocument;
}
#endif //_DEBUG


// CpaintingView ��Ϣ�������


void CpaintingView::sline()
{
	//MessageBox(_T("���ڿ��Ի���ֱ�ߣ�"));
	dType=SLine;// TODO: �ڴ���������������
}


int CpaintingView::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	
	if (CView::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	// TODO: Add your specialized creation code here
	btn.Create(_T("��ť"),WS_CHILD|WS_VISIBLE|BS_DEFPUSHBUTTON,CRect(20,20,100,100),this,123);
	
	return 0;
}


void CpaintingView::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
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
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
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
 GetClientRect(&rect); //��ȡ�ͻ�����
 pDoc->m_bmpBuf.DeleteObject();
 pDoc->m_bmpBuf.CreateCompatibleBitmap(pDC,rect.Width(),rect.Height());
 CBitmap *pOldBitmap = dcMem.SelectObject(&pDoc->m_bmpBuf);//�������õ�m_bmpBuf��ӵ���ʱ��CDC��Object�У���������ǽ���Ⱥ���ǽֽ^_^������ǽֽ����������������γɵĻ�������ǽ�ϡ�
 CPoint m_ptEnd = point;

 dcMem.BitBlt(0,0,rect.Width(),rect.Height(),pDC,0,0,SRCCOPY);
 dcMem.SelectObject(pOldBitmap); //��pDC����ǰ�ͻ�����������ݿ�������ʱ��MEM�У�MEM��Ȼ����ᱻdelete����������������CDocument���е�m_bmpBuf
 m_bDraw = false;
 dcMem.DeleteDC();
}


void CpaintingView::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
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
	// TODO: �ڴ���������������
	// TODO: Add your command handler code here
	
	//MessageBox("��ʼ������������!");
	dType=CLine;
}


void CpaintingView::OnLButtonDblClk(UINT nFlags, CPoint point)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	// TODO: Add your message handler code here and/or call default
	dType=NoDraw;
	CView::OnLButtonDblClk(nFlags, point);
}


void CpaintingView::nosector()
{
	// TODO: �ڴ���������������
	// TODO: Add your command handler code here
		dType=NoSector;
}


//void CpaintingView::On32775()
//{
//	// TODO: �ڴ���������������
//}


void CpaintingView::sector()
{
	// TODO: �ڴ���������������
	// TODO: Add your command handler code here
	dType=Sector;
}


void CpaintingView::rect()
{
	// TODO: �ڴ���������������
	// TODO: Add your command handler code here
	dType=Recta;
}


void CpaintingView::ecllipse()
{
	// TODO: �ڴ���������������
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
	// TODO: �ڴ���������������
}


void CpaintingView::DrawFont()
{
	// TODO: �ڴ���������������
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
	// TODO: �ڴ���������������
	CSettingDlg dlg;
	dlg.m_nLineWidth=m_nLineWidth;
	dlg.m_nLineStyle=m_nLineStyle;
	if(IDOK==dlg.DoModal())
	{
		m_nLineWidth=dlg.m_nLineWidth;
		m_nLineStyle=dlg.m_nLineStyle;
	
	}
}
