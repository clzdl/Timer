
// TimerDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "Timer.h"
#include "TimerDlg.h"
#include "afxdialogex.h"
#include "Setting.h"

#include "vfw.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

#define ID_SETTING			4444
#define ID_START			4445

#define ID_TIMER			4446
#define ID_TIMER_MUSIC		4447

// ����Ӧ�ó��򡰹��ڡ��˵���� CAboutDlg �Ի���

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// �Ի�������
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

// ʵ��
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CTimerDlg �Ի���




CTimerDlg::CTimerDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CTimerDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CTimerDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_TXT_LED_TIME, m_txtLedTime);
}

BEGIN_MESSAGE_MAP(CTimerDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDOK, &CTimerDlg::OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, &CTimerDlg::OnBnClickedCancel)
	ON_WM_TIMER()
	ON_WM_DESTROY()
END_MESSAGE_MAP()


// CTimerDlg ��Ϣ�������

BOOL CTimerDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// ��������...���˵�����ӵ�ϵͳ�˵��С�

	// IDM_ABOUTBOX ������ϵͳ���Χ�ڡ�
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// ���ô˶Ի����ͼ�ꡣ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	// TODO: �ڴ���Ӷ���ĳ�ʼ������

	m_hVideo = NULL;
	char *szTooBar = "setting\0start\0\0";

	TBBUTTON tb[2];

	m_ToolBar.Create(WS_VISIBLE | WS_CHILD |WS_BORDER|TBSTYLE_WRAPABLE|TBSTYLE_FLAT, CRect(0,0,0,0), this, 0);



	m_ToolBar.AddStrings(szTooBar);

	tb[0].dwData  = 0 ;
	tb[0].iString = 0;
	tb[0].fsState = TBSTATE_ENABLED;
	tb[0].fsStyle = TBSTYLE_BUTTON;
	tb[0].idCommand = ID_SETTING;

	tb[1].dwData  = 0 ;
	tb[1].iString = 1;
	tb[1].fsState = TBSTATE_ENABLED;
	tb[1].fsStyle = TBSTYLE_BUTTON;
	tb[1].idCommand = ID_START;


	m_ToolBar.AddButtons(2, tb);


	m_txtLedTime.SetColor(DARKRED, LIGHTRED);
	m_txtLedTime.SetText("00:00:00");
	VERIFY(m_txtLedTime.ModifyDigiStyle(0, CDigistring::DS_STYLE14 | CDigistring::DS_SZ_PROP));
	

	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

void CTimerDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CTimerDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // ���ڻ��Ƶ��豸������

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ʹͼ���ڹ����������о���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// ����ͼ��
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
HCURSOR CTimerDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CTimerDlg::OnBnClickedOk()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CDialogEx::OnOK();
}


void CTimerDlg::OnBnClickedCancel()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CDialogEx::OnCancel();
}


BOOL CTimerDlg::OnCommand(WPARAM wParam, LPARAM lParam)
{
	// TODO: �ڴ����ר�ô����/����û���

	switch(wParam)
	{
		case ID_SETTING:
		{//setting
			CSetting setting;
			if(IDOK == setting.DoModal() )
			{
				m_uiSeconds = setting.m_uiSecond;
				m_csMusicName = setting.m_csMusicName;
			}

			m_csMusicName.ReleaseBuffer();

			break;
		}

		case ID_START:
		{
			StopMusic();

			m_uiCurSecond = 0;
			SetTimer(ID_TIMER,1000,0);
			m_ToolBar.EnableButton(ID_START,false);
			break;
		}
	}

	return CDialogEx::OnCommand(wParam, lParam);
}


void CTimerDlg::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ

	switch(nIDEvent)
	{
		case ID_TIMER:
		{
			++m_uiCurSecond;

			CString csFormat;
			csFormat.Format("00:%02d:%02d", m_uiCurSecond/60 , m_uiCurSecond%60);

			TRACE("===: %s \n" , csFormat.GetBuffer());
			csFormat.ReleaseBuffer();


			m_txtLedTime.SetText(csFormat);

			if(m_uiCurSecond >= m_uiSeconds )
			{
				KillTimer(ID_TIMER);
				m_ToolBar.EnableButton(ID_START,true);
				m_txtLedTime.SetText("00:00:00");

				m_uiPlaySecond = 0;

				if(!m_csMusicName.Empty())
				{
					SetTimer(ID_TIMER_MUSIC,2000,0);
					PlayMusic(m_csMusicName);
				}
			}

			break;
		}
		case ID_TIMER_MUSIC:
		{
			++m_uiPlaySecond;

			if(m_uiPlaySecond >= 30)
			{
				StopMusic();
				KillTimer(ID_TIMER_MUSIC);

			}

			break;
		}
	}


	CDialogEx::OnTimer(nIDEvent);
}


void CTimerDlg::OnDestroy()
{
	CDialogEx::OnDestroy();


	KillTimer(ID_TIMER);
	KillTimer(ID_TIMER_MUSIC);

	// TODO: �ڴ˴������Ϣ����������
}

void CTimerDlg::PlayMusic(CString csMusicName)
{
	if(0 >= csMusicName.GetLength() )
		return ;

	m_hVideo = NULL;
	
	if(m_hVideo == NULL)
	{
		m_hVideo = MCIWndCreate(this->GetSafeHwnd(),
			AfxGetInstanceHandle(),
			WS_CHILD | WS_VISIBLE|MCIWNDF_NOMENU,csMusicName);
		
	}
	else
	{
		MCIWndHome(m_hVideo);
	}
	
	MCIWndPlay(m_hVideo);
	
}

void CTimerDlg::StopMusic()
{
	MCIWndStop(m_hVideo);
	if(m_hVideo !=NULL)
	{
		MCIWndDestroy(m_hVideo);

		m_hVideo = NULL;
	}
}
