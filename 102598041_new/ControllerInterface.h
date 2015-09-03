#pragma once
#include <iostream>
#include "TextUI.h"

using namespace std;

class TextUI;

class ControllerInterface
{
public:
	ControllerInterface(void);
	~ControllerInterface(void);
	virtual void ProcessCommand() = 0;
	virtual void ProcessInput(string) = 0;
};

