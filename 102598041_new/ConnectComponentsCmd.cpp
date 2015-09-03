#include "ConnectComponentsCmd.h"


ConnectComponentsCmd::ConnectComponentsCmd(ERModel *erModel, string firstId, string secondId, string cardinality)
{
	this->erModel = erModel;
	this->firstId = firstId;
	this->secondId = secondId;
	this->cardinality = cardinality;
}


ConnectComponentsCmd::~ConnectComponentsCmd(void)
{
	connection = nullptr;
	delete connection;
}

void ConnectComponentsCmd::Execute()
{
	erModel->ConnectComponents(firstId, secondId, cardinality);
	connection = erModel->GetCurrentCreateConnection();
}

void ConnectComponentsCmd::Unexecute()
{
	erModel->DeleteSpecifiedComponent(connection->GetId());
}

