#pragma once
#include "controllerinterface.h"
#include "MessageOfConstString.h"

class MainMenuController : public ControllerInterface
{
private:
	TextUI *textUI;

public:
	MainMenuController(void);
	~MainMenuController(void);
	void ProcessInput(string);
	bool CheckInput(string);
	void CallCommand(string);
};

