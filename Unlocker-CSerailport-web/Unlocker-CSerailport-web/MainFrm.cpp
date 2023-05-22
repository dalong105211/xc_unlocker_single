// MainFrm.cpp : CMainFrame ���ʵ��
//

#include "stdafx.h"
#include "RTK_Pack.h"

#include "MainFrm.h"
#include ".\mainfrm.h"

#include "ChildFrm.h"
#include <WinVer.h>
#include <Windows.h>
#include <Dbt.h>
#include <afxinet.h>
#define MAXSIZE 1024

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

const UINT WM_UPDATE_ALARMFILTER = ::RegisterWindowMessage(_T("UpdateAlarmFilter"));
// CMainFrame

IMPLEMENT_DYNAMIC(CMainFrame, CMDIFrameWnd)

BEGIN_MESSAGE_MAP(CMainFrame, CMDIFrameWnd)
	ON_WM_CREATE()
	//ON_COMMAND(ID_USER_MANAGE, &CMainFrame::OnUserManage)
	ON_COMMAND(ID_FUN_OPER, &CMainFrame::OnFunOper)
	//ON_COMMAND(ID_RECORD_REVIEW, &CMainFrame::OnRecordReview)
	ON_WM_DEVICECHANGE()
END_MESSAGE_MAP()

static UINT indicators[] =
{
	ID_SEPARATOR,           // ״̬��ָʾ��
	ID_INDICATOR_CAPS,
	ID_INDICATOR_CAPS,
	ID_INDICATOR_CAPS,
	ID_INDICATOR_NUM,
	ID_INDICATOR_SCRL,
};


// CMainFrame ����/����

CMainFrame::CMainFrame()
{
	// TODO: �ڴ���ӳ�Ա��ʼ������

	//m_Carton = NULL;
	m_Export = NULL;
	//m_Record = NULL;
}

CMainFrame::~CMainFrame()
{
}


int CMainFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CMDIFrameWnd::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	//if (!m_wndToolBar.CreateEx(this, TBSTYLE_FLAT, WS_CHILD | WS_VISIBLE | CBRS_TOP
	//	| CBRS_GRIPPER | CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_DYNAMIC) ||
	//	!m_wndToolBar.LoadToolBar(IDR_MAINFRAME))
	//{
	//	TRACE0("δ�ܴ���������\n");
	//	return -1;      // δ�ܴ���
	//}

	if (!m_wndStatusBar.Create(this) ||
		!m_wndStatusBar.SetIndicators(indicators,
		  sizeof(indicators)/sizeof(UINT)))
	{
		TRACE0("δ�ܴ���״̬��\n");
		return -1;      // δ�ܴ���
	}
	// TODO: �������Ҫ��������ͣ������ɾ��������
	//m_wndToolBar.EnableDocking(CBRS_ALIGN_ANY);
	//EnableDocking(CBRS_ALIGN_ANY);
	//DockControlBar(&m_wndToolBar);
	// 
	m_wndStatusBar.SetPaneInfo(0,ID_INDICATOR_TIP,SBPS_STRETCH,150);
	m_wndStatusBar.SetPaneText(0, "User:None", TRUE);
	m_wndStatusBar.SetPaneInfo(1,ID_INDICATOR_TIP,SBPS_NORMAL,120);
	m_wndStatusBar.SetPaneText(1,"unlock tool:0",TRUE);
	m_wndStatusBar.SetPaneInfo(2, ID_INDICATOR_TIP, SBPS_NORMAL, 120);
	m_wndStatusBar.SetPaneText(2,"switch mode tool:0",TRUE);
	m_wndStatusBar.SetPaneInfo(3, ID_INDICATOR_TIP, SBPS_NORMAL, 120);
	m_wndStatusBar.SetPaneText(3,"adb tool:0",TRUE);
	m_wndStatusBar.SetPaneInfo(4, ID_INDICATOR_TIP, SBPS_NORMAL, 120);
	m_wndStatusBar.SetPaneText(4, "puk tool:0", TRUE);
	m_wndStatusBar.SetPaneInfo(5, ID_INDICATOR_TIP, SBPS_NORMAL, 120);
	m_wndStatusBar.SetPaneText(5, "custres tool:0", TRUE);


	return 0;
}

