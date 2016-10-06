#include "StdAfx.h"
#include "LoopBoard.h"
#include "Render2d.h"
#include "Workspace.h"
#include "LoopTimer.h"
#include "Cell.h"
#include "Instrument.h"
#include "InstrumentManager.h"
#include "EditorOption.h"

#include <vector>
using namespace std;

static const VECTOR CellWidth(CCell::CellWidth, 0.0f);
static const VECTOR CellHeight(0.0f, CCell::CellHeight);

CLoopBoard::CLoopBoard(CLoopTimer* InLoopTimer, VECTOR InLocation) : CWindow(InLocation)
{
	LoopTimer = InLoopTimer;

	vector<string> InstrumentNames = CInstrumentManager::Get()->GetInstrumentNames();

	int CellsPerMeasure = LoopTimer->GetBeatsPerMeasure() * 4;

	NumRows = InstrumentNames.size();
	NumColumns = CellsPerMeasure * LoopTimer->GetNumMeasures();

	for (int y = 0; y < NumRows; y++)
	{
		VECTOR OptLocation = CellWidth * NumColumns + CellHeight * (float)y;
		CEditorOption* Option = new CEditorOption("Instrument", OptLocation, VECTOR(100.0f, 60.0f), InstrumentNames, y);
		CInstrument* Instrument = CInstrumentManager::Get()->GetInstrument(y);

		for (int x = 0; x < NumColumns; x++)
		{
			int Beat = x % CellsPerMeasure;
			int Measure = x / CellsPerMeasure;
			VECTOR Location = CellWidth * (float)x + CellHeight * (float)y;

			CCell* Cell = new CCell(Location, Beat, Measure, Instrument);
			SubWindows.push_back(Cell);
			InLoopTimer->AddBeatCallback(Cell);
			Option->AddCallback(Cell);
		}

		SubWindows.push_back(Option);
	}


}

void CLoopBoard::Update(const FLOAT DeltaTime)
{
	CWindow::Update(DeltaTime);
}

void CLoopBoard::Render()
{
	CWindow::Render();

	VECTOR Buffer(0.0f, 20.0f);

	VECTOR MaxScroll = CellWidth * (float)NumColumns;
	VECTOR Scroll = MaxScroll * LoopTimer->GetPercent();

	VECTOR TopLoc = Scroll;
	VECTOR BotLoc = TopLoc + (CellHeight * (float)NumRows);

	CRender2d::DrawLine(TopLoc - Buffer, BotLoc + Buffer, COLOUR_RGB(1.0f, 0.0f, 0.0f), 2.0f);
	CRender2d::DrawLine(TopLoc - Buffer - MaxScroll, BotLoc + Buffer - MaxScroll, COLOUR_RGB(1.0f, 0.0f, 0.0f), 2.0f);
	CRender2d::DrawLine(TopLoc - Buffer + MaxScroll, BotLoc + Buffer + MaxScroll, COLOUR_RGB(1.0f, 0.0f, 0.0f), 2.0f);
}

VECTOR CLoopBoard::GetWindowDimensions()
{
	return VECTOR(CCell::CellWidth * NumColumns, CCell::CellHeight * NumRows);
}
