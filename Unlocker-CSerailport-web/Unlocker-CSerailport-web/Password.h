#pragma once



// CPassword ������ͼ

class CPassword : public CFormView
{
	DECLARE_DYNCREATE(CPassword)

protected:
	CPassword();           // ��̬������ʹ�õ��ܱ����Ĺ��캯��
	virtual ~CPassword();

public:
	enum { IDD = IDD_DIALOG_PW_MODIFY };
#ifdef _DEBUG
	virtual void AssertValid() const;
#ifndef _WIN32_WCE
	virtual void Dump(CDumpContext& dc) const;
#endif
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
};


