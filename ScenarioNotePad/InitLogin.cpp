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
	// �α��� ����
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
	// ��񿬵��Ͽ� �ó����������Ͱ� �޾Ƽ� �ֱ�

	return bJustReturn;
}

bool InitLogin::LoadXML(std::vector<ScenarioData*>& vScenarioData)
{
	bool bJustReturn = false;
	// XML�����Ͽ� �ó����������Ͱ� �޾Ƽ� �ֱ�
	// �ϴ� �׽�Ʈ�� �����غ���
	int nSequence = 0;
	for (int i = 0; i < 4; i++)
	{ 
		CString strText = _T("");
		ScenarioData* pScenarioData = new ScenarioData();
		ThemeData::Theme theme = (ThemeData::Theme)i;
		ThemeData* pThemeData = new ThemeData(theme);
		
		strText.Format(_T("�ó�����%d"), i + 1);
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
				strtest = _T("�ȴ´�");
			}
			else if (i == 1)
			{
				strtest = _T("�޸���");
			}
			else if (i == 2)
			{
				strtest = _T("������");
			}
			else
			{
				strtest = _T("����");
			}
			strText.Format(_T("%s %d"), strtest, j + 1);
			pNotePad->SetNoteContent(strText);
			pNotePad->SetNoteSequence(++nSequence);

			CMarkup loadNoteOptionXML;
			// ���ο� xml�����Ͽ� �ɼǵ����͹޾ƿ���
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