BOOL CMainFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	if( !CMDIFrameWnd::PreCreateWindow(cs) )
		return FALSE;
	// TODO: �ڴ˴�ͨ���޸� CREATESTRUCT cs ���޸Ĵ������
	// ��ʽ
	cs.cx = 1150;
	cs.cy = 650;

	return TRUE;
}


// CMainFrame ���

#ifdef _DEBUG
void CMainFrame::AssertValid() const
{
	CMDIFrameWnd::AssertValid();
}

void CMainFrame::Dump(CDumpContext& dc) const
{
	CMDIFrameWnd::Dump(dc);
}

#endif //_DEBUG

// CMainFrame ��Ϣ�������

//
//void CMainFrame::OnUserManage()
//{
//	Logger("model ","OnUserManage");
//	// TODO: �ڴ���������������
//	if(m_Carton!=NULL)
//	{
//		m_Carton->MDIActivate();
//		return;
//	}
//
//	m_Carton=new CChildFrame();
//	CCreateContext context;
//	context.m_pNewViewClass=RUNTIME_CLASS(CCarton);
//	if(!m_Carton->LoadFrame(IDI_ICON_CREATPRODUCT,WS_MAXIMIZE|WS_OVERLAPPEDWINDOW,this,&context))
//		return;
//	m_Carton->ShowWindow(SW_SHOWMAXIMIZED);
//	m_Carton->InitialUpdateFrame(NULL,true);
//
//	m_Carton->Msg("Module->User Manage",true);
//}

void CMainFrame::OnFunOper()
{
	Logger("model ","OnFunOper");

	if(m_Export!=NULL)
	{
		m_Export->MDIActivate();
		return;
	}
	m_Export=new CChildFrame();
	CCreateContext context;
	context.m_pNewViewClass=RUNTIME_CLASS(CExport);
	if(!m_Export->LoadFrame(IDI_ICON_CREATPRODUCT,WS_MAXIMIZE|WS_OVERLAPPEDWINDOW,this,&context))
		return;
	m_Export->ShowWindow(SW_SHOWMAXIMIZED);
	m_Export->InitialUpdateFrame(NULL,true);

	m_Export->Msg("Module->Lock & Unlock",true);
	// TODO: �ڴ���������������
}

//
//void CMainFrame::OnRecordReview()
//{
//	// TODO: �ڴ���������������
//	Logger("model ", "OnRecordReview");
//
//	if (m_Record != NULL)
//	{
//		m_Record->MDIActivate();
//		return;
//	}
//
//	m_Record = new CChildFrame();
//	CCreateContext context;
//	context.m_pNewViewClass = RUNTIME_CLASS(CRecord);
//	if (!m_Record->LoadFrame(IDI_ICON_CREATPRODUCT, WS_MAXIMIZE | WS_OVERLAPPEDWINDOW, this, &context))
//		return;
//	m_Record->ShowWindow(SW_SHOWMAXIMIZED);
//	m_Record->InitialUpdateFrame(NULL, true);
//
//	m_Record->Msg("Module->Record review", true);
//}


void CMainFrame::SetStatusBar(CString user, CString unlock, CString switchMode, CString adb, CString puk, CString custres)
{

	CString Str;
	if (user != "")
	{
		Str.Format("User:%s", user);
		m_wndStatusBar.SetPaneText(0, Str, TRUE);
	}
	if (unlock != "")
	{
		Str.Format("unlock tool:%s", unlock);
		m_wndStatusBar.SetPaneText(1,Str,TRUE);
	}
	if (switchMode != "")
	{
		Str.Format("switch mode tool:%s", switchMode);
		m_wndStatusBar.SetPaneText(2,Str,TRUE);
	}	

	if (adb != "")
	{
		Str.Format("adb tool:%s", adb);
		m_wndStatusBar.SetPaneText(3,Str,TRUE);
	}

	if (puk != "")
	{
		Str.Format("puk tool:%s", puk);
		m_wndStatusBar.SetPaneText(4, Str, TRUE);
	}

	if (custres != "")
	{
		Str.Format("custres tool:%s", custres);
		m_wndStatusBar.SetPaneText(5, Str, TRUE);
	}

}



