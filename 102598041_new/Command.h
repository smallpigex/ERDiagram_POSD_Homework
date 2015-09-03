#pragma once
#include "ERModel.h"
#include "MessageOfConstString.h"

class Command
{
public:
	Command(void);
	virtual ~Command(void);
	virtual void Execute() = 0;
	virtual void Unexecute() = 0;
};

