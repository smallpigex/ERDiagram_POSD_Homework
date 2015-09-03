#include "EditNameOfComponent.h"


EditNameOfComponent::EditNameOfComponent(ERModel *erModel, int id, std::string name)
{
	this->erModel = erModel;
	this->id = id;
	this->name = name;
}


EditNameOfComponent::~EditNameOfComponent(void)
{
}

void EditNameOfComponent::Execute()
{
	tmpName = erModel->GetComponent(id)->GetName();
	erModel->SetComponentName(id, name);
}

void EditNameOfComponent::Unexecute()
{
	erModel->SetComponentName(id, tmpName);
}