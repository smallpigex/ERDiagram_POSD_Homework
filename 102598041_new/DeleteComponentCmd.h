#pragma once
#include "Command.h"
#include "ERModel.h"

class DeleteComponentCmd : public Command
{
	friend class DeleteComponentCmdTest;
	FRIEND_TEST(DeleteComponentCmdTest, Execute);
	FRIEND_TEST(DeleteComponentCmdTest, Unexecute);

private:
	int deleteId;
	ERModel *erModel;
	Components *tempComponents;

public:
	DeleteComponentCmd(ERModel *,int);
	~DeleteComponentCmd(void);
	void Execute();
	void Unexecute();

};

