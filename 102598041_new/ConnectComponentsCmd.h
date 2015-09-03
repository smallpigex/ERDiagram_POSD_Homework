#pragma once
#include "Command.h"
class ConnectComponentsCmd : public Command
{
	friend class ConnectComponentsCmdTest;
	FRIEND_TEST(ConnectComponentsCmdTest, Execute);
	FRIEND_TEST(ConnectComponentsCmdTest, Unexecute);

private:
	ERModel *erModel;
	string firstId, secondId, cardinality;
	Components *connection;

public:
	ConnectComponentsCmd(ERModel *, string, string, string);
	~ConnectComponentsCmd(void);
	void Execute();
	void Unexecute();
};

