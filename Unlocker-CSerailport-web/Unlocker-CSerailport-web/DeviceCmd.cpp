// DeviceCmd.cpp :

#include "stdafx.h"
#include "DeviceCmd.h"

#include "MainFrm.h"
#include ".\DeviceCmd.h"
#include <comutil.h>
#include <Windows.h>
#include <iostream>
#include "comdef.h"
#include "Shlwapi.h"
#include "VerifyCode.h"

#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <Windows.h>
#include <setupapi.h>
#pragma comment(lib, "setupapi.lib")

// CExport


/*
Unlocker Tool 串口通讯协议
Select Tool	Select Function	Request(0x58 0x43 0x05)	Response(0x58 0x43 0x06)
01_unlock_tool	Unlock	0x58 0x43 0x05 0x01 0x01	0x58 0x43 0x06 0x01 0x01
02_switch_mode_tool	Debug	0x58 0x43 0x05 0x02 0x01	0x58 0x43 0x06 0x02 0x01
Release	0x58 0x43 0x05 0x02 0x02	0x58 0x43 0x06 0x02 0x02
03_adb_tool	Lock	0x58 0x43 0x05 0x03 0x01	0x58 0x43 0x06 0x03 0x01
Unlock	0x58 0x43 0x05 0x03 0x02	0x58 0x43 0x06 0x03 0x02
04_pub	Delete PUK	0x58 0x43 0x05 0x04 0x01	0x58 0x43 0x06 0x04 0x01
05_general	Delete CustRes	0x58 0x43 0x05 0x05 0x01	0x58 0x43 0x06 0x05 0x01
说明：CMD固定byte[5]长的数组 -- Head:0x58 0x43 0x05 + Data:0xXX 0xXX

*/


#define AT_REQU_HEADER	"\x58\x43\x05 "
#define AT_RESP_HEADER	"58 43 06 "

HANDLE hMutex;



IMPLEMENT_DYNCREATE(CExport, CFormView)
CExport::CExport()
	: CFormView(CExport::IDD)
{
}

CExport::~CExport()
{
}

void CExport::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CExport, CFormView)
	ON_WM_DESTROY()
	ON_BN_CLICKED(IDC_BUTTON_START, &CExport::OnBnClickedButtonStart)
	ON_CBN_SELCHANGE(IDC_COMBO_COM, &CExport::OnCbnSelchangeComboCom)
	ON_CBN_SELCHANGE(IDC_COMBO_MODE, &CExport::OnCbnSelchangeComboMode)
	ON_MESSAGE(WM_MY_EVENT, OnMyEvent)
	ON_WM_CLOSE()
	ON_WM_SYSCOMMAND()
END_MESSAGE_MAP()


// CExport

#ifdef _DEBUG
void CExport::AssertValid() const
{
	CFormView::AssertValid();
}

void CExport::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif //_DEBUG

COleVariant
	covTrue((short)TRUE),
	covFalse((short)FALSE),
	covOptional((long)DISP_E_PARAMNOTFOUND, VT_ERROR);


void CExport::OnDestroy() 
{
	ComClose();
	CFormView::OnDestroy();
	((CMainFrame*)AfxGetMainWnd())->m_Export=NULL;
}