CString CMainFrame::MEID_Hex2Dec(CString m_MEID_Hex)
{
	CString m_MEID_Dec; 
	CString strTemp;

	strTemp.Format(TEXT("%010u"),_tcstoul(m_MEID_Hex.Mid(0,8),NULL,16));  
	m_MEID_Dec.Format(TEXT("%s%08u"),strTemp,_tcstoul(m_MEID_Hex.Mid(8,6),NULL,16));

	return m_MEID_Dec;
}

CString CMainFrame::MEID_Dec2Hex(CString m_MEID_Dec)
{
	CString m_MEID_Hex; 
	CString strTemp;

	strTemp.Format(TEXT("%08X"),_tcstoul(m_MEID_Dec.Mid(0,10),NULL,10));  
	m_MEID_Hex.Format(TEXT("%s%06X"),strTemp,_tcstoul(m_MEID_Dec.Mid(10,8),NULL,10)); 

	return m_MEID_Hex;
}

CString CMainFrame::GetFileVersion()
{
	int iVerInfoSize;
	char *pBuf;
	CString asVer = "";
	VS_FIXEDFILEINFO *pVsInfo;
	unsigned int iFileInfoSize = sizeof(VS_FIXEDFILEINFO);

	CString m_sFilePath;
	GetModuleFileName(NULL,m_sFilePath.GetBuffer(MAX_PATH),MAX_PATH);

	iVerInfoSize = GetFileVersionInfoSize(m_sFilePath,NULL);

	if (iVerInfoSize != 0)
	{
		pBuf = new char[iVerInfoSize];
		if (GetFileVersionInfo(m_sFilePath,0,iVerInfoSize,pBuf))
		{
			if (VerQueryValue(pBuf,"\\",(VOID **)&pVsInfo,&iFileInfoSize))
			{
				asVer.Format("%d.%d.%d.%d",HIWORD(pVsInfo->dwFileVersionMS),LOWORD(pVsInfo->dwFileVersionMS),HIWORD(pVsInfo->dwFileVersionLS),LOWORD(pVsInfo->dwFileVersionLS));
			}
		}
		delete pBuf;
	}
	//Logger("ver: ",asVer);
	return asVer;
	
}


