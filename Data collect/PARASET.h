#pragma once


// PARASET 对话框

class PARASET : public CDialog
{
	DECLARE_DYNAMIC(PARASET)

public:
	PARASET(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~PARASET();

// 对话框数据
	enum { IDD = IDD_DIALOG6 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedSaveSet();
};
