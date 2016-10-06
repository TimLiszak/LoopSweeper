#include "StdAfx.h"
#include "Window.h"
#include "Render2d.h"

CWindow::CWindow(VECTOR InLocation) : Location(InLocation)
{
}

void CWindow::Update(const FLOAT DeltaTime)
{
	for (std::vector<CWindow*>::iterator it = SubWindows.begin(); it != SubWindows.end(); ++it)
	{
		(*it)->Update(DeltaTime);
	}
}

void CWindow::Render()
{
	for (std::vector<CWindow*>::iterator it = SubWindows.begin(); it != SubWindows.end(); ++it)
	{
		(*it)->BeginWindow();
		(*it)->Render();
		(*it)->EndWindow();
	}
}

void CWindow::Term()
{
	for (std::vector<CWindow*>::iterator it = SubWindows.begin(); it != SubWindows.end(); ++it)
	{
		(*it)->Term();
		delete (*it);
	}
	SubWindows.clear();
}

void CWindow::BeginWindow()
{
	CRender2d::PushMatrix();
	CRender2d::Translate(Location);
}

void CWindow::EndWindow()
{
	CRender2d::PopMatrix();
}

bool CWindow::IsInWindow(VECTOR InLocation)
{
	for (std::vector<CWindow*>::iterator it = SubWindows.begin(); it != SubWindows.end(); ++it)
	{
		if ((*it)->IsInWindow(InLocation - Location))
		{
			return true;
		}
	}

	return InLocation.x >= Location.x &&
		InLocation.x <= Location.x + GetWindowDimensions().x &&
		InLocation.y >= Location.y &&
		InLocation.y <= Location.y + GetWindowDimensions().y;
}

void CWindow::OnLeftClick(VECTOR vPos, VECTOR vWorld)
{
	CWindow* FoundWindow = nullptr;
	for (std::vector<CWindow*>::iterator it = SubWindows.begin(); it != SubWindows.end(); ++it)
	{
		if ((*it)->IsInWindow(vPos))
		{
			FoundWindow = (*it);
			break;
		}
	}

	if (FoundWindow)
	{
		FoundWindow->OnLeftClick(vPos - FoundWindow->Location, vWorld);
	}
}

void CWindow::OnRightClick(VECTOR vPos, VECTOR vWorld)
{
	CWindow* FoundWindow = nullptr;
	for (std::vector<CWindow*>::iterator it = SubWindows.begin(); it != SubWindows.end(); ++it)
	{
		if ((*it)->IsInWindow(vPos))
		{
			FoundWindow = (*it);
			break;
		}
	}

	if (FoundWindow)
	{
		FoundWindow->OnRightClick(vPos - FoundWindow->Location, vWorld);
	}
}
