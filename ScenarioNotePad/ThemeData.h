#pragma once
#include "afxdialogex.h"

class ThemeData
{
public:
	enum Theme
	{
		DEFAULT_THEME_1 = 0,
		DEFAULT_THEME_2 = 1,
		DEFAULT_THEME_3 = 2,
		DEFAULT_THEME_4 = 3
	};


// 함수 //
public:
	ThemeData();
	ThemeData(Theme theme);
	~ThemeData();

	Theme GetTheme();
	CString GetThemeName();
	void SetTheme(Theme theme);
	void SetThemeName(CString themeName);
	int GetThemeMainImg() const;
	int GetThemeSubImg() const;

private:
//////////
	CString LoadThemeName(Theme theme);
	void SetThemeImg(Theme theme);

// 변수 //
public:

private:
	Theme thisTheme;
	CString strThemeName;
	int nThemeMainImgId;
	int nThemeSubImgId;

//////////
};

