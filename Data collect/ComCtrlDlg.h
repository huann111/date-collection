// ComCtrlDlg.h : header file
//
//{{AFX_INCLUDES()

//}}AFX_INCLUDES


#if !defined(AFX_EASYSIZEDEMODLG_H__8E227342_30AC_44D9_B83A_52321DCD07CE__INCLUDED_)
#define AFX_EASYSIZEDEMODLG_H__8E227342_30AC_44D9_B83A_52321DCD07CE__INCLUDED_

#if !defined(AFX_COMCTRLDLG_H__8E0BD8FF_3478_44F2_BCFF_63D8EE1FE4DE__INCLUDED_)
#define AFX_COMCTRLDLG_H__8E0BD8FF_3478_44F2_BCFF_63D8EE1FE4DE__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include "ChartCtrl_source/ChartCtrl.h"

#include "ReportCtrl.h"


/////////////////////////////////////////////////////////////////////////////
// CComCtrlDlg dialog

class CComCtrlDlg : public CDialog
{
// Construction
	//DECLARE_EASYSIZE
public:
	
	CComCtrlDlg(CWnd* pParent = NULL);	// standard constructor
	~CComCtrlDlg();
	POINT		Old;
		void		resize();
// Dialog Data
	//{{AFX_DATA(CComCtrlDlg)
	enum { IDD = IDD_COMCTRL_DIALOG };
	CReportCtrl	m_List2;
	CReportCtrl	m_List1;
	CTime	m_defaultDate;
	CDateTimeCtrl	m_PosTimeCtrl;
	CDateTimeCtrl	m_PreTimeCtrl;
	CListCtrl	m_ListCtrl;
	CComboBox	m_choice;
	int		m_CheckType;
	
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CComCtrlDlg)
	public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;
    CString strCom1;      //地点1对应的串口号
    CString strCom2;      //地点2对应的串口号
	int nCT1;             //匝数比1
	int nCT2;             //匝数比2
	int nCP1;             //电容组数1
	int nCP2;             //电容组数2
	

    CChartCtrl m_ChartCtrl;  //图形类
	//CChartScrollBar m_ChartScrollBar;
	HANDLE m_hHandle1; //发送命令句柄1
	HANDLE m_hHandle2; //发送命令句柄2
	HANDLE m_hRecvHandle1;  //接收线程1句柄
	HANDLE m_hRecvHandle2;  //接收线程2句柄
	HANDLE m_hCheckHandle1; //查询数据句柄
	HANDLE m_hCheckHandle2; //查询曲线句柄

	void PrintString( CString strPrint );
	void Draw(int n);
	void CreateAllDirectories(TCHAR* filePath);  //添加多级目录文件名
	// Generated message map functions
	//{{AFX_MSG(CComCtrlDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnBtnOpen();
	afx_msg void OnBtnManualsend();
	afx_msg void OnBtnClear();
	afx_msg void OnBtnCheck();
	afx_msg void OnBtnSend();
	afx_msg void OnBtnZt();
	afx_msg void OnBtnPc();
	afx_msg void OnBtnConfigdata();
	afx_msg LRESULT OnShowRecv(WPARAM wParam, LPARAM lParam);   //处理收到的数据
	afx_msg LRESULT OnShowResearch( WPARAM wParam, LPARAM lParam );  //处理查询的结果
	afx_msg LRESULT OnShowMessage(WPARAM wParam, LPARAM lParam);   //处理线程中的消息
	afx_msg LRESULT OnShowMessageA(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnShowXY(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnShowXY1(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnShowXYDIS(WPARAM wParam, LPARAM lParam);
		
	afx_msg void OnBtnpl();
	afx_msg void OnBtnpf();
	afx_msg void OnBtnv();
	afx_msg void OnBtni();
	afx_msg void OnBtnt();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnSizing(UINT fwSide, LPRECT pRect);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnLvnItemchangedList1(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnStnClickedStatic1();
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg void OnBnClickedButton6();
	afx_msg void OnBnClickedButton8();
	afx_msg void OnBnClickedButton7();
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedSetpara();
	
	afx_msg void OnBnClickedButton4();
	afx_msg void OnBnClickedButton9();
	afx_msg void OnBnClickedButton5();
	afx_msg void OnBnClickedButton15();
	afx_msg void OnBnClickedButton10();
	afx_msg void OnBnClickedButton13();
	afx_msg void OnBnClickedCheck2();
	afx_msg void OnBnClickedCheck3();
	afx_msg void OnBnClickedButton16();
	afx_msg void OnBnClickedButton17();
	afx_msg void OnBnClickedCheck1();
	afx_msg void OnBnClickedCheck4();
	afx_msg void OnEnChangeEdit6();
	afx_msg void OnBnClickedSave();
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_COMCTRLDLG_H__8E0BD8FF_3478_44F2_BCFF_63D8EE1FE4DE__INCLUDED_)
#endif