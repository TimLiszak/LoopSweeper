#include "StdAfx.h"
#include "PopupManager.h"

CPopupManager* CPopupManager::pInstance = NULL;

CPopupManager::CPopupManager()
{
	GetGameEngine()->AddMenuCallback(this);
	MenuCallback = nullptr;
}

void CPopupManager::PopupMenu(string InMenuName, VECTOR Location, vector<string> MenuItems, map<unsigned int, string> Categories, IMenuCallback* Callback)
{
	MenuCallback = Callback;
	PopupMenuName = InMenuName;

	HWND hWnd = GetGameEngine()->GetView()->GetHWnd();

	RECT Rect;
	GetWindowRect(hWnd, &Rect);

	HMENU hPopupMenu = CreatePopupMenu();

	HMENU hCategoryMenu = nullptr;
	
	for (unsigned int i = 0; i < MenuItems.size(); i++)
	{
		if (Categories.count(i))
		{
			hCategoryMenu = CreatePopupMenu();
			AppendMenu(hPopupMenu, MF_POPUP, (UINT)hCategoryMenu, Categories[i].c_str());
		}

		AppendMenu(hCategoryMenu ? hCategoryMenu : hPopupMenu, MF_BYPOSITION | MF_STRING, i, MenuItems[i].c_str());
	}

	SetForegroundWindow(hWnd);
	TrackPopupMenu(hPopupMenu, TPM_TOPALIGN | TPM_LEFTALIGN, Location.x + Rect.left, Location.y + Rect.top + 40.0f, 0, hWnd, NULL);
}

void CPopupManager::MenuSelected(string MenuName, INT nMenuId)
{
	if (MenuCallback)
	{
		MenuCallback->MenuSelected(PopupMenuName, nMenuId);
	}
	MenuCallback = nullptr;
}
