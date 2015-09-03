#pragma once
#include <vector>
#include "../102598041_new/ComponentData.h"
#include "../102598041_new/ConnectionData.h"
#include "../102598041_new/EntityData.h"

using namespace std;

class Attributes;
class Entity;
class Relationship;
class Connection;

class ComponentVisitor
{
public:
	ComponentVisitor(void);
	~ComponentVisitor(void);
	virtual void Visit(Attributes &) = 0;
	virtual void Visit(Entity &) = 0;
	virtual void Visit(Relationship &) = 0;
	virtual void Visit(Connection &) = 0;
	virtual vector<ComponentData> GetComponentsData() = 0;
	virtual vector<EntityData> GetEntitiesData() = 0;
	virtual vector<ConnectionData> GetConnectionsData() = 0;
};

