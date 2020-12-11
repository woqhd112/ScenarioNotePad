#include "pch.h"
#include "ThemeData.h"
#include "Resource.h"

ThemeData::ThemeData()
{
	thisTheme = DEFAULT_THEME_1;
	LoadThemeName(thisTheme);
}

ThemeData::ThemeData(Theme theme)
{
	thisTheme = theme;
	LoadThemeName(thisTheme);
}

ThemeData::~ThemeData()
{

}

CString ThemeData::LoadThemeName(Theme theme)
{
	CString strText = _T("");
	switch (theme)
	{
	case DEFAULT_THEME_1:
		strText = _T("기본테마1");
		break;
	case DEFAULT_THEME_2:
		strText = _T("기본테마2");
		break;
	case DEFAULT_THEME_3:
		strText = _T("기본테마3");
		break;
	default: break;
	}

	SetThemeImg(theme);

	return strText;
}

ThemeData::Theme ThemeData::GetTheme()
{
	return thisTheme;
}

CString ThemeData::GetThemeName()
{
	if (!strThemeName.IsEmpty())
	{
		return strThemeName;
	}
	return _T("");
}

void ThemeData::SetThemeImg(Theme theme)
{
	switch (theme)
	{
	case DEFAULT_THEME_1 :
		nThemeMainImgId = IDB_PNG_BOOK;
		nThemeSubImgId = IDB_PNG_BOOK2;
		break;
	case DEFAULT_THEME_2 :
		nThemeMainImgId = IDB_PNG_BOOK;
		nThemeSubImgId = IDB_PNG_BOOK2;
		break;
	case DEFAULT_THEME_3 : 
		nThemeMainImgId = IDB_PNG_BOOK;
		nThemeSubImgId = IDB_PNG_BOOK2;
		break;
	default : break;
	}
}

void ThemeData::SetTheme(Theme theme)
{
	this->thisTheme = theme;
}

void ThemeData::SetThemeName(CString themeName)
{
	this->strThemeName = themeName;
}

int ThemeData::GetThemeMainImg() const 
{
	return nThemeMainImgId;
}

int ThemeData::GetThemeSubImg() const
{
	return nThemeSubImgId;
}