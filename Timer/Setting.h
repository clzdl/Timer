#pragma once


// CSetting �Ի���

class CSetting : public CDialogEx
{
	DECLARE_DYNAMIC(CSetting)

public:
	CSetting(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CSetting();

// �Ի�������
	enum { IDD = IDD_DLG_SETTING };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedCancel();



	unsigned int m_uiSecond;
	CString m_csMusicName;
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedBtnChoose();
};
