// Datasearch.cpp : 实现文件
//

#include "stdafx.h"
#include "ComCtrl.h"
#include "Datasearch.h"
#include "afxdialogex.h"


// Datasearch 对话框

IMPLEMENT_DYNAMIC(Datasearch, CDialog)

Datasearch::Datasearch(CWnd* pParent /*=NULL*/)
	: CDialog(Datasearch::IDD, pParent)
{
	m_defaultDate = CTime(2017, 9, 18, 0, 0, 0 );
}

Datasearch::~Datasearch()
{
}

void Datasearch::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_DATETIMEPICKER4, m_PosTimeCtrl);
	//DDX_Control(pDX, IDC_DATETIMEPICKER1, m_PreTimeCtrl);
	DDX_DateTimeCtrl(pDX, IDC_DATETIMEPICKER3, m_defaultDate);
}


BEGIN_MESSAGE_MAP(Datasearch, CDialog)
END_MESSAGE_MAP()


// Datasearch 消息处理程序


BOOL Datasearch::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  在此添加额外的初始化

	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}
