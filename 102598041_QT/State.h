#pragma once
#include <iostream>
#include <string>
#include "QTConstString.h"

class State
{
public:
	State(void);
	virtual ~State(void);
	virtual void MousePressEvent() = 0;
	virtual void MouseReleaseEvent() = 0;
	virtual void MouseMoveEvent() = 0;
};

