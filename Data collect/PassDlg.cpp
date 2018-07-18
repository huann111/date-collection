// PassDlg.cpp : implementation file
//

#include "stdafx.h"
#include "comctrl.h"
#include "PassDlg.h"
#include "ChangeDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// PassDlg dialog


PassDlg::PassDlg(CWnd* pParent /*=NULL*/)
	: CDialog(PassDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(PassDlg)
	m_Pass = _T("");
	m_Name = _T("Admin");

	//}}AFX_DATA_INIT
}


void PassDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(PassDlg)
	DDX_Text(pDX, IDC_PASSWORD, m_Pass);
	DDX_Text(pDX, IDC_NAME, m_Name);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(PassDlg, CDialog)
	//{{AFX_MSG_MAP(PassDlg)
	ON_BN_CLICKED(IDC_BTN_CHANGE, OnBtnChange)
	//}}AFX_MSG_MAP
	//ON_BN_CLICKED(IDOK, &PassDlg::OnBnClickedOk)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// PassDlg message handlers

BOOL PassDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	TCHAR exeFullPath[MAX_PATH]; // MAX_PATH
	GetModuleFileName(NULL,exeFullPath,MAX_PATH);//得到程序模块名称，全路径
	//也就是当前运行程序的全路径	
    //解析路径，得到当前运行程序所在目录
	char drive[_MAX_DRIVE];
	char dir[_MAX_DIR];
	_splitpath(exeFullPath, drive, dir, NULL,NULL);
	CString strPath;
	strPath.Format("%s%s", drive, dir);
	strPath = strPath + "\\Save";
	//判断“记住密码”是否选中
	CStdioFile file;
	if (file.Open(strPath,CFile::modeNoTruncate|CFile::modeRead))
	{
		char Buf[20];
		memset(Buf,0,20);
		file.ReadString(Buf,19);
		int len=sizeof(Buf);
		int i,j;
		for(i=0;i<len;i++) 	
		{
			if(Buf[i]==',')
				break;
		}
		Buf[i] = '\0';
		CString m_str1 = Buf;
		j = i;
		CString m_str2 = Buf + j +1;
		if (m_str1=='1')
		{
			((CButton*)GetDlgItem(IDC_CHECK1))->SetCheck(TRUE);
			SetDlgItemText(IDC_PASSWORD,m_str2);
		}
		else
			((CButton*)GetDlgItem(IDC_CHECK1))->SetCheck(FALSE);
	}

	PassDlg *pdlg = (PassDlg*)GetDlgItem(IDC_PASSWORD);
	return TRUE;  // return TRUE unless you set the focus to a control
	              
}



BOOL PassDlg::PreTranslateMessage(MSG* pMsg) 
{
	if (pMsg->message==WM_KEYDOWN) 
	   { 
		int nVirtKey = (int)pMsg->wParam;         
		if   (nVirtKey==VK_ESCAPE) 
		{
			return   TRUE; 
		} 
	   }
	
	return CDialog::PreTranslateMessage(pMsg);
}

void PassDlg::OnBtnChange() 
{
	CChangeDlg dlg;
	dlg.DoModal();
}

void PassDlg::OnOK() 
{   //保存是否要“记住密码”的密码
	TCHAR exeFullPath[MAX_PATH]; // MAX_PATH
	GetModuleFileName(NULL,exeFullPath,MAX_PATH);//得到程序模块名称，全路径
	//也就是当前运行程序的全路径	
    //解析路径，得到当前运行程序所在目录
	char drive[_MAX_DRIVE];
	char dir[_MAX_DIR];
	_splitpath(exeFullPath, drive, dir, NULL,NULL);
	CString strPath;
	strPath.Format("%s%s", drive, dir);
	strPath = strPath + "\\Save";
	CFile file( strPath,CFile::modeCreate|CFile::modeWrite);
	CString m_strmima;
	GetDlgItemText(IDC_PASSWORD,m_strmima);
	CString m_str;
	if(BST_CHECKED==((CButton*)GetDlgItem(IDC_CHECK1))->GetCheck()) 
	{
		m_str.Format("1,%s",m_strmima);
		
	}
	if (BST_UNCHECKED==((CButton*)GetDlgItem(IDC_CHECK1))->GetCheck())
	{
		m_str.Format("0,%s",m_strmima);
	}
	int strlen=m_str.GetLength();
	file.Write(m_str,strlen);
	file.Close();
	CDialog::OnOK();
}



