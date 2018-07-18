// DataSave.cpp : 实现文件
//

#include "stdafx.h"
#include "ComCtrl.h"
#include "DataSave.h"
#include "afxdialogex.h"


// DataSave 对话框

IMPLEMENT_DYNAMIC(DataSave, CDialog)

DataSave::DataSave(CWnd* pParent /*=NULL*/)
	: CDialog(DataSave::IDD, pParent)
{

}

DataSave::~DataSave()
{
}

void DataSave::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_SAVEPATH, m_strCurPath);
}


BEGIN_MESSAGE_MAP(DataSave, CDialog)
	ON_BN_CLICKED(IDC_BUTTON1, &DataSave::OnBnClickedButton1)
END_MESSAGE_MAP()


// DataSave 消息处理程序


void DataSave::OnBnClickedButton1()
{
	static char displayname[MAX_PATH];
	static char path[MAX_PATH];
    LPITEMIDLIST pidlBrowse;    // PIDL selected by user 
	BROWSEINFO bi;
	bi.hwndOwner = this->m_hWnd;
	bi.pidlRoot = NULL;
	bi.pszDisplayName = displayname;
	bi.lpszTitle = "请选择要保存接收数据的文件夹";
	bi.ulFlags = BIF_EDITBOX ;
	bi.lpfn = NULL;
	pidlBrowse=SHBrowseForFolder( &bi);
	if(pidlBrowse!=NULL)
	{
		SHGetPathFromIDList(pidlBrowse,path);
	}
	CString str=path;  //得到路径
	if(str.IsEmpty()) return;  //如果没有选择，就返回
	m_strCurPath=str;	//接收路径编辑框对应变量
	UpdateData(FALSE);	
	// TODO: 在此添加控件通知处理程序代码
}


BOOL DataSave::OnInitDialog()
{
	CDialog::OnInitDialog();
	CTime tm = CTime::GetCurrentTime();  
	CString str2;  
    str2.Format(_T("%d/%d/%d__%d:%d:%d.txt"),tm.GetYear(),tm.GetMonth(),tm.GetDay(),tm.GetHour(),tm.GetMinute(),tm.GetSecond());  
	GetDlgItem(IDC_EDIT1)->SetWindowText(str2);

	// TODO:  在此添加额外的初始化

	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}
