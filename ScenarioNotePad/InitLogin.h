#pragma once

#include <afxwin.h>
#include "ScenarioData.h"


class InitLogin
{

// 함수 //
public:
	InitLogin();
	~InitLogin();
	void InitData(bool& bLogin, std::vector<ScenarioData*>& vScenarioData);

private:
//////////
	bool LoadDataBase(std::vector<ScenarioData*>& vScenarioData);
	bool LoadXML(std::vector<ScenarioData*>& vScenarioData);

// 변수 //
public:

private:

//////////
};

