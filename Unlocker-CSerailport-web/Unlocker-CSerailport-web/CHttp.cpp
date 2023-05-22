// HttpObj00.cpp : ���� DLL �ĳ�ʼ�����̡�
//

#include "stdafx.h"
#include <afxdllx.h>
#include "CHttp.h"
//
//#include <wininet.h>

#include <afxinet.h>
#include <string>


#define MAXSIZE 1024
//#pragma comment(lib, "Wininet.lib")


//��̬���ӿ��������


bool post(CString url,CString jStr)
{
	CString jStrEncode;
	EscapeURL(jStr, jStrEncode);

	CString out;
	if (!RequestUrl(url, "POST", jStrEncode, "application/json", out))
		return false;

	CString sOutput = "";
	//BOOL res = GetKeyValue(out, "code", sOutput);
	
	return true;
}


BOOL RequestUrl(CString strUrl, CString sMethod, CString sParams, CString sContentType, CString & sOutput)
{
	// ����Url
	// ���磺https://www.cnblogs.com/Zender/p/7596730.html
	DWORD dwServiceType;        // Э�����ͣ�http/https    AFX_INET_SERVICE_HTTP (3)    AFX_INET_SERVICE_HTTPS (4107)
	CString strServer;            // Host    ���磺www.cnblogs.com ���� 192.168.10.9
	CString strObject;            // other   ���磺/Zender/p/7596730.html
	INTERNET_PORT wPort;        // �˿ں�   http��Ĭ�϶˿ں���80��https��Ĭ�϶˿ں���443
	if (!AfxParseURL(strUrl, dwServiceType, strServer, strObject, wPort))
	{
		//����Urlʧ��
		sOutput = "PARSE URL FAIL";
		return FALSE;
	}

	//sParams.Replace("\\", "");
	int paramLen = sParams.GetLength();
	//EscapeURL(sParams, ICU_ENCODE_PERCENT);



	BYTE data[4096] = { 0 };
	memcpy(data, sParams.GetBuffer(sParams.GetLength()), paramLen);
	//memcpy(data,sParams,strlen(sParams));

	CInternetSession session; // �����Ự
	const int nTimeOut = 10 * 1000;  // ��ʱ����Ϊ 10s
	session.SetOption(INTERNET_OPTION_CONNECT_TIMEOUT, nTimeOut);
	session.SetOption(INTERNET_OPTION_CONNECT_RETRIES, 2);
	CHttpConnection* pConn = NULL;
	CHttpFile* pFile = NULL;
	if (AFX_INET_SERVICE_HTTP == dwServiceType)
	{
		pConn = session.GetHttpConnection(strServer, wPort);
		pFile = pConn->OpenRequest(CHttpConnection::HTTP_VERB_POST, strObject);
	}
	else if (AFX_INET_SERVICE_HTTPS == dwServiceType)
	{
		pConn = session.GetHttpConnection(strServer, INTERNET_FLAG_SECURE, wPort);
		pFile = pConn->OpenRequest(CHttpConnection::HTTP_VERB_POST, strObject, NULL, 1, NULL, NULL,
			INTERNET_FLAG_SECURE | INTERNET_FLAG_DONT_CACHE | INTERNET_FLAG_RELOAD |
			INTERNET_FLAG_IGNORE_CERT_CN_INVALID | INTERNET_FLAG_IGNORE_CERT_DATE_INVALID);//SECURITY_FLAG_IGNORE_UNKNOWN_CA
	}
	else
	{
		//����Э�鷵��
		sOutput = "unknown type";
		return FALSE;
	}
	try
	{
		//CString strHeaders("Content-Type: application/x-www-form-urlencoded");//����ͷ
		sContentType.Format("%s\r\n", sContentType);
		BOOL bRet = pFile->SendRequest(sContentType, (LPVOID)data, paramLen);
		if (!bRet)
		{
			goto Failure_label;
		}
		DWORD dwStatusCode;
		bRet = pFile->QueryInfoStatusCode(dwStatusCode);
		if (HTTP_STATUS_OK != dwStatusCode)//#define HTTP_STATUS_OK  200
		{
			CString strErrInfo;
			pFile->QueryInfo(HTTP_QUERY_RAW_HEADERS, strErrInfo);
			goto Failure_label;
		}
		std::string sReceive;
		char buffer[1024] = { 0 };
		for (UINT len = 0; (len = pFile->Read(buffer, sizeof(buffer))) > 0; memset(buffer, 0, sizeof(buffer)))
		{
			std::string s(buffer, len);
			sReceive += s;
		}
		sOutput = CStringA(sReceive.c_str(), sReceive.length());//ע�⣺��sReceive����\0�����ܻ�ض�
		return TRUE;
	}
	catch (CInternetException& e)
	{
		TCHAR szErr[512] = { 0 };
		e.GetErrorMessage(szErr, sizeof(szErr));
		CString strErrInfo;
		pFile->QueryInfo(HTTP_QUERY_RAW_HEADERS, strErrInfo);
		goto Failure_label;
	}

Failure_label:
	if (pConn)
	{
		pConn->Close();
		delete pConn;
		pConn = NULL;
	}
	if (pFile)
	{
		pFile->Close();
		delete pFile;
		pFile = NULL;
	}
	return FALSE;
}

void EscapeURL(CString url, CString &sOutput)
{
	sOutput = "";

	for (int i = 0; i < url.GetLength(); i++)
	{
		if (url.GetAt(i) == ' ')
			sOutput += "%20";
		else  if (url.GetAt(i) == '"')
			sOutput += "%22";
		else  if (url.GetAt(i) == '#')
			sOutput += "%23";
		else  if (url.GetAt(i) == '%')
			sOutput += "%25";
		else  if (url.GetAt(i) == '&')
			sOutput += "%26";
		else  if (url.GetAt(i) == '(')
			sOutput += "%28";
		else  if (url.GetAt(i) == ')')
			sOutput += "%29";
		else  if (url.GetAt(i) == '+')
			sOutput += "%2B";
		else  if (url.GetAt(i) == ',')
			sOutput += "%2C";
		else  if (url.GetAt(i) == '/')
			sOutput += "%2F";
		else  if (url.GetAt(i) == ':')
			sOutput += "%3A";
		else  if (url.GetAt(i) == ';')
			sOutput += "%3B";
		else  if (url.GetAt(i) == '<')
			sOutput += "%3C";
		else  if (url.GetAt(i) == '=')
			sOutput += "%3D";
		else  if (url.GetAt(i) == '>')
			sOutput += "%3E";
		else  if (url.GetAt(i) == '?')
			sOutput += "%3F";
		else  if (url.GetAt(i) == '@')
			sOutput += "%40";
		else  if (url.GetAt(i) == '|')
			sOutput += "%7C";
		else
			sOutput += url.GetAt(i);
	}
}
