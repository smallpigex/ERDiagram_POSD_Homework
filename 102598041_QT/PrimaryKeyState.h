#pragma once
#include "state.h"
#include "GUIPresentation.h"

class PrimaryKeyState : public State
{
private:
	GUIPresentation *guiPresentation;

public:
	PrimaryKeyState(GUIPresentation *);
	~PrimaryKeyState(void);
	void MousePressEvent();
	void MouseReleaseEvent();
	void MouseMoveEvent();
};

