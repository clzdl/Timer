
// TimerDlg.h : 头文件
//

#pragma once
#include "afxwin.h"
#include "LedShow/Digistring.h"

// CTimerDlg 对话框
class CTimerDlg : public CDialogEx
{
// 构造
public:
	CTimerDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
	enum { IDD = IDD_TIMER_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;
	CToolBarCtrl m_ToolBar;
	unsigned int m_uiSeconds;
	unsigned int m_uiCurSecond;
	unsigned int m_uiPlaySecond;

	CString m_csMusicName;

	CDigistring m_txtLedTime;

	HWND  m_hVideo;

	void PlayMusic(CString csMusicName);


	void StopMusic();

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedCancel();
	virtual BOOL OnCommand(WPARAM wParam, LPARAM lParam);



	
	
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnDestroy();
	
};
