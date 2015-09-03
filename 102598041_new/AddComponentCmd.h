#pragma once
#include "Command.h"
#include "gtest/gtest_prod.h"

class AddComponentCmd : public Command
{
	friend class AddComponentCmdTest;
	FRIEND_TEST(AddComponentCmdTest, Execute);

private:
	ERModel *erModel;
	string componentType;
	string componentName;
	int tmpComponentId;
	int pointX;
	int pointY;

public:
	AddComponentCmd(ERModel *, string, string);
	~AddComponentCmd(void);
	void Execute();
	void Unexecute();
};

