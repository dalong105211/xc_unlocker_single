// LineConfig.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "RTK_Pack.h"
#include "LineConfig.h"
#include ".\lineconfig.h"


// CLineConfig �Ի���

IMPLEMENT_DYNAMIC(CLineConfig, CDialog)
CLineConfig::CLineConfig(CWnd* pParent /*=NULL*/)
	: CDialog(CLineConfig::IDD, pParent)
{
}

CLineConfig::~CLineConfig()
{
}

void CLineConfig::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CLineConfig, CDialog)
	ON_BN_CLICKED(IDOK, OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, OnBnClickedCancel)
END_MESSAGE_MAP()

BOOL CLineConfig::OnInitDialog()
{
	CDialog::OnInitDialog();

	CString m_sFilePath;
	GetModuleFileName(NULL,m_sFilePath.GetBuffer(MAX_PATH),MAX_PATH);
	m_sFilePath.ReleaseBuffer();
	m_sFilePath.Replace("Check.exe","config.ini");
	char m_cBuff[124];
	GetPrivateProfileString("Line","Line","",m_cBuff,128,m_sFilePath);
	GetDlgItem(IDC_EDIT_LINE)->SetWindowText(m_cBuff);

	return TRUE;
}

// CLineConfig ��Ϣ�������

void CLineConfig::OnBnClickedOk()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	GetDlgItem(IDC_EDIT_LINE)->GetWindowText(m_sLine);
	if (m_sLine == "")
	{
		AfxMessageBox("�������ߺ�",MB_ICONERROR|MB_TOPMOST);
		return;
	}
	else
	{
		//д�������ļ�
		CString m_sFilePath;
		GetModuleFileName(NULL,m_sFilePath.GetBuffer(MAX_PATH),MAX_PATH);
		m_sFilePath.ReleaseBuffer();
		m_sFilePath.Replace("Check.exe","config.ini");
		WritePrivateProfileString("Line","Line",m_sLine,m_sFilePath);

		OnOK();
	}
}

void CLineConfig::OnBnClickedCancel()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	OnCancel();
}
