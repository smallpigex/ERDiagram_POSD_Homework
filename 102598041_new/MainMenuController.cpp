#include "MainMenuController.h"


MainMenuController::MainMenuController(void)
{
	/*
	textUI = new TextUI(this);
	textUI->DisplayMenu();
	textUI->InputString();*/
}


MainMenuController::~MainMenuController(void)
{
}

void MainMenuController::ProcessInput(string input)
{
	if(!CheckInput(input))
	{
		textUI->DisplayInvalidCommand();
	}
}

bool MainMenuController::CheckInput(string command)
{
	if(command.compare(Menu::ADD_A_NODE) == 0 ||
		command.compare(Menu::CONNECT_TO_NODES) == 0 ||
		command.compare(Menu::DISPLAY_DIAGRAM) == 0 ||
		command.compare(Menu::SET_PRIMARY_KEY) == 0 ||
		command.compare(Menu::DISPLAY_TABLE) == 0 ||
		command.compare(Menu::EXIT) == 0)
	{
		return true;
	}
	else
	{
		return false;
	}
}

void CallCommand(string command)
{
	
}