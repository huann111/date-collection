#if !defined(AFX_PASSDLG_H__DE58699F_88CF_4CF6_A130_FD3F162E9465__INCLUDED_)
#define AFX_PASSDLG_H__DE58699F_88CF_4CF6_A130_FD3F162E9465__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// PassDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// PassDlg dialog

class PassDlg : public CDialog
{
// Construction
public:
	PassDlg(CWnd* pParent = NULL);   // standard constructor
// Dialog Data
	//{{AFX_DATA(PassDlg)
	enum { IDD = IDD_DIALOG2 };
	CString	m_Pass;
	CString	m_Name;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(PassDlg)
	public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(PassDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnBtnChange();
	virtual void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
public:
	
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PASSDLG_H__DE58699F_88CF_4CF6_A130_FD3F162E9465__INCLUDED_)
