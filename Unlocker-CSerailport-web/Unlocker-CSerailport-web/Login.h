#pragma once


// CLogin �Ի���

class CLogin : public CDialog
{
	DECLARE_DYNAMIC(CLogin)

public:
	CLogin(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CLogin();

// �Ի�������
	enum { IDD = IDD_DIALOG_PW_MODIFY };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButtonLogin();
	afx_msg void OnBnClickedButtonModify();
	afx_msg void OnBnClickedCancel();
	int DoModal();
	CString _whois;
	afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
	LOGIN_USER_s l_user;
	virtual BOOL PreTranslateMessage(MSG* pMsg);
};
