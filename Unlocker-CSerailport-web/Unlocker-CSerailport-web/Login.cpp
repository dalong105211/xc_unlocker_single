// Login.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "RTK_Pack.h"
#include "Mainfrm.h"
#include "Login.h"
#include "afxdialogex.h"


// CLogin �Ի���

IMPLEMENT_DYNAMIC(CLogin, CDialog)

CLogin::CLogin(CWnd* pParent /*=NULL*/)
	: CDialog(CLogin::IDD, pParent)
{

}

CLogin::~CLogin()
{
}

void CLogin::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CLogin, CDialog)
	ON_BN_CLICKED(ID_BUTTON_LOGIN, &CLogin::OnBnClickedButtonLogin)
	ON_BN_CLICKED(ID_BUTTON_MODIFY, &CLogin::OnBnClickedButtonModify)
	ON_BN_CLICKED(IDCANCEL, &CLogin::OnBnClickedCancel)
	ON_WM_SHOWWINDOW()
END_MESSAGE_MAP()


// CLogin ��Ϣ�������


void CLogin::OnBnClickedButtonLogin()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	CString sOutput,sResp;
	CString str;
	CString user;
	int type;
	CString passw;
	CString new_passw;
	CString cfm_passw;
	int count = 0;//��ȡ����
	//�������ݿ�
	if (false == InitConfig(sOutput))
	{
		AfxMessageBox(sOutput, MB_OK | MB_ICONINFORMATION);
		return;
	}

	//��֤�˺��Ƿ�Ϊ��
	GetDlgItem(IDC_EDIT_USER)->GetWindowTextA(str);
	user = str.Trim();
	if (user == "")
	{
		AfxMessageBox("Please input account", MB_OK | MB_ICONINFORMATION);
		return;
	}
	GetDlgItem(IDC_EDIT_PASSWORD_OLD)->GetWindowTextA(passw);
	

	//��֤�˺������Ƿ�ƥ��
	if (api_login(user, passw, sResp) == FALSE)
	{
		AfxMessageBox(sResp, MB_OK | MB_ICONINFORMATION);
		return;
	}
	if (parseJson(sResp, "res", 0, 0, "", sOutput) == FALSE)
	{
		sOutput = "Parse res fail";
		AfxMessageBox(sOutput, MB_OK | MB_ICONINFORMATION);
		return ;
	}
	if (sOutput != "1")
	{
		if (parseJson(sResp, "msg", 0, 0, "", sOutput) == FALSE)
		{
			sOutput = "Login fail,query error msg fail";
		}
		AfxMessageBox(sOutput, MB_OK | MB_ICONINFORMATION);
		return;
	}

	CRTK_PackApp *app = (CRTK_PackApp *)AfxGetApp(); //����ָ��Ӧ�ó������ָ��
	app->g_user.name = user;
	app->g_user.type = type;
	if (parseJson(sResp, "msg", 0, 0, "", sOutput) == FALSE)
	{
		sOutput = "Parse msg fail";
		AfxMessageBox(sOutput, MB_OK | MB_ICONINFORMATION);
		return;
	}
	if (sOutput.GetLength() < 3)
	{
		sOutput = "Tool function authorize query fail";
		AfxMessageBox(sOutput, MB_OK | MB_ICONINFORMATION);
		return;
	}

	str = sOutput.GetAt(0);
	app->g_user.power.module1 = atoi(str);
	str = sOutput.GetAt(1);
	app->g_user.power.module2 = atoi(str);
	str = sOutput.GetAt(2);
	app->g_user.power.module3 = atoi(str);
	str = sOutput.GetAt(3);
	app->g_user.power.module4 = atoi(str);
	str = sOutput.GetAt(4);
	app->g_user.power.module5 = atoi(str);

	
	CString access1, access2, access3, access4, access5;
	if (type == 1)
	{
		access1 = access2 = access3 = access4 = access5 = "1";
	}
	else
	{
		access1.Format("%d", app->g_user.power.module1);
		access2.Format("%d", app->g_user.power.module2);
		access3.Format("%d", app->g_user.power.module3);
		access4.Format("%d", app->g_user.power.module4);
		access5.Format("%d", app->g_user.power.module5);
	}
	((CMainFrame*)AfxGetMainWnd())->SetStatusBar(user, access1, access2, access3, access4, access5);
	CDialog::OnOK();
}