void CExport::OnInitialUpdate() 
{
	CFormView::OnInitialUpdate();
	CString str;
	//str = "Augent Tool " + ((CMainFrame*)AfxGetMainWnd())->GetFileVersion();
	str = "v" + (((CMainFrame*)AfxGetMainWnd())->GetFileVersion()).Right(3);
	GetParentFrame()->SetWindowText(str);

	/*********************************************read config***********************************************************/
	CString sFileName;
	int tStatus;
	char key[128];
	GetCurrentDirectory(MAX_PATH, sFileName.GetBuffer(MAX_PATH));
	sFileName.Format("%s\\Config.ini", sFileName);

	//add comport rate
	((CComboBox*)GetDlgItem(IDC_COMBO_RATE))->ResetContent();
	for (int i = 0; i < 10; i++)
	{
		//load config
		str.Format("rate_%d", i);
		tStatus = GetPrivateProfileString("com", str, "", key, 128, sFileName);
		if (tStatus > 0)
		{
			((CComboBox*)GetDlgItem(IDC_COMBO_RATE))->AddString(key);
		}
	}
	((CComboBox*)GetDlgItem(IDC_COMBO_RATE))->SetCurSel(0);

	//add comport rate
	((CComboBox*)GetDlgItem(IDC_COMBO_RATE))->ResetContent();
	for (int i = 0; i < 10; i++)
	{
		//load config
		str.Format("rate_%d", i);
		tStatus = GetPrivateProfileString("com", str, "", key, 128, sFileName);
		if (tStatus > 0)
		{
			((CComboBox*)GetDlgItem(IDC_COMBO_RATE))->AddString(key);
		}
	}
	((CComboBox*)GetDlgItem(IDC_COMBO_RATE))->SetCurSel(0);

	CRTK_PackApp *app = (CRTK_PackApp *)AfxGetApp(); //生成指向应用程序类的指针
	((CComboBox*)GetDlgItem(IDC_COMBO_MODE))->ResetContent();
	//管理员全打开
	if (app->g_user.type == 1)
	{
		((CComboBox*)GetDlgItem(IDC_COMBO_MODE))->AddString("01_remove_tamper");
		((CComboBox*)GetDlgItem(IDC_COMBO_MODE))->AddString("02_switch_mode_tool");
		((CComboBox*)GetDlgItem(IDC_COMBO_MODE))->AddString("03_adb_tool");
		((CComboBox*)GetDlgItem(IDC_COMBO_MODE))->AddString("04_puk");
		((CComboBox*)GetDlgItem(IDC_COMBO_MODE))->AddString("05_close");
	}
	else
	{
		if (app->g_user.power.module1 == true)
			((CComboBox*)GetDlgItem(IDC_COMBO_MODE))->AddString("01_remove_tamper");
		if (app->g_user.power.module2 == true)
			((CComboBox*)GetDlgItem(IDC_COMBO_MODE))->AddString("02_switch_mode_tool");
		if (app->g_user.power.module3 == true)
			((CComboBox*)GetDlgItem(IDC_COMBO_MODE))->AddString("03_adb_tool");
		if (app->g_user.power.module4 == true)
			((CComboBox*)GetDlgItem(IDC_COMBO_MODE))->AddString("04_puk");
		if (app->g_user.power.module5 == true)
			((CComboBox*)GetDlgItem(IDC_COMBO_MODE))->AddString("05_custres");
		//((CComboBox*)GetDlgItem(IDC_COMBO_MODE))->AddString("05_close");
	}

	//((CComboBox*)GetDlgItem(IDC_COMBO_ACTIONS))->SetCurSel(0);

	//CString sOutput;
	//if (!(InitComDll(sOutput)))
	//{
	//	return;
	//}
	//SearchComport();
	getSpecialComNumFromDevInfo();
	((CComboBox*)GetDlgItem(IDC_COMBO_COM))->SetCurSel(0);
	m_SerialPort.connectReadEvent(this);
	
}

void CExport::getSpecialComNumFromDevInfo()
{
	CString sOutput;
	HDEVINFO hDevInfo = SetupDiGetClassDevs(NULL, NULL, NULL, DIGCF_PRESENT | DIGCF_ALLCLASSES);
	if (hDevInfo == INVALID_HANDLE_VALUE)
	{
		sOutput.Format("SetupDiGetClassDevs Err:%d", GetLastError());
		printLog(sOutput, false);
		return ;
	};

	SP_CLASSIMAGELIST_DATA _spImageData = { 0 };
	_spImageData.cbSize = sizeof(SP_CLASSIMAGELIST_DATA);
	SetupDiGetClassImageList(&_spImageData);

	SP_DEVINFO_DATA spDevInfoData = { 0 };
	spDevInfoData.cbSize = sizeof(SP_DEVINFO_DATA);
	for (DWORD i = 0; SetupDiEnumDeviceInfo(hDevInfo, i, &spDevInfoData); i++)
	{
		char  szBuf[MAX_PATH] = { 0 };
		int  wImageIdx = 0;
		short  wItem = 0;
		if (!SetupDiGetDeviceRegistryPropertyA(hDevInfo, &spDevInfoData, SPDRP_CLASS, NULL, (PBYTE)szBuf, MAX_PATH, 0))
		{
			continue;
		};
		if (strcmp(szBuf, "Ports") != 0) //只取端口
		{
			continue;
		}
		if (SetupDiGetClassImageIndex(&_spImageData, &spDevInfoData.ClassGuid, &wImageIdx))
		{
			char  szName[MAX_PATH] = { 0 };
			DWORD  dwRequireSize;

			if (!SetupDiGetClassDescription(&spDevInfoData.ClassGuid, (PSTR)szBuf, MAX_PATH, &dwRequireSize))
			{
				continue;
			};

			if (SetupDiGetDeviceRegistryProperty(hDevInfo, &spDevInfoData, SPDRP_FRIENDLYNAME, NULL, (PBYTE)szName, MAX_PATH - 1, 0))
			{
				//wprintf(L"FriendlyName:%s\r\n\r\n", szName);
				((CComboBox*)GetDlgItem(IDC_COMBO_COM))->AddString(szName);
			}
			else  if (SetupDiGetDeviceRegistryProperty(hDevInfo, &spDevInfoData, SPDRP_DEVICEDESC, NULL, (PBYTE)szName, MAX_PATH - 1, 0))
			{
				((CComboBox*)GetDlgItem(IDC_COMBO_COM))->AddString(szName);
			}
		}
	}
	SetupDiDestroyClassImageList(&_spImageData);
}

