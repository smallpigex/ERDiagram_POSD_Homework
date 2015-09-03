#pragma once
#include "../102598041_new/command.h"
#include "../102598041_new/ERModel.h"

class PasteComponents : public Command
{
private:
	ERModel *erModel;

public:
	PasteComponents(ERModel *);
	~PasteComponents(void);
	void Execute();
	void Unexecute();
};

