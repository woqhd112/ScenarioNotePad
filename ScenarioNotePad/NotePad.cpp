#include "pch.h"
#include "NotePad.h"
#include "CXml\Xml.h"

NotePad::NotePad()
{
	
}

NotePad::NotePad(ThemeData* themeData)
{
	strNoteContent = _T("");
	nNoteSequence = 0;
	bOverlap = false;
	nOverlapCount = 0;
	editBox = new CEdit;
	borderButton = new NoteButton;
	this->themeData = themeData;
}

NotePad::~NotePad()
{
	if (pNoteOption)
	{
		delete pNoteOption;
		pNoteOption = (NoteOption*)nullptr;
	}

	if (editBox)
	{
		delete editBox;
		editBox = (CEdit*)nullptr;
	}
	
	if (borderButton)
	{
		delete borderButton;
		borderButton = (NoteButton*)nullptr;
	}
}

void NotePad::SetNoteContent(CString strNoteContent)
{
	if (!strNoteContent.IsEmpty())
	{
		this->strNoteContent = strNoteContent;
	}
}

void NotePad::SetNoteSequence(int nNoteSequence)
{
	if (nNoteSequence >= 0)
	{
		this->nNoteSequence = nNoteSequence;
	}
}

void NotePad::SetOverlap(bool bOverlap)
{
	this->bOverlap = bOverlap;
}

void NotePad::SetOverlapCount(int nOverlapCount)
{
	this->nOverlapCount = nOverlapCount;
}

void NotePad::SetNoteOption(NoteOption* pNoteOption)
{
	this->pNoteOption = pNoteOption;
}

CString NotePad::GetNoteContent() const
{
	if (!strNoteContent.IsEmpty())
	{
		return strNoteContent;
	}
	return _T("");
}

unsigned int NotePad::GetNoteSequence() const
{
	if (nNoteSequence >= 0)
	{
		return nNoteSequence;
	}
	return 0;
}

bool NotePad::IsOverlap() const
{
	return bOverlap;
}

int NotePad::GetOverlapCount() const
{
	return nOverlapCount;
}

NotePad::NoteOption* NotePad::GetNoteOption() const
{
	return pNoteOption;
}

CEdit* NotePad::GetEditBox() const
{
	return editBox;
}

NoteButton* NotePad::GetBorderButton() const
{
	return borderButton;
}

ThemeData* NotePad::GetThemeData() const
{
	return themeData;
}

void NotePad::LoadNoteOption(CMarkup* loadXML, int nNoteSequence)
{
	CString strFullPath = _T("");
	CString strText = _T("");
	strText.Format(_T("%d"), nNoteSequence);
	strFullPath = _T("conf\\") + strText + _T(".opt");
	// 노트옵션정보 xml 불러오기 없으면 자동생성됨
	if (false == loadXML->Load(strFullPath))
	{
		CMarkup saveMarkup;
		CString strFormat = _T("");
		saveMarkup.AddElem(_T("notepad"));
		saveMarkup.AddAttrib(_T("sequence"), strText);
		saveMarkup.IntoElem();
		
		saveMarkup.AddElem(_T("option"));
		strFormat.Format(_T("%d"), (int)DEFAULT_THEME_1_COLOR_1);
		saveMarkup.AddAttrib(_T("notecolor"), strFormat);
		strFormat.Format(_T("%d"), (int)DEFAULT_THEME_1_FONTSTYLE_1);
		saveMarkup.AddAttrib(_T("notefontstyle"), strFormat);

		CString strXML = saveMarkup.GetDoc();
		//LoadXml 함수에서 "hr = 0x800401f0 : CoInitialize가 호출되지 않았습니다." 에러가 발생하여 CoInitializeEx와 CoUninitialize 함수 호출
		HRESULT hr = CoInitializeEx(NULL, COINIT_APARTMENTTHREADED | COINIT_DISABLE_OLE1DDE);	// https://docs.microsoft.com/ko-kr/windows/win32/learnwin32/initializing-the-com-library?redirectedfrom=MSDN
		JWXml::CXml saveXML;
		saveXML.LoadXml((LPCTSTR)strXML);
		saveXML.SaveWithFormatted(strFullPath);
		saveXML.Close();
		CoUninitialize();	// https://docs.microsoft.com/ko-kr/windows/win32/learnwin32/initializing-the-com-library?redirectedfrom=MSDN
	}

	if (false == loadXML->Load(strFullPath))
	{
		return;
	}

	if (loadXML->FindElem(_T("notepad")))
	{
		if (_ttoi(loadXML->GetAttrib(_T("sequence"))) == nNoteSequence)
		{
			loadXML->IntoElem();
			if (loadXML->FindElem(_T("option")))
			{
				loadXML->IntoElem();
			}
		}
	}


}