void Log(CString logText)
{
	CString Str,strPath,m_strData,m_strTime;
	
	CTime m_time;
	m_time = CTime::GetCurrentTime();
	//m_strData = m_time.Format(_T("%x"));//��ʽ������
	m_strData = m_time.Format(_T("%y-%m-%d")) ;
	m_strTime = m_time.Format(_T("%H:%M:%S "));//��ʽ������
	strPath ="C:\\" +  m_strData + ".txt";
	CString strText =m_strTime + _T(logText) + "\n";//strTextΪҪд��txt�ļ�������
	//�����Unicode�ַ�������д�����ĵ�ʹ����Ҫ���������һ�䣬ASCII����.��Ҫ����ͷ�ļ�locale.h
	char* pOldLocale = setlocale(LC_CTYPE, "chs");
	CStdioFile fOutput(_T(strPath), CFile::modeCreate |CFile::modeNoTruncate| CFile::modeWrite | CFile::typeText);
	if (fOutput)
	{
		fOutput.SeekToEnd();
		fOutput.WriteString(strText);
		fOutput.Close();
	}
	setlocale(LC_CTYPE, pOldLocale);//������˵
}
void Logger(CString header,CString logText)
{
	CString Str,strPath,m_strData,m_strTime;
	
	CTime m_time;
	m_time = CTime::GetCurrentTime();
	//m_strData = m_time.Format(_T("%x"));//��ʽ������
	m_strData = m_time.Format(_T("%y-%m-%d")) ;
	m_strTime = m_time.Format(_T("%H:%M:%S "));//��ʽ������


	//��ȡ·��
	CString m_path;
	GetCurrentDirectory(MAX_PATH, m_path.GetBuffer(MAX_PATH));
	m_path.Format("%s\\%s.txt", m_path, m_strData);
	CString strText =m_strTime + _T(header)+ _T(logText) + "\n";//strTextΪҪд��txt�ļ�������
	//�����Unicode�ַ�������д�����ĵ�ʹ����Ҫ���������һ�䣬ASCII����.��Ҫ����ͷ�ļ�locale.h
	//char* pOldLocale = setlocale(LC_CTYPE, "chs");
	CStdioFile fOutput(_T(m_path), CFile::modeCreate | CFile::modeNoTruncate | CFile::modeWrite | CFile::typeText);
	if (fOutput)
	{
		fOutput.SeekToEnd();
		fOutput.WriteString(strText);
		fOutput.Close();
	}
	//setlocale(LC_CTYPE, pOldLocale);//������˵

}
bool WriteToFile(CString pathFile, CString sn, CString wt )
{
	CString Str, strPath, m_strData, m_strTime;

	CTime m_time;
	m_time = CTime::GetCurrentTime();
	//m_strData = m_time.Format(_T("%x"));//��ʽ������
	m_strData = m_time.Format(_T("%y-%m-%d"));
	m_strTime = m_time.Format(_T("%H:%M:%S "));//��ʽ������

	strPath = pathFile;
	CString strText = m_strTime + ',' + _T(sn) + ',' + _T(wt) + "\n";//strTextΪҪд��txt�ļ�������
	//�����Unicode�ַ�������д�����ĵ�ʹ����Ҫ���������һ�䣬ASCII����.��Ҫ����ͷ�ļ�locale.h
	//char* pOldLocale = setlocale(LC_CTYPE, "chs");
	//char* pOldLocale = setlocale(LC_CTYPE,"utf-8");
	try
	{
		CStdioFile fOutput(_T(strPath), CFile::modeCreate | CFile::modeNoTruncate | CFile::modeWrite | CFile::typeText);
		if (fOutput)
		{
			fOutput.SeekToEnd();
			fOutput.WriteString(strText);
			fOutput.Close();
		}
		else
		{
			return false;
		}
	}
	catch (CFileException *e)
	{
		e->ReportError();
		e->Delete();
		return false;
	}
	
	//setlocale(LC_CTYPE, pOldLocale);//������˵
	return true;
}

/*************************************************MySql*************************************************************/

bool InitConfig(CString &sOutput)
{
	CRTK_PackApp *app = (CRTK_PackApp *)AfxGetApp();
	char Host[128];
	char Protocol[128];
	char Port[128];

	int tStatus;
	CString sFileName;

	GetCurrentDirectory(MAX_PATH, sFileName.GetBuffer(MAX_PATH));
	sFileName.Format("%s\\Config.ini", sFileName);

	//load config
	tStatus = GetPrivateProfileString("api", "host", "", Host, 128, sFileName);
	if (tStatus <= 0)
	{
		sOutput = "Read Config.ini file error, [api] host Empty";
		return false;
	}
	app->g_user.host = Host;

	tStatus = GetPrivateProfileString("api", "protocol", "", Protocol, 128, sFileName);
	if (tStatus <= 0)
	{
		sOutput = "Read Config.ini file error, [api] protocol Empty";
		return false;
	}
	app->g_user.protocol = Protocol;

	tStatus = GetPrivateProfileString("api", "port", "", Port, 128, sFileName);
	if (tStatus <= 0)
	{
		sOutput = "Read Config.ini file error, [api] port Empty";
		return false;
	}
	app->g_user.port = Port;

	return true;
}

