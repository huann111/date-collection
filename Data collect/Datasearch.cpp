// Datasearch.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "ComCtrl.h"
#include "Datasearch.h"
#include "afxdialogex.h"


// Datasearch �Ի���

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


// Datasearch ��Ϣ�������


BOOL Datasearch::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��

	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣: OCX ����ҳӦ���� FALSE
}
