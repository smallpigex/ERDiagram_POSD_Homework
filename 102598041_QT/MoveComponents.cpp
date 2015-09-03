#include "MoveComponents.h"


MoveComponents::MoveComponents(ERModel *erModel, vector<ComponentPoint> oldComponentsPointData, vector<ComponentPoint> newComponentsPointData)
{
	this->erModel = erModel;
	this->oldComponentsPointData = oldComponentsPointData;
	this->newComponentsPointData = newComponentsPointData;
}


MoveComponents::~MoveComponents(void)
{
}

void MoveComponents::Execute()
{
	for(unsigned int index = 0; index < newComponentsPointData.size(); index++)
	{
		int id = newComponentsPointData.at(index).GetId();
		int pointX = newComponentsPointData.at(index).GetPointX();
		int pointY = newComponentsPointData.at(index).GetPointY();
		erModel->GetComponent(id)->SetPointX(pointX);
		erModel->GetComponent(id)->SetPointY(pointY);
	}
	erModel->NotifyObserverResetPoint();
}

void MoveComponents::Unexecute()
{
	for(unsigned int index = 0; index < oldComponentsPointData.size(); index++)
	{
		int id = oldComponentsPointData.at(index).GetId();
		int pointX = oldComponentsPointData.at(index).GetPointX();
		int pointY = oldComponentsPointData.at(index).GetPointY();
		erModel->GetComponent(id)->SetPointX(pointX);
		erModel->GetComponent(id)->SetPointY(pointY);
	}
	erModel->NotifyObserverResetPoint();
}