#pragma once
#include <afxbutton.h>
#include <atlimage.h>
#include <vector>
#include "ScenarioNotePadDlg.h"
#include "ScenarioData.h"
#include "NotePad.h"
#include "TypeListView.h"

// TimeLine 대화 상자

class TimeLine : public CDialogEx
{
	DECLARE_DYNAMIC(TimeLine)

public:
	TimeLine(CWnd* pParent = nullptr);   // 표준 생성자입니다.
	TimeLine(CScenarioNotePadDlg* pScenarioNotePad, int nScenarioDataIndex, CWnd* pParent = nullptr);  
	virtual ~TimeLine();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_TIMELINE };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()


// 함수 //
public:

private:
	void SetTimeLineTitle(ScenarioData* pScenarioData);
	void SetTimeLine(ScenarioData* pScenarioData);
	void SetNotePad(ScenarioData* pScenarioData);
	void AddPlusButton(int nCount, int nPoint_x, int nPoint_y, int nId);
//////////

// 변수 //
public:

private:
	CScenarioNotePadDlg* pScenarioNotePad;
	CListCtrl* pScenarioList;
	TypeListView typeListView;
	int nScenarioDataIndex;


	CEdit m_edit_timeline_title;
	CEdit* aNotePad;
	CMFCButton plusBtn;
//////////
public:
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnChangeTimelineTitle();
	afx_msg void OnKillfocusTimelineTitle();
	afx_msg void OnSetfocusTimelineTitle();
	afx_msg void OnClose();
	virtual void PostNcDestroy();
};
