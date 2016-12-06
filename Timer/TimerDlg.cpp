
// TimerDlg.cpp : 实现文件
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

// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 对话框数据
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
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


// CTimerDlg 对话框




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


// CTimerDlg 消息处理程序

BOOL CTimerDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
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

	// 设置此对话框的图标。当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码

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
	

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
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

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CTimerDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CTimerDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CTimerDlg::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码
	CDialogEx::OnOK();
}


void CTimerDlg::OnBnClickedCancel()
{
	// TODO: 在此添加控件通知处理程序代码
	CDialogEx::OnCancel();
}


BOOL CTimerDlg::OnCommand(WPARAM wParam, LPARAM lParam)
{
	// TODO: 在此添加专用代码和/或调用基类

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
	// TODO: 在此添加消息处理程序代码和/或调用默认值

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

	// TODO: 在此处添加消息处理程序代码
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
