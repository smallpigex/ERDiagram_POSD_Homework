#pragma once
#include "../102598041_QT/ComponentVisitor.h"
#include "../102598041_new/MessageOfConstString.h"
#include "../102598041_new/Attributes.h"
#include "../102598041_new/Entity.h"
#include "../102598041_new/Relationship.h"
#include "../102598041_new/Connection.h"
#include <fstream>
#include <string>
using namespace std;

class SaveXmlComponentVisitor : public ComponentVisitor
{
private:
	fstream *file;
	string path;

public:
	SaveXmlComponentVisitor(fstream *, string);
	~SaveXmlComponentVisitor(void);
	void Visit(Attributes &attribute);
	void Visit(Entity &entity);
	void Visit(Relationship &relationship);
	void Visit(Connection &connection);
	vector<ComponentData> GetComponentsData();
	vector<EntityData> GetEntitiesData();
	vector<ConnectionData> GetConnectionsData();
	void FindAttribute(vector<Components *>);
	void StorePrimaryKey(Components *);
};

