#pragma once
#include "State.h"
#include "GUIPresentation.h"
using namespace std;

class GUIPresentation;

class AddNodeState : public State
{
private:
	GUIPresentation *guiPresentation;

public:
	AddNodeState(GUIPresentation *);
	~AddNodeState(void);
	void MousePressEvent();
	void MouseReleaseEvent();
	void MouseMoveEvent();
};

