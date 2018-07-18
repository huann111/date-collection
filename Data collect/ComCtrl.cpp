// ComCtrl.cpp : Defines the class behaviors for the application.
//

#include "stdafx.h"
#include "ComCtrl.h"
#include "ComCtrlDlg.h"
#include "PassDlg.h"
//#include "SkinPPWTL.h"
#include <string>
using namespace std;
#include "atlbase.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CComCtrlApp

BEGIN_MESSAGE_MAP(CComCtrlApp, CWinApp)
	//{{AFX_MSG_MAP(CComCtrlApp)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG
	ON_COMMAND(ID_HELP, CWinApp::OnHelp)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CComCtrlApp construction

void CreateAllDirectories(TCHAR* filePath)
{
	string strPath = filePath;
	//���ļ��оͷ���
	if(GetFileAttributes(strPath.c_str())!=-1)
		return;
	LONG count = strPath.find_last_of("\\",strPath.length());
	strPath = strPath.replace(count,strPath.length(),"");
	CreateAllDirectories((TCHAR*)strPath.c_str());
	CreateDirectory(strPath.c_str(),NULL);
}

CComCtrlApp::CComCtrlApp()
{
	// TODO: add construction code here,
	// Place all significant initialization in InitInstance
}

/////////////////////////////////////////////////////////////////////////////
// The one and only CComCtrlApp object

CComCtrlApp theApp;

/////////////////////////////////////////////////////////////////////////////
// CComCtrlApp initialization

BOOL CComCtrlApp::InitInstance()
{
	TCHAR exeFullPath[MAX_PATH]; // MAX_PATH
	GetModuleFileName(NULL,exeFullPath,MAX_PATH);//�õ�����ģ�����ƣ�ȫ·��
	//Ҳ���ǵ�ǰ���г����ȫ·��	
    //����·�����õ���ǰ���г�������Ŀ¼
	char drive[_MAX_DRIVE];
	char dir[_MAX_DIR];
	_splitpath(exeFullPath, drive, dir, NULL,NULL);
	CString strPath;//strPath��Ϊ�õ��ĵ�ǰ���г�������Ŀ¼
	strPath.Format("%s%s", drive, dir);
	//strPath = strPath+"\\�û���¼��Ϣ\\";
	strPath = strPath + "\\Admin";

	AfxEnableControlContainer();
	//skinppLoadSkin(_T("bOzen.ssk"));
	fQuit=0;
	int num=0;
	int i = 5;
	while(num<5)
	{
		if(passdlg.DoModal()==IDOK)
		{
			CString strpath;//strPath��Ϊ�õ��ĵ�ǰ���г�������Ŀ¼
			strpath.Format("%s%s", drive, dir);
			strpath = strpath + "\\Admin";
			CStdioFile file;
			if (file.Open(strpath,CFile::modeRead))
			{
				char buf[20];
				memset(buf,0,20);
				file.ReadString(buf,20);
				file.Close();
				CString str;
				str = buf;
				if (passdlg.m_Pass!=str)
				{
					i--;
					if (i==0)
					{
						MessageBox(NULL,"��������5��������ᣬ�������ʵ�û�������������룬лл!","��ʾ",MB_OK);
						return 0;
					}
					CString str;
					str.Format("�û������������������%d��������ᣬ����������!",i);
					MessageBox(NULL,str,"��ʾ",MB_OK);
						num++;
				}
				else
					break;
			}
			
			else
			{
				if(passdlg.m_Pass!="123")
				{
					i--;
					if (i==0)
					{
						MessageBox(NULL,"��������5��������ᣬ�������ʵ�û�������������룬лл!","��ʾ",MB_OK);
						return 0;
					}
					CString str;
					str.Format("�û������������������%d��������ᣬ����������!",i);
					MessageBox(NULL,str,"��ʾ",MB_OK);
					num++;
				}
				else break;
			}
			
		}  
		else 
		{
			fQuit=1;
			break;
		}
	   }
	   if(fQuit)
		   return false;
	   UINT nLength;
	   CString str;
	   str.Format("%s",passdlg.m_Pass);
	   CFile  cfFile(strPath,CFile::modeCreate|CFile::modeWrite);
	   nLength=str.GetLength();
	   cfFile.Write(str,nLength);
	   cfFile.Close();

#ifdef _AFXDLL
	Enable3dControls();			// Call this when using MFC in a shared DLL
#else
	Enable3dControlsStatic();	// Call this when linking to MFC statically
#endif

	CComCtrlDlg dlg;
	m_pMainWnd = &dlg;
	int nResponse = dlg.DoModal();
	if (nResponse == IDOK)
	{
		// TODO: Place code here to handle when the dialog is
		//  dismissed with OK
	}
	else if (nResponse == IDCANCEL)
	{
		// TODO: Place code here to handle when the dialog is
		//  dismissed with Cancel
	}

	return FALSE;
}
