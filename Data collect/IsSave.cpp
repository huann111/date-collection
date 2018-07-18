// IsSave.cpp : 实现文件
//

#include "stdafx.h"
#include "ComCtrl.h"
#include "IsSave.h"
#include "afxdialogex.h"
#include "DataSave.h"

// IsSave 对话框

IMPLEMENT_DYNAMIC(IsSave, CDialog)

IsSave::IsSave(CWnd* pParent /*=NULL*/)
	: CDialog(IsSave::IDD, pParent)
{

}

IsSave::~IsSave()
{
}

void IsSave::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(IsSave, CDialog)
	ON_BN_CLICKED(IDOK, &IsSave::OnBnClickedOk)
	ON_WM_PAINT()
END_MESSAGE_MAP()


// IsSave 消息处理程序


void IsSave::OnBnClickedOk()
{
	DataSave dlg5; 
    dlg5.DoModal();
	// TODO: 在此添加控件通知处理程序代码
	CDialog::OnOK();
}


BOOL IsSave::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  在此添加额外的初始化

	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}


void IsSave::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	CFont * cFont=new CFont;
	cFont->CreatePointFont(140,_T("华文楷体"));
	GetDlgItem(IDC_STATIC)->SetFont(cFont);
	GetDlgItem(IDOK)->SetFont(cFont);
	GetDlgItem(IDCANCEL)->SetFont(cFont);
	// TODO: 在此处添加消息处理程序代码
	// 不为绘图消息调用 CDialog::OnPaint()
}
