// EditBoxNum.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "RTK_Pack.h"
#include "EditBoxNum.h"
#include ".\editboxnum.h"

// CEditBoxNum �Ի���

IMPLEMENT_DYNAMIC(CEditBoxNum, CDialog)
CEditBoxNum::CEditBoxNum(CWnd* pParent /*=NULL*/)
	: CDialog(CEditBoxNum::IDD, pParent)
{
}

CEditBoxNum::~CEditBoxNum()
{
}

void CEditBoxNum::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CEditBoxNum, CDialog)
	ON_BN_CLICKED(IDOK, OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, OnBnClickedCancel)
END_MESSAGE_MAP()


// CEditBoxNum ��Ϣ�������

void CEditBoxNum::OnBnClickedOk()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CString Str;

	GetDlgItem(IDC_EDIT_BOXNUM)->GetWindowText(Str);
	sSpecifyNum = Str;
	/*SpecifyNum = atoi(Str);
	if (SpecifyNum <= 0)
	{
		AfxMessageBox("��������ȷ���",MB_OK);
		return;
	}*/
	if (sSpecifyNum.GetLength() == 0)
	{
		AfxMessageBox("��������ȷ���",MB_OK);
		return;
	}

	OnOK();
}

void CEditBoxNum::OnBnClickedCancel()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	OnCancel();
}
