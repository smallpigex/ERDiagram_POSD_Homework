#include "SaveComponentVisitor.h"


SaveComponentVisitor::SaveComponentVisitor(void)
{
}


SaveComponentVisitor::~SaveComponentVisitor(void)
{
}

void SaveComponentVisitor::Visit(Attributes &attribute)
{
	SetComponentsDate(attribute.GetId(), attribute.GetType(), attribute.GetName(), attribute.GetPointX(), attribute.GetPointY());
}

void SaveComponentVisitor::Visit(Entity &entity)
{
	SetComponentsDate(entity.GetId(), entity.GetType(), entity.GetName(), entity.GetPointX(), entity.GetPointY());
	vector<Components *> connections = entity.GetConnectComponents();
	EntityData entityData;

	for(unsigned int index = 0; index < connections.size(); index++)
	{
		SetEnityData(entityData, connections.at(index)->GetConnectComponents());
	}

	entityData.SetEntityId(entity.GetId());
	SetEntitiesData(entityData);
}

void SaveComponentVisitor::Visit(Relationship &relationship)
{
	SetComponentsDate(relationship.GetId(), relationship.GetType(), relationship.GetName(), relationship.GetPointX(), relationship.GetPointY());
}

void SaveComponentVisitor::Visit(Connection &connection)
{
	SetComponentsDate(connection.GetId(), connection.GetType(), connection.GetName(), connection.GetPointX(), connection.GetPointY());
	SetConnectionsData(connection.GetId(), connection.GetConnectComponentsId());
}

void SaveComponentVisitor::SetComponentsDate(int id, string type, string name, int pointX, int pointY)
{
	ComponentData componentData;
	componentData.SetId(id);
	componentData.SetType(type);
	componentData.SetName(name);
	componentData.SetPointX(pointX);
	componentData.SetPointY(pointY);
	componentsData.push_back(componentData);
}

void SaveComponentVisitor::SetConnectionsData(int connectionId,  vector<int> connectComponentsId)
{
	ConnectionData connectionData;
	connectionData.SetId(connectionId);
	connectionData.SetComponents(connectComponentsId);
	connectionsData.push_back(connectionData);
}

void SaveComponentVisitor::SetEntitiesData(EntityData entityData)
{
	entitiesData.push_back(entityData);
}

void SaveComponentVisitor::SetEnityData(EntityData &entityData, vector<Components *> components)
{
	if(components.at(0)->GetType().compare(ComponetType::ATTRIBUTE) == 0)
	{
		ClassifyAttribute(entityData, components.at(0));
	}
	else if(components.at(1)->GetType().compare(ComponetType::ATTRIBUTE) == 0)
	{
		ClassifyAttribute(entityData, components.at(1));
	}
	
}

//將attribute進行分類，儲存到entity Data中。
void SaveComponentVisitor::ClassifyAttribute(EntityData &entityData, Components *component)
{
	//將component轉型成attribute，確認是不是primaryKey，如果是放入primaryKey的vector中。
	if(dynamic_cast<Attributes *>(component)->GetPrimaryKey())
	{
		entityData.SetPrimaryKeysId(component->GetId());
	}
	else
	{
		entityData.SetAttributeId(component->GetId());
	}
}

vector<ComponentData> SaveComponentVisitor::GetComponentsData()
{
	return componentsData;
}

vector<EntityData> SaveComponentVisitor::GetEntitiesData()
{
	return entitiesData;
}

vector<ConnectionData> SaveComponentVisitor::GetConnectionsData()
{
	return connectionsData;
}