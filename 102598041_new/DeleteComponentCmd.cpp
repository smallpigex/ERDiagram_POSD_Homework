#include "DeleteComponentCmd.h"


DeleteComponentCmd::DeleteComponentCmd(ERModel *erModel, int id)
{
	this->deleteId = id;
	this->erModel = erModel;
}


DeleteComponentCmd::~DeleteComponentCmd(void)
{
	tempComponents = nullptr;
	delete tempComponents;
}

void DeleteComponentCmd::Execute()
{
	//將刪除的component暫存起來，以便之後recovery
	tempComponents = erModel->GetComponent(deleteId);
	erModel->DeleteSpecifiedComponent(deleteId);
}

void DeleteComponentCmd::Unexecute()
{
	erModel->RecoveryComponents(tempComponents);
}

