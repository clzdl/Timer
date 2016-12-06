
// TimerDlg.h : ͷ�ļ�
//

#pragma once
#include "afxwin.h"
#include "LedShow/Digistring.h"

// CTimerDlg �Ի���
class CTimerDlg : public CDialogEx
{
// ����
public:
	CTimerDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_TIMER_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��


// ʵ��
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

	// ���ɵ���Ϣӳ�亯��
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
