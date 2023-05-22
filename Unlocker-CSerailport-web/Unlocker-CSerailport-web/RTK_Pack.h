// RTK_Pack.h : RTK_Pack Ӧ�ó������ͷ�ļ�
//
#include "afxwin.h"
#include "winsock.h"
//#include "mysql.h"

#include "CApplication.h"
#include "CRange.h"
#include "CWorkbook.h"
#include "CWorkbooks.h"
#include "CWorksheet.h"
#include "CWorksheets.h"
#include "Cnterior.h"



#pragma once

#ifndef __AFXWIN_H__
	#error �ڰ������� PCH �Ĵ��ļ�֮ǰ������stdafx.h�� 
#endif

#include "resource.h"       // ������


// CRTK_PackApp:
// �йش����ʵ�֣������ RTK_Pack.cpp
//


typedef struct POWER
{
	bool module1;
	bool module2;
	bool module3;
	bool module4;
	bool module5;
} POWER_s;

typedef struct LOGIN_USER
{
	CString name;
	UINT type;		//0-user,1-admin
	POWER_s power;	//userģ��Ȩ��
	CString host;
	CString protocol;
	CString port;
}LOGIN_USER_s;


class CRTK_PackApp : public CWinApp
{
public:
	CRTK_PackApp();
	LOGIN_USER_s g_user;//ȫ�ֵ��û�������

// ��д
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

// ʵ��
protected:
	HMENU m_hMDIMenu_login;
	HMENU m_hMDIMenu_admin;
	HMENU m_hMDIMenu_user;
	HMENU m_hMenu;
	HACCEL m_hMDIAccel;

	HANDLE m_hMutex;

public:
	void LogOut();
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()

	char Machine[128];
	char SQL_User[128];
	char SQL_Password[128];
	char cPort[128];
	unsigned int Port;
	afx_msg void OnLogin();

	


	afx_msg void OnLoginLoginout();
};

extern CRTK_PackApp theApp;
