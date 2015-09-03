#pragma once
#include <stack>
#include "Command.h"

using namespace std;

class CommandManager
{
	friend class CommandManagerTest;
	FRIEND_TEST(CommandManagerTest, Execute);
	FRIEND_TEST(CommandManagerTest, Undo);
	FRIEND_TEST(CommandManagerTest, ClearCommand);
	FRIEND_TEST(IntegrateTest, testRedoConnectComponent);

private:
	stack<Command *> undoCommands;
	stack<Command *> redoCommands;

public:
	CommandManager(void);
	~CommandManager(void);
	void Execute(Command *);
	bool Undo();
	bool Redo();
	void ClearCommand();
};

