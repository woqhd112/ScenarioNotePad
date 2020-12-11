
// ScenarioNotePadDlg.cpp: 구현 파일
//

#include "pch.h"
#include "framework.h"
#include "ScenarioNotePad.h"
#include "ScenarioNotePadDlg.h"
#include "afxdialogex.h"
#include "TimeLine.h"
#include "ScenarioOption.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 응용 프로그램 정보에 사용되는 CAboutDlg 대화 상자입니다.

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

// 구현입니다.
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CScenarioNotePadDlg 대화 상자



CScenarioNotePadDlg::CScenarioNotePadDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_SCENARIONOTEPAD_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	bLogin = false;
	bAutoSelect = false;
	bSetScenarioSequence = false;
	nSetScenarioSequence = 0;
}

void CScenarioNotePadDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_SCENARIO_LIST, m_scenario_list);
	DDX_Control(pDX, IDC_OPTION, m_option_button);
}

BEGIN_MESSAGE_MAP(CScenarioNotePadDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_ERASEBKGND()
	ON_NOTIFY(NM_DBLCLK, IDC_SCENARIO_LIST, &CScenarioNotePadDlg::OnDblclkScenarioList)
	ON_NOTIFY(NM_CLICK, IDC_SCENARIO_LIST, &CScenarioNotePadDlg::OnClickScenarioList)
	ON_BN_CLICKED(IDC_OPTION, &CScenarioNotePadDlg::OnBnClickedOption)
END_MESSAGE_MAP()


// CScenarioNotePadDlg 메시지 처리기

BOOL CScenarioNotePadDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 시스템 메뉴에 "정보..." 메뉴 항목을 추가합니다.

	// IDM_ABOUTBOX는 시스템 명령 범위에 있어야 합니다.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != nullptr)
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

	// 이 대화 상자의 아이콘을 설정합니다.  응용 프로그램의 주 창이 대화 상자가 아닐 경우에는
	//  프레임워크가 이 작업을 자동으로 수행합니다.
	SetIcon(m_hIcon, TRUE);			// 큰 아이콘을 설정합니다.
	SetIcon(m_hIcon, FALSE);		// 작은 아이콘을 설정합니다.

	// TODO: 여기에 추가 초기화 작업을 추가합니다.
	LoadScenarioList();
	if (bAutoSelect)
	{
		AutoSelectScenario();
	}
	

	return TRUE;  // 포커스를 컨트롤에 설정하지 않으면 TRUE를 반환합니다.
}

void CScenarioNotePadDlg::LoadScenarioList()
{
	InitLogin login;
	std::vector<ScenarioData*> db_vScenarioData;
	login.InitData(bLogin, db_vScenarioData);

	if (bLogin)
	{
		if ((int)db_vScenarioData.size() > 0)
		{
			m_image_List.Create(64, 64, ILC_COLOR32 | ILC_MASK, (int)db_vScenarioData.size(), 10);
	
			//png로 사진불러오기
			//CPngImage pngImage;
			//pngImage.Load(IDB_PNG_BOOK);	// Theme값에 따라 이미지 불러오기 추가해야함 (함수로.. 테마변경시 동적변경 가능해야함)
			//CBitmap testBitmap;
			//testBitmap.Attach(pngImage.Detach());
			//m_image_List.Add(&testBitmap, RGB(255, 255, 255));
			//비트맵으로 사진불러오기
			/*CBitmap BitMap01;
			BitMap01.LoadBitmapW(IDB_BIT_BOOK);
			m_image_List.Add(&BitMap01, RGB(0, 0, 0));*/
	
			m_scenario_list.SetImageList(&m_image_List, LVSIL_NORMAL);

			CBitmap BitMap02;
			BitMap02.LoadBitmapW(IDB_COLOR_TABLE);
			HBITMAP bkBitmap = (HBITMAP)BitMap02.Detach();

			m_scenario_list.SetBkImage(bkBitmap, false);

			for (int i = 0; i < (int)db_vScenarioData.size(); i++)
			{
				ScenarioData* pScenarioData = db_vScenarioData.at(i);
				ThemeData* pThemeData = pScenarioData->GetThemeData();
				CPngImage pngImage;
				pngImage.Load(pThemeData->GetThemeMainImg());	// Theme값에 따라 이미지 불러오기 추가해야함 (함수로.. 테마변경시 동적변경 가능해야함)
				CBitmap testBitmap;
				testBitmap.Attach(pngImage.Detach());
				m_image_List.Add(&testBitmap, RGB(255, 255, 255));

				LVITEM LI;
				LI.mask = LVIF_TEXT | LVIF_IMAGE;
				LI.state = LVIS_DROPHILITED;
				LI.iItem = i;
				LI.iSubItem = 0;
				LI.iImage = 0;	// 이미지리스트에 추가한 이미지인덱스번호
				LI.pszText = (LPWSTR)(LPCWSTR)pScenarioData->GetScenarioName();
				int nItem = m_scenario_list.InsertItem(&LI);
				m_scenario_list.SetItemData(nItem, (int)pScenarioData);
			}
		}
	}
	AddPlusButton();

	LoadOption();
}

