// ComCtrl.h : main header file for the COMCTRL application
//

#if !defined(AFX_COMCTRL_H__37DFE9AF_68B4_4BF8_9283_0B2B5B851844__INCLUDED_)
#define AFX_COMCTRL_H__37DFE9AF_68B4_4BF8_9283_0B2B5B851844__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols
#include "PassDlg.h"

/////////////////////////////////////////////////////////////////////////////
// CComCtrlApp:
// See ComCtrl.cpp for the implementation of this class
//

class CComCtrlApp : public CWinApp
{
public:
	CTime	m_defaultDate;
	CComCtrlApp();
    PassDlg  passdlg;
	BOOL fQuit;
// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CComCtrlApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CComCtrlApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_COMCTRL_H__37DFE9AF_68B4_4BF8_9283_0B2B5B851844__INCLUDED_)
