#pragma once

#include <afxwin.h>
#include "ScenarioData.h"


class InitLogin
{

// �Լ� //
public:
	InitLogin();
	~InitLogin();
	void InitData(bool& bLogin, std::vector<ScenarioData*>& vScenarioData);

private:
//////////
	bool LoadDataBase(std::vector<ScenarioData*>& vScenarioData);
	bool LoadXML(std::vector<ScenarioData*>& vScenarioData);

// ���� //
public:

private:

//////////
};

