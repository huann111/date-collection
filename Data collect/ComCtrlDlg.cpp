// ComCtrlDlg.cpp : implementation file
//

#include "stdafx.h"
#include "ComCtrl.h"
#include "ComCtrlDlg.h"
#include "Com.h"
#include "ConfigDlg.h"
#include <ctime>
#include "comdef.h"     
#include <string>
using namespace std;
#include "atlbase.h"
#include "PassDlg.h"
//#include "ChangeDlg.h"
#include "Datasearch.h"
#include "manual.h"
#include "PARASET.h"
#include "TEST.h"
#include "DataSave.h"
#include "IsSave.h"

#include "ChartCtrl_source/ChartLineSerie.h"
#include "ChartCtrl_source/ChartAxisLabel.h"
#include "ChartCtrl_source/ChartCtrl.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#define RECVBUFFERLEN 500

char recvbuffer[RECVBUFFERLEN];
#define  SHOWRECVMESSAGE WM_USER + 111     //定义自定义消息，用于显示串口收到数据
#define  SHOWSEARCHRESULT WM_USER+ 112     //自定义消息，用于显示查找结果
#define  SHOWMESSAGE      WM_USER + 113    //自定义消息，多线程中的消息
#define  ShOWMESSAGEA     WM_USER + 114    //自定义消息，多线程中的异常查询消息
#define  SHOWXY           WM_USER+115
#define  SHOWDIS          WM_USER+116
#define  SHOWXY1          WM_USER+117
volatile float g_nWaitTime = 0;
CString strAdd1;
CString strAdd2;
CCom g_cComm1;
CCom g_cComm2;
int nYear,nMonth, nDate,nHour,nMin,nSec;
int nYear2,nMonth2, nDate2,nHour2,nMin2,nSec2;
CTime tm1;
CTime TM;
CString strtm;
CString strTM;
CRect m_rect;
void Recv(HWND hWnd, int nPos)
{
	int  nlen = 0;
	while(TRUE)
	{
		if (nPos==0)
		{
			nlen = g_cComm1.ReadComm(recvbuffer,RECVBUFFERLEN);
		}
		if (nPos==1)
		{
			nlen = g_cComm2.ReadComm(recvbuffer,RECVBUFFERLEN);
		}
		if(nlen > 0)
			PostMessage(hWnd, SHOWRECVMESSAGE, nPos + 1, nlen);    
		Sleep(3000);
	}
}

//专门处理第一个串口接收
DWORD WINAPI RecvThread1(LPVOID lpParameter )
{
	HWND hwnd = *(HWND*)(lpParameter);
    Recv(hwnd, 0);
	return 0;
}

//专门处理第二个串口接收
DWORD WINAPI RecvThread2(LPVOID lpParameter )
{
	HWND hwnd = *(HWND*)(lpParameter);
    Recv(hwnd, 1);
	return 0;
}

//专门用于定时向串口发送查询指令
void send(int ncom)
{
	char sendbuffer[5] ={0};
	sendbuffer[0]=0xB7;
	sendbuffer[1]=0xA2;
	sendbuffer[2]=0xCB;
	sendbuffer[3]=0xCD;
	TCHAR exeFullPath[MAX_PATH]; // MAX_PATH
	GetModuleFileName(NULL,exeFullPath,MAX_PATH);//得到程序模块名称，全路径
	//也就是当前运行程序的全路径	
    //解析路径，得到当前运行程序所在目录
	char drive[_MAX_DRIVE];
	char dir[_MAX_DIR];
	_splitpath(exeFullPath, drive, dir, NULL,NULL);
	CString strPath;//strPath即为得到的当前运行程序所在目录
	strPath.Format("%s%s", drive, dir);

	CTime time = CTime::GetCurrentTime();
	CString m_strtime = time.Format("%Y-%m-%d");
	
	while(TRUE)
	{
		if (ncom==0)
		{
			g_cComm1.WriteComm(sendbuffer,4);
		}
		if (ncom==1)
		{
			g_cComm2.WriteComm(sendbuffer,4);
		}
		HANDLE   hFile;   
		WIN32_FIND_DATA   wfd;   
		SYSTEMTIME   systime;   
		FILETIME   localtime;   
		memset(&wfd,0,sizeof(wfd));   
		CString str;
		if (ncom==0)
		{
			str=strAdd1;
		}
		if (ncom==1)
		{
			str = strAdd2;
		}
		
		str = strPath + "\\接收数据\\"+ str + "\\";
        str = str + m_strtime + ".txt";
		if((hFile=FindFirstFile(str,&wfd))==INVALID_HANDLE_VALUE)   
		{   
			continue;
		}   
		//ok,转换时间   
		FileTimeToLocalFileTime(&wfd.ftLastWriteTime,&localtime);   
		FileTimeToSystemTime(&localtime,&systime);   
		CTime ct(systime);
		
		CTime t =CTime::GetCurrentTime();
		CTimeSpan ts = t-ct;
		LONG a = ts.GetTotalMinutes();
	
		if (a>g_nWaitTime)
		{
			Sleep(1000);
		}
		else
		    Sleep(g_nWaitTime*60*1000);
	}
		
}

DWORD WINAPI SendCmdThread1(LPVOID lpParameter )
{
	send(0);
	return 0;
}

DWORD WINAPI SendCmdThread2(LPVOID lpParameter )
{
	send(1);
	return 0;
}

BEGIN_MESSAGE_MAP(CComCtrlDlg, CDialog)
//{{AFX_MSG_MAP(CComCtrlDlg)
ON_WM_SYSCOMMAND()
ON_WM_PAINT()
ON_WM_QUERYDRAGICON()
ON_BN_CLICKED(IDC_BTN_OPEN, OnBtnOpen)
ON_BN_CLICKED(IDC_BTN_MANUALSEND, OnBtnManualsend)
ON_BN_CLICKED(IDC_BTN_CLEAR, OnBtnClear)
ON_BN_CLICKED(IDC_BTN_CHECK, OnBtnCheck)
ON_BN_CLICKED(IDC_BTN_SEND, OnBtnSend)
ON_BN_CLICKED(IDC_BTN_ZT, OnBtnZt)
ON_BN_CLICKED(IDC_BTN_PC, OnBtnPc)
ON_BN_CLICKED(IDC_BTN_CONFIGDATA, OnBtnConfigdata)
ON_MESSAGE(SHOWRECVMESSAGE, OnShowRecv)            //处理界面显示消息
ON_MESSAGE(SHOWSEARCHRESULT, OnShowResearch)       //处理查询数据显示
ON_MESSAGE(SHOWMESSAGE,OnShowMessage)              //处理线程中的消息
ON_MESSAGE(ShOWMESSAGEA,OnShowMessageA)
ON_MESSAGE(SHOWXY,OnShowXY)
ON_MESSAGE(SHOWDIS,OnShowXYDIS)
ON_MESSAGE(SHOWXY1,OnShowXY1)

	ON_BN_CLICKED(IDC_BTNPL, OnBtnpl)
	ON_BN_CLICKED(IDC_BTNPF, OnBtnpf)
	ON_BN_CLICKED(IDC_BTNV, OnBtnv)
	ON_BN_CLICKED(IDC_BTNI, OnBtni)
	ON_BN_CLICKED(IDC_BTNT, OnBtnt)
	//}}AFX_MSG_MAP
	ON_STN_CLICKED(IDC_STATIC1, &CComCtrlDlg::OnStnClickedStatic1)
	ON_WM_TIMER()
	ON_WM_CTLCOLOR()
	ON_BN_CLICKED(IDC_BUTTON6, &CComCtrlDlg::OnBnClickedButton6)
	ON_BN_CLICKED(IDC_BUTTON8, &CComCtrlDlg::OnBnClickedButton8)
	ON_BN_CLICKED(IDC_BUTTON7, &CComCtrlDlg::OnBnClickedButton7)
	ON_BN_CLICKED(IDC_BUTTON1, &CComCtrlDlg::OnBnClickedButton1)
	ON_WM_SIZE()
	ON_WM_SIZING()
	ON_BN_CLICKED(IDC_BUTTON4, &CComCtrlDlg::OnBnClickedButton4)
	ON_BN_CLICKED(IDC_BUTTON9, &CComCtrlDlg::OnBnClickedButton9)
	ON_BN_CLICKED(IDC_BUTTON5, &CComCtrlDlg::OnBnClickedButton5)
	ON_BN_CLICKED(IDC_BUTTON15, &CComCtrlDlg::OnBnClickedButton15)
	//ON_BN_CLICKED(IDC_BUTTON10, &CComCtrlDlg::OnBnClickedButton10)
	ON_BN_CLICKED(IDC_BUTTON13, &CComCtrlDlg::OnBnClickedButton13)
	ON_BN_CLICKED(IDC_CHECK2, &CComCtrlDlg::OnBnClickedCheck2)
	ON_BN_CLICKED(IDC_CHECK3, &CComCtrlDlg::OnBnClickedCheck3)
//	ON_BN_CLICKED(IDC_BUTTON16, &CComCtrlDlg::OnBnClickedButton16)
ON_BN_CLICKED(IDC_BUTTON17, &CComCtrlDlg::OnBnClickedButton17)
ON_BN_CLICKED(IDC_CHECK1, &CComCtrlDlg::OnBnClickedCheck1)
ON_BN_CLICKED(IDC_CHECK4, &CComCtrlDlg::OnBnClickedCheck4)
ON_BN_CLICKED(IDC_SAVE, &CComCtrlDlg::OnBnClickedSave)
END_MESSAGE_MAP()

CComCtrlDlg::CComCtrlDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CComCtrlDlg::IDD, pParent)
{
	m_defaultDate = CTime(2017, 9, 18, 0, 0, 0 );
	m_CheckType = 0;
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}


CComCtrlDlg::~CComCtrlDlg()
{

}

void CComCtrlDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CComCtrlDlg)
	//DDX_Control(pDX, IDC_LIST3, m_List2);
	//DDX_Control(pDX, IDC_LIST1, m_List1);
	DDX_Control(pDX, IDC_DATETIMEPICKER2, m_PosTimeCtrl);
	//DDX_Control(pDX, IDC_DATETIMEPICKER1, m_PreTimeCtrl);
	DDX_DateTimeCtrl(pDX, IDC_DATETIMEPICKER1, m_defaultDate);
	//DDX_Control(pDX, IDC_DATETIMEPICKER1, m_PreTimeCtrl);
	DDX_Control(pDX, IDC_LIST2, m_ListCtrl);
	DDX_Control(pDX, IDC_COMBO_CHOICE, m_choice);
	DDX_Control(pDX, IDC_CUSTOM_CHART, m_ChartCtrl);
	DDX_Radio(pDX, IDC_RADIO1, m_CheckType);
	//}}AFX_DATA_MAP
}

void CComCtrlDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		//MessageBox("copyright@2011","提示");
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}


CBrush   m_bkBrush;
CChartLineSerie*pLineSeries1;
CChartLineSerie*pLineSeries2;
CChartLineSerie*pLineSeries3;



class CCustomLabelProvider : public CChartLabelProvider<SChartXYPoint>
{
public:
  TChartString GetText(CChartSerieBase<SChartXYPoint>* pSeries, unsigned uPtIndex)
  {
    TChartStringStream ssText;
    SChartXYPoint Point = pSeries->GetPoint(uPtIndex);
    ssText << _T("X=") << Point.X << _T(" Y=") << Point.Y;
    return ssText.str();
  }
};
double temp1,temp2;
int flag=0;




class CCustomMouseListener : public CChartSeriesMouseListener<SChartXYPoint>,public CChartMouseListener
//class CCustomMouseListener : public CChartMouseListener
{

#if 1
	public:
		void GetHwnd(HWND hwnd)  
    {  
        m_hwnd = hwnd;  
    }  
    HWND m_hwnd; 
	void OnCursorMoved(CChartCursor *pCursor, double xValue, double yValue)  
    {  
//      TChartStringStream ssText;  
//      ssText << _T("Cursor moved: xPos=") << xValue << _T(", yPos=") << yValue;  
//      TChartString strText = ssText.str();  
    //  MessageBox(NULL,strText.c_str(), _T("Info"), MB_OK);    
   //  MessageBox(NULL,_T("Axis clicked"), _T("Info"), MB_OK);
        // Do something with the string...  
    }  
  
  void OnMouseEventAxis(CChartMouseListener::MouseEvent mouseEvent, CPoint point,CChartAxis* pAxisClicked          )
  {
	  if (mouseEvent == CChartMouseListener::LButtonDoubleClick)
    {
		//PostMessage(m_hwnd,SHOWXY1,NULL,NULL);
      //MessageBox(NULL,_T("Axis clicked"), _T("Info"), MB_OK);
    }
	/*else{
		MessageBox(NULL,_T("Axis clicked11"), _T("Info"), MB_OK);
	}*/
  }
#endif

  void OnMouseEventPlotArea(MouseEvent mouseEvent, CPoint point) { 
	  if (mouseEvent == CChartMouseListener::MouseMove)
    {
		//PostMessage(m_hwnd,SHOWXY1,NULL,NULL);
     // MessageBox(NULL,_T("Axis clicked2"), _T("Info"), MB_OK);
	    PostMessage(m_hwnd,SHOWXY1,NULL,NULL);
    }
  }





#if 1
public:
	/*void GetHwnd(HWND hwnd)  
    {  
        m_hwnd = hwnd;  
    }  
    HWND m_hwnd; */
  void OnMouseEventSeries(CChartMouseListener::MouseEvent mouseEvent, CPoint point,
          CChartSerieBase<SChartXYPoint>* pSerie, unsigned uPointIndex)
  {
	 // HWND hwnd = *(HWND*)(lpParam);
	  if (mouseEvent == CChartMouseListener::MouseMove
        && uPointIndex != INVALID_POINT)
    {
		// PostMessage(m_hwnd,SHOWDIS,NULL,NULL);
		//Edit_HideBalloonTip(true);
     TChartStringStream ssText,ssText1;
	 
      SChartXYPoint Point = pSerie->GetPoint(uPointIndex);
	  TChartString name;
	 name=pSerie->GetName();
	 
	 // ssText << _T("Y value=")  << Point.Y;
	 ssText << _T("") << Point.X << _T(",") << Point.Y;
      TChartString strText = ssText.str();
	  flag=1;
	  temp1 =  Point.X;  
        temp2 =Point.Y;
	 PostMessage(m_hwnd,SHOWXY,NULL,NULL);
	 //pSerie->CreateBalloonLabel(Point.X,Point.Y);
     //MessageBox(NULL,name.c_str(), _T("Info"), MB_OK);
	// GetDlgItem(IDC_EDIT6)->SetWindowText(strText);
	 // pSerie->CreateBalloonLabel(uPointIndex,strText.c_str());
	 // pSerie->AttachCustomLabel(uPointIndex,strText.c_str());
    }
	  else if (mouseEvent == CChartMouseListener::MouseMove
		   && uPointIndex == INVALID_POINT
       )

	  {
		  flag=2;
		  PostMessage(m_hwnd,SHOWXY1,NULL,NULL);}
}
#endif
};

