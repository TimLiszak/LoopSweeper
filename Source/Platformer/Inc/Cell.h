#ifndef _CELL_H_
#define _CELL_H_

#include "GameEngine.h"
#include "Window.h"
#include "LoopTimer.h"
#include <vector>

class CCell : public CWindow, public IBeatCallback, public IMenuCallback
{
public:
	static const float CellWidth;
	static const float CellHeight;

	CCell(VECTOR InLocation, int Sixteenth, int Measure, class CInstrument* Instrument);
	virtual ~CCell() {}

	virtual void Update(const FLOAT DeltaTime);
	virtual void Render();

	virtual void OnLeftClick(VECTOR vPos, VECTOR vWorld);
	virtual void OnRightClick(VECTOR vPos, VECTOR vWorld);

	virtual void OnQuarter(int Quarter, int Measure);
	virtual void OnEighth(int Eighth, int Measure);
	virtual void OnSixteenth(int Sixteenth, int Measure);

	virtual void MenuSelected(string MenuName, INT nMenuId);

protected:
	virtual VECTOR GetWindowDimensions();

	int Sixteenth;
	int Measure;
	CInstrument* Instrument;

	bool bFlash;
	
	bool bBeat;
	string SoundName;
	int SoundId;
};

#endif