#include "AddComponentCmd.h"


AddComponentCmd::AddComponentCmd(ERModel *erModel, string componentType, string componentName)
{
	this->erModel = erModel;
	this->componentType = componentType;
	this->componentName = componentName;
	pointX = -1;
	pointY = -1;
}


AddComponentCmd::~AddComponentCmd(void)
{
}

void AddComponentCmd::Execute()
{
	erModel->SetComponentPointX(pointX);
	erModel->SetComponentPointY(pointY);
	erModel->AddNode(componentType, componentName);
	tmpComponentId = erModel->GetCurrentCreateComponentId();
}

void AddComponentCmd::Unexecute()
{
	pointX = erModel->GetComponent(tmpComponentId)->GetPointX();
	pointY = erModel->GetComponent(tmpComponentId)->GetPointY();
	erModel->DeleteSpecifiedComponent(tmpComponentId);
}