BOOL CExport::PreTranslateMessage(MSG* pMsg)
{
	CString Str;
	if (pMsg->message == WM_KEYDOWN && pMsg->wParam == VK_RETURN)
	{
		return TRUE;
	}
	if (pMsg->message == MY_THREAD_MSG)
	{
		printLog(lastMsg, false);
		Logger("DeviceCmd", lastMsg);
		return TRUE;
	}

	return CFormView::PreTranslateMessage(pMsg);

}

//register
void CExport::SearchComport()
{
	CString str;
	HKEY   hKey;
	((CComboBox*)GetDlgItem(IDC_COMBO_COM))->ResetContent();

	if (RegOpenKeyEx(HKEY_LOCAL_MACHINE, _T("Hardware\\DeviceMap\\SerialComm"), NULL, KEY_READ, &hKey) == ERROR_SUCCESS)
	{
		TCHAR       szPortName[256], szComName[256];
		DWORD       dwLong, dwSize;
		int         nCount = 0;
		while (true)
		{
			dwLong = dwSize = 256;
			if (RegEnumValue(hKey, nCount, szPortName, &dwLong, NULL, NULL, (PUCHAR)szComName, &dwSize) == ERROR_NO_MORE_ITEMS)
				break;
		
			str.Format(_T("%s"), szComName);
			((CComboBox*)GetDlgItem(IDC_COMBO_COM))->AddString(str);
			nCount++;
			dwLong = sizeof(szPortName);
			dwSize = sizeof(szComName);
		}

		RegCloseKey(hKey);
	}
}


void CExport::OnCbnSelchangeComboCom()
{
	ComClose();
	/*((CComboBox*)GetDlgItem(IDC_COMBO_COM))->ResetContent();
	getSpecialComNumFromDevInfo();
	((CComboBox*)GetDlgItem(IDC_COMBO_COM))->SetCurSel(0);*/
}


UINT pAutoTest(LPVOID lpParam)
{
	WaitForSingleObject(hMutex, INFINITE);
	CExport* pToolForDlg = (CExport*)lpParam;

	pToolForDlg->TestProcess();

	ReleaseMutex(hMutex);
	return 0;

}

BOOL CExport::TestProcess()
{
	CRTK_PackApp *app = (CRTK_PackApp *)AfxGetApp(); //生成指向应用程序类的指针
	CString user = app->g_user.name;
	CString str, fun_index, sOutput;
	CString sResp;
	if (getCmd() == FALSE)
	{
		goto end;
	}
		
	/*fun_index = parseCmd();
	if (fun_index.GetLength() == 0)
	{
		goto end;
	}*/
	//bool res;
	
	//TEST HTTP REQUEST PRESSURE
	/*int i = 0;
	do{
	i++;
	api_check_login(sResp);
	Sleep(1);
	} while (i < 1000);*/
	//check login status

	//弹窗动态申请码，客户2.7版本要求去掉动态码验证
	//if (needVerify() == TRUE)
	//{
	//	CVerifyCode vc;
	//	if (vc.DoModal() == IDCANCEL)
	//	{
	//		sOutput = "verify code cancel";
	//		//printLog(sOutput, false);
	//		Logger("DeviceCmd", sOutput);
	//		goto end;
	//	}
	//}

	//lastCmd = fun_index + "\r\n";
	
	if (DoAtCmd(lastCmd, sOutput))
	{
	}
	else
	{
		printLog(sOutput, false);
		Logger("DeviceCmd", sOutput);
		goto end;
	}
	//enable发送按钮
	((CComboBox*)GetDlgItem(IDC_BUTTON_START))->EnableWindow(true);
	return TRUE;
end:
	//enable发送按钮
	((CComboBox*)GetDlgItem(IDC_BUTTON_START))->EnableWindow(true);
	return FALSE;
}

