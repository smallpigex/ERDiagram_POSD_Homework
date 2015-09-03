#include "PasteComponents.h"


PasteComponents::PasteComponents(ERModel * erModel)
{
	this->erModel = erModel;
}


PasteComponents::~PasteComponents(void)
{
}

void PasteComponents::Execute()
{
	erModel->PasteComponent();
}

void PasteComponents::Unexecute()
{
}