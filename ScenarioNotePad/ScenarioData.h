#pragma once
#include <atlstr.h>
#include <vector>
#include "NotePad.h"
#include "ThemeData.h"


class ScenarioData
{


// 함수 //
public:
	ScenarioData();
	~ScenarioData();

	void SetScenarioName(CString strScenarioName);
	void SetScenarioSequence(int nScenarioSequence);
	void SetVectorNotePad(std::vector<NotePad*> notePad);
	void SetThemeData(ThemeData* pThemeData);
	CString GetScenarioName() const;
	unsigned int GetScenarioSequence() const;
	std::vector<NotePad*> GetVectorNotePad() const;
	ThemeData* GetThemeData() const;

private:
	
//////////

// 변수 //
public:

private:
	CString strScenarioName;
	unsigned int nScenarioSequence;
	std::vector<NotePad*> vNotePad;
	ThemeData* pThemeData;

//////////
};