DWORD GetHash(BYTE *pbData, DWORD dwDataLen, ALG_ID algId, LPTSTR pszHash)
{

	DWORD dwReturn = 0;
	HCRYPTPROV hProv;
	if (!CryptAcquireContext(&hProv, NULL, NULL, PROV_RSA_FULL, CRYPT_VERIFYCONTEXT))
		return (dwReturn = GetLastError());

	HCRYPTHASH hHash;
	//Alg Id:CALG_MD5,CALG_SHA
	if (!CryptCreateHash(hProv, algId, 0, 0, &hHash))
	{
		dwReturn = GetLastError();
		CryptReleaseContext(hProv, 0);
		return dwReturn;
	}

	if (!CryptHashData(hHash, pbData, dwDataLen, 0))
	{
		dwReturn = GetLastError();
		CryptDestroyHash(hHash);
		CryptReleaseContext(hProv, 0);
		return dwReturn;
	}

	DWORD dwSize;
	DWORD dwLen = sizeof(dwSize);
	CryptGetHashParam(hHash, HP_HASHSIZE, (BYTE*)(&dwSize), &dwLen, 0);

	BYTE* pHash = new BYTE[dwSize];
	dwLen = dwSize;
	CryptGetHashParam(hHash, HP_HASHVAL, pHash, &dwLen, 0);

	lstrcpy(pszHash, _T(""));
	TCHAR szTemp[3];
	for (DWORD i = 0; i < dwLen; ++i)
	{
		//wsprintf(szTemp, _T("%X%X"), pHash[i] >> 4, pHash[i] & 0xf);
		wsprintf(szTemp, "%02X", pHash[i]);
		lstrcat(pszHash, szTemp);
	}
	delete[] pHash;

	CryptDestroyHash(hHash);
	CryptReleaseContext(hProv, 0);
	return dwReturn;
}

CString Md5(CString str)
{
	TCHAR szStr[20] = { 0 };
	TCHAR szHash[41] = { 0 };

	strcpy(szStr, str);
	GetHash((BYTE*)szStr, strlen(szStr), CALG_MD5, szHash);
	return (CString)szHash;
}

int calcDays(CString dt)
{
	CTime m_now;
	m_now = CTime::GetCurrentTime();

	//ת��ΪCTime
	COleVariant vtime(dt);
	vtime.ChangeType(VT_DATE);
	COleDateTime cOleTime = vtime;
	SYSTEMTIME systime;
	VariantTimeToSystemTime(cOleTime, &systime);
	CTime cTimeFromDB(systime);
	return (m_now - systime).GetDays();
}

CString getDT()
{
	CTime nowdate = CTime::GetCurrentTime();
	CString s_Time;
	s_Time.Format("%d-%.2d-%.2d %.2d:%.2d:%.2d", nowdate.GetYear(), nowdate.GetMonth(), nowdate.GetDay(), nowdate.GetHour(), nowdate.GetMinute(), nowdate.GetSecond());
	return s_Time;
}

int GetLocalHostIPName(CString &sLocalName, CString &sIpAddress)
{
	char szLocalName[256];//����
	WSADATA wsaData;//�����׽��ִ洢����
	if (WSAStartup(MAKEWORD(2, 0), &wsaData) == 0)//<span class="con">windows��ʼ��socket����⣬����2��0�İ汾��windows socket��̱�<img class="selectsearch-hide" id="selectsearch-icon" alt="����" src="http://img.baidu.com/img/iknow/qb/select-search.png" />���ȳ�ʼ�����������,�򷵻�0</span>
	{
		if (gethostname(szLocalName, sizeof(szLocalName)) != 0)//��������
		{
			sLocalName = _T("û��ȡ��");
			WSACleanup();
			return GetLastError();
		}
		else
		{
			sLocalName = szLocalName;//��sLocalName�����洢��õļ��������
			struct hostent FAR * lpHostEnt = gethostbyname(sLocalName);
			if (lpHostEnt == NULL)//����
			{
				sIpAddress = _T("");
				WSACleanup();
				return GetLastError();
			}
			LPSTR lpAddr = lpHostEnt->h_addr_list[0];//��ȡIP��ַ
			if (lpAddr)
			{
				struct in_addr inAddr;
				memmove(&inAddr, lpAddr, 4);
				sIpAddress = inet_ntoa(inAddr);//ת��Ϊ��׼��ʽ
				if (sIpAddress.IsEmpty())
				{
					sIpAddress = _T("û��ȡ��");
					WSACleanup();
					return 1;
				}
			}
		}
	}
	WSACleanup();//����׽��ֳ�ʼ������
	return 0;
}