#if 0
class CCustomMouseListener : public CChartMouseListener
{
	public:
		void GetHwnd(HWND hwnd)  
    {  
        m_hwnd = hwnd;  
    }  
    HWND m_hwnd; 
  void OnMouseEventAxis(CChartMouseListener::MouseEvent mouseEvent, CPoint point,
          CChartAxis* pAxisClicked)
  {
    if (mouseEvent == CChartMouseListener::LButtonDoubleClick)
    {
		//PostMessage(m_hwnd,SHOWXY1,NULL,NULL)
      MessageBox(NULL,_T("Axis clicked"), _T("Info"), MB_OK);
    }
  }
};

#endif
BOOL CComCtrlDlg::OnInitDialog()
{

	CDialog::OnInitDialog();
	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);
	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		CString strAboutMenu;
		strAboutMenu.LoadString(IDS_ABOUTBOX);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
  
	
	m_ChartCtrl.EnableRefresh(false);
    COLORREF BackColor = RGB(200,200,255);
	COLORREF GridColor = RGB(0,0,0);
	COLORREF TextColor = RGB(0,0,0);
	// Specifies a sunken border for the control
	m_ChartCtrl.SetEdgeType(EDGE_SUNKEN);
	
	// Sets the color of the border and the back color
	m_ChartCtrl.SetBorderColor(TextColor);
	m_ChartCtrl.SetBackColor(BackColor);
	// Create the bottom axis and configure it properly
	
	m_ChartCtrl.GetTitle()->SetColor(TextColor);
	m_ChartCtrl.GetTitle()->SetFont(140,_T("Times New Roman"));
	m_ChartCtrl.GetTitle()->AddString(_T("实时曲线"));
	// Configure the legend
    m_ChartCtrl.GetLegend()->SetVisible(true);
	m_ChartCtrl.GetLegend()->SetHorizontalMode(true);
	m_ChartCtrl.GetLegend()->SetBackColor(BackColor);
	m_ChartCtrl.GetLegend()->UndockLegend(0,0);
	m_ChartCtrl.SetZoomEnabled(true);
	m_ChartCtrl.EnableRefresh(true);
	
	//m_ChartCtrl.ShowScrollBar(true);
	//SetAutoHideScrollBar

	//创建横坐标和纵坐标
	CChartStandardAxis* pLeftAxis =
		m_ChartCtrl.CreateStandardAxis(CChartCtrl::LeftAxis);//创建纵坐标
	
	m_ChartCtrl.GetLeftAxis()->SetAxisColor(TextColor);
	m_ChartCtrl.GetLeftAxis()->SetTextColor(TextColor);
	m_ChartCtrl.GetLeftAxis()->GetGrid()->SetColor(GridColor);
	CChartDateTimeAxis* pBottomAxis =
		m_ChartCtrl.CreateDateTimeAxis(CChartCtrl::BottomAxis);//创建横坐标，以时间为单位
	m_ChartCtrl.GetBottomAxis()->SetAxisColor(TextColor);
	m_ChartCtrl.GetBottomAxis()->SetTextColor(TextColor);
	m_ChartCtrl.GetBottomAxis()->GetGrid()->SetColor(GridColor);
	pLeftAxis->SetMinMax(0,100);
	pLeftAxis->SetTickIncrement(false,10);
	m_ChartCtrl.GetLeftAxis()->SetAutomatic(false);
	COleDateTime minValue(2006,1,1,1,0,0);
	//pLeftAxis->SetDiscrete(true);
COleDateTime maxValue(2006,1,1,1,1,0);

pBottomAxis->SetMinMax(CChartCtrl::DateToValue(minValue),

CChartCtrl::DateToValue(maxValue));

// Sets the tick increment to 4 months (disable automatic tick increment)

pBottomAxis->SetTickIncrement(false, CChartDateTimeAxis::tiSecond,5);
// Sets the tick label format for instance "Jan 2006"

pBottomAxis->SetTickLabelFormat(false, _T("%H:%M:%S"));

pBottomAxis->GetLabel()->SetText(_T("偏航角度/度")); 



	m_ChartCtrl.GetBottomAxis()->SetAutomatic(false);
	//创建曲线
	pLineSeries1 = m_ChartCtrl.CreateLineSerie();   
	pLineSeries2 = m_ChartCtrl.CreateLineSerie();   
	pLineSeries3 = m_ChartCtrl.CreateLineSerie();
	pLineSeries1->EnableMouseNotifications(1,1);
	pLineSeries2->EnableMouseNotifications(1,1);
	//pLineSeries1->CreateBalloonLabel(2,_T("This is a simple label"));
	//CComCtrlDlg:EnableMouseInPointer(false);
	//EnableMouseNotifications(false,false);
	CCustomMouseListener * m_pMouseListener = new CCustomMouseListener();
	CCustomMouseListener * m_pMouseListener1 = new CCustomMouseListener();
	HWND hWnd = this->GetSafeHwnd();  
	m_pMouseListener->GetHwnd(hWnd);
	HWND hWnd1 = this->GetSafeHwnd();  
	m_pMouseListener1->GetHwnd(hWnd);
	pLineSeries1->RegisterMouseListener((CChartSeriesMouseListener<SChartXYPoint>*)m_pMouseListener);
	pLineSeries2->RegisterMouseListener((CChartSeriesMouseListener<SChartXYPoint>*)m_pMouseListener);

	m_ChartCtrl.RegisterMouseListener((CChartMouseListener*)m_pMouseListener1);
	

	

	//delete(m_pMouseListener);
	//KillTimer(3);
	

    TCHAR exeFullPath[MAX_PATH]; // MAX_PATH
	GetModuleFileName(NULL,exeFullPath,MAX_PATH);//得到程序模块名称，全路径
	//也就是当前运行程序的全路径	
    //解析路径，得到当前运行程序所在目录
	char drive[_MAX_DRIVE];
	char dir[_MAX_DIR];
	_splitpath(exeFullPath, drive, dir, NULL,NULL);
	CString strPath;//strPath即为得到的当前运行程序所在目录
	strPath.Format("%s%s", drive, dir);
    strPath =strPath +"\\SaveConfig";
	
	CStdioFile file;
	if (file.Open(strPath,CFile::modeReadWrite | CFile::typeText))
	{
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
		strAdd1 = Buf;    //地点1
		j=i;
		for(i=j;i<len;i++)
		{
			if(Buf[i]==',')
				break;
		}
		Buf[i]='\0';
		strCom1 = Buf+j+1;       //串口1
		j=i;
		for(i=j;i<len;i++)
		{
			if(Buf[i]==',')
				break;
		}
		Buf[i]='\0';
		nCT1 = atoi(Buf+j+1);    //匝数比1
		j=i;
		for(i=j;i<len;i++)
		{
			if(Buf[i]==',')
				break;
		}
		Buf[i]='\0';             //电容组数1
		nCP1 = atoi(Buf+j+1);
		j=i;
		for(i=j;i<len;i++)
		{
			if(Buf[i]==',')
				break;
		}
		
		Buf[i]='\0';             
		strAdd2 = Buf+j+1;        //地点2
		j=i;
		for(i=j;i<len;i++)
		{
			if(Buf[i]==',')
				break;
		}
		Buf[i]='\0';            
		strCom2 = Buf+j+1;       //串口2
		j=i;
		for(i=j;i<len;i++)
		{
			if(Buf[i]==',')
				break;
		}
		Buf[i]='\0';
		nCT2 = atoi(Buf+j+1);    //匝数比2
		j=i;
		for(i=j;i<len;i++)
		{
			if(Buf[i]==',')
				break;
		}
		Buf[i]='\0';           //电容数组2
		nCP2 = atoi(Buf+j+1);
		j=i;
		g_nWaitTime = atof(Buf+j+1);  //发送时间间隔
		CComboBox *pcom = (CComboBox*)GetDlgItem(IDC_COMBO_CHOICE);
		pcom->ResetContent();
		pcom->AddString(strAdd1);
		pcom->AddString(strAdd2);
		pcom->SetCurSel(0);
		file.Close();
	}
	
	CString strHeader[6]={ "测试编号", "测试时间", "压力", "氧气浓度1", "温度", "氧气浓度2" };
	for (int nCol=0; nCol<6; nCol++)
		m_ListCtrl.InsertColumn(nCol,strHeader[nCol],LVCFMT_CENTER,80);
  //  m_ListCtrl.InsertColumn(2,"日期",LVCFMT_CENTER,120);

	//m_List1.SetColumnHeader(_T("数组, 40; 状态1, 40; 状态2, 40, 2"));
	//m_List2.SetColumnHeader(_T("数组, 40; 状态1, 40; 状态2, 40, 2"));
	//m_List1.SetGridLines(TRUE);
	//m_List2.SetGridLines(TRUE);
	//m_List1.SetGridLines(FALSE);
	//m_List2.SetGridLines(FALSE);
	//CBrush   m_bkBrush;
	//m_bkBrush.CreateSolidBrush(RGB(192,192,192));
	GetClientRect(&m_rect);
	return TRUE;  // return TRUE  unless you set the focus to a control
}




void CComCtrlDlg::CreateAllDirectories(TCHAR* filePath)
{
	string strPath = filePath;
	//有文件夹就返回
	if(GetFileAttributes(strPath.c_str())!=-1)
		return;
	LONG count = strPath.find_last_of("\\",strPath.length());
	strPath = strPath.replace(count,strPath.length(),"");
	CreateAllDirectories((TCHAR*)strPath.c_str());
	CreateDirectory(strPath.c_str(),NULL);
}

