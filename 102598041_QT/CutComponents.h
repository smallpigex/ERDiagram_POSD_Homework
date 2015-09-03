#pragma once
#include "../102598041_new/Command.h"
#include "../102598041_new/ERModel.h"
#include <vector>

using namespace std;

class CutComponents : public Command
{
private:
	ERModel *erModel;
	vector<int> componentsId;
	vector<Components *> cutComponents;

public:
	CutComponents(ERModel *, vector<int>);
	~CutComponents(void);
	void Execute();
	void Unexecute();
};