//0-正常，-1-异地登陆，-2-请求失败,-3-解析失败
int CExport::check_login_status()
{
	CString sResp, sOutput;
	if (api_check_login(sResp) == FALSE)
	{
		Logger("DeviceCmd", sResp);
		return -2;
	}
	if (parseJson(sResp, "res", 0, 0, "", sOutput) == FALSE)
	{
		sOutput = "Parse res fail";
		printLog(sOutput, false);
		return -3;
	}
	if (sOutput != "1")
	{
		if (parseJson(sResp, "msg", 0, 0, "", sOutput) == FALSE)
		{
			sOutput = "Login fail,query error msg fail";
		}
		printLog(sOutput, false);
		AfxMessageBox("Account has been logged in elsewhere,click to logout.", MB_OK | MB_ICONINFORMATION);
		return -1;
	}
	return 0;
}

void CExport::OnBnClickedButtonStart()
{
	//先disable发送按钮
	((CComboBox*)GetDlgItem(IDC_BUTTON_START))->EnableWindow(false);

	//check login
	int res = check_login_status();
	if (res == -1)	//异地登录
	{
		CRTK_PackApp *app = (CRTK_PackApp *)AfxGetApp();
		app->LogOut();
		return;
	}
	else if (res == -2 || res == -3)	//请求或解析失败
	{
		((CComboBox*)GetDlgItem(IDC_BUTTON_START))->EnableWindow(true);
		return;
	}
	CWinThread *pThread = AfxBeginThread(pAutoTest, this);

	
}

BOOL CExport::DoAtCmd(CString cmd, CString &sOutput)
{
	if (ComOpen() == FALSE)
	{
		sOutput = "Open comport error,please try it again";
		ComClose();
		return FALSE;
	}
	if (ComSend(cmd) == FALSE)
	{
		sOutput = "Send cmd error,please try it again";
		ComClose();
		return FALSE;
	}
	
	return TRUE;
}

void CExport::OnCbnSelchangeComboMode()
{
	// TODO:  在此添加控件通知处理程序代码
	CString sFileName,str,sec;
	int tStatus;
	char key[128];
	((CComboBox*)GetDlgItem(IDC_COMBO_MODE))->GetWindowTextA(sec);
	GetCurrentDirectory(MAX_PATH, sFileName.GetBuffer(MAX_PATH));
	sFileName.Format("%s\\Config.ini", sFileName);

	//add comport rate
	((CComboBox*)GetDlgItem(IDC_COMBO_FUNCTION))->ResetContent();
	for (int i = 0; i < 10; i++)
	{
		//load config
		str.Format("func_0%d", i);
		tStatus = GetPrivateProfileString(sec, str, "", key, 128, sFileName);
		if (tStatus > 0)
		{
			((CComboBox*)GetDlgItem(IDC_COMBO_FUNCTION))->AddString(key);
		}
	}
	//((CComboBox*)GetDlgItem(IDC_COMBO_FUNCTION))->SetCurSel(0);
}


CString CExport::parseComport()
{
	CString str;
	((CComboBox*)GetDlgItem(IDC_COMBO_COM))->GetWindowTextA(str);
	int index = str.MakeUpper().Find("(COM");

	if (index > 0)
	{
		for (int i = 0; i < str.GetLength(); i++)
		{
			/*CString temp;
			temp = str[index + 4 + i];*/
			if (str[index + 4 + i] >= '0' && str[index + 4 + i] <= '9')
			{
				continue;
			}
			else
			{
				str = str.Mid(index + 1,3+i);
				break;
			}
		}
		/*str = str.Right(str.GetLength() - str.Find("(COM"));
		str = str.Left(str.Find(")"));
		str.Replace("(", "");
		str.Replace(")", "");*/
		return str;
	}
	else
	{
		return "";
	}
}

