#pragma once
#include "State.h"
#include "GUIPresentation.h"

class GUIPresentation;

class ConnectState : public State
{
private:
	GUIPresentation *guiPresentation;

public:
	ConnectState(GUIPresentation *);
	~ConnectState(void);
	void MousePressEvent();
	void MouseReleaseEvent();
	void MouseMoveEvent();
};

