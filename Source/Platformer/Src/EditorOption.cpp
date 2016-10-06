#include "StdAfx.h"
#include "EditorOption.h"
#include "Render2d.h"
#include "PopupManager.h"

CEditorOption::CEditorOption(string InMenuName, VECTOR InLocation, VECTOR InDimensions, vector<string> InOptions, int InSelectedOption) :
CWindow(InLocation), MenuName(InMenuName), Dimensions(InDimensions), Options(InOptions), SelectedOption(InSelectedOption)
{
}

void CEditorOption::Update(const FLOAT DeltaTime)
{
}

void CEditorOption::Render()
{
	COLOUR_RGB Clr = COLOUR_RGB(0.6f, 0.6f, 0.6f);
	COLOUR_RGB ClrBlack = COLOUR_RGB(0.0f, 0.0f, 0.0f);

	CRender2d::DrawRectOutline(GetWindowDimensions() * 0.5f, GetWindowDimensions() * 0.5f, 0.0f, Clr, ClrBlack);

	CRender2d::PushMatrix();
	CRender2d::Translate(VECTOR(10.0f, GetWindowDimensions().y * 0.5f));
	glRasterPos2f(-4.0f, 0.0f);
	CRender2d::Print("%s", Options[SelectedOption].c_str());
	CRender2d::PopMatrix();
}

VECTOR CEditorOption::GetWindowDimensions()
{
	return Dimensions;
}

void CEditorOption::OnLeftClick(VECTOR vPos, VECTOR vWorld)
{
}

void CEditorOption::OnRightClick(VECTOR vPos, VECTOR vWorld)
{
	CPopupManager::Get()->PopupMenu(MenuName, vWorld, Options, map<unsigned int, string>(), this);
}

void CEditorOption::MenuSelected(string MenuName, INT nMenuId)
{
	SelectedOption = nMenuId;
	for (unsigned int i = 0; i < Callbacks.size(); i++)
	{
		Callbacks[i]->MenuSelected(MenuName, nMenuId);
	}
}

void CEditorOption::AddCallback(IMenuCallback* Callback)
{
	Callbacks.push_back(Callback);
}
