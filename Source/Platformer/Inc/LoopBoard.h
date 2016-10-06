#ifndef _LOOPBOARD_H_
#define _LOOPBOARD_H_

#include "GameEngine.h"
#include "Window.h"

class CLoopBoard : public CWindow
{
public:
	CLoopBoard(class CLoopTimer* LoopTimer, VECTOR InLocation);
	virtual ~CLoopBoard() {}

	virtual void Update(const FLOAT DeltaTime);
	virtual void Render();

protected:
	virtual VECTOR GetWindowDimensions();
	
	int NumColumns;
	int NumRows;
	CLoopTimer* LoopTimer;
};

#endif