#pragma once


// TEST �Ի���

class TEST : public CDialog
{
	DECLARE_DYNAMIC(TEST)

public:
	TEST(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~TEST();

// �Ի�������
	enum { IDD = IDD_DIALOG7 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
};
