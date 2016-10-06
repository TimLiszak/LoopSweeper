#ifndef _WORKSPACE_H_
#define _WORKSPACE_H_

#include "GameEngine.h"
#include "Mouse.h"
#include "Keyboard.h"
#include "LoopTimer.h"
#include <vector>

class CWorkspace : public CGameMode, IMouseCallback, IKeyboardCallback, IBeatCallback, IMenuCallback
{
public:
	void	Init();
	void	Update(const FLOAT DeltaTime);
	void	Term();
	void	Render();

	virtual void	MouseDownCallback(EMouseButton eButton, VECTOR vPos);
	virtual void	MouseUpCallback(EMouseButton eButton, VECTOR vPos);
	virtual void	MouseMoveCallback(VECTOR vPos);
	virtual void	MenuSelected(string MenuName, INT nMenuId);

	virtual void	KeyDownCallback(int nKey);
	virtual void	KeyUpCallback(int nKey);

	virtual void	BeatCallback(int Beat, int Measure);

protected:
	std::vector<class CWindow*> Windows;
	class CLoopTimer* LoopTimer;
	class CLoopBoard* LoopBoard;
};

#endif