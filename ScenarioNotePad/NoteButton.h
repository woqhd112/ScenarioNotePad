#pragma once

// NoteButton
class TypeListView;
class NoteButton : public CMFCButton
{
	DECLARE_DYNAMIC(NoteButton)

public:
	NoteButton();
	virtual ~NoteButton();

private:

protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnMouseHover(UINT nFlags, CPoint point);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnMouseLeave();
};


