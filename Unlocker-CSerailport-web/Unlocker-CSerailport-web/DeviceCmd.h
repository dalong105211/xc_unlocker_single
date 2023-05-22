#pragma once
#include "RTK_Pack.h"
#include "afxwin.h"

//About CSerialPort start
#include "CSerialPort/SerialPort.h"
#include "CSerialPort/SerialPortInfo.h"
using namespace itas109;



UINT pAutoTest(LPVOID lpParam);

// CExport 窗体视图

class CExport : public CFormView, public CSerialPortListener
{
	DECLARE_DYNCREATE(CExport)

protected:
	CExport();           // 动态创建所使用的受保护的构造函数
	virtual ~CExport();

public:
	enum { IDD = IDD_DIALOG_EXPORT };

	void onReadEvent(const char *portName, unsigned int readBufferLen); // About CSerialPort

#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif
	afx_msg void OnDestroy();

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()

public:
	virtual void OnInitialUpdate();

public:
	CApplication Excel_app;
	CWorkbook Excel_workBook;   
	CWorksheet Excel_workSheet;   
	CWorksheets Excel_workSheets;   
	CWorkbooks Excel_workBooks;   
	CRange Excel_range;   
	CRange Excel_range1;   
	char Excel_path[MAX_PATH];
	Cnterior inter;

	CString m_sProject;
	BOOL PreTranslateMessage(MSG* pMsg);
	
	void SearchComport();
	void getSpecialComNumFromDevInfo();
	CString parseComport();
	CString parseCmd();
	CString parseFunction();
	afx_msg void OnBnClickedButtonStart();
	afx_msg void OnCbnSelchangeComboCom();

	BOOL TestProcess();


	HINSTANCE hDLL;
	BOOL InitComDll(CString &sOutput);
	BOOL OpenComport(UINT port, CString rate, CString &sOutput);
	BOOL ReadComport(CString &sOutput);
	BOOL WriteComport(CString sInput, CString &sOutput);
	BOOL CloseComport(CString &sOutput);
	BOOL DoAtCmd(CString cmd,CString &sOutput);

	BOOL CExport::getCmd();
	BOOL CExport::needVerify();


	afx_msg void OnCbnSelchangeComboMode();
	
	afx_msg LRESULT OnMyEvent(WPARAM wParam, LPARAM lParam);

	BOOL ComOpen();
	BOOL ComClose();
	BOOL ComSend(CString cmd);

	char cmd[5];
	CString lastCmd;
	CString lastMsg;

	void CExport::printLog(CString msg, bool res);
	int check_login_status();


private:
	CSerialPort m_SerialPort;//About CSerialPort 
public:
	afx_msg void OnClose();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
};


