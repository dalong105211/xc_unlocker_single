#pragma once


// CLineConfig �Ի���

class CLineConfig : public CDialog
{
	DECLARE_DYNAMIC(CLineConfig)

public:
	CLineConfig(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CLineConfig();

// �Ի�������
	enum { IDD = IDD_DIALOG_LINECONFIG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()

public:
	virtual BOOL OnInitDialog();

	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedCancel();

	CString m_sLine;
};
