#include "Connection.h"
#include "../102598041_QT/ComponentVisitor.h"

Connection::Connection(void)
{
	cadinality = "";
}


Connection::~Connection(void)
{
}

void Connection::ConnectTo(Components *component)
{
	//如果id一樣表示已經相連，直接return
	for(vector<Components *>::iterator node = nodes->begin(); node != nodes->end(); ++node)
	{
		if((*node)->GetId() == component->GetId())
		{
			return ;
		}
	}
	nodes->push_back(component);
}

int Connection::CanConnectTo(Components *component)
{
	return ConnectMessage::CAN_NOT_CONNECT;
}

bool Connection::CheckHasBeenConnect(Components * component)
{
	for(vector<Components *>::iterator node = nodes->begin(); node != nodes->end(); ++node)
	{
		if((*node)->GetId() == component->GetId())
		{
			return true;
		}
	}

	return false;
}

vector<int> Connection::GetConnectComponentsId()
{
	vector<int> componentsId;

	for(vector<Components *>::iterator component = nodes->begin(); component != nodes->end(); ++component)
	{
		componentsId.push_back((*component)->GetId());
	}

	return componentsId;
}

void Connection::SetCardinality(string cadinality)
{
	this->cadinality = cadinality;
}

int Connection::GetEntityConnectAttributeId()
{
	for(vector<Components *>::iterator component = nodes->begin(); component != nodes->end(); ++component)
	{
		if((*component)->GetType().compare(ComponetType::ATTRIBUTE) == 0)
		{
			return (*component)->GetId();
		}
	}

	return NotGet::ID;
}

void Connection::DeleteConnectComponents(int id)
{
	//呼叫node刪除與自己的連結
	for(unsigned int index = 0; index < nodes->size(); ++index)
	{
		if(nodes->at(index)->GetId() == id)
		{
			nodes->at(index)->DeleteConnectComponents(this->GetId());
		}
	}
}

vector<Components *>  Connection::GetConnectComponents()
{
	vector<Components *> components;
	components = (*nodes);
	return components;
}

void Connection::Save(ComponentVisitor &componentVisitor)
{
	componentVisitor.Visit(*this);
}

Components *Connection::Clone()
{
	Components *connection = new Connection();
	return connection;
}

void Connection::ClearConnection()
{
	nodes->clear();
}