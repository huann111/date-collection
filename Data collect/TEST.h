#pragma once


// TEST 对话框

class TEST : public CDialog
{
	DECLARE_DYNAMIC(TEST)

public:
	TEST(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~TEST();

// 对话框数据
	enum { IDD = IDD_DIALOG7 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
};
