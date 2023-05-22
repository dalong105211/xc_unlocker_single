// WeightConfig.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "RTK_Pack.h"
#include "WeightConfig.h"
#include ".\weightconfig.h"


// CWeightConfig �Ի���

IMPLEMENT_DYNAMIC(CWeightConfig, CDialog)
CWeightConfig::CWeightConfig(CWnd* pParent /*=NULL*/)
	: CDialog(CWeightConfig::IDD, pParent)
{
}

CWeightConfig::~CWeightConfig()
{
}

void CWeightConfig::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CWeightConfig, CDialog)
	ON_BN_CLICKED(IDOK, OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, OnBnClickedCancel)
	ON_CBN_SELCHANGE(IDC_COMBO_BALANCE, OnCbnSelchangeComboBalance)
END_MESSAGE_MAP()


// CWeightConfig ��Ϣ�������
BOOL CWeightConfig::OnInitDialog()
{
	CDialog::OnInitDialog();
	

	return TRUE;
}

void CWeightConfig::OnBnClickedOk()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	//m_iBalanceSel = ((CComboBox*)GetDlgItem(IDC_COMBO_BALANCE))->GetCurSel();

	CString Str;
	GetDlgItem(IDC_EDIT_WEIGHT_MIN)->GetWindowText(Str);
	if (Str == "")
	{
		AfxMessageBox("��������������",MB_ICONERROR|MB_TOPMOST);
		return;
	}
	m_fWeight_Min = atof(Str);
	GetDlgItem(IDC_EDIT_WEIGHT_MAX)->GetWindowText(Str);
	if (Str == "")
	{
		AfxMessageBox("��������������",MB_ICONERROR|MB_TOPMOST);
		return;
	}
	m_fWeight_Max = atof(Str);

	OnOK();
}

void CWeightConfig::OnBnClickedCancel()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	OnCancel();
}

void CWeightConfig::OnCbnSelchangeComboBalance()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
}
