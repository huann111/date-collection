#pragma once


// manual �Ի���

class manual : public CDialog
{
	DECLARE_DYNAMIC(manual)

public:
	manual(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~manual();

// �Ի�������
	enum { IDD = IDD_DIALOG5 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
};
