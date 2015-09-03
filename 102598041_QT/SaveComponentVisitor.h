#pragma once
#include "../102598041_QT/ComponentVisitor.h"
#include "../102598041_new/Attributes.h"
#include "../102598041_new/Entity.h"
#include "../102598041_new/Relationship.h"
#include "../102598041_new/Connection.h"

using namespace std;

class Attributes;
class Entity;
class Relationship;
class Connection;

class SaveComponentVisitor : public ComponentVisitor
{
private:
	vector<ComponentData> componentsData;
	vector<ConnectionData> connectionsData;
	vector<EntityData> entitiesData;
public:
	SaveComponentVisitor(void);
	~SaveComponentVisitor(void);
	void Visit(Attributes &attribute);
	void Visit(Entity &entity);
	void Visit(Relationship &relationship);
	void Visit(Connection &connection);
	void SetComponentsDate(int, string, string, int, int);
	void SetConnectionsData(int, vector<int>);
	void SetEntitiesData(EntityData);
	vector<ComponentData> GetComponentsData();
	vector<EntityData> GetEntitiesData();
	vector<ConnectionData> GetConnectionsData();
	void SetEnityData(EntityData &, vector<Components *>);
	void ClassifyAttribute(EntityData &, Components *);
};

