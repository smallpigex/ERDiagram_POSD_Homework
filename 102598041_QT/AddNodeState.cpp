#include "AddNodeState.h"


AddNodeState::AddNodeState(GUIPresentation *guiPresentation)
{
	this->guiPresentation = guiPresentation;
}


AddNodeState::~AddNodeState(void)
{
}

void AddNodeState::MousePressEvent()
{
	guiPresentation->ChangeState(StringState::POINT_NODE_STATE);
	//guiPresentation->SetStateMessage(StringState::ADD_NODE_STATE);
	guiPresentation->NotifyObserverDisplayEditText();
	//return StringState::INPUT_DIALOG;
}

void AddNodeState::MouseReleaseEvent()
{
	//guiPresentation->SetStateMessage(StringState::ADD_NODE_STATE);
}

void AddNodeState::MouseMoveEvent()
{
	guiPresentation->NotifyObserverUpdatePreviewPos();
}
