#include "CommandManager.h"


CommandManager::CommandManager(void)
{
}

CommandManager::~CommandManager(void)
{
	ClearCommand();
}

void CommandManager::Execute(Command *command)
{
	command->Execute();
	undoCommands.push(command);

	// cleanup and release redoable commands
	while (!redoCommands.empty()) 
	{
		Command* command = redoCommands.top();
		redoCommands.pop();
		delete command;
	}
}

bool CommandManager::Undo()
{
	if (undoCommands.size() == 0)
	{
		return false;
	}

	Command* command = undoCommands.top();
	undoCommands.pop();
	command->Unexecute(); // redo the command
	redoCommands.push(command);
	return true;
}

bool CommandManager::Redo()
{
	if (redoCommands.size() == 0)
	{
		return false;
	}

	Command* command = redoCommands.top();
	redoCommands.pop();
	command->Execute(); // redo the command
	undoCommands.push(command);
	return true;
}

void CommandManager::ClearCommand()
{
	while (!undoCommands.empty())
	{
		Command* command = undoCommands.top();
		undoCommands.pop();
		delete command;
	}

	while (!redoCommands.empty())
	{
		Command* command = redoCommands.top();
		redoCommands.pop();
		delete command;
	}
}