LRESULT CComCtrlDlg::OnShowRecv( WPARAM wParam, LPARAM lParam )
{
	TCHAR exeFullPath[MAX_PATH]; // MAX_PATH
	GetModuleFileName(NULL,exeFullPath,MAX_PATH);//得到程序模块名称，全路径
	//也就是当前运行程序的全路径	
    //解析路径，得到当前运行程序所在目录
	char drive[_MAX_DRIVE];
	char dir[_MAX_DIR];
	_splitpath(exeFullPath, drive, dir, NULL,NULL);
	CString strPath;//strPath即为得到的当前运行程序所在目录
	strPath.Format("%s%s", drive, dir);
	strPath = strPath+"\\接收数据\\";
	CreateAllDirectories(strPath.GetBuffer(strPath.GetLength() + 1));
	strPath.ReleaseBuffer();
	int nComm = wParam;       //得到串口号
	int nlen = lParam;
	CString strAdd;
	
	if(nComm == 1)
	{
		strAdd = strAdd1;
	}
	if(nComm == 2)
	{
		strAdd = strAdd2;
	}
	if(recvbuffer[0]==0x0A
		&&(byte)(recvbuffer[1])==0xC6
		&&recvbuffer[nlen-1]==0x0A
		&&recvbuffer[nlen-2]==0x0D)
	{
		//提取数据
		int npos = 0;  //当前位置
		int npre = 0;  //先前位置
		if ((byte)(recvbuffer[2])!=0xB5||(byte)(recvbuffer[3])!=0xC2
			||(byte)recvbuffer[4]!=0xCA||(byte)recvbuffer[5]!=0xA3||(byte)recvbuffer[6]!=0xBA
			)
		{
			return 0;
		}
		for(npos=7; npos + 1 < nlen; npos++)
		{
			if(recvbuffer[npos]==0x20
				&&recvbuffer[npos+1]==0x20)
			{
				break;
			}
		}
		
		if(npos == nlen)
		{
			return 0;
		}
		
		recvbuffer[npos]=0x00;
		double pl = atof(recvbuffer + 7); 
		if (pl<49||pl>51)
		{
			return 0;
		}
		
		if ((byte)recvbuffer[npos+2]!=0xB9||(byte)recvbuffer[npos+3]!=0xA6||(byte)recvbuffer[npos+4]!=0xC2
			||(byte)recvbuffer[npos+5]!=0xCA||(byte)recvbuffer[npos+6]!=0xD2||(byte)recvbuffer[npos+7]!=0xF2
			||(byte)recvbuffer[npos+8]!=0xCB||(byte)recvbuffer[npos+9]!=0xD8||(byte)recvbuffer[npos+10]!=0xA3
			||(byte)recvbuffer[npos+11]!=0xBA)
		{
			return 0;
		}
		npre = npos + 12;
		
		for( npos = npos + 12; npos + 1 < nlen; npos++)
		{
			if(recvbuffer[npos]==0x20
				&&recvbuffer[npos+1]==0x0D)
			{
				break;
			}
			
		}
		
		recvbuffer[npos]=0x00;
		double pf = atof(recvbuffer + npre); 
		if (pf<0||pf>1)
		{
			return 0;
		}
		if ((byte)recvbuffer[npos+4]!=0xB5||(byte)recvbuffer[npos+5]!=0xE7||(byte)recvbuffer[npos+6]!=0xD1
			||(byte)recvbuffer[npos+7]!=0xB9||(byte)recvbuffer[npos+8]!=0xA3||(byte)recvbuffer[npos+9]!=0xBA)
		{
			return 0 ;
		}
		npre = npos + 10;
		for(npos = npos + 10;npos +1 < nlen;npos++)
		{
			if(recvbuffer[npos]==0x20
				&&recvbuffer[npos+1]==0x20)
			{
				break;
			}
		}
		recvbuffer[npos]=0x00;
		double v =atof(recvbuffer + npre);
		if (v<220||v>250)
		{
			return 0;
		}
		if ((byte)recvbuffer[npos+3]!=0xB5||(byte)recvbuffer[npos+4]!=0xE7||(byte)recvbuffer[npos+5]!=0xC1
			||(byte)recvbuffer[npos+6]!=0xF7||(byte)recvbuffer[npos+7]!=0xA3||(byte)recvbuffer[npos+8]!=0xBA)
		{
			return 0;
		}
		npre = npos + 9;
		for(npos = npos + 9;npos +1 < nlen;npos++)
		{
			if(recvbuffer[npos]==0x20
				&&recvbuffer[npos+1]==0x20)
			{
				break;
			}
		}
		recvbuffer[npos]=0x00;
		double i =atof(recvbuffer + npre);
		if(i<0)
		{
			return 0;
		}
		if ((byte)recvbuffer[npos+2]!=0xCE||(byte)recvbuffer[npos+3]!=0xC2||(byte)recvbuffer[npos+4]!=0xB6
			||(byte)recvbuffer[npos+5]!=0xC8||(byte)recvbuffer[npos+6]!=0xA3||(byte)recvbuffer[npos+7]!=0xBA)
		{
			return 0;
		}
		npre = npos + 8;
		for(npos = npos + 8;npos +1 < nlen;npos++)
		{
			if(recvbuffer[npos]==0x0D
				&&recvbuffer[npos+1]==0x0A)
			{
				break;
			}
		}
		recvbuffer[npos]=0x00;
		double t =atof(recvbuffer + npre);
		if (t<(-55)||t>125)
		{
			return 0;
		}
		
		//写入文本文件中 
		
		if(nComm == 1)
		{
			i = i* nCT1;
		}
		if(nComm == 2)
		{
			i = i* nCT2;
		}
		strAdd = strPath+strAdd+"\\";
		CreateAllDirectories(strAdd.GetBuffer(strAdd.GetLength() + 1));
		strAdd.ReleaseBuffer();
		CTime time=CTime::GetCurrentTime();
		CString strtime;
		strtime = time.Format("%Y-%m-%d");
		CString  strInfo;
		UINT  nLength; 
		strtime = strtime + ".txt";
		strtime = strAdd + strtime;
		CFile  cfFile( strtime,CFile::modeCreate|CFile::modeNoTruncate|CFile::modeReadWrite);
		DWORD len = cfFile.GetLength();
		if (len==0)
		{
			CString m_str;
			m_str = "频率(Hz)  功率因素   电压(V)    电流(A)   温度(℃)        日  期";
			CString str;
			str.Format("%s\r\n",m_str);
			UINT nlen = strlen((LPCTSTR)str);
			cfFile.Write(str,nlen);
		}
		cfFile.SeekToEnd();
		strInfo.Format( "%4.2f      %3.2f       %3.0f        %3.2f       %4.2f       %s", 
			pl,pf,v,i,t,time.Format("%Y-%m-%d %H:%M\r\n"));
		nLength=strlen((LPCTSTR)strInfo);
		cfFile.Write(strInfo,nLength);
		cfFile.Close(); 
		if(nComm==1)
			strInfo.Format( "%s\r\n 频率:%4.2f,功率因素:%3.2f,电压:%3.0f,电流:%3.2f,温度:%4.2f",
			strAdd1,pl,pf,v,i,t);
		else
			strInfo.Format( "%s\r\n 频率:%4.2f,功率因素:%3.2f,电压:%3.0f,电流:%3.2f,温度:%4.2f",
			strAdd2,pl,pf,v,i,t);
		PrintString(strInfo);
	}
	else
	{
		for (int i = 0; i< nlen; i++)
		{
			if(recvbuffer[i] == 0x00 )
			{
				recvbuffer[i] = '.';
			}
		}
		PrintString("\r\n" + strAdd + "\r\n");
		PrintString(recvbuffer);	
	}
    return 0;
}

CFileFind finder;//定义CFileFind对象

char Buf[100];
int A = 0;
DWORD WINAPI SearchThread(LPVOID lpParam)
{
	
	HWND hwnd = *(HWND*)(lpParam);
	CString strName;//保存文件名
	CTimeSpan ts(1,0,0,0); // 1天 
	for (tm1;tm1<=TM;tm1=tm1+ts)//起始时间和终止时间
	{
		strtm = tm1.Format("%Y-%m-%d");
		bool bIsWorking = finder.FindFile("*.txt");
		for (;;)
		{//查找文件
			if (bIsWorking)
			{
				bIsWorking = finder.FindNextFile();
				strName = finder.GetFileTitle();
				
				if (strtm==strName)//判断文件名是否相同，相同的就显示
				{
					strName = strName + ".txt";
					CStdioFile file;
					if(!file.Open(strName,CFile::modeReadWrite | CFile::typeText))
					{
						PostMessage(hwnd,SHOWMESSAGE,NULL,NULL);
						return 0;
					}
					memset(Buf,0,100);
					int m = 1;
					while(file.ReadString(Buf,99))
					{
						if (m>=2)
						{
							PostMessage(hwnd, SHOWSEARCHRESULT, NULL, NULL);
							Sleep(100);
							A++;
							//	count++;
						}
						m++;
					}
					file.Close();
				}
			}

			else
			{
				break;
			}
			
		}
		finder.Close();
	}
		
	if (A==0)
	{
		PostMessage(hwnd,ShOWMESSAGEA,NULL,NULL);
		return 0;
	}
	A=0;
	return 0;
}

LRESULT CComCtrlDlg::OnShowResearch( WPARAM wParam, LPARAM lParam )
{
	int len=sizeof(Buf);
	int j,k;
	for(j=0;j<len;j++)
	{
		if(Buf[j]==' ')
			break;
	}
	Buf[j]='\0';
	double pl = atof(Buf);
	k=j;
	for(j=k+6;j<len;j++)
	{
		if(Buf[j]==' ')
			break;
	}
	Buf[j]='\0';
	double pf = atof(Buf+k+6);
	k=j;
	for(j=k+7;j<len;j++)
	{
		if(Buf[j]==' ')
			break;
	}
	Buf[j]='\0';
	double v = atof(Buf+k+7);
	k=j;
	for(j=k+8;j<len;j++)
	{
		if(Buf[j]==' ')
			break;
	}
	Buf[j]='\0';
	double i = atof(Buf+k+8);
	k=j;
	for(j=k+7;j<len;j++)
	{
		if(Buf[j]==' ')
			break;
	}
	Buf[j]='\0';
	double t = atof(Buf+k+7);
	k=j;
	CString strTime=Buf+k+7;
	int nItem = m_ListCtrl.GetItemCount();
	CString str;
	str.Format("%4.2f", pl );
	m_ListCtrl.InsertItem( nItem, str );
	str.Format("%3.2f", pf );
	m_ListCtrl.SetItemText( nItem, 1, str );
	str.Format("%3.0f", v);
	m_ListCtrl.SetItemText( nItem, 2, str );
	str.Format("%3.2f", i);
	m_ListCtrl.SetItemText( nItem, 3, str );
	str.Format("%4.2f", t);
	m_ListCtrl.SetItemText( nItem, 4, str );
	m_ListCtrl.SetItemText( nItem, 5, strTime );
	return 0;
}

LRESULT CComCtrlDlg::OnShowMessage(WPARAM wParam, LPARAM lParam)
{
	MessageBox("上次查询的数据还没有完全显示，请稍后再试","提示",MB_OK);
	return 0;
}

LRESULT CComCtrlDlg::OnShowMessageA(WPARAM wParam, LPARAM lParam)
{
	MessageBox("您选择的时间段没有数据信息，请重新设置查询时间","提示",MB_OK);
	return 0;
}

LRESULT CComCtrlDlg::OnShowXY(WPARAM wParam, LPARAM lParam)
{
	//MessageBox("您选择的时间段没有数据信息，请重新设置查询时间","提示",MB_OK);
	if(flag==1)
	{
	CString s;  
    s.Format(_T("x=%.2f,y=%.2f"),temp1,temp2);
	CStatic* pStatic;
    pStatic = (CStatic*)GetDlgItem(IDC_TEMP_NO);  
	pStatic->SetWindowText(s);
	}
	else
	{
	CStatic* pStatic;
    pStatic = (CStatic*)GetDlgItem(IDC_TEMP_NO);  
	pStatic->SetWindowText(_T(""));
	}
	flag=3;
		return 0;
}

LRESULT CComCtrlDlg::OnShowXY1(WPARAM wParam, LPARAM lParam)
{
	//MessageBox("您选择的时间段没有数据信息，请重新设置查询时间","提示",MB_OK);
	CString s;  
    s.Format(_T("x=%.2f,y=%.2f"),temp1,temp2);
	CStatic* pStatic;
    pStatic = (CStatic*)GetDlgItem(IDC_TEMP_NO);  
	pStatic->SetWindowText(_T(""));
		return 0;
}
LRESULT CComCtrlDlg::OnShowXYDIS(WPARAM wParam, LPARAM lParam)
{
	//MessageBox("您选择的时间段没有数据信息，请重新设置查询时间","提示",MB_OK);
	CStatic* pStatic;
    pStatic = (CStatic*)GetDlgItem(IDC_TEMP_NO);  
	pStatic->SetWindowText(_T(""));
	return 0;
}
void CComCtrlDlg::OnBtnCheck() 
{
	m_ListCtrl.DeleteAllItems();
	TCHAR exeFullPath[MAX_PATH]; // MAX_PATH
	GetModuleFileName(NULL,exeFullPath,MAX_PATH);//得到程序模块名称，全路径
	//也就是当前运行程序的全路径	
    //解析路径，得到当前运行程序所在目录
	char drive[_MAX_DRIVE];
	char dir[_MAX_DIR];
	_splitpath(exeFullPath, drive, dir, NULL,NULL);
	CString strPath;//strPath即为得到的当前运行程序所在目录
	strPath.Format("%s%s", drive, dir);
	GetDlgItem(IDC_BTN_CHECK)->EnableWindow(FALSE);
	int count = 0;
	int nPos =((CComboBox*)GetDlgItem(IDC_COMBO_CHOICE))->GetCurSel();
	if (nPos==-1)
	{
		MessageBox("当前没有可查询的数据","提示");
		GetDlgItem(IDC_BTN_CHECK)->EnableWindow(true);
		return;
	}
	CString  str;//选择查询的地点名
	((CComboBox*)GetDlgItem(IDC_COMBO_CHOICE))->GetLBText(nPos,str);
	str = strPath + "\\接收数据\\"+ str + "\\";

	BOOL bl = SetCurrentDirectory(str);//设置查找目录
	if(bl==false)
	{
		MessageBox("暂没有该地址的历史信息","提示");
		GetDlgItem(IDC_BTN_CHECK)->EnableWindow(true);
		return;
	}

	
	m_PreTimeCtrl.GetTime(tm1);
	strtm = tm1.Format("%Y-%m-%d");
	
	m_PosTimeCtrl.GetTime(TM);
	strTM = TM.Format("%Y-%m-%d");
	
	HANDLE hThread = CreateThread(NULL, 0, SearchThread, (LPVOID)&m_hWnd, 0, NULL);
	GetDlgItem(IDC_BTN_CHECK)->EnableWindow(true);
}

