#ifndef _POPUPMANAGER_H_
#define _POPUPMANAGER_H_

#include "GameEngine.h"
#include <vector>
#include <string>
using namespace std;

class CPopupManager : public IMenuCallback
{
public:
	static CPopupManager* Get()
	{
		if (!pInstance)
		{
			pInstance = new CPopupManager();
		}
		return pInstance;
	}

	virtual ~CPopupManager() {}

	virtual void PopupMenu(string MenuName, VECTOR Location, vector<string> MenuItems, map<unsigned int, string> Categories, IMenuCallback* Callback);

	virtual void MenuSelected(string MenuName, INT nMenuId);

protected:
	CPopupManager();
	static CPopupManager*		pInstance;
	IMenuCallback* MenuCallback;
	string PopupMenuName;
};

#endif