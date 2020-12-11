// NoteButton.cpp: 구현 파일
//

#include "pch.h"
#include "ScenarioNotePad.h"
#include "NoteButton.h"

// NoteButton

IMPLEMENT_DYNAMIC(NoteButton, CMFCButton)

NoteButton::NoteButton()
{

}


NoteButton::~NoteButton()
{
}


BEGIN_MESSAGE_MAP(NoteButton, CMFCButton)
	ON_WM_MOUSEHOVER()
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_MOUSELEAVE()
END_MESSAGE_MAP()



// NoteButton 메시지 처리기




void NoteButton::OnMouseHover(UINT nFlags, CPoint point)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	
	TRACE(L"hover\n");
	CMFCButton::OnMouseHover(nFlags, point);
}


void NoteButton::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.

	TRACE(L"down\n");
	CMFCButton::OnLButtonDown(nFlags, point);
}


void NoteButton::OnLButtonUp(UINT nFlags, CPoint point)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	
	TRACE(L"up\n");
	CMFCButton::OnLButtonUp(nFlags, point);
}


void NoteButton::OnMouseLeave()
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	
	TRACE(L"leave\n");
	CMFCButton::OnMouseLeave();
}
