#if !defined(AFX_CONFIGDLG_H__892C3F54_D001_4DF0_9551_CD1F6E6DE607__INCLUDED_)
#define AFX_CONFIGDLG_H__892C3F54_D001_4DF0_9551_CD1F6E6DE607__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ConfigDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CConfigDlg dialog

class CConfigDlg : public CDialog
{
// Construction
public:
	CConfigDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CConfigDlg)
	enum { IDD = IDD_DIALOG1 };
	CString	m_strcomm1;
	CString	m_strcomm2;
	int		m_nCT1;
	int		m_nCT2;
	CString	m_strAdd1;
	CString	m_strAdd2;
	int		m_nCP1;
	int		m_nCP2;
	float	m_nTime;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CConfigDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL
private:
	void GetConfig();   //µ√µΩ≈‰÷√

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CConfigDlg)
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CONFIGDLG_H__892C3F54_D001_4DF0_9551_CD1F6E6DE607__INCLUDED_)
