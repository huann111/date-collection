// PARASET.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "ComCtrl.h"
#include "PARASET.h"
#include "afxdialogex.h"


// PARASET �Ի���

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


// PARASET ��Ϣ�������


void PARASET::OnBnClickedSaveSet()
{
	EndDialog(IDOK);
	// TODO: �ڴ���ӿؼ�֪ͨ����������
}
