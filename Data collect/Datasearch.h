#pragma once


// Datasearch 对话框

class Datasearch : public CDialog
{
	DECLARE_DYNAMIC(Datasearch)

public:
	Datasearch(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~Datasearch();

// 对话框数据
	enum { IDD = IDD_DIALOG4 };
	CTime	m_defaultDate;
	CDateTimeCtrl	m_PosTimeCtrl;

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
};
