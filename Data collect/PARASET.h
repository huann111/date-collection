#pragma once


// PARASET �Ի���

class PARASET : public CDialog
{
	DECLARE_DYNAMIC(PARASET)

public:
	PARASET(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~PARASET();

// �Ի�������
	enum { IDD = IDD_DIALOG6 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedSaveSet();
};
