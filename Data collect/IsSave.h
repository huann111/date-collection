#pragma once


// IsSave 对话框

class IsSave : public CDialog
{
	DECLARE_DYNAMIC(IsSave)

public:
	IsSave(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~IsSave();

// 对话框数据
	enum { IDD = IDD_DIALOG9 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
};
