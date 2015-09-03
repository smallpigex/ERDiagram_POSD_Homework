#include "Attributes.h"
#include "../102598041_QT/ComponentVisitor.h"

Attributes::Attributes(void)
{
	primaryKey = false;
}


Attributes::~Attributes(void)
{
}

void Attributes::ConnectTo(Components *component)
{
	connection->push_back(component);
}

int Attributes::CanConnectTo(Components *component)
{
	if(component->GetId() == this->GetId())
	{
		return ConnectMessage::ITSELF;
	}
	else if(component->GetType().compare(this->GetType()) == 0)
	{
		return ConnectMessage::SAME_TYPE;
	}
	else if(component->GetType().compare(ComponetType::CONNECTION) == 0)
	{
		return ConnectMessage::CAN_NOT_CONNECT;
	}
	else
	{
		//attribute的vector<connection>
		if(!connection->empty())
		{
			return CheckConnectionHasConnectComponent(component);
		}
		return ConnectMessage::CAN_CONNECT;
	}
}

//檢查是否和Node相連
bool Attributes::CheckHasBeenConnect(Components *component)
{
	return (*connection)[0]->CheckHasBeenConnect(component);
}

//找出相連的connection
vector<int> Attributes::GetConnectComponentsId()
{
	vector<int> componentsId;

	if(!connection->empty())
	{
		componentsId.push_back(connection->at(0)->GetId());
	}

	return componentsId;
}

void Attributes::SetPrimaryKey(bool primaryKey)
{
	this->primaryKey = primaryKey;
}

bool Attributes::GetPrimaryKey()
{
	return primaryKey;
}

//刪除vector中的connection
void Attributes::DeleteConnectComponents(int id)
{
	if(connection->at(0)->GetId() == id)
	{
		connection->erase(connection->begin() + 0);
	}
}

vector<Components *>  Attributes::GetConnectComponents()
{
	vector<Components *> components;
	components = (*connection);
	return components;
}

int Attributes::CheckConnectionHasConnectComponent(Components *component)
{
	if(CheckHasBeenConnect(component))
	{
		return ConnectMessage::HAS_BEEN_CONNECT;
	}

	return ConnectMessage::HAS_BEEN_CONNECT_OTHER_NODE;
}


void Attributes::Save(ComponentVisitor &componentVisitor)
{
	componentVisitor.Visit(*this);
}

Components *Attributes::Clone()
{
	Components *attributes = new Attributes();
	attributes->SetId(this->GetId());
	attributes->SetType(this->GetType());
	attributes->SetName(this->GetName());
	attributes->SetPointX(this->GetPointX());
	attributes->SetPointY(this->GetPointY());
	return attributes;
}

void Attributes::ClearConnection()
{
	connection->clear();
}