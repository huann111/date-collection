// IsSave.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "ComCtrl.h"
#include "IsSave.h"
#include "afxdialogex.h"
#include "DataSave.h"

// IsSave �Ի���

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


// IsSave ��Ϣ�������


void IsSave::OnBnClickedOk()
{
	DataSave dlg5; 
    dlg5.DoModal();
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CDialog::OnOK();
}


BOOL IsSave::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��

	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣: OCX ����ҳӦ���� FALSE
}


void IsSave::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	CFont * cFont=new CFont;
	cFont->CreatePointFont(140,_T("���Ŀ���"));
	GetDlgItem(IDC_STATIC)->SetFont(cFont);
	GetDlgItem(IDOK)->SetFont(cFont);
	GetDlgItem(IDCANCEL)->SetFont(cFont);
	// TODO: �ڴ˴������Ϣ����������
	// ��Ϊ��ͼ��Ϣ���� CDialog::OnPaint()
}
