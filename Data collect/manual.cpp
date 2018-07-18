// manual.cpp : 实现文件
//

#include "stdafx.h"
#include "ComCtrl.h"
#include "manual.h"
#include "afxdialogex.h"


// manual 对话框

IMPLEMENT_DYNAMIC(manual, CDialog)

manual::manual(CWnd* pParent /*=NULL*/)
	: CDialog(manual::IDD, pParent)
{

}

manual::~manual()
{
}

void manual::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(manual, CDialog)
END_MESSAGE_MAP()


// manual 消息处理程序