//01_ login
BOOL api_login(CString username,CString passw, CString & sOutput)
{
	CString str,url;
	CString m_strLocalIP; //
	CString m_strLocalName; //
	GetLocalHostIPName(m_strLocalName, m_strLocalIP);//
	CRTK_PackApp *app = (CRTK_PackApp *)AfxGetApp();

	url.Format("%s://%s:%s/api/main", app->g_user.protocol.Trim(), app->g_user.host.Trim(), app->g_user.port.Trim());
	str.Format("{\"username\":\"%s\",\"ip\":\"%s\",\"pc\":\"%s\",\"password\":\"%s\",\"func\":\"01_login\"}", username, m_strLocalIP, m_strLocalName, passw);
	return PostSubmit(url, str, sOutput);
}

//02_ update password
BOOL api_edit_password(CString username, CString passw, CString newNassw, CString & sOutput)
{
	CString str, url;
	CString m_strLocalIP; //
	CString m_strLocalName; //
	GetLocalHostIPName(m_strLocalName, m_strLocalIP);//
	CRTK_PackApp *app = (CRTK_PackApp *)AfxGetApp();

	url.Format("%s://%s:%s/api/main", app->g_user.protocol.Trim(), app->g_user.host.Trim(), app->g_user.port.Trim());
	str.Format("{\"username\":\"%s\",\"ip\":\"%s\",\"pc\":\"%s\",\"password\":\"%s\",\"newPassword\":\"%s\",\"func\":\"02_edit_password\"}", username, m_strLocalIP, m_strLocalName, passw,newNassw);
	return PostSubmit(url, str, sOutput);
}

//03_ insert cmd and result
BOOL api_insert_cmd_record(CString cmd, CString result, CString & sOutput)
{
	CString str, url;
	CString m_strLocalIP; //
	CString m_strLocalName; //
	GetLocalHostIPName(m_strLocalName, m_strLocalIP);//
	CRTK_PackApp *app = (CRTK_PackApp *)AfxGetApp();

	url.Format("%s://%s:%s/api/main", app->g_user.protocol.Trim(), app->g_user.host.Trim(), app->g_user.port.Trim());
	str.Format("{\"username\":\"%s\",\"ip\":\"%s\",\"pc\":\"%s\",\"cmd\":\"%s\",\"res\":\"%s\",\"func\":\"03_record_cmd\"}", app->g_user.name, m_strLocalIP, m_strLocalName, cmd, result);
	str.Replace("\r","");
	str.Replace("\n", "");
	return PostSubmit(url, str, sOutput);
}

//04_ verify dycode
BOOL api_verify_code(CString code, CString & sOutput)
{
	CString str, url;
	CString m_strLocalIP; //
	CString m_strLocalName; //
	GetLocalHostIPName(m_strLocalName, m_strLocalIP);//
	CRTK_PackApp *app = (CRTK_PackApp *)AfxGetApp();

	url.Format("%s://%s:%s/api/main", app->g_user.protocol.Trim(), app->g_user.host.Trim(), app->g_user.port.Trim());
	str.Format("{\"username\":\"%s\",\"ip\":\"%s\",\"pc\":\"%s\",\"dycode\":\"%s\",\"func\":\"04_verify\"}", app->g_user.name, m_strLocalIP, m_strLocalName, code);
	return PostSubmit(url, str, sOutput);
}

//05_ check last login info to verify logined in other place
BOOL api_check_login(CString & sOutput)
{
	CString url, params;
	CString m_strLocalIP; //
	CString m_strLocalName; //
	GetLocalHostIPName(m_strLocalName, m_strLocalIP);//
	CRTK_PackApp *app = (CRTK_PackApp *)AfxGetApp();

	url.Format("%s://%s:%s/api/main", app->g_user.protocol.Trim(), app->g_user.host.Trim(), app->g_user.port.Trim());
	params.Format("{\"username\":\"%s\",\"ip\":\"%s\",\"pc\":\"%s\",\"func\":\"05_check_last_login\"}", app->g_user.name, m_strLocalIP, m_strLocalName);
	return PostSubmit(url, params, sOutput);
}

//�豸����¼�����Ϣ���Ӵ���view
BOOL CMainFrame::OnDeviceChange(UINT nEventType, DWORD dwData)
{
	if (nEventType == DBT_DEVICEREMOVECOMPLETE)
	{
		Logger("MainFrame", "device remove");
	}
	else if (nEventType == DBT_DEVICEARRIVAL)
	{
		Logger("MainFrame", "device insert");
	}
	
	if (m_Export != NULL)
	{
		//�ж�viewָ���Ƿ�Ϊ��
		if (m_Export->GetActiveView() != NULL)
		{
			m_Export->GetActiveView()->PostMessage(WM_MY_EVENT, 0, 0);	
		}
	}
	return TRUE;
}

