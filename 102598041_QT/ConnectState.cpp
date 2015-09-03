#include "ConnectState.h"


ConnectState::ConnectState(GUIPresentation *guiPresentation)
{
	this->guiPresentation = guiPresentation;
}


ConnectState::~ConnectState(void)
{
}

void ConnectState::MousePressEvent()
{
}

void ConnectState::MouseReleaseEvent()
{
	guiPresentation->ConnectNode();
}

void ConnectState::MouseMoveEvent()
{
}

