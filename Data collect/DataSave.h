#pragma once


// DataSave �Ի���

class DataSave : public CDialog
{
	DECLARE_DYNAMIC(DataSave)

public:
	DataSave(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~DataSave();

// �Ի�������
	enum { IDD = IDD_DIALOG8 };
	CString	m_strCurPath;
	CString	m_strSendFilePathName;
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButton1();
	virtual BOOL OnInitDialog();
};
