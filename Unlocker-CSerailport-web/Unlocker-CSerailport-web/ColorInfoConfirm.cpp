// ColorInfoConfirm.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "RTK_Pack.h"
#include "ColorInfoConfirm.h"
#include "afxdialogex.h"


// CColorInfoConfirm �Ի���

IMPLEMENT_DYNAMIC(CColorInfoConfirm, CDialog)

CColorInfoConfirm::CColorInfoConfirm(CWnd* pParent /*=NULL*/)
	: CDialog(CColorInfoConfirm::IDD, pParent)
{

}

CColorInfoConfirm::~CColorInfoConfirm()
{
}

void CColorInfoConfirm::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT_USB, m_edit_USB);
	DDX_Control(pDX, IDC_EDIT_BATTERY, m_edit_Battery);
	DDX_Control(pDX, IDC_EDIT_EARPHONE, m_edit_earphone);
	DDX_Control(pDX, IDC_EDIT_CHAGER, m_edit_chager);
	DDX_Control(pDX, IDC_EDIT_CUP, m_edit_cup);
}


BEGIN_MESSAGE_MAP(CColorInfoConfirm, CDialog)
	ON_BN_CLICKED(IDOK, &CColorInfoConfirm::OnBnClickedOk)
END_MESSAGE_MAP()


// CColorInfoConfirm ��Ϣ�������


void CColorInfoConfirm::OnBnClickedOk()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CDialog::OnOK();
}


BOOL CColorInfoConfirm::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
	//��������
	CFont* m_font;
	m_font = new CFont;
	m_font->CreateFont(25,0,0,0,700,FALSE,FALSE,0,DEFAULT_CHARSET,OUT_DEFAULT_PRECIS,CLIP_DEFAULT_PRECIS,DEFAULT_QUALITY,DEFAULT_PITCH | FF_MODERN,"����");

	m_edit_USB.SetFont(m_font);
	m_edit_Battery.SetFont(m_font);
	m_edit_earphone.SetFont(m_font);
	m_edit_chager.SetFont(m_font);
	m_edit_cup.SetFont(m_font);

	GetDlgItem(IDC_STATIC_USB)->SetFont(m_font);
	GetDlgItem(IDC_STATIC_BATTERY)->SetFont(m_font);
	GetDlgItem(IDC_STATIC_EARPHONE)->SetFont(m_font);
	GetDlgItem(IDC_STATIC_CHAGER)->SetFont(m_font);
	GetDlgItem(IDC_STATIC_CUP)->SetFont(m_font);

	m_edit_USB.SetWindowTextA(m_USB);
	m_edit_Battery.SetWindowTextA(m_Battery);
	m_edit_earphone.SetWindowTextA(m_earphone);
	m_edit_chager.SetWindowTextA(m_chager);
	m_edit_cup.SetWindowTextA(m_cup);
	//m_edit_Battery.SetWindowTextA();

	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣: OCX ����ҳӦ���� FALSE
}
