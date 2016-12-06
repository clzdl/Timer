// Setting.cpp : 实现文件
//

#include "stdafx.h"
#include "Timer.h"
#include "Setting.h"
#include "afxdialogex.h"


// CSetting 对话框

IMPLEMENT_DYNAMIC(CSetting, CDialogEx)

CSetting::CSetting(CWnd* pParent /*=NULL*/)
	: CDialogEx(CSetting::IDD, pParent)
{

}

CSetting::~CSetting()
{
}

void CSetting::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CSetting, CDialogEx)
	ON_BN_CLICKED(IDOK, &CSetting::OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, &CSetting::OnBnClickedCancel)
	ON_BN_CLICKED(IDC_BTN_CHOOSE, &CSetting::OnBnClickedBtnChoose)
END_MESSAGE_MAP()


// CSetting 消息处理程序


void CSetting::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码
	CString csTemp;
	GetDlgItem(IDC_EDT_DURATION)->GetWindowTextA(csTemp);
	m_uiSecond = atoi(csTemp.GetBuffer());
	csTemp.ReleaseBuffer();

	GetDlgItem(IDC_EDT_MUSIC_NAME)->GetWindowTextA(m_csMusicName);


	CDialogEx::OnOK();
}


void CSetting::OnBnClickedCancel()
{
	// TODO: 在此添加控件通知处理程序代码
	CDialogEx::OnCancel();
}


BOOL CSetting::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化
	
	GetDlgItem(IDC_EDT_DURATION)->SetWindowTextA("300");



	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}


void CSetting::OnBnClickedBtnChoose()
{
	// TODO: 在此添加控件通知处理程序代码

	CFileDialog    dlgFile(TRUE, NULL, NULL, OFN_HIDEREADONLY, _T("music (*.mp3)|*.mp3|All Files (*.*)|*.*||"), NULL);

	if (dlgFile.DoModal())
	{
		m_csMusicName = dlgFile.GetPathName();

		GetDlgItem(IDC_EDT_MUSIC_NAME)->SetWindowTextA(m_csMusicName);
	}

}
