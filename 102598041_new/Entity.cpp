#include "Entity.h"
#include "../102598041_QT/ComponentVisitor.h"

Entity::Entity(void)
{
}


Entity::~Entity(void)
{
}

void Entity::ConnectTo(Components *component)
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

int Entity::CanConnectTo(Components *component)
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

//檢查是否和Node相連
bool Entity::CheckHasBeenConnect(Components *component)
{
	for(vector<Components *>::iterator connection = connections.begin(); connection != connections.end(); ++connection)
	{
		if((*connection)->CheckHasBeenConnect(component))
		{
			return true;
		}
	}

	return false;
}

vector<int> Entity::GetConnectComponentsId()
{
	vector<int> componentsId;

	for(vector<Components *>::iterator component = connections.begin(); component != connections.end(); ++component)
	{
		componentsId.push_back((*component)->GetId());
	}

	return componentsId;
}

void Entity::DeleteConnectComponents(int id)
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

vector<Components *>  Entity::GetConnectComponents()
{
	vector<Components *> components;
	components = connections;
	return components;
}

int Entity::VarifyComponentType(Components *component)
{
	if(component->GetType().compare(ComponetType::RELATIONSHIP) == 0)
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

void Entity::Save(ComponentVisitor &componentVisitor)
{
	componentVisitor.Visit(*this);
}

Components *Entity::Clone()
{
	Components *entity = new Entity();
	entity->SetId(this->GetId());
	entity->SetType(this->GetType());
	entity->SetName(this->GetName());
	entity->SetPointX(this->GetPointX());
	entity->SetPointY(this->GetPointY());
	return entity;
}

void Entity::ClearConnection()
{
	connections.clear();
}