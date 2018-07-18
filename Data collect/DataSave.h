#pragma once


// DataSave 对话框

class DataSave : public CDialog
{
	DECLARE_DYNAMIC(DataSave)

public:
	DataSave(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~DataSave();

// 对话框数据
	enum { IDD = IDD_DIALOG8 };
	CString	m_strCurPath;
	CString	m_strSendFilePathName;
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButton1();
	virtual BOOL OnInitDialog();
};
