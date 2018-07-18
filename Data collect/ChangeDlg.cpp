// ChangeDlg.cpp : implementation file
//

#include "stdafx.h"
#include "comctrl.h"
#include "ChangeDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CChangeDlg dialog


CChangeDlg::CChangeDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CChangeDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CChangeDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CChangeDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CChangeDlg)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CChangeDlg, CDialog)
	//{{AFX_MSG_MAP(CChangeDlg)
	//}}AFX_MSG_MAP
	ON_WM_TIMER()
	ON_BN_CLICKED(IDOK, &CChangeDlg::OnBnClickedOk)
//	ON_WM_SIZING()
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CChangeDlg message handlers

void CChangeDlg::OnOK() 
{
	TCHAR exeFullPath[MAX_PATH]; // MAX_PATH
	GetModuleFileName(NULL,exeFullPath,MAX_PATH);//得到程序模块名称，全路径
	//也就是当前运行程序的全路径	
    //解析路径，得到当前运行程序所在目录
	char drive[_MAX_DRIVE];
	char dir[_MAX_DIR];
	_splitpath(exeFullPath, drive, dir, NULL,NULL);
	CString strPath;
	strPath.Format("%s%s", drive, dir);
	strPath = strPath + "\\Admin";
	char buf[20];
    memset(buf,0,20);
	CStdioFile file;
	if (file.Open(strPath,CFile::modeRead))
	{
		file.ReadString(buf,20);
		file.Close();
	}
		CString str;
		str = buf;
	CString m_strpre;
	GetDlgItemText(IDC_EDIT1,m_strpre);
	if (str!=m_strpre)
	{
		MessageBox("原有密码输入错误！","提示");
		return;
	}
	CString m_strpos;
	CString m_strnpos;
	GetDlgItemText(IDC_EDIT2,m_strpos);
	GetDlgItemText(IDC_EDIT3,m_strnpos);
	if (m_strnpos==""||m_strpos=="")
	{
		MessageBox("密码修改失败！","提示");
		return;
	}
	if (m_strpos!=m_strnpos)
	{
		MessageBox("密码修改失败！","提示");
		return;
	}
	file.Open(strPath,CFile::modeCreate|CFile::modeWrite);
	CString m_str;
	m_str.Format("%s",m_strnpos);
	int strlen=m_str.GetLength();
    file.Write(m_str,strlen);
	file.Close();
	MessageBox("密码修改成功！","提示");
	return;
	CDialog::OnOK();
}


void CChangeDlg::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值

	CDialog::OnTimer(nIDEvent);
}


void CChangeDlg::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码
	CDialog::OnOK();
}


BOOL CChangeDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  在此添加额外的初始化

	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}


//void CChangeDlg::OnSizing(UINT fwSide, LPRECT pRect)
//{
//	CDialog::OnSizing(fwSide, pRect);
//
//	// TODO: 在此处添加消息处理程序代码
//}
