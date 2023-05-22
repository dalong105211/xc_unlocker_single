// ChildFrm.cpp : CChildFrame ���ʵ��
//
#include "stdafx.h"
#include "RTK_Pack.h"

#include "ChildFrm.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CChildFrame

IMPLEMENT_DYNCREATE(CChildFrame, CMDIChildWnd)

BEGIN_MESSAGE_MAP(CChildFrame, CMDIChildWnd)
	ON_COMMAND(ID_FILE_CLOSE, OnFileClose)
	ON_WM_SETFOCUS()
	ON_WM_CREATE()
END_MESSAGE_MAP()


// CChildFrame ����/����

CChildFrame::CChildFrame()
{
	// TODO: �ڴ���ӳ�Ա��ʼ������

	i_Line = 0;

}

CChildFrame::~CChildFrame()
{
}


BOOL CChildFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: �ڴ˴�ͨ���޸� CREATESTRUCT cs ���޸Ĵ��������ʽ
	if( !CMDIChildWnd::PreCreateWindow(cs) )
		return FALSE;

	cs.dwExStyle &= ~WS_EX_CLIENTEDGE;
	cs.lpszClass = AfxRegisterWndClass(0);
	return TRUE;
}


// CChildFrame ���

#ifdef _DEBUG
void CChildFrame::AssertValid() const
{
	CMDIChildWnd::AssertValid();
}

void CChildFrame::Dump(CDumpContext& dc) const
{
	CMDIChildWnd::Dump(dc);
}

#endif //_DEBUG


// CChildFrame ��Ϣ�������
void CChildFrame::OnFileClose() 
{
	// ��Ҫ�رտ�ܣ�ֻ�跢�� WM_CLOSE
	//�����൱�ڴ�ϵͳ�˵���ѡ��رա�
	SendMessage(WM_CLOSE);
}

int CChildFrame::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CMDIChildWnd::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	// ����һ����ͼ��ռ�ÿ�ܵĹ�����
	//if (!m_wndView.Create(NULL, NULL, AFX_WS_DEFAULT_VIEW, 
	//	CRect(0, 0, 0, 0), this, AFX_IDW_PANE_FIRST, NULL))
	//{
	//	TRACE0("δ�ܴ�����ͼ����\n");
	//	return -1;
	//}

	//�����Ի���
	if(!m_wndBar.Create(this,IDD_DIALOG_MSG,WS_CHILD|WS_VISIBLE|
		CBRS_BOTTOM|CBRS_GRIPPER | CBRS_TOOLTIPS | CBRS_FLYBY | 
		CBRS_SIZE_DYNAMIC,IDD_DIALOG_MSG))
	{
		TRACE0("Failed to create dialogbar\n");
		return -1;      // fail to create
	}

	//���غ���ʾCListBox�ؼ�
	CListCtrl * pListCtrl=(CListCtrl *)m_wndBar.GetDlgItem(IDC_LIST_MSG);
	pListCtrl->SetWindowPos(NULL,0,0,GetSystemMetrics(SM_CXSCREEN)-11,132,SWP_NOMOVE|SWP_NOZORDER | SWP_NOACTIVATE|SWP_SHOWWINDOW);

	//���ݶԻ����ϵ�CTabCtrl�ؼ�
	pListCtrl->SetExtendedStyle(LVS_EX_FULLROWSELECT);
	pListCtrl->InsertColumn(0,"DateTime",LVCFMT_LEFT,140);
	pListCtrl->InsertColumn(1,"Status",LVCFMT_LEFT,750);

	pImagelist = new CImageList();
	pImagelist->Create(16,16,ILC_COLOR32,0,2);
	pImagelist->Add(AfxGetApp()->LoadIcon(IDI_ICON_PASS));
	pImagelist->Add(AfxGetApp()->LoadIcon(IDI_ICON_FAIL));

	CBitmap bmp;
	pImagelist->Add(&bmp,RGB(0,0,0));
	pListCtrl->SetImageList(pImagelist,LVSIL_SMALL);
	pListCtrl->SetImageList(pImagelist,LVSIL_SMALL);

	return 0;
}

void CChildFrame::OnSetFocus(CWnd* pOldWnd) 
{
	CMDIChildWnd::OnSetFocus(pOldWnd);

	//m_wndView.SetFocus();
}

BOOL CChildFrame::OnCmdMsg(UINT nID, int nCode, void* pExtra, AFX_CMDHANDLERINFO* pHandlerInfo) 
{
	// ����ͼ��һ�γ��Ը�����
	//if (m_wndView.OnCmdMsg(nID, nCode, pExtra, pHandlerInfo))
	//	return TRUE;
	
	// ����ִ��Ĭ�ϴ���
	return CMDIChildWnd::OnCmdMsg(nID, nCode, pExtra, pHandlerInfo);
}

void CChildFrame::Msg(CString Str,BOOL Status) 
{
	CListCtrl * pListCtrl=(CListCtrl *)m_wndBar.GetDlgItem(IDC_LIST_MSG);
	CTime time = CTime::GetCurrentTime();
	if (Status)
	{
		pListCtrl->InsertItem(i_Line,time.Format("[%Y-%m-%d %H:%M:%S] "),0);
	}
	else
	{
		pListCtrl->InsertItem(i_Line,time.Format("[%Y-%m-%d %H:%M:%S] "),1);
	}
	pListCtrl->SetItemText(i_Line,1,Str);
	pListCtrl->EnsureVisible(i_Line,TRUE);
	i_Line++;
	/*if (pListCtrl)
		free(pListCtrl);*/
	return;
}