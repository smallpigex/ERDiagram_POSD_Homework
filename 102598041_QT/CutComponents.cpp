#include "CutComponents.h"


CutComponents::CutComponents(ERModel *erModel, vector<int> componentsId)
{
	this->erModel = erModel;
	this->componentsId = componentsId;
}


CutComponents::~CutComponents(void)
{
}

void CutComponents::Execute()
{
	erModel->ClearCutComponents();
	erModel->ClearCopyComponents();
	for (unsigned int index = 0; index < componentsId.size(); index++)
	{
		erModel->StoreCutComponents(componentsId.at(index));
		erModel->DeleteSpecifiedComponent(componentsId.at(index));
	}
	cutComponents = erModel->GetCutComponents();
}

void CutComponents::Unexecute()
{
	erModel->RecoveryCutComponents(cutComponents);
}