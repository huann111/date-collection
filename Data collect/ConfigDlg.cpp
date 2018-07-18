// ConfigDlg.cpp : implementation file
//

#include "stdafx.h"
#include "ComCtrl.h"
#include "ConfigDlg.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif



/////////////////////////////////////////////////////////////////////////////
// CConfigDlg dialog


CConfigDlg::CConfigDlg(CWnd* pParent /*=NULL*/)
: CDialog(CConfigDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CConfigDlg)
	m_strcomm1 = _T("");
	m_strcomm2 = _T("");
	m_nCT1 = 1;
	m_nCT2 = 1;
	m_strAdd1 = _T("");
	m_strAdd2 = _T("");
	m_nCP1 = 0;
	m_nCP2 = 0;
	m_nTime = 10.0f;
	//}}AFX_DATA_INIT
}


void CConfigDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CConfigDlg)
	DDX_CBString(pDX, IDC_COMBO_COM1, m_strcomm1);
	DDX_CBString(pDX, IDC_COMBO_COM2, m_strcomm2);
	DDX_Text(pDX, IDC_EDIT_CT1, m_nCT1);
	DDX_Text(pDX, IDC_EDIT_CT2, m_nCT2);
	DDX_Text(pDX, IDC_EDIT_ADD1, m_strAdd1);
	DDX_Text(pDX, IDC_EDIT_ADD2, m_strAdd2);
	DDX_Text(pDX, IDC_EDIT_CP1, m_nCP1);
	DDX_Text(pDX, IDC_EDIT_CP2, m_nCP2);
	DDX_Text(pDX, IDC_EDIT_TIME, m_nTime);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CConfigDlg, CDialog)
//{{AFX_MSG_MAP(CConfigDlg)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CConfigDlg message handlers

BOOL CConfigDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	//串口初始化
	CComboBox* pcComboComm1 = (CComboBox*)GetDlgItem(IDC_COMBO_COM1);
	pcComboComm1->ResetContent();
	CComboBox* pcComboComm2 = (CComboBox*)GetDlgItem(IDC_COMBO_COM2);
	pcComboComm2->ResetContent();
	HKEY hKey;
	if (::RegOpenKeyEx(HKEY_LOCAL_MACHINE,_T("Hardware\\DeviceMap\\SerialComm"),NULL,KEY_READ,&hKey)== ERROR_SUCCESS)
	{
		int i=0;
		char portName[50], commName[50];
		DWORD dwLong, dwSize;
		
		while (true)
		{
			dwLong = dwSize = sizeof(portName);
			if (::RegEnumValueA(hKey, i, portName, &dwLong,NULL,NULL,(PUCHAR)commName,&dwSize) ==ERROR_NO_MORE_ITEMS)
			{
				break;
			}
			pcComboComm1->AddString(CString(commName));
			pcComboComm2->AddString(CString(commName));
			i++;
		}
		RegCloseKey(hKey);
		
		if (pcComboComm1->GetCount() > 0)
		{
			pcComboComm1->SetCurSel(0);
		}
		if (pcComboComm2->GetCount() > 0)
		{
			pcComboComm2->SetCurSel(0);
		}
	}
    
	
	GetConfig();
	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}


