#pragma once


// manual 对话框

class manual : public CDialog
{
	DECLARE_DYNAMIC(manual)

public:
	manual(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~manual();

// 对话框数据
	enum { IDD = IDD_DIALOG5 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
};
