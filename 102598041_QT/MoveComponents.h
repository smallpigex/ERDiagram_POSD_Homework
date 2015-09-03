#pragma once
#include "../102598041_QT/ComponentPoint.h"
#include "../102598041_new/Command.h"
#include <vector>

using namespace std;

class MoveComponents : public Command
{
private:
	ERModel *erModel;
	vector<ComponentPoint> oldComponentsPointData;
	vector<ComponentPoint> newComponentsPointData;

public:
	MoveComponents(ERModel *, vector<ComponentPoint>, vector<ComponentPoint>);
	~MoveComponents(void);
	void Execute();
	void Unexecute();
};

