// Setting.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "Timer.h"
#include "Setting.h"
#include "afxdialogex.h"


// CSetting �Ի���

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


// CSetting ��Ϣ�������


void CSetting::OnBnClickedOk()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CString csTemp;
	GetDlgItem(IDC_EDT_DURATION)->GetWindowTextA(csTemp);
	m_uiSecond = atoi(csTemp.GetBuffer());
	csTemp.ReleaseBuffer();

	GetDlgItem(IDC_EDT_MUSIC_NAME)->GetWindowTextA(m_csMusicName);


	CDialogEx::OnOK();
}


void CSetting::OnBnClickedCancel()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CDialogEx::OnCancel();
}


BOOL CSetting::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
	
	GetDlgItem(IDC_EDT_DURATION)->SetWindowTextA("300");



	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣: OCX ����ҳӦ���� FALSE
}


void CSetting::OnBnClickedBtnChoose()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������

	CFileDialog    dlgFile(TRUE, NULL, NULL, OFN_HIDEREADONLY, _T("music (*.mp3)|*.mp3|All Files (*.*)|*.*||"), NULL);

	if (dlgFile.DoModal())
	{
		m_csMusicName = dlgFile.GetPathName();

		GetDlgItem(IDC_EDT_MUSIC_NAME)->SetWindowTextA(m_csMusicName);
	}

}
