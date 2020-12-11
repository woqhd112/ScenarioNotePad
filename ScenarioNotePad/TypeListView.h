#pragma once
#include "ScenarioData.h"
#include <vector>

// TypeListView 대화 상자

class TypeListView : public CDialogEx
{
	DECLARE_DYNAMIC(TypeListView)

public:
	TypeListView(CWnd* pParent = nullptr);   // 표준 생성자입니다.
	virtual ~TypeListView();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_TYPE_LIST };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

public:
	enum Type
	{
		TYPE_TABLE = 0,
		TYPE_BOOK
	};

	Type type;

private:

	// controller size
	unsigned int nTypeEdit_size_x;
	unsigned int nTypeEdit_size_y;
	unsigned int nTypeButton_size_x;
	unsigned int nTypeButton_size_y;
	unsigned int nTypeList_size_x;
	unsigned int nTypeList_size_y;

	// set text
	int nTestSize_x;
	int nTestSize_y;
	int nCount;
	int nIdx;
	int nId;

	//note variable
	std::vector<CEdit*> noteVector;
	std::vector<NoteButton*> buttonVector;

public:
	bool Init(Type type);
	void InsertData(NotePad* pNotePad);
	void InsertData(ScenarioData* pNotePad);

private:
	void SetNoteStyle(NotePad* pNotePad);
	void ButtonStyle(NotePad* pNotePad, int nId);
	void EditStyle(NotePad* pNotePad, int nId);

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
};
