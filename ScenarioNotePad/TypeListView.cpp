// TypeListView.cpp: 구현 파일
//

#include "pch.h"
#include "ScenarioNotePad.h"
#include "TypeListView.h"
#include "afxdialogex.h"


// TypeListView 대화 상자

IMPLEMENT_DYNAMIC(TypeListView, CDialogEx)

TypeListView::TypeListView(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_TYPE_LIST, pParent)
{
	nTestSize_x = 0;
	nTestSize_y = 0;
	nCount = 0;
	nIdx = 0;
	nId = 10000;
}

TypeListView::~TypeListView()
{
	for (int i = 0; i < (int)noteVector.size(); i++)
	{
		noteVector.at(i)->DestroyWindow();
	}

	for (int i = 0; i < (int)buttonVector.size(); i++)
	{
		buttonVector.at(i)->DestroyWindow();
	}
}

void TypeListView::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(TypeListView, CDialogEx)
END_MESSAGE_MAP()


// TypeListView 메시지 처리기

bool TypeListView::Init(Type type)
{
	this->type = type;
	bool bReturn = true;

	if (type == TYPE_TABLE)
	{
		nTypeEdit_size_x = 0;
		nTypeEdit_size_y = 0;
		nTypeButton_size_x = 64;
		nTypeButton_size_y = 64;
		nTypeList_size_x = 400;
		nTypeList_size_y = 400;
	}
	else if (type == TYPE_BOOK)
	{
		nTypeEdit_size_x = 120;
		nTypeEdit_size_y = 170;
		nTypeButton_size_x = 140;
		nTypeButton_size_y = 210;
		nTypeList_size_x = 400;
		nTypeList_size_y = 600;
	}
	else
	{
		bReturn = false;
	}

	return bReturn;
}


void TypeListView::InsertData(NotePad* pNotePad)
{
	nCount++;
	if ((nIdx % 3) != 0)
	{
		nTestSize_x += 160;
	}
	else
	{
		nTestSize_x = 0;
		if (nCount == 4)
		{
			nTestSize_y += 225;
			nCount = 1;
		}
	}

	SetNoteStyle(pNotePad);
	nIdx++;
}

void TypeListView::InsertData(ScenarioData* pNotePad)
{

}

void TypeListView::SetNoteStyle(NotePad* pNotePad)
{
	int editIdx = 0;
	int buttonIdx = 0;

	nId += nIdx;
	editIdx = nId;
	buttonIdx = nId + 10000;
	CEdit* editBox = pNotePad->GetEditBox();
	NoteButton* borderButton = pNotePad->GetBorderButton();

	EditStyle(pNotePad, nId);
	ButtonStyle(pNotePad, buttonIdx);

	editBox->ModifyStyle(0, WS_CLIPSIBLINGS | WS_CLIPCHILDREN, 0);
	borderButton->ModifyStyle(0, WS_CLIPSIBLINGS | WS_CLIPCHILDREN, 0);
	editBox->BringWindowToTop();
	
	noteVector.push_back(editBox);
	buttonVector.push_back(borderButton);
}

void TypeListView::ButtonStyle(NotePad* pNotePad, int nId)
{
	NoteButton* borderButton = pNotePad->GetBorderButton();
	borderButton->Create(_T(""), WS_CHILD | WS_VISIBLE | BS_OWNERDRAW | BS_PUSHBUTTON, CRect(0, 0, 0, 0), this, nId);
	borderButton->MoveWindow(20 + nTestSize_x, 20 + nTestSize_y, nTypeButton_size_x, nTypeButton_size_y);

	CPngImage pngImage;
	pngImage.Load(pNotePad->GetThemeData()->GetThemeSubImg());
	HBITMAP bitmap = (HBITMAP)pngImage.Detach();
	borderButton->m_bTransparent = TRUE;
	borderButton->m_bDrawFocus = FALSE;
	//버튼 오버, 다운, 업 시 이벤트처리해야함 https://codingcoding.tistory.com/347
	borderButton->m_nFlatStyle = CMFCButton::BUTTONSTYLE_NOBORDERS;
	borderButton->SetImage(bitmap, TRUE);
	borderButton->SizeToContent();
}

void TypeListView::EditStyle(NotePad* pNotePad, int nId)
{
	CEdit* editBox = pNotePad->GetEditBox();
	editBox->Create(WS_CHILD | WS_VISIBLE | WS_BORDER | ES_AUTOHSCROLL, CRect(0, 0, 0, 0), this, nId);
	editBox->MoveWindow(30 + nTestSize_x, 30 + nTestSize_y, nTypeEdit_size_x, nTypeEdit_size_y);
	editBox->SetWindowTextW(pNotePad->GetNoteContent());
}

BOOL TypeListView::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  여기에 추가 초기화 작업을 추가합니다.
	this->SetBackgroundColor(RGB(255, 255, 255));


	return TRUE;  // return TRUE unless you set the focus to a control
				  // 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}

