
// ScenarioNotePadDlg.h: 헤더 파일
//

#pragma once
#include "ScenarioData.h"
#include "InitLogin.h"
#include "CMarkup\Markup.h"
#include <vector>


// CScenarioNotePadDlg 대화 상자
class CScenarioNotePadDlg : public CDialogEx
{
// 생성입니다.
public:
	CScenarioNotePadDlg(CWnd* pParent = nullptr);	// 표준 생성자입니다.

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_SCENARIONOTEPAD_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 지원입니다.


// 구현입니다.
protected:
	HICON m_hIcon;

	// 생성된 메시지 맵 함수
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnDblclkScenarioList(NMHDR *pNMHDR, LRESULT *pResult);
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	afx_msg void OnClickScenarioList(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnBnClickedOption();

private:
	virtual void OnOK();


// 함수 //
public:
	void AddPlusButton();
	CListCtrl* GetScenarioList();
	void SetOption(bool bAutoSelect, bool bSetScenarioSequence, int nSetScenarioSequence);
	void SaveScenarioXML();

private:
	void LoadScenarioList();
	void OpenTimeLine(int nListDataIndex);
	void AutoSelectScenario();
	void LoadOption();

//////////

// 변수 //
public:

private:
	CListCtrl m_scenario_list;
	CImageList m_image_List;
	CButton m_option_button;
	bool bLogin;
	bool bAutoSelect;
	bool bSetScenarioSequence;
	int nSetScenarioSequence;
//////////
};
