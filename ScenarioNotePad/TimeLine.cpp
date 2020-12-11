// TimeLine.cpp: 구현 파일
//

#include "pch.h"
#include "afxdialogex.h"
#include "ScenarioNotePad.h"
#include "TimeLine.h"


// TimeLine 대화 상자

IMPLEMENT_DYNAMIC(TimeLine, CDialogEx)

TimeLine::TimeLine(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_TIMELINE, pParent)
{

}

TimeLine::TimeLine(CScenarioNotePadDlg* pScenarioNotePad, int nScenarioDataIndex, CWnd* pParent /*=nullptr*/) :
	CDialogEx(IDD_TIMELINE, pParent),
	nScenarioDataIndex(nScenarioDataIndex),
	pScenarioNotePad(pScenarioNotePad)
{
	pScenarioList = pScenarioNotePad->GetScenarioList();
	ScenarioData* pScenarioData = (ScenarioData*)pScenarioList->GetItemData(nScenarioDataIndex);
	//aNotePad = new CEdit[(int)pScenarioData->GetVectorNotePad().size()];
}

TimeLine::~TimeLine()
{
	typeListView.DestroyWindow();
}

void TimeLine::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_TIMELINE_TITLE, m_edit_timeline_title);
}


BEGIN_MESSAGE_MAP(TimeLine, CDialogEx)
	ON_WM_ERASEBKGND()
	ON_EN_CHANGE(IDC_TIMELINE_TITLE, &TimeLine::OnChangeTimelineTitle)
	ON_EN_KILLFOCUS(IDC_TIMELINE_TITLE, &TimeLine::OnKillfocusTimelineTitle)
	ON_EN_SETFOCUS(IDC_TIMELINE_TITLE, &TimeLine::OnSetfocusTimelineTitle)
	ON_WM_CLOSE()
END_MESSAGE_MAP()


// TimeLine 메시지 처리기


BOOL TimeLine::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  여기에 추가 초기화 작업을 추가합니다.
	pScenarioList = pScenarioNotePad->GetScenarioList();
	ScenarioData* pScenarioData = (ScenarioData*)pScenarioList->GetItemData(nScenarioDataIndex);

	CRect tempRect = CRect();
	tempRect.bottom = 500;
	tempRect.top = 100;
	tempRect.left = 20;
	tempRect.right = 540;
	typeListView.Create(IDD_TYPE_LIST, this);
	typeListView.MoveWindow(tempRect);
	typeListView.ShowWindow(SW_SHOW);
	typeListView.Init(TypeListView::TYPE_BOOK);

	SetTimeLineTitle(pScenarioData);
	SetTimeLine(pScenarioData);
	SetNotePad(pScenarioData);

	return TRUE;  // return TRUE unless you set the focus to a control
				  // 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}

void TimeLine::SetNotePad(ScenarioData* pScenarioData)
{
	std::vector<NotePad*> vNotePad = pScenarioData->GetVectorNotePad();

	int nNoteSize = (int)pScenarioData->GetVectorNotePad().size();
	int nTestSize_x = 0;
	int nTestSize_y = 0;
	int nCount = 0;
	int nId = 10000;
	for (int i = 0; i < nNoteSize; i++)
	{
		NotePad* pNotePad = vNotePad.at(i);
		typeListView.InsertData(pNotePad);
		/*nCount++;
		if ((i % 3) != 0)
		{
			nTestSize_x += 150;
		}
		else
		{
			nTestSize_x = 0;
			if (nCount == 4)
			{
				nTestSize_y += 120;
				nCount = 1;
			}
		}
		aNotePad[i].Create(WS_CHILD | WS_VISIBLE | WS_BORDER | ES_AUTOHSCROLL, CRect(0, 0, 0, 0), this, nId += i);
		aNotePad[i].MoveWindow(20 + nTestSize_x, 100 + nTestSize_y, 100, 100);
		aNotePad[i].SetWindowTextW(pNotePad->GetNoteContent());*/
		// 노트패드의 옵션값으로 화면구성
	}
	//AddPlusButton(nCount, nTestSize_x, nTestSize_y, nId);
}

void TimeLine::AddPlusButton(int nCount, int nPoint_x, int nPoint_y, int nId)
{
	CPngImage pngImage;
	pngImage.Load(IDB_PNG_PLUS);
	HBITMAP bitmap = (HBITMAP)pngImage.Detach();
	
	if (nCount == 3)
	{
		nPoint_x = 0;
		nPoint_y += 120;
	}
	else
	{
		nPoint_x += 150;
	}
	
	plusBtn.Create(_T(""), WS_CHILD | WS_VISIBLE | BS_OWNERDRAW | BS_PUSHBUTTON, CRect(0, 0, 0, 0), this, nId + 1);
	plusBtn.MoveWindow(20 + nPoint_x, 100 + nPoint_y, 100, 100);
	plusBtn.m_bTransparent = TRUE;
	plusBtn.m_bDrawFocus = FALSE;
	plusBtn.SetImage(bitmap, TRUE);
	plusBtn.SizeToContent();
}

void TimeLine::SetTimeLine(ScenarioData* pScenarioData)
{

}

void TimeLine::SetTimeLineTitle(ScenarioData* pScenarioData)
{
	m_edit_timeline_title.SetWindowTextW(pScenarioData->GetScenarioName() + _T("의 타임라인"));
}

void TimeLine::OnOK()
{
	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.

	//CDialogEx::OnOK();
}

BOOL TimeLine::OnEraseBkgnd(CDC* pDC)
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

// 에딧타이틀 컨트롤
void TimeLine::OnChangeTimelineTitle()
{
	// TODO:  RICHEDIT 컨트롤인 경우, 이 컨트롤은
	// CDialogEx::OnInitDialog() 함수를 재지정 
	//하고 마스크에 OR 연산하여 설정된 ENM_CHANGE 플래그를 지정하여 CRichEditCtrl().SetEventMask()를 호출하지 않으면
	// 이 알림 메시지를 보내지 않습니다.

	// TODO:  여기에 컨트롤 알림 처리기 코드를 추가합니다.

}

// 에딧타이틀 컨트롤
void TimeLine::OnKillfocusTimelineTitle()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.

}

// 에딧타이틀 컨트롤
void TimeLine::OnSetfocusTimelineTitle()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	m_edit_timeline_title.ModifyStyle(0, WS_BORDER);
}


void TimeLine::OnClose()
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.

	CDialogEx::OnClose();
	TimeLine::PostNcDestroy();
}


void TimeLine::PostNcDestroy()
{
	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.
	delete this;
	CDialogEx::PostNcDestroy();
}