void CComCtrlDlg::OnPaint() 
{
	CFont * cFont=new CFont;
	cFont->CreatePointFont(140,_T("华文楷体"));
	GetDlgItem(IDC_TITLE)->SetFont(cFont);
	GetDlgItem(IDC_AUTHOR)->SetFont(cFont);
	GetDlgItem(IDC_AUTHER_ENG)->SetFont(cFont);
	GetDlgItem(IDC_TEMP_NO)->SetFont(cFont);
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, (WPARAM) dc.GetSafeHdc(), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

HCURSOR CComCtrlDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

int temp=0;
int O2=0;
void CComCtrlDlg::OnBtnOpen() 
{

	/*if(strCom1==""&&strCom2=="")
	{
	    MessageBox("请先配置参数！","提示");
		return ;
	}*/
#if 0
	CString strTemp;
	GetDlgItemText(IDC_BTN_OPEN, strTemp);
	CString strComm1;
	strComm1 = strCom1;
	CString strComm2;
	strComm2 = strCom2;
#endif
	SetTimer(3,1000,NULL);
#if 0
	if (strTemp == "开始采集")
	{
		
		SetDlgItemText(IDC_BTN_OPEN, _T("停止采集"));
		//SetTimer(3,1000,NULL);
		//Draw(0);
		/*m_hRecvHandle1 = CreateThread(NULL, 0, RecvThread1, (LPVOID)&m_hWnd, 0, NULL);
		m_hRecvHandle2 = CreateThread(NULL, 0, RecvThread2, (LPVOID)&m_hWnd, 0, NULL);*/
		
		/*if (m_hRecvHandle1 == INVALID_HANDLE_VALUE || m_hRecvHandle1 == NULL
			||m_hRecvHandle2 == INVALID_HANDLE_VALUE || m_hRecvHandle2 == NULL)
		{
			MessageBox("创建线程失败，请重试","提示");
			return;
		}
		
		SetDlgItemText(IDC_BTN_OPEN, _T("停止运行"));*/
	

	}
	else
	{
		SetDlgItemText(IDC_BTN_OPEN, _T("开始采集"));
		/*g_cComm2.CloseComm();
		SetDlgItemText(IDC_BTN_OPEN, _T("开始运行"));*/
	}
#endif
}



void CComCtrlDlg::OnBtnManualsend() 
{
	CString strTemp;
	GetDlgItemText(IDC_BTN_OPEN, strTemp);
	if (strTemp=="开始运行")
	{
		MessageBox("请先运行程序","提示");
		return ;
	}
	for (int i = 0; i< 2; i++)
	{
		char sendbuffer[5]={0};
		sendbuffer[0]=0xB7;
		sendbuffer[1]=0xA2;
		sendbuffer[2]=0xCB;
		sendbuffer[3]=0xCD;
		if (i==0)
		{
			g_cComm1.WriteComm(sendbuffer,4);
		}
		if (i==1)
		{
			g_cComm2.WriteComm(sendbuffer,4);
		}
	}
}

void CComCtrlDlg::OnBtnClear()
{ 
	SetDlgItemText(ID_EDIT_LOG, "");  
}

void CComCtrlDlg::OnBtnConfigdata() 
{
	CConfigDlg dlg;
	if (IDOK==dlg.DoModal())
	{
		
		strCom1 = dlg.m_strcomm1;
		strCom2 = dlg.m_strcomm2;
		nCT1 = dlg.m_nCT1;
		nCT2 = dlg.m_nCT2;
		nCP1 = dlg.m_nCP1;
		nCP2 = dlg.m_nCP2;
		g_nWaitTime=dlg.m_nTime;
		strAdd1 = dlg.m_strAdd1;
		strAdd2 = dlg.m_strAdd2;
		CComboBox *pCombo = (CComboBox*)GetDlgItem(IDC_COMBO_CHOICE);
		pCombo->ResetContent();
		pCombo->AddString(strAdd1);
		pCombo->AddString(strAdd2);
		pCombo->SetCurSel(0);
	}
	
}

void CComCtrlDlg::PrintString( CString strPrint )
{
	strPrint +="\r\n";
	CEdit* pEdit = (CEdit*)GetDlgItem(ID_EDIT_LOG);
	if (pEdit->GetWindowTextLength() > 8000)
	{
		pEdit->SetWindowText(_T(""));
	}
	pEdit->SetFocus();
	pEdit->SetSel(-1, -1);
	pEdit->ReplaceSel(strPrint);
}

void CComCtrlDlg::OnBtnSend() 
{
	CString strtemp;
    GetDlgItemText(IDC_BTN_SEND,strtemp);
	if(strtemp=="自动获取")
	{
		CString strTemp;
		GetDlgItemText(IDC_BTN_OPEN, strTemp);
		if (strTemp=="开始运行")
		{
			MessageBox("请先运行程序","提示");
			return ;
		}
		m_hHandle1 = CreateThread(NULL, 0, SendCmdThread1, (LPVOID)&m_hWnd, 0, NULL);
		m_hHandle2 = CreateThread(NULL, 0, SendCmdThread2, (LPVOID)&m_hWnd, 0, NULL);
		if (m_hHandle1 == INVALID_HANDLE_VALUE || m_hHandle1 == NULL
			||m_hHandle2 == INVALID_HANDLE_VALUE || m_hHandle2 == NULL
			)
		{
			MessageBox("创建线程失败，请重试","提示");
			return;
		}
        GetDlgItem(IDC_BTN_MANUALSEND)->EnableWindow(FALSE);
		GetDlgItem(IDC_BTN_OPEN)->EnableWindow(FALSE);
		GetDlgItem(IDC_BTN_CONFIGDATA)->EnableWindow(FALSE);
		SetDlgItemText(IDC_BTN_SEND,_T("停止获取"));
	}
	else
	{
		GetDlgItem(IDC_BTN_MANUALSEND)->EnableWindow(TRUE);
		GetDlgItem(IDC_BTN_OPEN)->EnableWindow(TRUE);
		GetDlgItem(IDC_BTN_CONFIGDATA)->EnableWindow(TRUE);
		TerminateThread(m_hHandle1, 0);    
		CloseHandle(m_hHandle1);
		TerminateThread(m_hHandle2, 0);    
		CloseHandle(m_hHandle2);
		SetDlgItemText(IDC_BTN_SEND,_T("自动获取"));
	}
}

void CComCtrlDlg::OnBtnZt() 
{
	m_List1.DeleteAllItems();
	m_List2.DeleteAllItems();
	for (int i = 1; i <= nCP1; i++)
	{
		int nItem = m_List1.GetItemCount();
	
		CString str;
		if (i<10)
		{
			str.Format("0%d",i);
		}
		else
			str.Format("%d",i);
		m_List1.InsertItem(nItem,str);
		m_List1.SetItemText(nItem,1,"投");
		m_List1.SetItemText(nItem,2,"切");
	}

	for ( int i = 1; i <= nCP2; i++)
	{
		int nItem2 = m_List2.GetItemCount();
		CString str2;
		if (i<10)
		{
			str2.Format("0%d",i);
		}
		else
			str2.Format("%d",i);
		m_List2.InsertItem(nItem2,str2);
	    m_List2.SetItemText(nItem2, 1, "投");
		m_List2.SetItemText(nItem2, 2, "切");  
		
	}
	SetDlgItemText(IDC_STATIC1,strAdd1);

	SetDlgItemText(IDC_STATIC2,strAdd2);
}

void CComCtrlDlg::OnBtnPc() 
{

	Draw(0);
}

BOOL CComCtrlDlg::PreTranslateMessage(MSG* pMsg) 
{ 
	if (pMsg->message==WM_KEYDOWN) 
	   { 
		   int nVirtKey = (int)pMsg->wParam;         
		   if   (nVirtKey==VK_ESCAPE) 
		   {
			   return   TRUE; 
		   } 
		   if (nVirtKey==VK_RETURN)
		   {
			   return TRUE;
		   }
	   }
    return CDialog::PreTranslateMessage(pMsg);
}

void CComCtrlDlg::Draw(int n)
{	
#if 0
	m_ChartCtrl.RemoveAllSeries();
    TCHAR exeFullPath[MAX_PATH]; // MAX_PATH
	GetModuleFileName(NULL,exeFullPath,MAX_PATH);//得到程序模块名称，全路径
	//也就是当前运行程序的全路径	
    //解析路径，得到当前运行程序所在目录
	char drive[_MAX_DRIVE];
	char dir[_MAX_DIR];
	_splitpath(exeFullPath, drive, dir, NULL,NULL);
	CString strPath;//strPath即为得到的当前运行程序所在目录
	strPath.Format("%s%s", drive, dir);
	int m_count = 0;//记录文件中数据的条数
	CString m_strtime;//记录前一次读取的时间字符串
	double sumpl = 0,sumpf =0,sumv = 0,sumi = 0,sumt = 0;//各个数据求和
	int hour =-1,date =-1,month =-1;//提取的小时，天数，月份
	int N = 0;//累计求和的次数
	double maxpl = 0,maxpf = 0,maxv = 0,maxi = 0,maxt = 0;
	double minpl = 10000,minpf = 10000,minv = 10000,mini = 10000,mint = 10000;
	double npl,npf,nv,ni,nt;//各个数据的平均值
	CTime tm;
	m_PreTimeCtrl.GetTime(tm);
	strtm = tm.Format("%Y-%m-%d");
	CTime TM;
	m_PosTimeCtrl.GetTime(TM);
	strTM = TM.Format("%Y-%m-%d");
    COleDateTime min;
	min.ParseDateTime(strtm);
	COleDateTime max;
	max.ParseDateTime(strTM);
	int nPos =((CComboBox*)GetDlgItem(IDC_COMBO_CHOICE))->GetCurSel();
 #if 0
	if (nPos==-1)
	{
		MessageBox("当前没有可查询的数据","提示");
		return;
	}
 #endif

	CString  str;//要查询的地点名
	//((CComboBox*)GetDlgItem(IDC_COMBO_CHOICE))->GetLBText(nPos,str);
	str = strPath + "\\接收数据\\"+ str + "\\";
    CFileFind finder;//定义CFileFind对象
	CString strName;//保存文件名
	BOOL bIsWorking;//标志是否找完所有文件
	#if 0
	BOOL bl = SetCurrentDirectory(str);//设置查找目录

	if (false==bl)
	{
		MessageBox("暂没有该地址的历史信息","提示");
        return;
	}

	bIsWorking = finder.FindFile("*.txt");
	if (FALSE==bIsWorking)
	{		
		MessageBox("暂没有该地址的历史信息","提示");
        return;
	}
	#endif
	//做曲线
	COLORREF BackColor = RGB(200,200,255);
	COLORREF GridColor = RGB(0,0,0);
	COLORREF TextColor = RGB(0,0,0);
	CChartStandardAxis* pLeftAxis =
		m_ChartCtrl.CreateStandardAxis(CChartCtrl::LeftAxis);//创建纵坐标
	
	m_ChartCtrl.GetLeftAxis()->SetAxisColor(TextColor);
	m_ChartCtrl.GetLeftAxis()->SetTextColor(TextColor);
	m_ChartCtrl.GetLeftAxis()->GetGrid()->SetColor(GridColor);
	CChartDateTimeAxis* pBottomAxis =
		m_ChartCtrl.CreateDateTimeAxis(CChartCtrl::BottomAxis);//创建横坐标，以时间为单位
	pBottomAxis->SetTickLabelFormat(false,_T("%m月%d日"));
	//Sets the color of the different elements of the bottom axis
	m_ChartCtrl.GetBottomAxis()->SetAxisColor(TextColor);
	m_ChartCtrl.GetBottomAxis()->SetTextColor(TextColor);
	m_ChartCtrl.GetBottomAxis()->GetGrid()->SetColor(GridColor);
	m_ChartCtrl.GetBottomAxis()->SetAutomatic(true);
    
	
	if(n==0)
	{
		
		m_ChartCtrl.GetLeftAxis()->SetAutomatic(true);
		
	}
	if(n==1)
	{
		pLeftAxis->SetMinMax(48,52);
	    m_ChartCtrl.GetLeftAxis()->SetAutomatic(false);
	}
	if(n==2)
	{
		pLeftAxis->SetMinMax(0,2);
	    m_ChartCtrl.GetLeftAxis()->SetAutomatic(false);
	}
	if(n==3)
	{
		pLeftAxis->SetMinMax(210,250);
	    m_ChartCtrl.GetLeftAxis()->SetAutomatic(false);
	}
	if(n==4)
	{
		pLeftAxis->SetMinMax(-5,50);
	    m_ChartCtrl.GetLeftAxis()->SetAutomatic(false);
	}
	if(n==5)
	{
		pLeftAxis->SetMinMax(-20,50);
	    m_ChartCtrl.GetLeftAxis()->SetAutomatic(false);
	}

    CChartLineSerie*pLineSeries1 = m_ChartCtrl.CreateLineSerie();   //频率
	CChartLineSerie*pLineSeries2 = m_ChartCtrl.CreateLineSerie();   //功率因素
	CChartLineSerie*pLineSeries3 = m_ChartCtrl.CreateLineSerie();   //电压
	CChartLineSerie*pLineSeries4 = m_ChartCtrl.CreateLineSerie();   //电流
	CChartLineSerie*pLineSeries5 = m_ChartCtrl.CreateLineSerie();   //温度		
    if (n==0)
    {
		
		
		pLineSeries1->SetColor(RGB(0,0,0));
		pLineSeries1->SetName(_T("压力"));
		pLineSeries1->SetWidth(1);
		
		
		pLineSeries2->SetColor(RGB(255,0,0));
		pLineSeries2->SetName(_T("氧气浓度"));
		pLineSeries2->SetWidth(1);
		
		
		pLineSeries3->SetColor(RGB(255,255,255));
		pLineSeries3->SetName(_T("温度"));
		pLineSeries3->SetWidth(1);
		
#if 0
		pLineSeries4->SetColor(RGB(0,148,148));
		pLineSeries4->SetName(_T("电流"));
		pLineSeries4->SetWidth(1);
		
		
		pLineSeries5->SetColor(RGB(0,0,250));
		pLineSeries5->SetName(_T("温度"));
		pLineSeries5->SetWidth(1);
#endif
    }
	else if (n==1)
	{
		
        pLineSeries1->SetVisible(1);
		pLineSeries1->SetColor(RGB(0,128,0));
		pLineSeries1->SetName(_T("压力"));
		pLineSeries1->SetWidth(1);
	}
	else if (n==2)
	{
		
		pLineSeries1->SetColor(RGB(250,0,0));
		pLineSeries1->SetName(_T("氧气浓度"));
		pLineSeries1->SetWidth(1);
	}
	else if (n==3)
	{
		
		pLineSeries1->SetColor(RGB(150,80,100));
		pLineSeries1->SetName(_T("温度"));
		pLineSeries1->SetWidth(1);
	}
	else if(n==4)
	{
		
		pLineSeries1->SetColor(RGB(0,148,148));
		pLineSeries1->SetName(_T("电流"));
		pLineSeries1->SetWidth(1);
	}
	else if (n==5)
	{
		
		pLineSeries1->SetColor(RGB(0,0,250));
		pLineSeries1->SetName(_T("温度"));
		pLineSeries1->SetWidth(1);
	}
	
	CString m_strTime;//按月查询中读取最后一次的时间值
	int m = 0;//判断文件有无数据
	CTimeSpan T = TM - tm;
	int days = T.GetDays();//计算要查询的天数
	double pl=1,pf=2,v=3;
	COleDateTime dt;
	UpdateData(TRUE);
	double x[1000], y[1000],x1[1000],y1[1000],x2[1000],y2[1000];  
	for (int i=0; i<1000; i++)  
	{  
    x[i] = i;  
    y[i] = 2*i; 
	x1[i]=i;
	y1[i]=3*i;
	x2[i]=i;
	y2[i]=4*i;
	}   
	
	
	switch (m_CheckType)
	{
	case 0:
		if(n==0)
		{
			
			pLineSeries1->AddPoints(x,y,500);
			pLineSeries2->AddPoints(x1,y1,500);
			pLineSeries3->AddPoints(x2,y2,1000);
			
		}
		break;
	default:
		break;
	}
#if 0
	switch (m_CheckType)
	{
	case 0:// 按平均值查询
		for (;;)
		{

			if (bIsWorking)
			{
				bIsWorking = finder.FindNextFile();
				strName = finder.GetFileTitle();
				int a = strName.CompareNoCase(strtm);
				int b = strName.CompareNoCase(strTM);
				
				if (a>=0&&b<=0)
				{
					strName = strName + ".txt";
					CStdioFile file;
					if(!file.Open(strName,CFile::modeReadWrite | CFile::typeText))
					{
						MessageBox("您选择的时间段没有数据信息，请重新设置查询时间或该文件正被访问，请稍后再试","提示");
						return;
					}
					int count = 1;
					char Buf[100];
					memset(Buf,0,100);
					while (file.ReadString(Buf,99))//读取每个文件的数据的条数
					{
						m_count++;
					}
					file.Close();
					memset(Buf,0,100);
					if (m_count<=21)
					{
						file.Open(strName,CFile::modeReadWrite | CFile::typeText);
						while(file.ReadString(Buf,99))
						{
							if (count>=2)
							{
								int len=sizeof(Buf);
								int j,k;
								for(j=0;j<len;j++)
								{
									if(Buf[j]==' ')
										break;
								}
								Buf[j]='\0';
								double pl = atof(Buf);
								k=j;
								for(j=k+6;j<len;j++)
								{
									if(Buf[j]==' ')
										break;
								}
								Buf[j]='\0';
								double pf = atof(Buf+k+6);
								k=j;
								for(j=k+7;j<len;j++)
								{
									if(Buf[j]==' ')
										break;
								}
								Buf[j]='\0';
								double v = atof(Buf+k+7);
								k=j;
								for(j=k+8;j<len;j++)
								{
									if(Buf[j]==' ')
										break;
								}
								Buf[j]='\0';
								double i = atof(Buf+k+8);
								k=j;
								for(j=k+7;j<len;j++)
								{
									if(Buf[j]==' ')
										break;
								}
								Buf[j]='\0';
								double t = atof(Buf+k+7);
								k=j;
								CString strTime=Buf+k+7;
								COleDateTime dt;
								dt.ParseDateTime(strTime);
								SYSTEMTIME  st;
								dt.GetAsSystemTime(st);
								CTime Time(st);
								if (n==0)
								{
									pLineSeries1->AddPoint(dt,pl);
									pLineSeries2->AddPoint(dt,pf);
									pLineSeries3->AddPoint(dt,v);
									pLineSeries4->AddPoint(dt,i);
									pLineSeries5->AddPoint(dt,t);
								}
								else if (n==1)
								{
									pLineSeries1->AddPoint(dt,pl);
								}
								else if (n==2)
								{
									pLineSeries1->AddPoint(dt,pf);
								}
								else if (n==3)
								{
									pLineSeries1->AddPoint(dt,v);
								}
								else if (n==4)
								{
									pLineSeries1->AddPoint(dt,i);
								}
								else if (n==5)
								{
									pLineSeries1->AddPoint(dt,t);
								}
								m++;
							}
							count++;
						}//while
						file.Close();
					}//if(m_count)
					else
					{
						if (days>=0&&days<5)//按小时查询
						{
							file.Open(strName,CFile::modeReadWrite | CFile::typeText);
							while(file.ReadString(Buf,99))
							{
								if (count>=2)
								{
									int len=sizeof(Buf);
									int j,k;
									for(j=0;j<len;j++)
										
									{
										if(Buf[j]==' ')
											break;
									}
									Buf[j]='\0';
									double pl = atof(Buf);
									k=j;
									for(j=k+6;j<len;j++)
									{
										if(Buf[j]==' ')
											break;
									}
									Buf[j]='\0';
									double pf = atof(Buf+k+6);
									k=j;
									for(j=k+7;j<len;j++)
									{
										if(Buf[j]==' ')
											break;
									}
									Buf[j]='\0';
									double v = atof(Buf+k+7);
									k=j;
									for(j=k+8;j<len;j++)
									{
										if(Buf[j]==' ')
											break;
									}
									Buf[j]='\0';
									double i = atof(Buf+k+8);
									k=j;
									for(j=k+7;j<len;j++)
									{
										if(Buf[j]==' ')
											break;
									}
									Buf[j]='\0';
									double t = atof(Buf+k+7);
									k=j;
									CString strTime=Buf+k+7;
									sscanf(strTime,"%d-%d-%d %d:%d:%d",&nYear,&nMonth,&nDate,&nHour,&nMin,&nSec);
									if (hour==-1)
									{
										hour = nHour;
									}
									if (hour==nHour)
									{
										m_strtime = strTime;
										sumpl +=pl;
										sumpf +=pf;
										sumv  +=v;
										sumi  +=i;
										sumt  +=t;
										N++;
									}
									else
									{
										hour= nHour;
										npl = sumpl/N;
										npf = sumpf/N;
										nv  = sumv/N;
										ni  = sumi/N;
										nt  = sumt/N;
										
										COleDateTime dt;
										dt.ParseDateTime(m_strtime);
										SYSTEMTIME  st;
										dt.GetAsSystemTime(st);
										CTime Time(st);
										if (n==0)
										{
											pLineSeries1->AddPoint(dt,npl);
											pLineSeries2->AddPoint(dt,npf);
											pLineSeries3->AddPoint(dt,nv);
											pLineSeries4->AddPoint(dt,ni);
											pLineSeries5->AddPoint(dt,nt);
										}
										else if (n==1)
										{
											pLineSeries1->AddPoint(dt,npl);
										}
										else if (n==2)
										{
											pLineSeries1->AddPoint(dt,npf);
										}
										else if (n==3)
										{
											pLineSeries1->AddPoint(dt,nv);
										}
										else if (n==4)
										{
											pLineSeries1->AddPoint(dt,ni);
										}
										else if (n==5)
										{
											pLineSeries1->AddPoint(dt,nt);
										}
										m++;
										sumpl = 0;
										sumpf = 0;
										sumv  = 0;
										sumi  = 0;
										sumt  = 0;
										N=0;
									}
							}
							count++;	
						}//while 读取文件
						file.Close();
						//读取一个文件中最后一次平均值，并画图
						npl = sumpl/N;
						npf = sumpf/N;
						nv  = sumv/N;
						ni  = sumi/N;
						nt  = sumt/N;	
						COleDateTime dt;
						dt.ParseDateTime(m_strtime);
						SYSTEMTIME  st;
						dt.GetAsSystemTime(st);
						CTime Time(st);
						if (n==0)
						{
							pLineSeries1->AddPoint(dt,npl);
							pLineSeries2->AddPoint(dt,npf);
							pLineSeries3->AddPoint(dt,nv);
							pLineSeries4->AddPoint(dt,ni);
							pLineSeries5->AddPoint(dt,nt);
						}
						else if (n==1)
						{
							pLineSeries1->AddPoint(dt,npl);
						}
						else if (n==2)
						{
							pLineSeries1->AddPoint(dt,npf);
						}
						else if (n==3)
						{
							pLineSeries1->AddPoint(dt,nv);
						}
						else if (n==4)
						{
							pLineSeries1->AddPoint(dt,ni);
						}
						else if (n==5)
						{
							pLineSeries1->AddPoint(dt,nt);
						}
					}//if 0到5天的数据	
					if (days>=5&&days<=56)//按天数查询
					{
						file.Open(strName,CFile::modeReadWrite | CFile::typeText);
						while(file.ReadString(Buf,99))
						{
							if (count>=2)
							{
								int len=sizeof(Buf);
								int j,k;
								for(j=0;j<len;j++)
								{
									if(Buf[j]==' ')
										break;
								}
								Buf[j]='\0';
								double pl = atof(Buf);
								k=j;
								for(j=k+6;j<len;j++)
								{
									if(Buf[j]==' ')
										break;
								}
								Buf[j]='\0';
								double pf = atof(Buf+k+6);
								k=j;
								for(j=k+7;j<len;j++)
								{
									if(Buf[j]==' ')
										break;
								}
								Buf[j]='\0';
								double v = atof(Buf+k+7);
								k=j;
								for(j=k+8;j<len;j++)
								{
									if(Buf[j]==' ')
										break;
								}
								Buf[j]='\0';
								double i = atof(Buf+k+8);
								k=j;
								for(j=k+7;j<len;j++)
								{
									if(Buf[j]==' ')
										break;
								}
								Buf[j]='\0';
								double t = atof(Buf+k+7);
								k=j;
								CString strTime=Buf+k+7;
								m_strtime = strTime;
								sumpl +=pl;
								sumpf +=pf;
								sumv  +=v;
								sumi  +=i;
								sumt  +=t;
								N++;				
								
							}
							count++;
						}//while
						file.Close();
						COleDateTime dt;
						dt.ParseDateTime(m_strtime);
						SYSTEMTIME  st;
						dt.GetAsSystemTime(st);
						CTime Time(st);
						npl = sumpl/N;
						npf = sumpf/N;
						nv  = sumv/N;
						ni  = sumi/N;
						nt  = sumt/N;
						if (n==0)
						{
							pLineSeries1->AddPoint(dt,npl);
							pLineSeries2->AddPoint(dt,npf);
							pLineSeries3->AddPoint(dt,nv);
							pLineSeries4->AddPoint(dt,ni);
							pLineSeries5->AddPoint(dt,nt);
						}
						else if (n==1)
						{
							pLineSeries1->AddPoint(dt,npl);
						}
						else if (n==2)
						{
							pLineSeries1->AddPoint(dt,npf);
						}
						else if (n==3)
						{
							pLineSeries1->AddPoint(dt,nv);
						}
						else if (n==4)
						{
							pLineSeries1->AddPoint(dt,ni);
						}
						else if (n==5)
						{
							pLineSeries1->AddPoint(dt,nt);
						}
						m++;
						sumpl = 0;
						sumpf = 0;
						sumv  = 0;
						sumi  = 0;
						sumt  = 0;
						N=0;
					}//if 5到4个月的数据
					
				}//else
				
			}//if(a,b)
		}//if(bIsWorking)	
		 else
			break;		
    }//for(;;)
	
	if (days>56)//按月数查询
	{
		int kk = 1;//记录while中读取的次数
		
		CTimeSpan ts(1,0,0,0); // 1天 
		for (tm;tm<=TM;tm=tm+ts)//起始时间和终止时间
		{
			strtm = tm.Format("%Y-%m-%d");
			bIsWorking = finder.FindFile("*.txt");
			for (;;)
			{
				if (bIsWorking)
				{
					bIsWorking = finder.FindNextFile();
					strName = finder.GetFileTitle();
					if (strtm==strName)
					{
						strName = strName + ".txt";
						CStdioFile file;
						file.Open(strName,CFile::modeReadWrite | CFile::typeText);
						while(file.ReadString(Buf,99))
						{
							//memset(Buf,0,100);
							if (kk>=2)
							{
								int len=sizeof(Buf);
								int j,k;
								for(j=0;j<len;j++)
								{
									if(Buf[j]==' ')
										break;
								}
								Buf[j]='\0';
								double pl = atof(Buf);
								k=j;
								for(j=k+6;j<len;j++)
								{
									if(Buf[j]==' ')
										break;
								}
								Buf[j]='\0';
								double pf = atof(Buf+k+6);
								k=j;
								for(j=k+7;j<len;j++)
								{
									if(Buf[j]==' ')
										break;
								}
								Buf[j]='\0';
								double v = atof(Buf+k+7);
								k=j;
								for(j=k+8;j<len;j++)
								{
									if(Buf[j]==' ')
										break;
								}
								Buf[j]='\0';
								double i = atof(Buf+k+8);
								k=j;
								for(j=k+7;j<len;j++)
								{
									if(Buf[j]==' ')
										break;
								}
								Buf[j]='\0';
								double t = atof(Buf+k+7);
								k=j;
								CString strTime=Buf+k+7;
								sscanf(strTime,"%d-%d-%d %d:%d:%d",&nYear,&nMonth,&nDate,&nHour,&nMin,&nSec);
								if (month == -1)
								{
									month = nMonth;
								}
								if (month == nMonth)
								{
									m_strTime = strTime;
									sumpl +=pl;
									sumpf +=pf;
									sumv  +=v;
									sumi  +=i;
									sumt  +=t;
									N++;
								}
								else
								{
									month = nMonth;
									npl = sumpl/N;
									npf = sumpf/N;
									nv  = sumv/N;
									ni  = sumi/N;
									nt  = sumt/N;
									
									COleDateTime dt;
									dt.ParseDateTime(m_strTime);
									SYSTEMTIME  st;
									dt.GetAsSystemTime(st);
									CTime Time(st);
									if (n==0)
									{
										pLineSeries1->AddPoint(dt,npl);
										pLineSeries2->AddPoint(dt,npf);
										pLineSeries3->AddPoint(dt,nv);
										pLineSeries4->AddPoint(dt,ni);
										pLineSeries5->AddPoint(dt,nt);
									}
									else if (n==1)
									{
										pLineSeries1->AddPoint(dt,npl);
									}
									else if (n==2)
									{
										pLineSeries1->AddPoint(dt,npf);
									}
									else if (n==3)
									{
										pLineSeries1->AddPoint(dt,nv);
									}
									else if (n==4)
									{
										pLineSeries1->AddPoint(dt,ni);
									}
									else if (n==5)
									{
										pLineSeries1->AddPoint(dt,nt);
									}
									m++;
									sumpl = 0;
									sumpf = 0;
									sumv  = 0;
									sumi  = 0;
									sumt  = 0;
									N=0;
								}
							}
							kk++;
                     }//while
					 file.Close();
					 kk = 0;
					}
				}
				else
					break;
			}
		}
	}//if(大于56)
	if (days>56)
    {
		npl = sumpl/N;
		npf = sumpf/N;
		nv  = sumv/N;
		ni  = sumi/N;
		nt  = sumt/N;
		
		COleDateTime dt;
		dt.ParseDateTime(m_strTime);
		SYSTEMTIME  st;
		dt.GetAsSystemTime(st);
		CTime Time(st);
		if (n==0)
		{
			pLineSeries1->AddPoint(dt,npl);
			pLineSeries2->AddPoint(dt,npf);
			pLineSeries3->AddPoint(dt,nv);
			pLineSeries4->AddPoint(dt,ni);
			pLineSeries5->AddPoint(dt,nt);
		}
		else if (n==1)
		{
			pLineSeries1->AddPoint(dt,npl);
		}
		else if (n==2)
		{
			pLineSeries1->AddPoint(dt,npf);
		}
		else if (n==3)
		{
			pLineSeries1->AddPoint(dt,nv);
		}
		else if (n==4)
		{
			pLineSeries1->AddPoint(dt,ni);
		}
		else if (n==5)
		{
			pLineSeries1->AddPoint(dt,nt);
		}
    }
	    break;
	case 1:  //按最大值查询
		for (;;)
		{
			if (bIsWorking)
			{
				bIsWorking = finder.FindNextFile();
				strName = finder.GetFileTitle();
				int a = strName.CompareNoCase(strtm);
				int b = strName.CompareNoCase(strTM);
				
				if (a>=0&&b<=0)
				{
					strName = strName + ".txt";
					CStdioFile file;
					if(!file.Open(strName,CFile::modeReadWrite | CFile::typeText))
					{
						MessageBox("您选择的时间段没有数据信息，请重新设置查询时间","提示");
						return;
					}
					int count = 1;
					char Buf[100];
					memset(Buf,0,100);
					while (file.ReadString(Buf,99))//读取每个文件的数据的条数
					{
						m_count++;
					}
					file.Close();
					memset(Buf,0,100);
					if (m_count<=21)
					{
						file.Open(strName,CFile::modeReadWrite | CFile::typeText);
						while(file.ReadString(Buf,99))
						{
							if (count>=2)
							{
								int len=sizeof(Buf);
								int j,k;
								for(j=0;j<len;j++)
								{
									if(Buf[j]==' ')
										break;
								}
								Buf[j]='\0';
								double pl = atof(Buf);
								k=j;
								for(j=k+6;j<len;j++)
								{
									if(Buf[j]==' ')
										break;
								}
								Buf[j]='\0';
								double pf = atof(Buf+k+6);
								k=j;
								for(j=k+7;j<len;j++)
								{
									if(Buf[j]==' ')
										break;
								}
								Buf[j]='\0';
								double v = atof(Buf+k+7);
								k=j;
								for(j=k+8;j<len;j++)
								{
									if(Buf[j]==' ')
										break;
								}
								Buf[j]='\0';
								double i = atof(Buf+k+8);
								k=j;
								for(j=k+7;j<len;j++)
								{
									if(Buf[j]==' ')
										break;
								}
								Buf[j]='\0';
								double t = atof(Buf+k+7);
								k=j;
								CString strTime=Buf+k+7;
								COleDateTime dt;
								dt.ParseDateTime(strTime);
								SYSTEMTIME  st;
								dt.GetAsSystemTime(st);
								CTime Time(st);
								if (n==0)
								{
									pLineSeries1->AddPoint(dt,pl);
									pLineSeries2->AddPoint(dt,pf);
									pLineSeries3->AddPoint(dt,v);
									pLineSeries4->AddPoint(dt,i);
									pLineSeries5->AddPoint(dt,t);
								}
								else if (n==1)
								{
									pLineSeries1->AddPoint(dt,pl);
								}
								else if (n==2)
								{
									pLineSeries1->AddPoint(dt,pf);
								}
								else if (n==3)
								{
									pLineSeries1->AddPoint(dt,v);
								}
								else if (n==4)
								{
									pLineSeries1->AddPoint(dt,i);
								}
								else if (n==5)
								{
									pLineSeries1->AddPoint(dt,t);
								}
								m++;
							}
							count++;
						}//while
						file.Close();
					}//if(m_count)
					else
					{
						if (days>=0&&days<5)//按小时查询
						{
							file.Open(strName,CFile::modeReadWrite | CFile::typeText);
							while(file.ReadString(Buf,99))
							{
								if (count>=2)
								{
									int len=sizeof(Buf);
									int j,k;
									for(j=0;j<len;j++)
										
									{
										if(Buf[j]==' ')
											break;
									}
									Buf[j]='\0';
									double pl = atof(Buf);
									k=j;
									for(j=k+6;j<len;j++)
									{
										if(Buf[j]==' ')
											break;
									}
									Buf[j]='\0';
									double pf = atof(Buf+k+6);
									k=j;
									for(j=k+7;j<len;j++)
									{
										if(Buf[j]==' ')
											break;
									}
									Buf[j]='\0';
									double v = atof(Buf+k+7);
									k=j;
									for(j=k+8;j<len;j++)
									{
										if(Buf[j]==' ')
											break;
									}
									Buf[j]='\0';
									double i = atof(Buf+k+8);
									k=j;
									for(j=k+7;j<len;j++)
									{
										if(Buf[j]==' ')
											break;
									}
									Buf[j]='\0';
									double t = atof(Buf+k+7);
									k=j;
									CString strTime=Buf+k+7;
									sscanf(strTime,"%d-%d-%d %d:%d:%d",&nYear,&nMonth,&nDate,&nHour,&nMin,&nSec);
									if (hour==-1)
									{
										hour = nHour;
									}
									if (hour==nHour)
									{
										m_strtime = strTime;
										if (maxpl<=pl)
											maxpl = pl;
										if (maxpf<=pf)
											maxpf = pf;
										if (maxv<=v)
											maxv = v;
										if (maxi<=i)
											maxi = i;
										if (maxt<=t)
											maxt = t;
									}
									else
									{
										hour= nHour;
										
										COleDateTime dt;
										dt.ParseDateTime(m_strtime);
										SYSTEMTIME  st;
										dt.GetAsSystemTime(st);
										CTime Time(st);
										if (n==0)
										{
											pLineSeries1->AddPoint(dt,maxpl);
											pLineSeries2->AddPoint(dt,maxpf);
											pLineSeries3->AddPoint(dt,maxv);
											pLineSeries4->AddPoint(dt,maxi);
											pLineSeries5->AddPoint(dt,maxt);
										}
										else if (n==1)
										{
											pLineSeries1->AddPoint(dt,maxpl);
										}
										else if (n==2)
										{
											pLineSeries1->AddPoint(dt,maxpf);
										}
										else if (n==3)
										{
											pLineSeries1->AddPoint(dt,maxv);
										}
										else if (n==4)
										{
											pLineSeries1->AddPoint(dt,maxi);
										}
										else if (n==5)
										{
											pLineSeries1->AddPoint(dt,maxt);
										}
										m++;
										maxpl = 0;
										maxpf = 0;
										maxv = 0;
										maxi = 0;
										maxt = 0;
										if (maxpl<=pl)
											maxpl = pl;
										if (maxpf<=pf)
											maxpf = pf;
										if (maxv<=v)
											maxv = v;
										if (maxi<=i)
											maxi = i;
										if (maxt<=t)
											maxt = t;
										
									}
							}
							count++;	
						}//while 读取文件
						file.Close();
						//读取一个文件中最后一次平均值，并画图
						
						COleDateTime dt;
						dt.ParseDateTime(m_strtime);
						SYSTEMTIME  st;
						dt.GetAsSystemTime(st);
						CTime Time(st);
						if (n==0)
						{
							pLineSeries1->AddPoint(dt,maxpl);
							pLineSeries2->AddPoint(dt,maxpf);
							pLineSeries3->AddPoint(dt,maxv);
							pLineSeries4->AddPoint(dt,maxi);
							pLineSeries5->AddPoint(dt,maxt);
						}
						else if (n==1)
						{
							pLineSeries1->AddPoint(dt,maxpl);
						}
						else if (n==2)
						{
							pLineSeries1->AddPoint(dt,maxpf);
						}
						else if (n==3)
						{
							pLineSeries1->AddPoint(dt,maxv);
						}
						else if (n==4)
						{
							pLineSeries1->AddPoint(dt,maxi);
						}
						else if (n==5)
						{
							pLineSeries1->AddPoint(dt,maxt);
						}
					}//if 0到5天的数据	
					if (days>=5&&days<=56)//按天数查询
					{
						file.Open(strName,CFile::modeReadWrite | CFile::typeText);
						while(file.ReadString(Buf,99))
						{
							if (count>=2)
							{
								int len=sizeof(Buf);
								int j,k;
								for(j=0;j<len;j++)
								{
									if(Buf[j]==' ')
										break;
								}
								Buf[j]='\0';
								double pl = atof(Buf);
								k=j;
								for(j=k+6;j<len;j++)
								{
									if(Buf[j]==' ')
										break;
								}
								Buf[j]='\0';
								double pf = atof(Buf+k+6);
								k=j;
								for(j=k+7;j<len;j++)
								{
									if(Buf[j]==' ')
										break;
								}
								Buf[j]='\0';
								double v = atof(Buf+k+7);
								k=j;
								for(j=k+8;j<len;j++)
								{
									if(Buf[j]==' ')
										break;
								}
								Buf[j]='\0';
								double i = atof(Buf+k+8);
								k=j;
								for(j=k+7;j<len;j++)
								{
									if(Buf[j]==' ')
										break;
								}
								Buf[j]='\0';
								double t = atof(Buf+k+7);
								k=j;
								CString strTime=Buf+k+7;
								m_strtime = strTime;
								if (maxpl<=pl)
									maxpl = pl;
								if (maxpf<=pf)
									maxpf = pf;
								if (maxv<=v)
									maxv = v;
								if (maxi<=i)
									maxi = i;
								if (maxt<=t)
									maxt = t;																				
								}
							count++;
						}//while
						file.Close();
						COleDateTime dt;
						dt.ParseDateTime(m_strtime);
						SYSTEMTIME  st;
						dt.GetAsSystemTime(st);
						CTime Time(st);
						
						if (n==0)
						{
							pLineSeries1->AddPoint(dt,maxpl);
							pLineSeries2->AddPoint(dt,maxpf);
							pLineSeries3->AddPoint(dt,maxv);
							pLineSeries4->AddPoint(dt,maxi);
							pLineSeries5->AddPoint(dt,maxt);
						}
						else if (n==1)
						{
							pLineSeries1->AddPoint(dt,maxpl);
						}
						else if (n==2)
						{
							pLineSeries1->AddPoint(dt,maxpf);
						}
						else if (n==3)
						{
							pLineSeries1->AddPoint(dt,maxv);
						}
						else if (n==4)
						{
							pLineSeries1->AddPoint(dt,maxi);
						}
						else if (n==5)
						{
							pLineSeries1->AddPoint(dt,maxt);
						}
						m++;
						maxpl = 0;
						maxpf = 0;
						maxv = 0;
						maxi = 0;
						maxt = 0;
					}//if 5到4个月的数据
					
				}//else
				
			}//if(a,b)
		}//if(bIsWorking)	
		 else
			break;		
    }//for(;;)
	
	if (days>56)//按月数查询
	{
		int kk = 1;//记录while中读取的次数
		
		CTimeSpan ts(1,0,0,0); // 1天 
		for (tm;tm<=TM;tm=tm+ts)//起始时间和终止时间
		{
			strtm = tm.Format("%Y-%m-%d");
			bIsWorking = finder.FindFile("*.txt");
			for (;;)
			{
				if (bIsWorking)
				{
					bIsWorking = finder.FindNextFile();
					strName = finder.GetFileTitle();
					if (strtm==strName)
					{
						strName = strName + ".txt";
						CStdioFile file;
						file.Open(strName,CFile::modeReadWrite | CFile::typeText);
						while(file.ReadString(Buf,99))
						{
							//memset(Buf,0,100);
							if (kk>=2)
							{
								int len=sizeof(Buf);
								int j,k;
								for(j=0;j<len;j++)
								{
									if(Buf[j]==' ')
										break;
								}
								Buf[j]='\0';
								double pl = atof(Buf);
								k=j;
								for(j=k+6;j<len;j++)
								{
									if(Buf[j]==' ')
										break;
								}
								Buf[j]='\0';
								double pf = atof(Buf+k+6);
								k=j;
								for(j=k+7;j<len;j++)
								{
									if(Buf[j]==' ')
										break;
								}
								Buf[j]='\0';
								double v = atof(Buf+k+7);
								k=j;
								for(j=k+8;j<len;j++)
								{
									if(Buf[j]==' ')
										break;
								}
								Buf[j]='\0';
								double i = atof(Buf+k+8);
								k=j;
								for(j=k+7;j<len;j++)
								{
									if(Buf[j]==' ')
										break;
								}
								Buf[j]='\0';
								double t = atof(Buf+k+7);
								k=j;
								CString strTime=Buf+k+7;
								sscanf(strTime,"%d-%d-%d %d:%d:%d",&nYear,&nMonth,&nDate,&nHour,&nMin,&nSec);
								if (month == -1)
								{
									month = nMonth;
								}
								if (month == nMonth)
								{
									m_strTime = strTime;
									if (maxpl<=pl)
										maxpl = pl;
									if (maxpf<=pf)
										maxpf = pf;
									if (maxv<=v)
										maxv = v;
									if (maxi<=i)
										maxi = i;
									if (maxt<=t)
										maxt = t;
								}
								else
								{
									month = nMonth;
									COleDateTime dt;
									dt.ParseDateTime(m_strTime);
									SYSTEMTIME  st;
									dt.GetAsSystemTime(st);
									CTime Time(st);
									if (n==0)
									{
										pLineSeries1->AddPoint(dt,maxpl);
										pLineSeries2->AddPoint(dt,maxpf);
										pLineSeries3->AddPoint(dt,maxv);
										pLineSeries4->AddPoint(dt,maxi);
										pLineSeries5->AddPoint(dt,maxt);
									}
									else if (n==1)
									{
										pLineSeries1->AddPoint(dt,maxpl);
									}
									else if (n==2)
									{
										pLineSeries1->AddPoint(dt,maxpf);
									}
									else if (n==3)
									{
										pLineSeries1->AddPoint(dt,maxv);
									}
									else if (n==4)
									{
										pLineSeries1->AddPoint(dt,maxi);
									}
									else if (n==5)
									{
										pLineSeries1->AddPoint(dt,maxt);
									}
									m++;
									maxpl = 0;
									maxpf = 0;
									maxv = 0;
									maxi = 0;
									maxt = 0;
									if (maxpl<=pl)
										maxpl = pl;
									if (maxpf<=pf)
										maxpf = pf;
									if (maxv<=v)
										maxv = v;
									if (maxi<=i)
										maxi = i;
									if (maxt<=t)
										maxt = t;
									
								}
							}
							kk++;
                     }//while
					 file.Close();
					 kk = 0;
					}
				}
				else
					break;
			}
		}
	}//if(大于56)
	if (days>56)//显示最后一次查询的数据
    {
		COleDateTime dt;
		dt.ParseDateTime(m_strTime);
		SYSTEMTIME  st;
		dt.GetAsSystemTime(st);
		CTime Time(st);
		if (n==0)
		{
			pLineSeries1->AddPoint(dt,maxpl);
			pLineSeries2->AddPoint(dt,maxpf);
			pLineSeries3->AddPoint(dt,maxv);
			pLineSeries4->AddPoint(dt,maxi);
			pLineSeries5->AddPoint(dt,maxt);
		}
		else if (n==1)
		{
			pLineSeries1->AddPoint(dt,maxpl);
		}
		else if (n==2)
		{
			pLineSeries1->AddPoint(dt,maxpf);
		}
		else if (n==3)
		{
			pLineSeries1->AddPoint(dt,maxv);
		}
		else if (n==4)
		{
			pLineSeries1->AddPoint(dt,maxi);
		}
		else if (n==5)
		{
			pLineSeries1->AddPoint(dt,maxt);
		}
    }
		break;
	case 2://按最小值查询
        for (;;)
		{
			if (bIsWorking)
			{
				bIsWorking = finder.FindNextFile();
				strName = finder.GetFileTitle();
				int a = strName.CompareNoCase(strtm);
				int b = strName.CompareNoCase(strTM);
				
				if (a>=0&&b<=0)
				{
					strName = strName + ".txt";
					CStdioFile file;
					if(!file.Open(strName,CFile::modeReadWrite | CFile::typeText))
					{
						MessageBox("您选择的时间段没有数据信息，请重新设置查询时间","提示");
						return;
					}
					int count = 1;
					char Buf[100];
					memset(Buf,0,100);
					while (file.ReadString(Buf,99))//读取每个文件的数据的条数
					{
						m_count++;
					}
					file.Close();
					memset(Buf,0,100);
					if (m_count<=21)
					{
						file.Open(strName,CFile::modeReadWrite | CFile::typeText);
						while(file.ReadString(Buf,99))
						{
							if (count>=2)
							{
								int len=sizeof(Buf);
								int j,k;
								for(j=0;j<len;j++)
								{
									if(Buf[j]==' ')
										break;
								}
								Buf[j]='\0';
								double pl = atof(Buf);
								k=j;
								for(j=k+6;j<len;j++)
								{
									if(Buf[j]==' ')
										break;
								}
								Buf[j]='\0';
								double pf = atof(Buf+k+6);
								k=j;
								for(j=k+7;j<len;j++)
								{
									if(Buf[j]==' ')
										break;
								}
								Buf[j]='\0';
								double v = atof(Buf+k+7);
								k=j;
								for(j=k+8;j<len;j++)
								{
									if(Buf[j]==' ')
										break;
								}
								Buf[j]='\0';
								double i = atof(Buf+k+8);
								k=j;
								for(j=k+7;j<len;j++)
								{
									if(Buf[j]==' ')
										break;
								}
								Buf[j]='\0';
								double t = atof(Buf+k+7);
								k=j;
								CString strTime=Buf+k+7;
								COleDateTime dt;
								dt.ParseDateTime(strTime);
								SYSTEMTIME  st;
								dt.GetAsSystemTime(st);
								CTime Time(st);
								if (n==0)
								{
									pLineSeries1->AddPoint(dt,pl);
									pLineSeries2->AddPoint(dt,pf);
									pLineSeries3->AddPoint(dt,v);
									pLineSeries4->AddPoint(dt,i);
									pLineSeries5->AddPoint(dt,t);
								}
								else if (n==1)
								{
									pLineSeries1->AddPoint(dt,pl);
								}
								else if (n==2)
								{
									pLineSeries1->AddPoint(dt,pf);
								}
								else if (n==3)
								{
									pLineSeries1->AddPoint(dt,v);
								}
								else if (n==4)
								{
									pLineSeries1->AddPoint(dt,i);
								}
								else if (n==5)
								{
									pLineSeries1->AddPoint(dt,t);
								}
								m++;
							}
							count++;
						}//while
						file.Close();
					}//if(m_count)
					else
					{
						if (days>=0&&days<5)//按小时查询
						{
							file.Open(strName,CFile::modeReadWrite | CFile::typeText);
							while(file.ReadString(Buf,99))
							{
								if (count>=2)
								{
									int len=sizeof(Buf);
									int j,k;
									for(j=0;j<len;j++)
										
									{
										if(Buf[j]==' ')
											break;
									}
									Buf[j]='\0';
									double pl = atof(Buf);
									k=j;
									for(j=k+6;j<len;j++)
									{
										if(Buf[j]==' ')
											break;
									}
									Buf[j]='\0';
									double pf = atof(Buf+k+6);
									k=j;
									for(j=k+7;j<len;j++)
									{
										if(Buf[j]==' ')
											break;
									}
									Buf[j]='\0';
									double v = atof(Buf+k+7);
									k=j;
									for(j=k+8;j<len;j++)
									{
										if(Buf[j]==' ')
											break;
									}
									Buf[j]='\0';
									double i = atof(Buf+k+8);
									k=j;
									for(j=k+7;j<len;j++)
									{
										if(Buf[j]==' ')
											break;
									}
									Buf[j]='\0';
									double t = atof(Buf+k+7);
									k=j;
									CString strTime=Buf+k+7;
									sscanf(strTime,"%d-%d-%d %d:%d:%d",&nYear,&nMonth,&nDate,&nHour,&nMin,&nSec);
									if (hour==-1)
									{
										hour = nHour;
									}
									if (hour==nHour)
									{
										m_strtime = strTime;
										if (minpl>=pl)
											minpl = pl;
										if (minpf>=pf)
											minpf = pf;
										if (minv>=v)
											minv = v;
										if (mini>=i)
											mini = i;
										if (mint>=t)
											mint = t;
									}
									else
									{
										hour= nHour;
										COleDateTime dt;
										dt.ParseDateTime(m_strtime);
										SYSTEMTIME  st;
										dt.GetAsSystemTime(st);
										CTime Time(st);
										if (n==0)
										{
											pLineSeries1->AddPoint(dt,minpl);
											pLineSeries2->AddPoint(dt,minpf);
											pLineSeries3->AddPoint(dt,minv);
											pLineSeries4->AddPoint(dt,mini);
											pLineSeries5->AddPoint(dt,mint);
										}
										else if (n==1)
										{
											pLineSeries1->AddPoint(dt,minpl);
										}
										else if (n==2)
										{
											pLineSeries1->AddPoint(dt,minpf);
										}
										else if (n==3)
										{
											pLineSeries1->AddPoint(dt,minv);
										}
										else if (n==4)
										{
											pLineSeries1->AddPoint(dt,mini);
										}
										else if (n==5)
										{
											pLineSeries1->AddPoint(dt,mint);
										}
										m++;
										minpl = 10000;
										minpf = 10000;
										minv = 10000;
										mini = 10000;
										mint = 10000;
										if (minpl>=pl)
											minpl = pl;
										if (minpf>=pf)
											minpf = pf;
										if (minv>=v)
											minv = v;
										if (mini>=i)
											mini = i;
										if (mint>=t)
											mint = t;
									}
							}
							count++;	
						}//while 读取文件
						file.Close();
						//读取一个文件中最后一次平均值，并画图
						
						COleDateTime dt;
						dt.ParseDateTime(m_strtime);
						SYSTEMTIME  st;
						dt.GetAsSystemTime(st);
						CTime Time(st);
						if (n==0)
						{
							pLineSeries1->AddPoint(dt,minpl);
							pLineSeries2->AddPoint(dt,minpf);
							pLineSeries3->AddPoint(dt,minv);
							pLineSeries4->AddPoint(dt,mini);
							pLineSeries5->AddPoint(dt,mint);
						}
						else if (n==1)
						{
							pLineSeries1->AddPoint(dt,minpl);
						}
						else if (n==2)
						{
							pLineSeries1->AddPoint(dt,minpf);
						}
						else if (n==3)
						{
							pLineSeries1->AddPoint(dt,minv);
						}
						else if (n==4)
						{
							pLineSeries1->AddPoint(dt,mini);
						}
						else if (n==5)
						{
							pLineSeries1->AddPoint(dt,mint);
						}
					}//if 0到5天的数据	
					if (days>=5&&days<=56)//按天数查询
					{
						file.Open(strName,CFile::modeReadWrite | CFile::typeText);
						while(file.ReadString(Buf,99))
						{
							if (count>=2)
							{
								int len=sizeof(Buf);
								int j,k;
								for(j=0;j<len;j++)
								{
									if(Buf[j]==' ')
										break;
								}
								Buf[j]='\0';
								double pl = atof(Buf);
								k=j;
								for(j=k+6;j<len;j++)
								{
									if(Buf[j]==' ')
										break;
								}
								Buf[j]='\0';
								double pf = atof(Buf+k+6);
								k=j;
								for(j=k+7;j<len;j++)
								{
									if(Buf[j]==' ')
										break;
								}
								Buf[j]='\0';
								double v = atof(Buf+k+7);
								k=j;
								for(j=k+8;j<len;j++)
								{
									if(Buf[j]==' ')
										break;
								}
								Buf[j]='\0';
								double i = atof(Buf+k+8);
								k=j;
								for(j=k+7;j<len;j++)
								{
									if(Buf[j]==' ')
										break;
								}
								Buf[j]='\0';
								double t = atof(Buf+k+7);
								k=j;
								CString strTime=Buf+k+7;
								m_strtime = strTime;
								if (minpl>=pl)
									minpl = pl;
								if (minpf>=pf)
									minpf = pf;
								if (minv>=v)
									minv = v;
								if (mini>=i)
									mini = i;
								if (mint>=t)
									mint = t;
								
								
							}
							count++;
						}//while
						file.Close();
						COleDateTime dt;
						dt.ParseDateTime(m_strtime);
						SYSTEMTIME  st;
						dt.GetAsSystemTime(st);
						CTime Time(st);
						if (n==0)
						{
							pLineSeries1->AddPoint(dt,minpl);
							pLineSeries2->AddPoint(dt,minpf);
							pLineSeries3->AddPoint(dt,minv);
							pLineSeries4->AddPoint(dt,mini);
							pLineSeries5->AddPoint(dt,mint);
						}
						else if (n==1)
						{
							pLineSeries1->AddPoint(dt,minpl);
						}
						else if (n==2)
						{
							pLineSeries1->AddPoint(dt,minpf);
						}
						else if (n==3)
						{
							pLineSeries1->AddPoint(dt,minv);
						}
						else if (n==4)
						{
							pLineSeries1->AddPoint(dt,mini);
						}
						else if (n==5)
						{
							pLineSeries1->AddPoint(dt,mint);
						}
						m++;
						minpl = 10000;
						minpf = 10000;
						minv = 10000;
						mini = 10000;
						mint = 10000;
					}//if 5到4个月的数据
					
				}//else
				
			}//if(a,b)
		}//if(bIsWorking)	
		 else
			break;		
    }//for(;;)
	
	if (days>56)//按月数查询
	{
		int kk = 1;//记录while中读取的次数
		
		CTimeSpan ts(1,0,0,0); // 1天 
		for (tm;tm<=TM;tm=tm+ts)//起始时间和终止时间
		{
			strtm = tm.Format("%Y-%m-%d");
			bIsWorking = finder.FindFile("*.txt");
			for (;;)
			{
				if (bIsWorking)
				{
					bIsWorking = finder.FindNextFile();
					strName = finder.GetFileTitle();
					if (strtm==strName)
					{
						strName = strName + ".txt";
						CStdioFile file;
						file.Open(strName,CFile::modeReadWrite | CFile::typeText);
						while(file.ReadString(Buf,99))
						{
							//memset(Buf,0,100);
							if (kk>=2)
							{
								int len=sizeof(Buf);
								int j,k;
								for(j=0;j<len;j++)
								{
									if(Buf[j]==' ')
										break;
								}
								Buf[j]='\0';
								double pl = atof(Buf);
								k=j;
								for(j=k+6;j<len;j++)
								{
									if(Buf[j]==' ')
										break;
								}
								Buf[j]='\0';
								double pf = atof(Buf+k+6);
								k=j;
								for(j=k+7;j<len;j++)
								{
									if(Buf[j]==' ')
										break;
								}
								Buf[j]='\0';
								double v = atof(Buf+k+7);
								k=j;
								for(j=k+8;j<len;j++)
								{
									if(Buf[j]==' ')
										break;
								}
								Buf[j]='\0';
								double i = atof(Buf+k+8);
								k=j;
								for(j=k+7;j<len;j++)
								{
									if(Buf[j]==' ')
										break;
								}
								Buf[j]='\0';
								double t = atof(Buf+k+7);
								k=j;
								CString strTime=Buf+k+7;
								sscanf(strTime,"%d-%d-%d %d:%d:%d",&nYear,&nMonth,&nDate,&nHour,&nMin,&nSec);
								if (month == -1)
								{
									month = nMonth;
								}
								if (month == nMonth)
								{
									m_strTime = strTime;
									if (minpl>=pl)
										minpl = pl;
									if (minpf>=pf)
										minpf = pf;
									if (minv>=v)
										minv = v;
									if (mini>=i)
										mini = i;
									if (mint>=t)
										mint = t;
								}
								else
								{
									month = nMonth;
									
									COleDateTime dt;
									dt.ParseDateTime(m_strTime);
									SYSTEMTIME  st;
									dt.GetAsSystemTime(st);
									CTime Time(st);
									if (n==0)
									{
										pLineSeries1->AddPoint(dt,minpl);
										pLineSeries2->AddPoint(dt,minpf);
										pLineSeries3->AddPoint(dt,minv);
										pLineSeries4->AddPoint(dt,mini);
										pLineSeries5->AddPoint(dt,mint);
									}
									else if (n==1)
									{
										pLineSeries1->AddPoint(dt,minpl);
									}
									else if (n==2)
									{
										pLineSeries1->AddPoint(dt,minpf);
									}
									else if (n==3)
									{
										pLineSeries1->AddPoint(dt,minv);
									}
									else if (n==4)
									{
										pLineSeries1->AddPoint(dt,mini);
									}
									else if (n==5)
									{
										pLineSeries1->AddPoint(dt,mint);
									}
									m++;
									minpl = 10000;
									minpf = 10000;
									minv = 10000;
									mini = 10000;
									mint = 10000;
									if (minpl>=pl)
										minpl = pl;
									if (minpf>=pf)
										minpf = pf;
									if (minv>=v)
										minv = v;
									if (mini>=i)
										mini = i;
									if (mint>=t)
										mint = t;
								}
							}
							kk++;
                     }//while
					 file.Close();
					 kk = 0;
					}
				}
				else
					break;
			}
		}
	}//if(大于56)
	if (days>56)
    {
		COleDateTime dt;
		dt.ParseDateTime(m_strTime);
		SYSTEMTIME  st;
		dt.GetAsSystemTime(st);
		CTime Time(st);
		if (n==0)
		{
			pLineSeries1->AddPoint(dt,minpl);
			pLineSeries2->AddPoint(dt,minpf);
			pLineSeries3->AddPoint(dt,minv);
			pLineSeries4->AddPoint(dt,mini);
			pLineSeries5->AddPoint(dt,mint);
		}
		else if (n==1)
		{
			pLineSeries1->AddPoint(dt,minpl);
		}
		else if (n==2)
		{
			pLineSeries1->AddPoint(dt,minpf);
		}
		else if (n==3)
		{
			pLineSeries1->AddPoint(dt,minv);
		}
		else if (n==4)
		{
			pLineSeries1->AddPoint(dt,mini);
		}
		else if (n==5)
		{
			pLineSeries1->AddPoint(dt,mint);
		}
    }
		break;
	}

	if (m==0)
	{
		
		if (n==0)
		{
			MessageBox("您选择的时间段没有数据信息，请重新设置查询时间","提示");
			m_ChartCtrl.RemoveAllSeries();
		}
		if (n==1)
		{
			MessageBox("您选择的时间段没有数据信息，请重新设置查询时间","提示");
			m_ChartCtrl.RemoveAllSeries();
		}
		if (n==2)
		{
			MessageBox("您选择的时间段没有数据信息，请重新设置查询时间","提示");
			m_ChartCtrl.RemoveAllSeries();
		}
		if (n==3)
		{
			MessageBox("您选择的时间段没有数据信息，请重新设置查询时间","提示");
			m_ChartCtrl.RemoveAllSeries();
		}
		if (n==4)
		{
			MessageBox("您选择的时间段没有数据信息，请重新设置查询时间","提示");
			m_ChartCtrl.RemoveAllSeries();
		}
		if (n==5)
		{
			MessageBox("您选择的时间段没有数据信息，请重新设置查询时间","提示");
			m_ChartCtrl.RemoveAllSeries();
		}
		
		return;
	}
	#endif
    
	return;
#endif
}

void CComCtrlDlg::OnBtnpl() 
{

	Draw(1);
}

void CComCtrlDlg::OnBtnpf() 
{
	Draw(2);
}

void CComCtrlDlg::OnBtnv() 
{
	Draw(3);
}

void CComCtrlDlg::OnBtni() 
{
	Draw(4);	
}

void CComCtrlDlg::OnBtnt() 
{
	Draw(5);
}



void CComCtrlDlg::OnStnClickedStatic1()
{
	// TODO: 在此添加控件通知处理程序代码
}

int x=1,y=1;
int y2=4;
COleDateTime dt(2006,1,1,0,0,0);
void CComCtrlDlg::OnTimer(UINT_PTR nIDEvent)
{
	CString str_temp1,str_temp2;
	COleDateTimeSpan  timespan( 0, 4, 0, 0 );
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	switch (nIDEvent)
	{
	case 1:
		KillTimer(1);
		temp++;
		O2++;
		str_temp1.Format(_T("%d"), temp);
		GetDlgItem(IDC_TEMP_NO)->SetWindowText(str_temp1);
		str_temp2.Format(_T("%d"), O2);
		GetDlgItem(IDC_O2_NO)->SetWindowText(str_temp2);
		SetTimer(1,500,NULL);
		break;
	case 3:
		KillTimer(3);
		pLineSeries1->AddPoint(dt,y);
		pLineSeries2->AddPoint(dt,y2);
        dt=dt + timespan;
		y++;
		y2++;
		SetTimer(3,1000,NULL);

	default:
		break;
	}
	CDialog::OnTimer(nIDEvent);
}


HBRUSH CComCtrlDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	
	switch (pWnd->GetDlgCtrlID()) 
	{ 
//针对ID为IDC_EDIT6控件进行同样的设置
#if 1
		case IDC_TITLE: 
		case IDC_AUTHOR:
			{
				pDC->SetBkMode(TRANSPARENT);
				pDC->SetTextColor(RGB(0,0,0));
				//pWnd->SetFont(cFont);
				HBRUSH B = CreateSolidBrush(RGB(240,240,240));
				return (HBRUSH) B;
			}
		case IDC_CHECK2:
			{
				pDC->SetBkMode(TRANSPARENT);
				pDC->SetTextColor(RGB(255,0,0));
				//pWnd->SetFont(cFont);
				HBRUSH B = CreateSolidBrush(RGB(240,240,240));
				return (HBRUSH) B;
			}
		case IDC_CHECK3:
			{
				pDC->SetBkMode(TRANSPARENT);
				pDC->SetTextColor(RGB(0,255,0));
				//pWnd->SetFont(cFont);
				HBRUSH B = CreateSolidBrush(RGB(240,240,240));
				return (HBRUSH) B;
			}
#endif
		default:
		return CDialog::OnCtlColor(pDC, pWnd, nCtlColor);
		HBRUSH hbr = CDialog::OnCtlColor(pDC, pWnd, nCtlColor);
	 if(nCtlColor==CTLCOLOR_DLG)

         {

              return   m_bkBrush; //返回刚才创建的背景刷子

         }
	}
}


