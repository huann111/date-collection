#pragma once


// Datasearch �Ի���

class Datasearch : public CDialog
{
	DECLARE_DYNAMIC(Datasearch)

public:
	Datasearch(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~Datasearch();

// �Ի�������
	enum { IDD = IDD_DIALOG4 };
	CTime	m_defaultDate;
	CDateTimeCtrl	m_PosTimeCtrl;

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
};