void CConfigDlg::GetConfig()
{
	TCHAR exeFullPath[MAX_PATH]; // MAX_PATH
	GetModuleFileName(NULL,exeFullPath,MAX_PATH);//得到程序模块名称，全路径
	//也就是当前运行程序的全路径	
    //解析路径，得到当前运行程序所在目录
	char drive[_MAX_DRIVE];
	char dir[_MAX_DIR];
	_splitpath(exeFullPath, drive, dir, NULL,NULL);
	CString strPath;
	strPath.Format("%s%s", drive, dir);
	strPath = strPath + "\\SaveConfig";
	CStdioFile file;
 	if (!file.Open(strPath,CFile::modeReadWrite | CFile::typeText))
 	{
		MessageBox("暂无已配置文件信息","提示");
		return;
 	}
 	char Buf[100];
	memset(Buf,0,100);
 	file.ReadString(Buf,99);
    int len=sizeof(Buf);
 	int i,j;
 	for(i=0;i<len;i++) 	
	{
 		if(Buf[i]==',')
 			break;
 	}
 
	Buf[i]='\0';
 	CString stradd1 = Buf;
 	j=i;
 	for(i=j;i<len;i++)
 	{
 		if(Buf[i]==',')
 			break;
 	}
 	Buf[i]='\0';
     CString strcom1 = Buf+j+1;
 	j=i;
 	for(i=j;i<len;i++)
 	{
 		if(Buf[i]==',')
 			break;
 	}
 	Buf[i]='\0';
     CString strct1 = Buf+j+1;
 	j=i;
 	for(i=j;i<len;i++)
 	{
 		if(Buf[i]==',')
 			break;
 	}
 	Buf[i]='\0';
 	CString strcp1 = Buf+j+1;
 	j=i;
 	for(i=j;i<len;i++)
 	{
 		if(Buf[i]==',')
 			break;
 	}
 
 	Buf[i]='\0';
 	CString stradd2 = Buf+j+1;
 	j=i;
 	for(i=j;i<len;i++)
 	{
 		if(Buf[i]==',')
 			break;
 	}
 	Buf[i]='\0';
    CString strcom2 = Buf+j+1;
 	j=i;
	for(i=j;i<len;i++)
 	{
 		if(Buf[i]==',')
 			break;
 	}
 	Buf[i]='\0';
    CString strct2 = Buf+j+1;
	j=i;
 	for(i=j;i<len;i++)
 	{
 		if(Buf[i]==',')
 			break;
 	}
 	Buf[i]='\0';
 	CString strcp2 = Buf+j+1;
 	j=i;
	for(i=j;i<len;i++)
	{
		if(Buf[i]==',')
			break;
	}
	Buf[i]='\0';
	CString strtime = Buf+j+1;
    GetDlgItem(IDC_EDIT_ADD1)->SetWindowText(stradd1);
	GetDlgItem(IDC_EDIT_ADD2)->SetWindowText(stradd2);
	GetDlgItem(IDC_EDIT_CT1)->SetWindowText(strct1);
	GetDlgItem(IDC_EDIT_CT2)->SetWindowText(strct2);
	GetDlgItem(IDC_EDIT_CP1)->SetWindowText(strcp1);
	GetDlgItem(IDC_EDIT_CP2)->SetWindowText(strcp2);
	GetDlgItem(IDC_EDIT_TIME)->SetWindowText(strtime);

	CComboBox* pcComboComm1 = (CComboBox*)GetDlgItem(IDC_COMBO_COM1);
	CComboBox* pcComboComm2 = (CComboBox*)GetDlgItem(IDC_COMBO_COM2);
	int nPos = 0;
	CString strTemp;
	for ( i = 0; i< pcComboComm1->GetCount(); i++)
	{
		pcComboComm1->GetLBText(i, strTemp);
		if(strcom1 == strTemp)
		{
			pcComboComm1->SetCurSel(i);
			break;
		}
	}

	for ( i = 0; i< pcComboComm2->GetCount(); i++)
	{
		pcComboComm2->GetLBText(i, strTemp);
		if(strcom2 == strTemp)
		{
			pcComboComm2->SetCurSel(i);
			break;
		}
	}
}

void CConfigDlg::OnOK() 
{
	TCHAR exeFullPath[MAX_PATH]; // MAX_PATH
	GetModuleFileName(NULL,exeFullPath,MAX_PATH);//得到程序模块名称，全路径
	//也就是当前运行程序的全路径	
    //解析路径，得到当前运行程序所在目录
	char drive[_MAX_DRIVE];
	char dir[_MAX_DIR];
	_splitpath(exeFullPath, drive, dir, NULL,NULL);
	CString strpath;
	strpath.Format("%s%s", drive, dir);
	CString strAdd1;
	GetDlgItemText(IDC_EDIT_ADD1,strAdd1);
	CString strAdd2;
	GetDlgItemText(IDC_EDIT_ADD2,strAdd2);
	
	if(strAdd1.IsEmpty() || strAdd2.IsEmpty())
	{
		MessageBox("地点不能为空！请输入地点名。","提示");
		return;
	}
	strpath = strpath + "\\SaveConfig";
	CFile  cfFile( strpath,CFile::modeCreate | CFile::modeWrite);
	CString strCom1;
	GetDlgItemText(IDC_COMBO_COM1,strCom1);
	CString strCT1;
	GetDlgItemText(IDC_EDIT_CT1,strCT1);
	CString strCP1;
	GetDlgItemText(IDC_EDIT_CP1,strCP1);
	CString strCom2;
	GetDlgItemText(IDC_COMBO_COM2,strCom2);
	CString strCT2;
	GetDlgItemText(IDC_EDIT_CT2,strCT2);
	CString strCP2;
	GetDlgItemText(IDC_EDIT_CP2,strCP2);
	CString strTime;
	GetDlgItemText(IDC_EDIT_TIME,strTime);
	if (strCom1==strCom2)
	{
		MessageBox("两个串口号不能相同，请重新配置","提示");
		return;
	}
	CString str;
	str.Format("%s,%s,%s,%s,%s,%s,%s,%s,%s",strAdd1,strCom1,strCT1,strCP1,
		strAdd2,strCom2,strCT2,strCP2,strTime);
	int strlen=str.GetLength();
    cfFile.Write(str,strlen);
	cfFile.Close();
	MessageBox("保存成功","提示");
	CDialog::OnOK();
}
