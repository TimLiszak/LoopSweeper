#ifndef _EDITOROPTION_H_
#define _EDITOROPTION_H_

#include "GameEngine.h"
#include "Window.h"

class CEditorOption : public CWindow, IMenuCallback
{
public:
	static const float CellWidth;
	static const float CellHeight;

	CEditorOption(string MenuName, VECTOR InLocation, VECTOR Dimensions, vector<string> Options, int SelectedOption);
	virtual ~CEditorOption() {}

	virtual void Update(const FLOAT DeltaTime);
	virtual void Render();

	virtual void OnLeftClick(VECTOR vPos, VECTOR vWorld);
	virtual void OnRightClick(VECTOR vPos, VECTOR vWorld);

	virtual void MenuSelected(string MenuName, INT nMenuId);

	virtual void AddCallback(IMenuCallback* Callback);

protected:
	virtual VECTOR GetWindowDimensions();

	VECTOR Dimensions;
	vector<string> Options;
	int SelectedOption;
	string MenuName;

	vector<IMenuCallback*> Callbacks;
};

#endif