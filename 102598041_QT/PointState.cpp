#include "PointState.h"


PointState::PointState(GUIPresentation *guiPresentation)
{
	this->guiPresentation = guiPresentation;
}


PointState::~PointState(void)
{
}

void PointState::MousePressEvent()
{
	guiPresentation->SetIsMove(true);
	guiPresentation->setDeleteActionDisabled();
	guiPresentation->SetStateMessage(StringState::POINT_NODE_STATE);
	guiPresentation->NotifyObserverStoreOldComponentPoint();
}

void PointState::MouseReleaseEvent()
{
	guiPresentation->SetStateMessage(StringState::POINT_NODE_STATE);
	guiPresentation->NotifyObserverStoreNewComponentPoint();
	guiPresentation->MoveComponents();
}

void PointState::MouseMoveEvent()
{
	guiPresentation->SetStateMessage(StringState::POINT_NODE_STATE);
	guiPresentation->NotifyObserverGUIConnectionUpdate();
	guiPresentation->NotifyObserverUpdateGUIComponentPos();
}


