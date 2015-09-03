#include "PrimaryKeyState.h"


PrimaryKeyState::PrimaryKeyState(GUIPresentation *guiPresentation)
{
	this->guiPresentation = guiPresentation;
}


PrimaryKeyState::~PrimaryKeyState(void)
{
}

void PrimaryKeyState::MousePressEvent()
{

}

void PrimaryKeyState::MouseReleaseEvent()
{
	guiPresentation->SetPrimaryKey();
}

void PrimaryKeyState::MouseMoveEvent()
{
	
}
