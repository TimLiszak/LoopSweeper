#include "StdAfx.h"
#include "Workspace.h"
#include "Render2d.h"
#include "Input.h"
#include "Window.h"
#include "LoopBoard.h"
#include "LoopTimer.h"
#include "AudioDevice.h"
#include "PopupManager.h"
#include "Instrument.h"
#include "..\resource.h"

const int TUNING_MENU_ID = 41000;
const int CLEAR_NOTES_ID = 53454;

void CWorkspace::Init()
{
	CAudioDevice::Get()->Init();

	CKeyboard* pKeyboard = GetGameEngine()->GetInput()->GetKeyboard();
	CMouse* pMouse = GetGameEngine()->GetInput()->GetMouse();
	pMouse->Callbacks.push_back(this);
	pKeyboard->Callbacks.push_back(this);
	GetGameEngine()->AddMenuCallback(this);

	LoopTimer = new CLoopTimer(120.0f, 4, 1);
	LoopTimer->AddBeatCallback(this);

	LoopBoard = new CLoopBoard(LoopTimer, VECTOR(300.0f, 200.0f));
	Windows.push_back(LoopBoard);

	LoopTimer->Play();
}

void CWorkspace::BeatCallback(int Beat, int Measure)
{
}

void CWorkspace::Update(const FLOAT DeltaTime)
{
	CAudioDevice::Get()->Update(DeltaTime);

	for (std::vector<CWindow*>::iterator it = Windows.begin(); it != Windows.end(); ++it)
	{
		(*it)->Update(DeltaTime);
	}

	LoopTimer->Update(DeltaTime);
}

void CWorkspace::Term()
{
	for (std::vector<CWindow*>::iterator it = Windows.begin(); it != Windows.end(); ++it)
	{
		(*it)->Term();
		delete (*it);
	}
	Windows.clear();

	delete LoopTimer;
}

void CWorkspace::Render()
{
	for (std::vector<CWindow*>::iterator it = Windows.begin(); it != Windows.end(); ++it)
	{
		(*it)->BeginWindow();
		(*it)->Render();
		(*it)->EndWindow();
	}
}

void CWorkspace::MouseDownCallback(EMouseButton eButton, VECTOR vPos)
{
	CWindow* FoundWindow = nullptr;
	for (std::vector<CWindow*>::iterator it = Windows.begin(); it != Windows.end(); ++it)
	{
		if ((*it)->IsInWindow(vPos))
		{
			FoundWindow = (*it);
			break;
		}
	}

	if (eButton == EMouseButton_Left)
	{
		if (FoundWindow)
		{
			FoundWindow->OnLeftClick(vPos - FoundWindow->Location, vPos);
		}
	}

	if (eButton == EMouseButton_Right)
	{
		if (FoundWindow)
		{
			FoundWindow->OnRightClick(vPos - FoundWindow->Location, vPos);
		}
	}
}

void CWorkspace::MouseUpCallback(EMouseButton eButton, VECTOR vPos)
{
}

void CWorkspace::MouseMoveCallback(VECTOR vPos)
{
}

void CWorkspace::MenuSelected(string MenuName, INT nMenuId)
{
}

void CWorkspace::KeyDownCallback(int nKey)
{
}

void CWorkspace::KeyUpCallback(int nKey)
{
}
