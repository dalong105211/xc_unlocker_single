// RTK_Pack.cpp : ����Ӧ�ó��������Ϊ��
//

#include "stdafx.h"
#include "RTK_Pack.h"
#include "MainFrm.h"

#include "ChildFrm.h"
#include ".\rtk_pack.h"
#include "Login.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CRTK_PackApp

BEGIN_MESSAGE_MAP(CRTK_PackApp, CWinApp)
	ON_COMMAND(ID_APP_ABOUT, OnAppAbout)
	ON_COMMAND(ID_LOGIN, &CRTK_PackApp::OnLogin)
	ON_COMMAND(ID_LOGIN_LOGINOUT, &CRTK_PackApp::OnLoginLoginout)
END_MESSAGE_MAP()


// CRTK_PackApp ����

CRTK_PackApp::CRTK_PackApp()
{
	// TODO: �ڴ˴���ӹ�����룬
	// ��������Ҫ�ĳ�ʼ�������� InitInstance ��
}


// Ψһ��һ�� CRTK_PackApp ����

CRTK_PackApp theApp;

// CRTK_PackApp ��ʼ��

BOOL CRTK_PackApp::InitInstance()
{
	// ���һ�������� Windows XP �ϵ�Ӧ�ó����嵥ָ��Ҫ
	// ʹ�� ComCtl32.dll �汾 6 ����߰汾�����ÿ��ӻ���ʽ��
	//����Ҫ InitCommonControls()�����򣬽��޷��������ڡ�
	InitCommonControls();

	CWinApp::InitInstance();

	// ��ʼ�� OLE ��
	if (!AfxOleInit())
	{
		AfxMessageBox(IDP_OLE_INIT_FAILED);
		return FALSE;
	}
	AfxEnableControlContainer();
	// ��׼��ʼ��
	// ���δʹ����Щ���ܲ�ϣ����С
	// ���տ�ִ���ļ��Ĵ�С����Ӧ�Ƴ�����
	// ����Ҫ���ض���ʼ������
	// �������ڴ洢���õ�ע�����
	// TODO: Ӧ�ʵ��޸ĸ��ַ�����
	// �����޸�Ϊ��˾����֯��
	SetRegistryKey(_T("Ӧ�ó��������ɵı���Ӧ�ó���"));

	m_hMutex = ::CreateMutex(NULL, FALSE, _T("DEM"));//����һ���������ÿһ�γ���򿪵�ʱ�򶼻���            
	//CreateMutex��������
	//����������󣬲��Ե���������������������ΪΨһ��ʶ����                                                 
	//��������򷵻� ERROR_ALREADY_EXISTS

	if (GetLastError() == ERROR_ALREADY_EXISTS)

	{
		AfxMessageBox(_T("Application was already running"));
		return FALSE;
	}

	// ��Ҫ���������ڣ��˴��뽫�����µĿ�ܴ���
	// ����Ȼ��������ΪӦ�ó���������ڶ���
	CMDIFrameWnd* pFrame = new CMainFrame;
	if (!pFrame)
		return FALSE;
	m_pMainWnd = pFrame;
	// ������ MDI ��ܴ���
	if (!pFrame->LoadFrame(IDR_MAINFRAME))
		return FALSE;
	// ��ͼ���ع��� MDI �˵��Ϳ�ݼ���
	//TODO: ��Ӹ��ӳ�Ա�����������ض�
	//	Ӧ�ó��������Ҫ�ĸ��Ӳ˵����͵ĵ���
	HINSTANCE hInst = AfxGetResourceHandle();
	m_hMDIMenu_login = ::LoadMenu(hInst, MAKEINTRESOURCE(IDR_MENU_LOGIN));
	m_hMDIMenu_admin = ::LoadMenu(hInst, MAKEINTRESOURCE(IDR_MENU_AMDIN));
	m_hMDIMenu_user = ::LoadMenu(hInst, MAKEINTRESOURCE(IDR_MENU_USER));

	m_hMenu=::LoadMenu(hInst, MAKEINTRESOURCE(IDR_MAINFRAME));
	m_hMDIAccel = ::LoadAccelerators(hInst, MAKEINTRESOURCE(IDR_RTK_PackTYPE));
	// �������ѳ�ʼ���������ʾ����������и���

	pFrame->ShowWindow(SW_SHOW);
	CString Str;
	//Str = "Augent Tool " + ((CMainFrame*)AfxGetMainWnd())->GetFileVersion();
	Str = "Augent Tool v" + (((CMainFrame*)AfxGetMainWnd())->GetFileVersion()).Right(3);
	pFrame->SetWindowText(Str);
	//((CMainFrame*)AfxGetMainWnd())->m_wndStatusBar.SetPaneText(0,"״̬: δ����",TRUE);

	//pFrame->ShowWindow(m_nCmdShow);
	//pFrame->ShowWindow(SW_SHOWMAXIMIZED);
	pFrame->UpdateWindow();

	
	SetMenu(AfxGetMainWnd()->m_hWnd, m_hMDIMenu_login);

	return TRUE;
}


