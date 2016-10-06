#include "StdAfx.h"
#include "Cell.h"
#include "Render2d.h"
#include "Workspace.h"
#include "Instrument.h"
#include "InstrumentManager.h"
#include "PopupManager.h"

#include <vector>
using namespace std;

const float CCell::CellWidth = 60.0f;
const float CCell::CellHeight = 60.0f;

CCell::CCell(VECTOR InLocation, int InSixteenth, int InMeasure, CInstrument* InInstrument) :
CWindow(InLocation), Sixteenth(InSixteenth), Measure(InMeasure), Instrument(InInstrument)
{
	bFlash = false;
	bBeat = false;
	SoundId = 0; 
	SoundName = Instrument->GetSoundNames()[0];
}

void CCell::Update(const FLOAT DeltaTime)
{
}

void CCell::Render()
{
	COLOUR_RGB Clr = COLOUR_RGB(1.0f, 1.0f, 1.0f);
	COLOUR_RGB ClrFlash = COLOUR_RGB(1.0f, 1.0f, 0.0f);
	COLOUR_RGB ClrBeat = COLOUR_RGB(0.6f, 0.6f, 1.0f);
	COLOUR_RGB ClrBlack = COLOUR_RGB(0.0f, 0.0f, 0.0f);

	CRender2d::DrawRectOutline(GetWindowDimensions() * 0.5f, GetWindowDimensions() * 0.5f, 0.0f, bFlash ? ClrFlash : bBeat ? ClrBeat : Clr, ClrBlack);

	if (bBeat)
	{
		CRender2d::PushMatrix();
		CRender2d::Translate(VECTOR(10.0f, GetWindowDimensions().y * 0.5f));
		glRasterPos2f(-4.0f, 0.0f);
		CRender2d::Print("%s", SoundName.c_str());
		CRender2d::PopMatrix();
	}
}

VECTOR CCell::GetWindowDimensions()
{
	return VECTOR(CellWidth, CellHeight);
}

void CCell::OnLeftClick(VECTOR vPos, VECTOR vWorld)
{
	bBeat = !bBeat;
}

void CCell::OnRightClick(VECTOR vPos, VECTOR vWorld)
{
	CPopupManager::Get()->PopupMenu("Sound", vWorld, Instrument->GetSoundNames(), Instrument->GetCategories(), this);
}

void CCell::MenuSelected(string MenuName, INT nMenuId)
{
	if (MenuName == "Sound")
	{
		bBeat = true;
		SoundId = nMenuId;
		SoundName = Instrument->GetSoundNames()[nMenuId];
	}
	else if (MenuName == "Instrument")
	{
		Instrument = CInstrumentManager::Get()->GetInstrument(nMenuId);

		if (SoundId < Instrument->GetSoundNames().size())
		{
			SoundName = Instrument->GetSoundNames()[SoundId];
		}
		else
		{
			bBeat = false;
			SoundId = 0;
			SoundName = Instrument->GetSoundNames()[0];
		}
	}
}

void CCell::OnQuarter(int InQuarter, int InMeasure)
{
}

void CCell::OnEighth(int InEighth, int InMeasure)
{
}

void CCell::OnSixteenth(int InSixteenth, int InMeasure)
{
	if (InSixteenth == Sixteenth &&
		InMeasure == Measure)
	{
		if (bBeat)
		{
			Instrument->PlaySound(SoundName.c_str());
			bFlash = true;
		}
	}
	else
	{
		if (bFlash && bBeat)
		{
			//Instrument->StopSound(SoundName.c_str());
		}
		bFlash = false;
	}
}
