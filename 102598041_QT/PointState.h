#pragma once
#include "state.h"
#include "GUIPresentation.h"

class GUIPresentation;

class PointState : public State
{
	friend class PointStateTest;
	FRIEND_TEST(PointStateTest, MousePressEvent);
private:
	GUIPresentation *guiPresentation;

public:
	PointState(GUIPresentation *);
	~PointState(void);
	void MousePressEvent();
	void MouseReleaseEvent();
	void MouseMoveEvent();
};

