// manual.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "ComCtrl.h"
#include "manual.h"
#include "afxdialogex.h"


// manual �Ի���

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


// manual ��Ϣ�������
