#pragma once
#include "GridCtrl.h"
#include "afxwin.h"
#include "BtnST.h"

// CCarton ������ͼ

class CCarton : public CFormView
{
	DECLARE_DYNCREATE(CCarton)

protected:
	CCarton();           // ��̬������ʹ�õ��ܱ����Ĺ��캯��
	virtual ~CCarton();

public:
	enum { IDD = IDD_DIALOG_CARTON };
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif
	afx_msg void OnDestroy();

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	virtual void OnInitialUpdate();

	BOOL PreTranslateMessage(MSG* pMsg);

public:
	CGridCtrl* m_pGridCtrl;
	CComboBox m_ComboBox_Product;
	GV_ITEM Item;
	afx_msg void OnCbnSelchangeComboFunction();
	afx_msg void OnBnClickedButtonAct();

	bool AddNormalUser();
	bool AddAdminUser();
	bool ModifyPassword();
	bool DeleteUser();

	void UpdateUserList();
	afx_msg void OnCbnSelchangeComboUser();
};


