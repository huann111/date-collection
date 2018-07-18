// DataSave.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "ComCtrl.h"
#include "DataSave.h"
#include "afxdialogex.h"


// DataSave �Ի���

IMPLEMENT_DYNAMIC(DataSave, CDialog)

DataSave::DataSave(CWnd* pParent /*=NULL*/)
	: CDialog(DataSave::IDD, pParent)
{

}

DataSave::~DataSave()
{
}

void DataSave::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_SAVEPATH, m_strCurPath);
}


BEGIN_MESSAGE_MAP(DataSave, CDialog)
	ON_BN_CLICKED(IDC_BUTTON1, &DataSave::OnBnClickedButton1)
END_MESSAGE_MAP()


// DataSave ��Ϣ�������


void DataSave::OnBnClickedButton1()
{
	static char displayname[MAX_PATH];
	static char path[MAX_PATH];
    LPITEMIDLIST pidlBrowse;    // PIDL selected by user 
	BROWSEINFO bi;
	bi.hwndOwner = this->m_hWnd;
	bi.pidlRoot = NULL;
	bi.pszDisplayName = displayname;
	bi.lpszTitle = "��ѡ��Ҫ����������ݵ��ļ���";
	bi.ulFlags = BIF_EDITBOX ;
	bi.lpfn = NULL;
	pidlBrowse=SHBrowseForFolder( &bi);
	if(pidlBrowse!=NULL)
	{
		SHGetPathFromIDList(pidlBrowse,path);
	}
	CString str=path;  //�õ�·��
	if(str.IsEmpty()) return;  //���û��ѡ�񣬾ͷ���
	m_strCurPath=str;	//����·���༭���Ӧ����
	UpdateData(FALSE);	
	// TODO: �ڴ���ӿؼ�֪ͨ����������
}


BOOL DataSave::OnInitDialog()
{
	CDialog::OnInitDialog();
	CTime tm = CTime::GetCurrentTime();  
	CString str2;  
    str2.Format(_T("%d/%d/%d__%d:%d:%d.txt"),tm.GetYear(),tm.GetMonth(),tm.GetDay(),tm.GetHour(),tm.GetMinute(),tm.GetSecond());  
	GetDlgItem(IDC_EDIT1)->SetWindowText(str2);

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��

	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣: OCX ����ҳӦ���� FALSE
}
