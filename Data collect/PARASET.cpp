// PARASET.cpp : 实现文件
//

#include "stdafx.h"
#include "ComCtrl.h"
#include "PARASET.h"
#include "afxdialogex.h"


// PARASET 对话框

IMPLEMENT_DYNAMIC(PARASET, CDialog)

PARASET::PARASET(CWnd* pParent /*=NULL*/)
	: CDialog(PARASET::IDD, pParent)
{

}

PARASET::~PARASET()
{
}

void PARASET::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(PARASET, CDialog)
	ON_BN_CLICKED(IDC_SAVE_SET, &PARASET::OnBnClickedSaveSet)
END_MESSAGE_MAP()


// PARASET 消息处理程序


void PARASET::OnBnClickedSaveSet()
{
	EndDialog(IDOK);
	// TODO: 在此添加控件通知处理程序代码
}
