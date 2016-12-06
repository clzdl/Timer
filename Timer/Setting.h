#pragma once


// CSetting 对话框

class CSetting : public CDialogEx
{
	DECLARE_DYNAMIC(CSetting)

public:
	CSetting(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CSetting();

// 对话框数据
	enum { IDD = IDD_DLG_SETTING };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedCancel();



	unsigned int m_uiSecond;
	CString m_csMusicName;
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedBtnChoose();
};