void CComCtrlDlg::OnBnClickedButton6()
{
	
   //this->ShowWindow(0);
	//this->OnCancel();
	PassDlg dlg2; 
    dlg2.DoModal();
	//PassDlg dlg;
	//m_pMainWnd = &dlg;
	//int nResponse = dlg.DoModal();
	//this->OnOK();
	//this->OnCancel();
	// TODO: 在此添加控件通知处理程序代码
}


void CComCtrlDlg::OnBnClickedButton8()
{
	Datasearch dlg3; 
    dlg3.DoModal();
	//this->OnCancel();
	// TODO: 在此添加控件通知处理程序代码
}


void CComCtrlDlg::OnBnClickedButton7()
{
	// TODO: 在此添加控件通知处理程序代码
	manual dlg4; 
    dlg4.DoModal();
//	this->OnCancel();
}


void CComCtrlDlg::OnBnClickedButton1()
{
	
}


void CComCtrlDlg::OnBnClickedSetpara()
{
	// TODO: 在此添加控件通知处理程序代码
}

void CComCtrlDlg::resize()
{
	float fsp[2];
	POINT Newp; //获取现在对话框的大小
	CRect recta;    
	GetClientRect(&recta);     //取客户区大小  
	Newp.x=recta.right-recta.left;
	Newp.y=recta.bottom-recta.top;
	fsp[0]=(float)Newp.x/Old.x;
	fsp[1]=(float)Newp.y/Old.y;
	CRect Rect;
	int woc;
	CPoint OldTLPoint,TLPoint; //左上角
	CPoint OldBRPoint,BRPoint; //右下角
	HWND  hwndChild=::GetWindow(m_hWnd,GW_CHILD);  //列出所有控件  
	while(hwndChild)    
	{    
		woc=::GetDlgCtrlID(hwndChild);//取得ID
		GetDlgItem(woc)->GetWindowRect(Rect);  
		ScreenToClient(Rect);  
		OldTLPoint = Rect.TopLeft();  
		TLPoint.x = long(OldTLPoint.x*fsp[0]);  
		TLPoint.y = long(OldTLPoint.y*fsp[1]);  
		OldBRPoint = Rect.BottomRight();  
		BRPoint.x = long(OldBRPoint.x *fsp[0]);  
		BRPoint.y = long(OldBRPoint.y *fsp[1]);  
		Rect.SetRect(TLPoint,BRPoint);  
		GetDlgItem(woc)->MoveWindow(Rect,TRUE);
		hwndChild=::GetWindow(hwndChild, GW_HWNDNEXT);    
	}
	Old=Newp;

}