// CRTK_PackApp ��Ϣ�������

int CRTK_PackApp::ExitInstance() 
{
	CString sOutput;
	//((CMainFrame*)AfxGetMainWnd())->CloseComport(sOutput);
	//TODO: �����������ӵĸ�����Դ
	if (m_hMDIMenu_login != NULL)
		FreeResource(m_hMDIMenu_login);
	if (m_hMDIMenu_admin != NULL)
		FreeResource(m_hMDIMenu_admin);
	if (m_hMDIMenu_user != NULL)
		FreeResource(m_hMDIMenu_user);
	if (m_hMDIAccel != NULL)
		FreeResource(m_hMDIAccel);

	return CWinApp::ExitInstance();
}

// ����Ӧ�ó��򡰹��ڡ��˵���� CAboutDlg �Ի���

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// �Ի�������
	enum { IDD = IDD_ABOUTBOX };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

// ʵ��
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
END_MESSAGE_MAP()

// �������жԻ����Ӧ�ó�������
void CRTK_PackApp::OnAppAbout()
{
	CAboutDlg aboutDlg;
	aboutDlg.DoModal();
}


// CRTK_PackApp ��Ϣ�������




void CRTK_PackApp::OnLogin()
{
	// TODO:  �ڴ���������������
	CLogin m_login;
	if (m_login.DoModal() == IDCANCEL)
	{
		return;
	}
	else
	{
		if (g_user.type == 1)
		{
			SetMenu(AfxGetMainWnd()->m_hWnd, m_hMDIMenu_admin);
			/*if (m_pMainWnd != NULL)
				m_pMainWnd->UpdateWindow();*/
		}
		else
			SetMenu(AfxGetMainWnd()->m_hWnd, m_hMDIMenu_user);


		//��¼��Ĭ�ϴ򿪲�������
		CMainFrame *pFrame = (CMainFrame*)AfxGetApp()->GetMainWnd();
		if (pFrame == NULL)
			return;
		pFrame->OnFunOper();
	}
}



void CRTK_PackApp::OnLoginLoginout()
{
	// TODO:  �ڴ���������������
	if (m_hMDIMenu_login != NULL)
		FreeResource(m_hMDIMenu_login);
	if (m_hMDIMenu_admin != NULL)
		FreeResource(m_hMDIMenu_admin);
	if (m_hMDIMenu_user != NULL)
		FreeResource(m_hMDIMenu_user);
	if (m_hMDIAccel != NULL)
		FreeResource(m_hMDIAccel);
	
	if (IDYES == AfxMessageBox("Confirm Logout?", MB_YESNO | MB_ICONQUESTION))
	{
		/*if (((CMainFrame*)AfxGetMainWnd())->m_Carton != NULL)
		{
			((CMainFrame*)AfxGetMainWnd())->m_Carton->DestroyWindow();
		}*/

		if (((CMainFrame*)AfxGetMainWnd())->m_Export != NULL)
		{
			((CMainFrame*)AfxGetMainWnd())->m_Export->DestroyWindow();
		}

		/*if (((CMainFrame*)AfxGetMainWnd())->m_Record != NULL)
		{
			((CMainFrame*)AfxGetMainWnd())->m_Record->DestroyWindow();
		}*/
		SetMenu(AfxGetMainWnd()->m_hWnd, m_hMDIMenu_login);

		((CMainFrame*)AfxGetMainWnd())->SetStatusBar("None", "0", "0", "0", "0","0");
	}
}



void CRTK_PackApp::LogOut()
{
	// TODO:  �ڴ���������������
	if (m_hMDIMenu_login != NULL)
		FreeResource(m_hMDIMenu_login);
	if (m_hMDIMenu_admin != NULL)
		FreeResource(m_hMDIMenu_admin);
	if (m_hMDIMenu_user != NULL)
		FreeResource(m_hMDIMenu_user);
	if (m_hMDIAccel != NULL)
		FreeResource(m_hMDIAccel);

	if (((CMainFrame*)AfxGetMainWnd())->m_Export != NULL)
	{
		((CMainFrame*)AfxGetMainWnd())->m_Export->DestroyWindow();
	}

	SetMenu(AfxGetMainWnd()->m_hWnd, m_hMDIMenu_login);

	CMainFrame *pFrame = (CMainFrame*)AfxGetApp()->GetMainWnd();
	if (pFrame == NULL)
		return;
	pFrame->SetStatusBar("None", "0", "0", "0", "0", "0");	
}