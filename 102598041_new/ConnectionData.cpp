#include "ConnectionData.h"


ConnectionData::ConnectionData(void)
{
}


ConnectionData::~ConnectionData(void)
{
}

void ConnectionData::SetId(int id)
{
	this->conneciontId = id;
}

void ConnectionData::SetComponents(std::vector<int> &components)
{
	this->connectComponens = components;
}

int ConnectionData::GetId()
{
	return this->conneciontId;
}

int ConnectionData::GetConnectComponetId(int index)
{
	return connectComponens[index];
}

void ConnectionData::SetComponentForIndex(int index, int id)
{
	connectComponens.at(index) = id;
}