BOOL PostSubmit(CString strUrl, CString strPara, CString&strContent)
{
	BOOL bRet = FALSE;

	CString strInfo;

	try
	{
		CString strServer, strObject, strHeader, strRet;
		unsigned short nPort;
		DWORD dwServiceType;

		strInfo.Format("strUrl is %s\n", strUrl);
		printf("strUrl is %s\n", strUrl);

		strInfo.Format("strPara is %s\n", strPara);
		printf("strPara is %s\n", strPara);

		if (!AfxParseURL(strUrl, dwServiceType, strServer, strObject, nPort))//������Ч�������ַ��
		{
			strContent = "Invalid host address!";

			return FALSE;
		}

		strInfo.Format("dwServiceType:%d\n", dwServiceType);
		printf("dwServiceType:%d\n", dwServiceType);

		strInfo.Format("strServer:%s\n", strServer);
		printf("strServer:%s\n", strServer);

		strInfo.Format("strObject:%s\n", strObject);
		printf("strObject:%s\n", strObject);

		strInfo.Format("nPort:%d\n", nPort);
		printf("nPort:%d\n", nPort);

		CInternetSession sess(_T("faxsms"));

		CHttpFile* pFile = NULL;

		CHttpConnection *pServer = sess.GetHttpConnection(strServer, nPort);
		if (pServer == NULL)//���ӷ�����ʧ�ܣ�
		{
			strInfo.Format("%s\n", "Connect to server fail!");
			strContent = "Connect to server fail!";

			return FALSE;
		}

		pFile = pServer->OpenRequest(CHttpConnection::HTTP_VERB_POST, strObject, NULL, 1, NULL, NULL, INTERNET_FLAG_EXISTING_CONNECT);
		if (pFile == NULL)//�Ҳ��������ַ
		{
			strContent = "Can not find the net address!";

			sess.Close();
			return FALSE;
		}

		//pFile->AddRequestHeaders("Content-Type: application/x-www-form-urlencoded");
		/*CString contype;
		contype.Format("Content-Type: application/json%s\r\n");*/
		pFile->AddRequestHeaders("Content-Type: application/json\r\n");
		pFile->AddRequestHeaders("Accept: */*\r\n");
		pFile->AddRequestHeaders("Accept-Encoding: gzip, deflate, br\r\n");
		pFile->AddRequestHeaders("User-Agent: PostmanRuntime / 7.29.2\r\n");
		pFile->AddRequestHeaders("Connection: keep-alive\r\n");
		
		CHAR buf[1024] = { 0 };
		memcpy(buf, strPara.GetBuffer(), strlen(strPara.GetBuffer()));
		int buf_len = strlen(buf);
		//if (!pFile->SendRequest(NULL, 0, (LPTSTR)(LPCTSTR)strPara, strPara.GetLength()))
		if (!pFile->SendRequest(NULL, 0, buf, buf_len))
		{
			strContent = "SendRequest error!";

			pFile->Close();
			sess.Close();

			return FALSE;
		}

		CString strSentence;
		DWORD dwStatus;
		DWORD dwBuffLen = sizeof(dwStatus);
		BOOL bSuccess = pFile->QueryInfo(HTTP_QUERY_STATUS_CODE | HTTP_QUERY_FLAG_NUMBER, &dwStatus, &dwBuffLen);

		//if( bSuccess&& dwStatus>=200&& dwStatus<300) 
		if (bSuccess&& dwStatus == 200)
		{
			strInfo.Format("dwStatus:%d\n", dwStatus);
			printf("dwStatus:%d\n", dwStatus);

			char buffer[2049];
			memset(buffer, 0, 2049);

			int nReadCount = 0;

			while ((nReadCount = pFile->Read(buffer, 2048))>0)
			{
				strContent += buffer;
				memset(buffer, 0, 2049);
			}

			char *szBuf = new char[strContent.GetLength() + 1];//ע�⡰+1����char�ַ�Ҫ�����������CStringû��
			memset(szBuf, '\0', strContent.GetLength());


			int i;
			for (i = 0; i < strContent.GetLength(); i++)
			{
				szBuf[i] = (char)strContent.GetAt(i);
			}
			szBuf[i] = '\0';//���������������ĩβ�������롣

			int nLen;
			WCHAR *ptch;
			CString strOut;
			if (szBuf == NULL)
			{
				return TRUE;
			}
			nLen = MultiByteToWideChar(CP_UTF8, 0, szBuf, -1, NULL, 0);//�����Ҫ�Ŀ��ַ��ֽ���
			ptch = new WCHAR[nLen];
			memset(ptch, '\0', nLen);
			MultiByteToWideChar(CP_UTF8, 0, szBuf, -1, ptch, nLen);
			//str.Format(_T("%s"), ptch);
			strContent = ptch;
			if (NULL != ptch)
				delete[] ptch;
			ptch = NULL;


			if (NULL != szBuf)
				delete[]szBuf;
			szBuf = NULL;


			bRet = TRUE;
		}
		else//���� 
		{
			if (bSuccess&& dwStatus>200 && dwStatus<300)
			{
				char buffer[2049];
				memset(buffer, 0, 2049);

				int nReadCount = 0;

				while ((nReadCount = pFile->Read(buffer, 2048))>0)
				{
					strContent += buffer;
					memset(buffer, 0, 2049);
				}

				strInfo.Format("strContent:%s\n", strContent);
			}
			strContent.Format("Query result:%d,code:%d\n", bSuccess, dwStatus);
			bRet = FALSE;
		}

		pFile->Close();
		sess.Close();

	}
	catch (CInternetException *e)
	{
		strContent.Format("ERROR001 :error code is %ld\n", e->m_dwError);

		bRet = FALSE;

	}
	catch (...)
	{
		strContent = "Unknown Error";

		bRet = FALSE;
	}

	return bRet;
}

