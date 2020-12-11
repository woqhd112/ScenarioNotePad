#pragma once
#include "ThemeData.h"
#include "CMarkup\Markup.h"
#include "NoteButton.h"

class NotePad
{
public:
	enum NoteColor
	{
		DEFAULT_THEME_1_COLOR_1 = 0,
		DEFAULT_THEME_1_COLOR_2 = 1,
		DEFAULT_THEME_1_COLOR_3 = 2,
		DEFAULT_THEME_1_COLOR_4 = 3,
		DEFAULT_THEME_2_COLOR_1 = 4,
		DEFAULT_THEME_2_COLOR_2 = 5,
		DEFAULT_THEME_2_COLOR_3 = 6,
		DEFAULT_THEME_2_COLOR_4 = 7,
		DEFAULT_THEME_3_COLOR_1 = 8,
		DEFAULT_THEME_3_COLOR_2 = 9,
		DEFAULT_THEME_3_COLOR_3 = 10,
		DEFAULT_THEME_3_COLOR_4 = 11,
		DEFAULT_THEME_4_COLOR_1 = 12,
		DEFAULT_THEME_4_COLOR_2 = 13,
		DEFAULT_THEME_4_COLOR_3 = 14,
		DEFAULT_THEME_4_COLOR_4 = 15
	};

	enum NoteFontStyle
	{
		DEFAULT_THEME_1_FONTSTYLE_1 = 0,
		DEFAULT_THEME_1_FONTSTYLE_2 = 1,
		DEFAULT_THEME_1_FONTSTYLE_3 = 2,
		DEFAULT_THEME_2_FONTSTYLE_1 = 3,
		DEFAULT_THEME_2_FONTSTYLE_2 = 4,
		DEFAULT_THEME_2_FONTSTYLE_3 = 5,
		DEFAULT_THEME_3_FONTSTYLE_1 = 6,
		DEFAULT_THEME_3_FONTSTYLE_2 = 7,
		DEFAULT_THEME_3_FONTSTYLE_3 = 8,
		DEFAULT_THEME_4_FONTSTYLE_1 = 9,
		DEFAULT_THEME_4_FONTSTYLE_2 = 10,
		DEFAULT_THEME_4_FONTSTYLE_3 = 11,
	};

	struct NoteOption
	{
		NoteColor noteColor;
		NoteFontStyle noteFontStyle;
	};


// 함수 //
public:
	NotePad();
	NotePad(ThemeData* themeData);
	~NotePad();

	void SetNoteContent(CString strNoteContent);
	void SetNoteSequence(int nNoteSequence);
	void SetOverlap(bool bOverlap);
	void SetOverlapCount(int nOverlapCount);
	void SetNoteOption(NoteOption* pNoteOption);
	CString GetNoteContent() const;
	unsigned int GetNoteSequence() const;
	bool IsOverlap() const;
	int GetOverlapCount() const;
	NoteOption* GetNoteOption() const;
	CEdit* GetEditBox() const;
	NoteButton* GetBorderButton() const;
	ThemeData* GetThemeData() const;

	void LoadNoteOption(CMarkup* loadXML, int nNoteSequence);

private:

//////////

// 변수 //
public:

private:
	CString strNoteContent;
	unsigned int nNoteSequence;
	bool bOverlap;
	int nOverlapCount;

	ThemeData* themeData;
	CEdit* editBox;
	//CMFCButton* borderButton;
	NoteButton* borderButton;
	NoteOption* pNoteOption;
//////////
};

