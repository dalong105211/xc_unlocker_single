#pragma once


// CWeightConfig �Ի���

class CWeightConfig : public CDialog
{
	DECLARE_DYNAMIC(CWeightConfig)

public:
	CWeightConfig(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CWeightConfig();

// �Ի�������
	enum { IDD = IDD_DIALOG_WEIGHTCONFIG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedCancel();

	double m_fWeight_Min,m_fWeight_Max;
	int m_iBalanceSel;

	afx_msg void OnCbnSelchangeComboBalance();
};
