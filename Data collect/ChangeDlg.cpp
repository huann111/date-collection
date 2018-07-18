// ChangeDlg.cpp : implementation file
//

#include "stdafx.h"
#include "comctrl.h"
#include "ChangeDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CChangeDlg dialog


CChangeDlg::CChangeDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CChangeDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CChangeDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CChangeDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CChangeDlg)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CChangeDlg, CDialog)
	//{{AFX_MSG_MAP(CChangeDlg)
	//}}AFX_MSG_MAP
	ON_WM_TIMER()
	ON_BN_CLICKED(IDOK, &CChangeDlg::OnBnClickedOk)
//	ON_WM_SIZING()
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CChangeDlg message handlers

void CChangeDlg::OnOK() 
{
	TCHAR exeFullPath[MAX_PATH]; // MAX_PATH
	GetModuleFileName(NULL,exeFullPath,MAX_PATH);//�õ�����ģ�����ƣ�ȫ·��
	//Ҳ���ǵ�ǰ���г����ȫ·��	
    //����·�����õ���ǰ���г�������Ŀ¼
	char drive[_MAX_DRIVE];
	char dir[_MAX_DIR];
	_splitpath(exeFullPath, drive, dir, NULL,NULL);
	CString strPath;
	strPath.Format("%s%s", drive, dir);
	strPath = strPath + "\\Admin";
	char buf[20];
    memset(buf,0,20);
	CStdioFile file;
	if (file.Open(strPath,CFile::modeRead))
	{
		file.ReadString(buf,20);
		file.Close();
	}
		CString str;
		str = buf;
	CString m_strpre;
	GetDlgItemText(IDC_EDIT1,m_strpre);
	if (str!=m_strpre)
	{
		MessageBox("ԭ�������������","��ʾ");
		return;
	}
	CString m_strpos;
	CString m_strnpos;
	GetDlgItemText(IDC_EDIT2,m_strpos);
	GetDlgItemText(IDC_EDIT3,m_strnpos);
	if (m_strnpos==""||m_strpos=="")
	{
		MessageBox("�����޸�ʧ�ܣ�","��ʾ");
		return;
	}
	if (m_strpos!=m_strnpos)
	{
		MessageBox("�����޸�ʧ�ܣ�","��ʾ");
		return;
	}
	file.Open(strPath,CFile::modeCreate|CFile::modeWrite);
	CString m_str;
	m_str.Format("%s",m_strnpos);
	int strlen=m_str.GetLength();
    file.Write(m_str,strlen);
	file.Close();
	MessageBox("�����޸ĳɹ���","��ʾ");
	return;
	CDialog::OnOK();
}


void CChangeDlg::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ

	CDialog::OnTimer(nIDEvent);
}


void CChangeDlg::OnBnClickedOk()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CDialog::OnOK();
}


BOOL CChangeDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��

	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣: OCX ����ҳӦ���� FALSE
}


//void CChangeDlg::OnSizing(UINT fwSide, LPRECT pRect)
//{
//	CDialog::OnSizing(fwSide, pRect);
//
//	// TODO: �ڴ˴������Ϣ����������
//}
