
// paintingView.h : CpaintingView ��Ľӿ�
//

#pragma once
#include "afxwin.h"

enum DrawType {SLine,CLine,Ecllipse,SetPen,SetBrush,NoSector,Sector,Recta,ColorSet,NoDraw};
class CpaintingView : public CView
{
protected: // �������л�����
	CpaintingView();
	DECLARE_DYNCREATE(CpaintingView)

// ����
public:
	CpaintingDoc* GetDocument() const;

// ����
public:

// ��д
public:
	virtual void OnDraw(CDC* pDC);  // ��д�Ի��Ƹ���ͼ
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// ʵ��
public:
	virtual ~CpaintingView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// ���ɵ���Ϣӳ�亯��
protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void sline();
private:
	CPoint m_ptNext;
	DrawType dType;
	CPoint m_ptOrigin;
	COLORREF m_clr;
	BOOL m_bDraw;
	CButton btn;
public:
	int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void cline();
	afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point);
	afx_msg void nosector();
//	afx_msg void On32775();
	afx_msg void sector();
	afx_msg void rect();
	afx_msg void ecllipse();
//	void OnDrawColor();
	afx_msg void DrawColor();
	CString m_strFontName;
	CFont m_font;
	afx_msg void DrawFont();
	afx_msg void OnSetting();
	unsigned int m_nLineWidth;
	int m_nLineStyle;
};

#ifndef _DEBUG  // paintingView.cpp �еĵ��԰汾
inline CpaintingDoc* CpaintingView::GetDocument() const
   { return reinterpret_cast<CpaintingDoc*>(m_pDocument); }
#endif

