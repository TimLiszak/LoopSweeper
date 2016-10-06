#ifndef _WINDOW_H_
#define _WINDOW_H_

#include "GameEngine.h"
class CWorkspace;

class CWindow
{
public:
	CWindow(VECTOR InLocation);
	virtual ~CWindow() {}

	virtual void Update(const FLOAT DeltaTime);
	virtual void Render();
	virtual void Term();

	virtual void BeginWindow();
	virtual void EndWindow();

	virtual bool IsInWindow(VECTOR InLocation);

	virtual void OnLeftClick(VECTOR vPos, VECTOR vWorld);
	virtual void OnRightClick(VECTOR vPos, VECTOR vWorld);

	virtual void ClearAll() {}

	VECTOR Location;
	bool bDrawBackground;

protected:
	virtual VECTOR GetWindowDimensions() = 0;

	CWorkspace* Workspace;

	std::vector<class CWindow*> SubWindows;
};

#endif