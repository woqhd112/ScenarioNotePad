#pragma once
#include "ScenarioNotePadDlg.h"

// ScenarioOption 대화 상자

class ScenarioOption : public CDialogEx
{
	DECLARE_DYNAMIC(ScenarioOption)

public:
	ScenarioOption(CWnd* pParent = nullptr);   // 표준 생성자입니다.
	ScenarioOption(CScenarioNotePadDlg* pScenarioNotePadDlg,bool bAutoSelect, bool bSetScenarioSequence, int nSetScenarioSequence, CWnd* pParent = nullptr); 
	virtual ~ScenarioOption();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_OPTION_DLG };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()


// 함수 //
public:

private:
	void SaveXMLOption();

//////////

// 변수 //
public:

private:
	CButton m_check_autoselect;
	CEdit m_edit_sequence;
	CButton m_button_save;

	CScenarioNotePadDlg* pScenarioNotePadDlg;
	bool bAutoSelect;
	bool bSetScenarioSequence;
	int nSetScenarioSequence;
	int nLastIndex;
//////////


public:
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedCheckAutoselect();
	afx_msg void OnBnClickedSave();
	afx_msg void OnEnChangeEditSequence();
};
