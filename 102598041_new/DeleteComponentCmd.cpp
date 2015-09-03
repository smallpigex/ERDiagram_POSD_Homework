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
	//�N�R����component�Ȧs�_�ӡA�H�K����recovery
	tempComponents = erModel->GetComponent(deleteId);
	erModel->DeleteSpecifiedComponent(deleteId);
}

void DeleteComponentCmd::Unexecute()
{
	erModel->RecoveryComponents(tempComponents);
}

