#pragma once


// IsSave �Ի���

class IsSave : public CDialog
{
	DECLARE_DYNAMIC(IsSave)

public:
	IsSave(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~IsSave();

// �Ի�������
	enum { IDD = IDD_DIALOG9 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
};
