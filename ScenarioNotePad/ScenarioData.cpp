#include "pch.h"
#include "ScenarioData.h"

ScenarioData::ScenarioData()
{
	strScenarioName = _T("");
	nScenarioSequence = 0;
}

ScenarioData::~ScenarioData()
{
	if (pThemeData)
	{
		delete pThemeData;
		pThemeData = (ThemeData*)nullptr;
	}

	for (int i = 0; i < (int)vNotePad.size(); i++)
	{
		NotePad* pNotePad = vNotePad.at(i);
		delete pNotePad;
		pNotePad = (NotePad*)nullptr;
	}
	vNotePad.clear();
}

void ScenarioData::SetScenarioName(CString strScenarioName)
{
	this->strScenarioName = strScenarioName;
}

void ScenarioData::SetScenarioSequence(int nScenarioSequence)
{
	this->nScenarioSequence = nScenarioSequence;
}

void ScenarioData::SetVectorNotePad(std::vector<NotePad*> notePad)
{
	this->vNotePad = notePad;
}

void ScenarioData::SetThemeData(ThemeData* pThemeData)
{
	if (pThemeData)
	{
		this->pThemeData = pThemeData;
	}
}

CString ScenarioData::GetScenarioName() const
{
	if (!strScenarioName.IsEmpty())
	{
		return strScenarioName;
	}
	return _T("");
}

unsigned int ScenarioData::GetScenarioSequence() const
{
	if (nScenarioSequence >= 0)
	{
		return nScenarioSequence;
	}
	return 0;
}

std::vector<NotePad*> ScenarioData::GetVectorNotePad() const
{
	return vNotePad;
}

ThemeData* ScenarioData::GetThemeData() const
{
	return pThemeData;
}