void CComCtrlDlg::OnSize(UINT nType, int cx, int cy)
{
	CDialog::OnSize(nType, cx, cy);
	
	// TODO: Add your message handler code here
	if(nType==SIZE_RESTORED||nType==SIZE_MAXIMIZED)
	{
		resize();
	}
}


void CComCtrlDlg::OnSizing(UINT fwSide, LPRECT pRect)
{
	//CDialog::OnSizing(fwSide, pRect);

	// TODO: 在此处添加消息处理程序代码
}
void CComCtrlDlg::OnBnClickedButton4()
{
	PARASET dlg4; 
    dlg4.DoModal();
	// TODO: 在此添加控件通知处理程序代码
}


void CComCtrlDlg::OnBnClickedButton9()
{
	// TODO: 在此添加控件通知处理程序代码
	TEST dlg4; 
    dlg4.DoModal();
}


void CComCtrlDlg::OnBnClickedButton5()
{
	//Draw(1);
	// TODO: 在此添加控件通知处理程序代码
}


void CComCtrlDlg::OnBnClickedButton15()
{
	// TODO: 在此添加控件通知处理程序代码
	
	SetTimer(3,1000,NULL);
	//MessageBox(_T("test"));
}


void CComCtrlDlg::OnBnClickedButton10()
{
	SetTimer(3,500,NULL);
	// TODO: 在此添加控件通知处理程序代码
}


