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
	//有文件夹就返回
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
	GetModuleFileName(NULL,exeFullPath,MAX_PATH);//得到程序模块名称，全路径
	//也就是当前运行程序的全路径	
    //解析路径，得到当前运行程序所在目录
	char drive[_MAX_DRIVE];
	char dir[_MAX_DIR];
	_splitpath(exeFullPath, drive, dir, NULL,NULL);
	CString strPath;//strPath即为得到的当前运行程序所在目录
	strPath.Format("%s%s", drive, dir);
	//strPath = strPath+"\\用户登录信息\\";
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
			CString strpath;//strPath即为得到的当前运行程序所在目录
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
						MessageBox(NULL,"您已用完5次输入机会，请认真核实用户和密码后再输入，谢谢!","提示",MB_OK);
						return 0;
					}
					CString str;
					str.Format("用户名或密码错误，您还有%d次输入机会，请重新输入!",i);
					MessageBox(NULL,str,"提示",MB_OK);
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
						MessageBox(NULL,"您已用完5次输入机会，请认真核实用户和密码后再输入，谢谢!","提示",MB_OK);
						return 0;
					}
					CString str;
					str.Format("用户名或密码错误，您还有%d次输入机会，请重新输入!",i);
					MessageBox(NULL,str,"提示",MB_OK);
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
