#pragma once
#include "../102598041_new/command.h"

class SetPrimaryKeyCmd : public Command
{
private:
	int tmpComponentId;
	ERModel *erModel;

public:
	SetPrimaryKeyCmd(ERModel *, int);
	~SetPrimaryKeyCmd(void);
	void Execute();
	void Unexecute();
};