// 父窗口发来的消息，进行响应
LRESULT CExport::OnMyEvent(WPARAM wParam, LPARAM lParam)
{
	ComClose();
	Logger("DeviceCmd", "Get main message to refresh comport list");
	((CComboBox*)GetDlgItem(IDC_COMBO_COM))->ResetContent();
	getSpecialComNumFromDevInfo();
	((CComboBox*)GetDlgItem(IDC_COMBO_COM))->SetCurSel(0);
	return 0;
}



void CExport::onReadEvent(const char *portName, unsigned int readBufferLen)
{
	if (readBufferLen > 0)
	{
		char *data = new char[readBufferLen + 1]; // '\0'

		if (data)
		{
			int recLen = m_SerialPort.readData(data, readBufferLen);

			if (recLen > 0)
			{
				data[recLen] = '\0';
				bool res;
				CString out;
				if (strncmp(data, cmd, 2) == 0)
				{
					res = true;
					out = "success";
				}
				else
				{
					res = false;
					out = "fail";
				}
				CString func,str;
				((CComboBox*)GetDlgItem(IDC_COMBO_FUNCTION))->GetWindowTextA(func);
				str.Format("%s %s", func, out);
				printLog(str, res);
				if (needVerify() == TRUE)
				{
					if (res == false)
						printLog("Switch to debug mode failed", res);
					else
						printLog("Switch to debug mode successed", res);
				}

				CString sOutput;
				CString sResp;
				//check login status
				
				if (api_insert_cmd_record(func, out, sResp) == FALSE)
				{
					printLog(sResp, false);
					Logger("DeviceCmd", sResp);
					return;
				}
				if (parseJson(sResp, "res", 0, 0, "", sOutput) == FALSE)
				{
					sOutput = "Parse res fail";
					printLog(sOutput, false);
					return;
				}
				if (sOutput != "1")
				{
					if (parseJson(sResp, "msg", 0, 0, "", sOutput) == FALSE)
					{
						sOutput = "Login fail,query error msg fail";
					}
					printLog(sOutput, false);
					return;
				}
			}

			delete[] data;
			data = NULL;
		}
	}
}

BOOL CExport::ComOpen()
{
	if (m_SerialPort.isOpen())
	{
		m_SerialPort.close();
	}
	//解析串口
	char portName[256] = { 0 };
	int SelBaudRate;
	int SelParity;
	int SelDataBits;
	int SelStop;

	UpdateData(true);
	CString temp;
	temp = parseComport();
	if (temp.GetLength() < 3)
	{
		printLog("Get comport failed", false);
		Logger("DeviceCmd", "Get comport failed");
		return FALSE;
	}
#ifdef UNICODE
	strcpy_s(portName, 256, CW2A(temp.GetString()));
#else
	strcpy_s(portName, 256, temp.GetBuffer());
#endif	

	((CComboBox*)GetDlgItem(IDC_COMBO_RATE))->GetWindowTextA(temp);
	SelBaudRate = _tstoi(temp);

	SelParity = 0;
	SelDataBits = 8;
	SelStop = 0;

	m_SerialPort.setReadIntervalTimeout(50);
	m_SerialPort.init(portName, SelBaudRate, itas109::Parity(SelParity), itas109::DataBits(SelDataBits), itas109::StopBits(SelStop));
	m_SerialPort.open();

	if (m_SerialPort.isOpen())
	{
		return TRUE;
	}
	else
	{
		printLog("Comport open failed, please check it exist or idle", false);
		Logger("DeviceCmd", "Comport open failed, please check it exist or idle");
		return FALSE;
	}
}


BOOL CExport::ComClose()
{
	if (m_SerialPort.isOpen())
	{
		m_SerialPort.close();
	}
	return TRUE;
}

BOOL CExport::ComSend(CString temp)
{
	if (!m_SerialPort.isOpen()) ///没有打开串口
	{
		printLog("Comport not opened.", false);
		Logger("DeviceCmd", "Comport not opened.");
		return FALSE;
	}

	int len = 0;
	char* m_str = NULL;
#ifdef UNICODE
	// 兼容中文
	CStringA strA(temp);
	len = strA.GetLength();
	m_str = strA.GetBuffer();
#else
	len = temp.GetLength();
	m_str = temp.GetBuffer(0);
#endif
	


	//m_SerialPort.writeData(m_str, len);
	m_SerialPort.writeData(cmd, sizeof(cmd));
	return TRUE;
}