void CScenarioNotePadDlg::LoadOption()
{
	CMarkup loadMarkup;
	CString strFullPath = _T("conf\\Settings.xml");

	if (false == loadMarkup.Load(strFullPath))
	{
		return;
	}
	if (loadMarkup.FindElem(_T("setting")))
	{
		loadMarkup.IntoElem();
		while (loadMarkup.FindElem(_T("option")))
		{
			// value = 1 >>> 자동선택o 
			// value = 0 >>> 자동선택x
			if (loadMarkup.GetAttrib(_T("key")) == _T("autoselect"))	
			{
				if (_ttoi(loadMarkup.GetAttrib(_T("value"))) == 1)
				{
					bAutoSelect = true;
				}
				else
				{
					bAutoSelect = false;
				}
			}
			// value = 1 >>> 자동선택시퀀스 사용o
			// value = 0 >>> 자동선택시퀀스 사용x
			else if (loadMarkup.GetAttrib(_T("key")) == _T("setsequence"))
			{
				if (_ttoi(loadMarkup.GetAttrib(_T("value"))) == 1)
				{
					bSetScenarioSequence = true;
				}
				else
				{
					bSetScenarioSequence = false;
				}
			}
			else
			{
				nSetScenarioSequence = _ttoi(loadMarkup.GetAttrib(_T("value")));
			}
		}
	}

}

void CScenarioNotePadDlg::AutoSelectScenario()
{
	if (bSetScenarioSequence)
	{
		OpenTimeLine(nSetScenarioSequence);
	}
	else
	{
		OpenTimeLine(m_scenario_list.GetItemCount() - 1);
	}
}

void CScenarioNotePadDlg::AddPlusButton()
{
	CPngImage pngImage;
	pngImage.Load(IDB_PNG_PLUS);
	CBitmap testBitmap;
	testBitmap.Attach(pngImage.Detach());
	m_image_List.Add(&testBitmap, RGB(255, 255, 255));

	m_scenario_list.SetImageList(&m_image_List, LVSIL_NORMAL);

	LVITEM LI;
	LI.mask = LVIF_IMAGE;
	LI.state = LVIS_DROPHILITED;
	LI.iItem = m_scenario_list.GetItemCount();
	LI.iSubItem = 0;
	LI.iImage = m_image_List.GetImageCount() - 1;	// 이미지리스트에 추가한 이미지인덱스번호
	int nItem = m_scenario_list.InsertItem(&LI);
}

void CScenarioNotePadDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

// 대화 상자에 최소화 단추를 추가할 경우 아이콘을 그리려면
//  아래 코드가 필요합니다.  문서/뷰 모델을 사용하는 MFC 응용 프로그램의 경우에는
//  프레임워크에서 이 작업을 자동으로 수행합니다.

void CScenarioNotePadDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 그리기를 위한 디바이스 컨텍스트입니다.

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 클라이언트 사각형에서 아이콘을 가운데에 맞춥니다.
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 아이콘을 그립니다.
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// 사용자가 최소화된 창을 끄는 동안에 커서가 표시되도록 시스템에서
//  이 함수를 호출합니다.
HCURSOR CScenarioNotePadDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



