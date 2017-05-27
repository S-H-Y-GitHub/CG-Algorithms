
// cgTest1View.cpp : CcgTest1View ���ʵ��
//

#include "stdafx.h"
// SHARED_HANDLERS ������ʵ��Ԥ��������ͼ������ɸѡ�������
// ATL ��Ŀ�н��ж��壬�����������Ŀ�����ĵ����롣
#ifndef SHARED_HANDLERS
#include "cgTest1.h"
#endif

#include "cgTest1Doc.h"
#include "cgTest1View.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CcgTest1View

IMPLEMENT_DYNCREATE(CcgTest1View, CView)

BEGIN_MESSAGE_MAP(CcgTest1View, CView)
	// ��׼��ӡ����
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CcgTest1View::OnFilePrintPreview)
	//ON_WM_CONTEXTMENU()
	//	ON_WM_RBUTTONUP()
	ON_COMMAND(ID_POLYGON, &CcgTest1View::OnPolygon)
	ON_COMMAND(ID_FILLPOLYGON, &CcgTest1View::OnFillpolygon)
	ON_WM_LBUTTONDOWN()
	ON_WM_RBUTTONDOWN()
	ON_COMMAND(ID_CHANGE_DC, &CcgTest1View::OnChangeDc)
END_MESSAGE_MAP()

// CcgTest1View ����/����

CcgTest1View::CcgTest1View()
{
	// TODO: �ڴ˴���ӹ������
	finish = false;
	m_pointNum = 0;
	m_point.clear();
	m_graphType = 1;
}

CcgTest1View::~CcgTest1View()
{
}

BOOL CcgTest1View::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: �ڴ˴�ͨ���޸�
	//  CREATESTRUCT cs ���޸Ĵ��������ʽ

	return CView::PreCreateWindow(cs);
}

// CcgTest1View ����

void CcgTest1View::OnDraw(CDC* /*pDC*/)
{
	CcgTest1Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: �ڴ˴�Ϊ����������ӻ��ƴ���
}


// CcgTest1View ��ӡ


void CcgTest1View::OnFilePrintPreview()
{
#ifndef SHARED_HANDLERS
	AFXPrintPreview(this);
#endif
}

BOOL CcgTest1View::OnPreparePrinting(CPrintInfo* pInfo)
{
	// Ĭ��׼��
	return DoPreparePrinting(pInfo);
}

void CcgTest1View::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: ��Ӷ���Ĵ�ӡǰ���еĳ�ʼ������
}

void CcgTest1View::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: ��Ӵ�ӡ����е��������
}

//void CcgTest1View::OnRButtonUp(UINT /* nFlags */, CPoint point)
//{
//	ClientToScreen(&point);
//	OnContextMenu(this, point);
//}

//	void CcgTest1View::OnContextMenu(CWnd* /* pWnd */, CPoint point)
//	{
//#ifndef SHARED_HANDLERS
//		theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
//#endif
//	}


	// CcgTest1View ���

#ifdef _DEBUG
void CcgTest1View::AssertValid() const
{
	CView::AssertValid();
}

void CcgTest1View::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CcgTest1Doc* CcgTest1View::GetDocument() const // �ǵ��԰汾��������
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CcgTest1Doc)));
	return (CcgTest1Doc*)m_pDocument;
}
#endif //_DEBUG


// CcgTest1View ��Ϣ�������


void CcgTest1View::OnPolygon()
{
	// TODO: �ڴ���������������
	m_graphType = 1;
}


void CcgTest1View::OnFillpolygon()
{
	// TODO: �ڴ���������������
	m_graphType = 2;
}


void CcgTest1View::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	if (m_graphType == 1 && !finish)
	{
		m_point.push_back(point);
		m_pointNum++;
	}
	CView::OnLButtonDown(nFlags, point);
}

void CcgTest1View::OnRButtonDown(UINT nFlags, CPoint point)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ

	if (m_graphType == 1)
	{
		finish = true;
		int i;
		for (i = 0; i < m_pointNum; i++)
		{
			int t;
			if (i < m_pointNum - 1)
				t = i + 1;
			else
				t = 0;
			drawLineMid(m_point[i], m_point[t]);
		}
		//drawLineMid(m_point[0],m_point[1]);
	}
	else
	{
		CDC *pDC = GetWindowDC();
		double y = 0.5;//saomiaoxian
		for (; y < 1000; y++)
		{
			vector<int> c;
			for (int i = 0; i < m_pointNum; i++)
			{
				int t;
				if (i < m_pointNum - 1)
					t = i + 1;
				else
					t = 0;
				CPoint p1 = m_point[i];
				CPoint p2 = m_point[t];
				if ((y<p1.y&&y>p2.y) || (y > p1.y&&y < p2.y))
				{
					int x = (y - p2.y)*(p1.x - p2.x) / (p1.y - p2.y) + p2.x;
					c.push_back(x);
				}
			}
			sort(c.begin(), c.end());
			for (int i = 0, j = 1; j < c.size(); i += 2, j += 2)
			{
				for (int x = c[i]; x <= c[j]; x++)
					pDC->SetPixel(CPoint(x, (int)y), RGB(255, 0, 0));
			}
		}
	}
	CView::OnRButtonDown(nFlags, point);
}


void CcgTest1View::drawLineMid(CPoint p1, CPoint p2)
{
	CDC *pDC = GetWindowDC();

	if (p1.x > p2.x)
	{
		CPoint t = p1;
		p1 = p2;
		p2 = t;
	}
	bool convert_y = false, convert_xy = false;
	if (p1.y > p2.y)
	{
		convert_y = true;
		p1.y = -p1.y;
		p2.y = -p2.y;
	}
	if (p1.x == p2.x)
	{
		for (int i = p1.y; i <= p2.y; i++)
			pDC->SetPixel(CPoint(p1.x, i), RGB(255, 0, 0));
		return;
	}
	if (p1.y == p2.y)
	{
		for (int i = p1.x; i <= p2.x; i++)
			pDC->SetPixel(CPoint(i, p1.y), RGB(255, 0, 0));
		return;
	}
	if (p2.y - p1.y > p2.x - p1.x)
	{
		convert_xy = true;
		int t = p1.x;
		p1.x = p1.y;
		p1.y = t;
		t = p2.x;
		p2.x = p2.y;
		p2.y = t;
	}
	int a = p1.y - p2.y;
	int b = p2.x - p1.x;
	int d = 2 * a + b;
	int deta1 = 2 * a;
	int deta2 = 2 * (a + b);
	int x = p1.x, y = p1.y, px = x, py = y;
	while (x < p2.x)
	{
		px = x;
		py = y;
		if (convert_xy)
		{
			int t = px;
			px = py;
			py = t;
		}
		if (convert_y)
		{
			py = -py;
		}
		pDC->SetPixel(CPoint(px, py), RGB(255, 0, 0));

		if (d < 0)
		{
			x = x + 1;
			y = y + 1;
			d = d + deta2;
		}
		else
		{
			x = x + 1;
			d = d + deta1;
		}
	}
}


void CcgTest1View::OnChangeDc()
{
	// TODO: �ڴ���������������
	CDC *pDC = GetWindowDC();
	pDC->LineTo(100, 100);
}