BOOL CExport::getCmd()
{
	CString func, mode;
	((CComboBox*)GetDlgItem(IDC_COMBO_MODE))->GetWindowTextA(mode);
	((CComboBox*)GetDlgItem(IDC_COMBO_FUNCTION))->GetWindowTextA(func);
	if (mode == "")
	{
		printLog("Please select mode", false);
		return FALSE;
	}
	if (func == "")
	{
		printLog("Please select func", false);
		return FALSE;
	}
	cmd[0] = { 0x58};
	cmd[1] = { 0x43};
	cmd[2] = { 0x05};
	if (mode.Find("01_") > -1 && func.Find("01_") > -1)
	{
		cmd[3] = { 0x01 };
		cmd[4] = { 0x01 };
	}
	else if (mode.Find("02_") > -1 && func.Find("01_") > -1)
	{
		cmd[3] = { 0x02 };
		cmd[4] = { 0x01 };
	}
	else if (mode.Find("02_") > -1 && func.Find("02_") > -1)
	{
		cmd[3] = { 0x02 };
		cmd[4] = { 0x02 };
	}
	else if (mode.Find("03_") > -1 && func.Find("01_") > -1)
	{
		cmd[3] = { 0x03 };
		cmd[4] = { 0x01 };
	}
	else if (mode.Find("03_") > -1 && func.Find("02_") > -1)
	{
		cmd[3] = { 0x03 };
		cmd[4] = { 0x02 };
	}
	else if (mode.Find("04_") > -1 && func.Find("01_") > -1)
	{
		cmd[3] = { 0x04 };
		cmd[4] = { 0x01 };
	}
	else if (mode.Find("05_") > -1 && func.Find("01_") > -1)
	{
		cmd[3] = { 0x05 };
		cmd[4] = { 0x01 };
	}
	else
	{
		printLog("Unknown cmd", false);
		return FALSE;
	}
}


BOOL CExport::needVerify()
{
	CString func, mode;
	((CComboBox*)GetDlgItem(IDC_COMBO_MODE))->GetWindowTextA(mode);
	((CComboBox*)GetDlgItem(IDC_COMBO_FUNCTION))->GetWindowTextA(func);
	if (mode == "")
	{
		printLog("Please select mode", false);
		return FALSE;
	}
	if (func == "")
	{
		printLog("Please select func", false);
		return FALSE;
	}
	
	if (mode.Find("02_") > -1 && func.Find("01_") > -1)
	{
		return TRUE;
	}
	else
	{
		return FALSE;
	}
}

CString CExport::parseCmd()
{
	CString fun_index, sOutput;

	((CComboBox*)GetDlgItem(IDC_COMBO_FUNCTION))->GetWindowTextA(fun_index);

	int n = fun_index.Find(',');
	if (n < 0 || fun_index.Trim().GetLength() == 0)
	{
		printLog("Please select function", false);
		Logger("DeviceCmd", "Please select function");
		return "";
	}
	CString fun_name = fun_index.Left(n);
	CString fun_cmd = fun_index.Right(fun_index.GetLength() - n - 1);
	return fun_cmd;
}


CString CExport::parseFunction()
{
	CString fun_index, sOutput;

	((CComboBox*)GetDlgItem(IDC_COMBO_FUNCTION))->GetWindowTextA(fun_index);

	int n = fun_index.Find(',');
	if (n < 0 || fun_index.Trim().GetLength() == 0)
	{
		printLog("Please select function", false);
		Logger("DeviceCmd", "Please select function");
		return "";
	}
	CString fun_name = fun_index.Left(n);
	CString fun_cmd = fun_index.Right(fun_index.GetLength() - n - 1);
	return fun_cmd;
}

void CExport::OnClose()
{
	// TODO:  在此添加消息处理程序代码和/或调用默认值
	ComClose();
	__super::OnClose();
}


void CExport::OnSysCommand(UINT nID, LPARAM lParam)
{
	// TODO:  在此添加消息处理程序代码和/或调用默认值

	__super::OnSysCommand(nID, lParam);
}



void CExport::printLog(CString msg,bool res)
{
	CMainFrame *pFrame = (CMainFrame*)AfxGetApp()->GetMainWnd();
	if (pFrame == NULL)
		return;

	pFrame->m_Export->Msg(msg, res);	
}