void CLogin::OnBnClickedButtonModify()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	CString sOutput, sResp;
	CString str;
	CString user;
	int type;
	CString passw;
	CString new_passw;
	CString cfm_passw;
	GetDlgItem(IDC_EDIT_USER)->GetWindowTextA(str);
	user = str.Trim();
	GetDlgItem(IDC_EDIT_PASSWORD_OLD)->GetWindowTextA(passw);
	GetDlgItem(IDC_EDIT_PASSWORD_NEW)->GetWindowTextA(new_passw);
	GetDlgItem(IDC_EDIT_PASSWORD_CONFIRM)->GetWindowTextA(cfm_passw);

	if (new_passw.GetLength() == 0)
	{
		AfxMessageBox("New password is empty.", MB_OK | MB_ICONINFORMATION);
		return;
	}
	if (cfm_passw.GetLength() == 0)
	{
		AfxMessageBox("Confirm password is empty.", MB_OK | MB_ICONINFORMATION);
		return;
	}
	if (new_passw != cfm_passw)
	{
		AfxMessageBox("New password and confirm password is not same.", MB_OK | MB_ICONINFORMATION);
		return;
	}
	if (new_passw.GetLength() < 8 || new_passw.GetLength() > 20)
	{
		AfxMessageBox("Password length should be 8 to 20 and assembly by number and letter [0-9]&[A-z].", MB_OK | MB_ICONINFORMATION);
		return;
	}
	
	if (FALSE == api_edit_password(user, passw, new_passw, sResp))
	{
		AfxMessageBox(sResp, MB_OK | MB_ICONINFORMATION);
		return;
	}
	AfxMessageBox("Change password success.", MB_OK | MB_ICONINFORMATION);
	
	if (parseJson(sResp, "res", 0, 0, "", sOutput) == FALSE)
	{
		sOutput = "Parse res fail";
		AfxMessageBox(sOutput, MB_OK | MB_ICONINFORMATION);
		return;
	}
	if (sOutput != "1")
	{
		if (parseJson(sResp, "msg", 0, 0, "", sOutput) == FALSE)
		{
			sOutput = "Login fail,query error msg fail";
		}
		AfxMessageBox(sOutput, MB_OK | MB_ICONINFORMATION);
		return;
	}

	CRTK_PackApp *app = (CRTK_PackApp *)AfxGetApp(); //����ָ��Ӧ�ó������ָ��
	app->g_user.name = user;
	app->g_user.type = type;
	if (parseJson(sResp, "msg", 0, 0, "", sOutput) == FALSE)
	{
		sOutput = "Parse msg fail";
		AfxMessageBox(sOutput, MB_OK | MB_ICONINFORMATION);
		return;
	}
	if (sOutput.GetLength() < 3)
	{
		sOutput = "Tool function authorize query fail";
		AfxMessageBox(sOutput, MB_OK | MB_ICONINFORMATION);
		return;
	}
	str = sOutput.GetAt(0);
	app->g_user.power.module1 = atoi(str);
	str = sOutput.GetAt(1);
	app->g_user.power.module2 = atoi(str);
	str = sOutput.GetAt(2);
	app->g_user.power.module3 = atoi(str);
	str = sOutput.GetAt(3);
	app->g_user.power.module4 = atoi(str);
	str = sOutput.GetAt(4);
	app->g_user.power.module5 = atoi(str);


	CString access1, access2, access3, access4, access5;
	if (type == 1)
	{
		access1 = access2 = access3 = access4 = access5 = "1";
	}
	else
	{
		access1.Format("%d", app->g_user.power.module1);
		access2.Format("%d", app->g_user.power.module2);
		access3.Format("%d", app->g_user.power.module3);
		access4.Format("%d", app->g_user.power.module4);
		access5.Format("%d", app->g_user.power.module5);
	}
	((CMainFrame*)AfxGetMainWnd())->SetStatusBar(user, access1, access2, access3, access4, access5);
	CDialog::OnOK();
}

void CLogin::OnBnClickedCancel()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	CDialog::OnCancel();
}

int CLogin::DoModal()
{
	return CDialog::DoModal();
}

void CLogin::OnShowWindow(BOOL bShow, UINT nStatus)
{
	CDialog::OnShowWindow(bShow, nStatus);

	// TODO:  �ڴ˴������Ϣ����������
	GetDlgItem(IDC_EDIT_USER)->SetFocus();
}



BOOL CLogin::PreTranslateMessage(MSG* pMsg)
{
	// TODO:  �ڴ����ר�ô����/����û���
	if (pMsg->message == WM_KEYDOWN && pMsg->wParam == VK_RETURN)
	{
		OnBnClickedButtonLogin();
		return TRUE;
	}
	return CDialog::PreTranslateMessage(pMsg);
}