BOOL CScenarioNotePadDlg::OnEraseBkgnd(CDC* pDC)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	CRect bkRect;
	GetClientRect(&bkRect);

	CBrush bkBrush(RGB(255, 255, 255));

	CBrush *pOldBrush = pDC->SelectObject(&bkBrush);
	BOOL bRes = pDC->PatBlt(0, 0, bkRect.Width(), bkRect.Height(), PATCOPY);
	pDC->SelectObject(pOldBrush);

	return bRes; 
	//return CDialogEx::OnEraseBkgnd(pDC);
}


void CScenarioNotePadDlg::OnDblclkScenarioList(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CPoint cur_pos;
	GetCursorPos(&cur_pos);
	m_scenario_list.ScreenToClient(&cur_pos);

	UINT flag = 0;
	int nListDataIndex = m_scenario_list.HitTest(cur_pos, &flag);

	if (nListDataIndex != -1 && nListDataIndex != m_scenario_list.GetItemCount() - 1)
	{
		OpenTimeLine(nListDataIndex);
	}

	*pResult = 0;
}

void CScenarioNotePadDlg::OnClickScenarioList(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CPoint cur_pos;
	GetCursorPos(&cur_pos);
	m_scenario_list.ScreenToClient(&cur_pos);

	UINT flag = 0;
	int nListDataIndex = m_scenario_list.HitTest(cur_pos, &flag);

	if (nListDataIndex == -1)
	{
		m_scenario_list.SetItemState(-1, 0, LVIS_SELECTED | LVIS_FOCUSED);
		m_scenario_list.SetSelectionMark(-1);
		m_scenario_list.SetFocus();
	}

	if (nListDataIndex == m_scenario_list.GetItemCount() - 1)
	{
		// 플러스버튼 클릭이벤트
		// 시나리오 추가 팝업 생성
		ScenarioData* pNewScenarioData = new ScenarioData();
		ThemeData::Theme theme = (ThemeData::Theme)0;
		ThemeData* pThemeData = new ThemeData(theme);
		pNewScenarioData->SetScenarioName(_T("시나리오"));
		pNewScenarioData->SetScenarioSequence(nListDataIndex);
		pNewScenarioData->SetThemeData(pThemeData);

		LVITEM LI;
		m_scenario_list.GetItem(&LI);
		LI.mask = LVIF_TEXT | LVIF_IMAGE;
		LI.state = LVIS_DROPHILITED;
		LI.iItem = nListDataIndex;
		LI.iSubItem = 0;
		LI.iImage = 0;	// 이미지리스트에 추가한 이미지인덱스번호
		LI.pszText = (LPWSTR)(LPCWSTR)pNewScenarioData->GetScenarioName();
		m_scenario_list.SetItem(&LI);

		m_scenario_list.SetItemData(nListDataIndex, (int)pNewScenarioData);

		AddPlusButton();
		SaveScenarioXML();
	}

	*pResult = 0;
}

void CScenarioNotePadDlg::SaveScenarioXML()
{

}

BOOL CScenarioNotePadDlg::PreTranslateMessage(MSG* pMsg)
{
	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.
	if (pMsg->message == WM_KEYDOWN)
	{
		if (pMsg->wParam == VK_RETURN)
		{
			int nListDataIndex = m_scenario_list.GetSelectionMark();
			if (nListDataIndex != -1)
			{
				OpenTimeLine(nListDataIndex);
			}
		}
	}


	return CDialogEx::PreTranslateMessage(pMsg);
}

void CScenarioNotePadDlg::OpenTimeLine(int nListDataIndex)
{
	TimeLine* timeLine = new TimeLine(this, nListDataIndex);
	timeLine->Create(IDD_TIMELINE);
	timeLine->ShowWindow(SW_SHOW);
}

void CScenarioNotePadDlg::OnOK()
{
	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.

	//CDialogEx::OnOK();
}

CListCtrl* CScenarioNotePadDlg::GetScenarioList()
{
	return &m_scenario_list;
}

void CScenarioNotePadDlg::SetOption(bool bAutoSelect, bool bSetScenarioSequence, int nSetScenarioSequence)
{
	this->bAutoSelect = bAutoSelect;
	this->bSetScenarioSequence = bSetScenarioSequence;
	this->nSetScenarioSequence = nSetScenarioSequence;
}

void CScenarioNotePadDlg::OnBnClickedOption()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	ScenarioOption option(this, bAutoSelect, bSetScenarioSequence, nSetScenarioSequence);
	option.DoModal();
}
