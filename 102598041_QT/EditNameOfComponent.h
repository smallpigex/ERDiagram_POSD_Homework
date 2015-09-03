#pragma once
#include "../102598041_new/Command.h"

class EditNameOfComponent : public Command
{
	friend class EditNameOfComponentTest;
	FRIEND_TEST(EditNameOfComponentTest, Execute);
	FRIEND_TEST(EditNameOfComponentTest, Unexecute);

private:
	ERModel *erModel;
	int id;
	std::string name;
	std::string tmpName;

public:
	EditNameOfComponent(ERModel *, int, string);
	~EditNameOfComponent(void);
	void Execute();
	void Unexecute();
};

