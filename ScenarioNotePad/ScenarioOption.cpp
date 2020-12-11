// ScenarioOption.cpp: 구현 파일
//

#include "pch.h"
#include "afxdialogex.h"
#include "ScenarioNotePad.h"
#include "ScenarioOption.h"
#include "CXml\Xml.h"


// ScenarioOption 대화 상자

IMPLEMENT_DYNAMIC(ScenarioOption, CDialogEx)

ScenarioOption::ScenarioOption(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_OPTION_DLG, pParent)
{

}

ScenarioOption::ScenarioOption(CScenarioNotePadDlg* pScenarioNotePadDlg, bool bAutoSelect, bool bSetScenarioSequence, int nSetScenarioSequence, CWnd* pParent /*= nullptr*/)
	: CDialogEx(IDD_OPTION_DLG, pParent),
	pScenarioNotePadDlg(pScenarioNotePadDlg),
	bAutoSelect(bAutoSelect),
	bSetScenarioSequence(bSetScenarioSequence),
	nSetScenarioSequence(nSetScenarioSequence)
{
	nLastIndex = pScenarioNotePadDlg->GetScenarioList()->GetItemCount() - 1;
}

ScenarioOption::~ScenarioOption()
{
}

void ScenarioOption::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_CHECK_AUTOSELECT, m_check_autoselect);
	DDX_Control(pDX, IDC_EDIT_SEQUENCE, m_edit_sequence);
	DDX_Control(pDX, IDC_SAVE, m_button_save);
}


BEGIN_MESSAGE_MAP(ScenarioOption, CDialogEx)
	ON_BN_CLICKED(IDC_CHECK_AUTOSELECT, &ScenarioOption::OnBnClickedCheckAutoselect)
	ON_BN_CLICKED(IDC_SAVE, &ScenarioOption::OnBnClickedSave)
	ON_EN_CHANGE(IDC_EDIT_SEQUENCE, &ScenarioOption::OnEnChangeEditSequence)
END_MESSAGE_MAP()


// ScenarioOption 메시지 처리기


BOOL ScenarioOption::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  여기에 추가 초기화 작업을 추가합니다.
	CString strText = _T("");
	if (nSetScenarioSequence >= 0)
	{
		strText.Format(_T("%d"), nSetScenarioSequence + 1);
	}
	
	if (bAutoSelect)
	{
		m_check_autoselect.SetCheck(TRUE);
		m_edit_sequence.SetWindowTextW(strText);
	}
	else
	{
		m_check_autoselect.SetCheck(FALSE);
		m_edit_sequence.EnableWindow(FALSE);
	}


	return TRUE;  // return TRUE unless you set the focus to a control
				  // 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}


void ScenarioOption::OnBnClickedCheckAutoselect()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	if (m_check_autoselect.GetCheck())
	{
		m_edit_sequence.EnableWindow(TRUE);
	}
	else
	{
		m_edit_sequence.EnableWindow(FALSE);
		m_edit_sequence.SetWindowTextW(_T(""));
	}
}


void ScenarioOption::OnBnClickedSave()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	if (m_check_autoselect.GetCheck())
	{
		CString strText = _T("");
		bAutoSelect = true;
		bSetScenarioSequence = true;
		m_edit_sequence.GetWindowTextW(strText);
		if (!strText.IsEmpty())
		{
			nSetScenarioSequence = _ttoi(strText) - 1;
		}
		else
		{
			nSetScenarioSequence = nLastIndex;
		}

		if (nSetScenarioSequence < 0)
		{
			nSetScenarioSequence = nLastIndex;
		}
	}
	else
	{
		bAutoSelect = false;
		bSetScenarioSequence = false;
		nSetScenarioSequence = 0;
	}
	pScenarioNotePadDlg->SetOption(bAutoSelect, bSetScenarioSequence, nSetScenarioSequence);
	SaveXMLOption();
	ScenarioOption::OnOK();
}

void ScenarioOption::SaveXMLOption()
{
	CMarkup loadMarkup;
	CString strFullPath = _T("conf\\Settings.xml");

	if (false == loadMarkup.Load(strFullPath))
	{
		return;
	}

	CString strText = _T("");
	if (loadMarkup.FindElem(_T("setting")))
	{
		loadMarkup.IntoElem();
		while (loadMarkup.FindElem(_T("option")))
		{
			if (loadMarkup.GetAttrib(_T("key")) == _T("autoselect"))
			{
				strText.Format(_T("%d"), (int)bAutoSelect);
				loadMarkup.SetAttrib(_T("value"), strText);
			}
			else if (loadMarkup.GetAttrib(_T("key")) == _T("setsequence"))
			{
				strText.Format(_T("%d"), (int)bSetScenarioSequence);
				loadMarkup.SetAttrib(_T("value"), strText);
			}
			else
			{
				strText.Format(_T("%d"), nSetScenarioSequence);
				loadMarkup.SetAttrib(_T("value"), strText);
			}
		}
	}

	CString strXML = loadMarkup.GetDoc();
	//LoadXml 함수에서 "hr = 0x800401f0 : CoInitialize가 호출되지 않았습니다." 에러가 발생하여 CoInitializeEx와 CoUninitialize 함수 호출
	HRESULT hr = CoInitializeEx(NULL, COINIT_APARTMENTTHREADED | COINIT_DISABLE_OLE1DDE);	// https://docs.microsoft.com/ko-kr/windows/win32/learnwin32/initializing-the-com-library?redirectedfrom=MSDN
	JWXml::CXml saveXML;
	saveXML.LoadXml((LPCTSTR)strXML);
	saveXML.SaveWithFormatted(strFullPath);
	saveXML.Close();
	CoUninitialize();	// https://docs.microsoft.com/ko-kr/windows/win32/learnwin32/initializing-the-com-library?redirectedfrom=MSDN
}

void ScenarioOption::OnEnChangeEditSequence()
{
	// TODO:  RICHEDIT 컨트롤인 경우, 이 컨트롤은
	// CDialogEx::OnInitDialog() 함수를 재지정 
	//하고 마스크에 OR 연산하여 설정된 ENM_CHANGE 플래그를 지정하여 CRichEditCtrl().SetEventMask()를 호출하지 않으면
	// 이 알림 메시지를 보내지 않습니다.

	// TODO:  여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CString strText = _T("");
	m_edit_sequence.GetWindowTextW(strText);
	if (_ttoi(strText) > nLastIndex)
	{
		strText.Format(_T("%d"), nLastIndex);
		m_edit_sequence.Clear();
		m_edit_sequence.SetWindowTextW(strText);
	}
}
