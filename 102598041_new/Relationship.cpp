#include "Relationship.h"
#include "../102598041_QT/ComponentVisitor.h"

Relationship::Relationship(void)
{
}


Relationship::~Relationship(void)
{
}

void Relationship::ConnectTo(Components *component)
{
	//如果id一樣表示已經相連，直接return
	for(vector<Components *>::iterator connection = connections.begin(); connection != connections.end(); ++connection)
	{
		if((*connection)->GetId() == component->GetId())
		{
			return ;
		}
	}

	connections.push_back(component);
}

int Relationship::CanConnectTo(Components *component)
{
	if(component->GetId() == this->GetId())
	{
		return ConnectMessage::ITSELF;
	}
	else if(CheckHasBeenConnect(component))
	{
		return ConnectMessage::HAS_BEEN_CONNECT;
	}
	else
	{
		return VarifyComponentType(component);
	}
}

bool Relationship::CheckHasBeenConnect(Components *component)
{
	for(vector<Components *>::iterator connection = connections.begin();  connection != connections.end(); ++connection)
	{
		if((*connection)->CheckHasBeenConnect(component))
		{
			return true;
		}
	}
	return false;
}

vector<int> Relationship::GetConnectComponentsId()
{
	vector<int> componentsId;

	for(vector<Components *>::iterator component = connections.begin(); component != connections.end(); ++component)
	{
		componentsId.push_back((*component)->GetId());
	}

	return componentsId;
}

void Relationship::DeleteConnectComponents(int id)
{
	//將相連接的connection刪除
	for(unsigned int index = 0; index < connections.size(); ++index)
	{
		if(connections.at(index)->GetId() == id)
		{
			connections.erase(connections.begin() + index);
		}
	}
}

vector<Components *>  Relationship::GetConnectComponents()
{
	vector<Components *> components;
	components = connections;
	return components;
}

int Relationship::VarifyComponentType(Components *component)
{
	if(component->GetType().compare(ComponetType::ENTITY) == 0)
	{
		return ConnectMessage::IS_CARDINALITY;
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
		return ConnectMessage::CAN_CONNECT;
	}
}

void Relationship::Save(ComponentVisitor &componentVisitor)
{
	componentVisitor.Visit(*this);
}

Components *Relationship::Clone()
{
	Components *relationship = new Relationship();
	relationship->SetId(this->GetId());
	relationship->SetType(this->GetType());
	relationship->SetName(this->GetName());
	relationship->SetPointX(this->GetPointX());
	relationship->SetPointY(this->GetPointY());
	return relationship;
}

void Relationship::ClearConnection()
{
	connections.clear();
}