void CComCtrlDlg::OnBnClickedButton13()
{
	//MessageBox(_T("TEST"));
	// TODO: 在此添加控件通知处理程序代码
	if (pLineSeries1->IsVisible())
	{
		pLineSeries1->SetVisible(false);
	}
	else
		pLineSeries1->SetVisible(true);
}


void CComCtrlDlg::OnBnClickedCheck2()
{
	if (pLineSeries1->IsVisible())
	{
		pLineSeries1->SetVisible(false);
	}
	else
		pLineSeries1->SetVisible(true);
	// TODO: 在此添加控件通知处理程序代码
}


void CComCtrlDlg::OnBnClickedCheck3()
{
	if (pLineSeries2->IsVisible())
	{
		pLineSeries2->SetVisible(false);
	}
	else
		pLineSeries2->SetVisible(true);
}


void CComCtrlDlg::OnBnClickedButton16()
{
	// TODO: 在此添加控件通知处理程序代码
	
}


void CComCtrlDlg::OnBnClickedButton17()
{
	// TODO: 在此添加控件通知处理程序代码
//CComCtrlDlg:EnableMouseInPointer(false);
	//EnableMouseNotifications(false,false);
	CCustomMouseListener * m_pMouseListener = new CCustomMouseListener();
	pLineSeries1->RegisterMouseListener((CChartSeriesMouseListener<SChartXYPoint>*)m_pMouseListener);
	//delete(m_pMouseListener);
	KillTimer(3);
}


void CComCtrlDlg::OnBnClickedCheck1()

{
	CButton *bt = (CButton *)GetDlgItem(IDC_CHECK1);
    if(bt->GetCheck())
	{
		((CButton *)GetDlgItem(IDC_CHECK4))->SetCheck(false);
	SetTimer(3,1000,NULL);
	}
	// TODO: 在此添加控件通知处理程序代码
}


void CComCtrlDlg::OnBnClickedCheck4()

{
	IsSave dlg6; 
    dlg6.DoModal();
	CButton *bt = (CButton *)GetDlgItem(IDC_CHECK4);
    if(bt->GetCheck())
	{
		((CButton *)GetDlgItem(IDC_CHECK1))->SetCheck(false);
		KillTimer(3);
	}
	// TODO: 在此添加控件通知处理程序代码
}




void CComCtrlDlg::OnBnClickedSave()
{
	DataSave dlg5; 
    dlg5.DoModal();
	// TODO: 在此添加控件通知处理程序代码
}
