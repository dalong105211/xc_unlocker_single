#pragma once
#include "afxwin.h"


// CColorInfoConfirm �Ի���

class CColorInfoConfirm : public CDialog
{
	DECLARE_DYNAMIC(CColorInfoConfirm)

public:
	CColorInfoConfirm(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CColorInfoConfirm();

// �Ի�������
	enum { IDD = IDD_DIALOG_COLORINFO_CONFIRM };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	CEdit m_edit_USB;
	CEdit m_edit_Battery;
	CEdit m_edit_earphone;
	CEdit m_edit_chager;

	CString m_USB;
	CString m_Battery;
	CString m_earphone;
	CString m_chager;
	CString m_cup;

	afx_msg void OnBnClickedOk();
	virtual BOOL OnInitDialog();
	CEdit m_edit_cup;
};