/*
content-������json�ַ���
sKey-keyֵ
isArray-Ҫȡ����������������
size-Ҫ�ӵڼ���������ȡ����
sKey2-Ҫȡ�����еùؼ���
sOutput-���
return-ȡֵ�Ƿ�ɹ�
*/
BOOL parseJson(CString content, CString sKey, bool isArray, int size, CString sKey2, CString & sOutput)
{
	sOutput = "";
	WDocument jsonDoc;//����һ��dom
	jsonDoc.Parse(content);
	//�ж��ַ����Ƿ��д���
	if (jsonDoc.HasParseError()) {
		sOutput.Format("Json Parse error:%d", jsonDoc.GetParseError()); //��ӡ������
		return FALSE;
	}

	//��ȡjson���е�����
	if (jsonDoc.HasMember(sKey))
	{
		WValue v_data;
		v_data = jsonDoc[(LPCTSTR)(sKey)];
		if (isArray == false)
		{
			if (v_data.IsArray() == false)
			{
				sOutput = v_data.GetString();
				return TRUE;
			}
			else
			{
				WValue v_tempData;
				v_tempData = v_data[0];
				sOutput = v_tempData.GetString();
				return TRUE;
			}

		}
		else
		{
			if (v_data.IsArray())
			{
				if (v_data.Size() <= size)
				{
					sOutput.Format("input size %d is more array size %d", size, v_data.Size());
					return FALSE;
				}
				else
				{
					WValue v_tempData;
					v_tempData = v_data[size];
					//Ҫ���ж��Ƿ������ݣ�������쳣
					if (v_tempData.IsObject() && v_tempData.HasMember((sKey2))) {
						WValue v_data_name;
						v_data_name = v_tempData[(LPCTSTR)(sKey2)];
						sOutput = v_data_name.GetString();
						return TRUE;
					}
					else
					{
						sOutput.Format("Json parse array fail.");
						return FALSE;
					}
				}
			}
			else
			{
				sOutput.Format("Json parse array fail.%s", v_data.GetString());
				return FALSE;
			}
		}
	}
	else
	{
		sOutput.Format("Json has not key:%s", sKey);
		return FALSE;
	}
}
