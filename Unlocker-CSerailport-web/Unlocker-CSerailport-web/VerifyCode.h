#pragma once


// CVerifyCode �Ի���

class CVerifyCode : public CDialog
{
	DECLARE_DYNAMIC(CVerifyCode)

public:
	CVerifyCode(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CVerifyCode();

// �Ի�������
	enum { IDD = IDD_DIALOG_PASSWORD };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
};
