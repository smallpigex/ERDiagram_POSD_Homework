#include "SetPrimaryKeyCmd.h"


SetPrimaryKeyCmd::SetPrimaryKeyCmd(ERModel *erModel, int id)
{
	this->erModel = erModel;
	tmpComponentId = id;
}


SetPrimaryKeyCmd::~SetPrimaryKeyCmd(void)
{
}

void SetPrimaryKeyCmd::Execute()
{
	erModel->SetPrimaryKey(tmpComponentId);
}

void SetPrimaryKeyCmd::Unexecute()
{
	erModel->SetPrimaryKey(tmpComponentId);
}
