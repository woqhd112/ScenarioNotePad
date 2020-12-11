#include "pch.h"
#include "InitLogin.h"
#include "CMarkup\Markup.h"

InitLogin::InitLogin()
{

}
InitLogin::~InitLogin()
{

}

void InitLogin::InitData(bool& bLogin, std::vector<ScenarioData*>& vScenarioData)
{
	// 로그인 연동
	if (LoadDataBase(vScenarioData))
	{
		bLogin = true;
	}
	else
	{
		if (LoadXML(vScenarioData))
		{
			bLogin = true;
		}
	}
}

bool InitLogin::LoadDataBase(std::vector<ScenarioData*>& vScenarioData)
{
	bool bJustReturn = false;
	// 디비연동하여 시나리오데이터값 받아서 넣기

	return bJustReturn;
}

bool InitLogin::LoadXML(std::vector<ScenarioData*>& vScenarioData)
{
	bool bJustReturn = false;
	// XML연동하여 시나리오데이터값 받아서 넣기
	// 일단 테스트를 진행해보자
	int nSequence = 0;
	for (int i = 0; i < 4; i++)
	{ 
		CString strText = _T("");
		ScenarioData* pScenarioData = new ScenarioData();
		ThemeData::Theme theme = (ThemeData::Theme)i;
		ThemeData* pThemeData = new ThemeData(theme);
		
		strText.Format(_T("시나리오%d"), i + 1);
		pScenarioData->SetScenarioName(strText);
		pScenarioData->SetScenarioSequence(i + 1);
		pScenarioData->SetThemeData(pThemeData);
		std::vector<NotePad*> vNotePad;
		for (int j = 0; j < 7; j++)
		{
			NotePad* pNotePad = new NotePad(pThemeData);
			CString strtest = _T("");
			if (i == 0)
			{
				strtest = _T("걷는다");
			}
			else if (i == 1)
			{
				strtest = _T("달린다");
			}
			else if (i == 2)
			{
				strtest = _T("구른다");
			}
			else
			{
				strtest = _T("기어간다");
			}
			strText.Format(_T("%s %d"), strtest, j + 1);
			pNotePad->SetNoteContent(strText);
			pNotePad->SetNoteSequence(++nSequence);

			CMarkup loadNoteOptionXML;
			// 새로운 xml생성하여 옵션데이터받아오기
			pNotePad->LoadNoteOption(&loadNoteOptionXML, nSequence);
			NotePad::NoteOption* nOption = new NotePad::NoteOption;
			nOption->noteColor = (NotePad::NoteColor)_ttoi(loadNoteOptionXML.GetAttrib(_T("notecolor")));
			nOption->noteFontStyle = (NotePad::NoteFontStyle)_ttoi(loadNoteOptionXML.GetAttrib(_T("notefontstyle")));

			pNotePad->SetNoteOption(nOption);
			vNotePad.push_back(pNotePad);
		}
		pScenarioData->SetVectorNotePad(vNotePad);
		vScenarioData.push_back(pScenarioData);
	}
	bJustReturn = true;

	return bJustReturn;
}