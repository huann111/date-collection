// TEST.cpp : 实现文件
//

#include "stdafx.h"
#include "ComCtrl.h"
#include "TEST.h"
#include "afxdialogex.h"


// TEST 对话框

IMPLEMENT_DYNAMIC(TEST, CDialog)

TEST::TEST(CWnd* pParent /*=NULL*/)
	: CDialog(TEST::IDD, pParent)
{

}

TEST::~TEST()
{
}

void TEST::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(TEST, CDialog)
END_MESSAGE_MAP()


// TEST 消息处理程序
