#include "SaveXmlComponentVisitor.h"


SaveXmlComponentVisitor::SaveXmlComponentVisitor(fstream *file, string path)
{
	this->file = file;
	this->path = path;
	(*file).open(path, ios::out  | ios::app);
}


SaveXmlComponentVisitor::~SaveXmlComponentVisitor(void)
{
}

void SaveXmlComponentVisitor::Visit(Attributes &attribute)
{
	(*file) << " " << XmlTag::startTagAttribute << "\n"
		 << "    " << XmlTag::startTagId << attribute.GetId() << XmlTag::endTagId << "\n"
		 << "    " << XmlTag::startTagText << attribute.GetName() << XmlTag::endTagText << "\n"
		 << "    " << XmlTag::startTagPointX << attribute.GetPointX() << XmlTag::endTagPointX << "\n"
		 << "    " << XmlTag::startTagPointY << attribute.GetPointY() << XmlTag::endTagPointY << "\n"
		 << " " << XmlTag::endTagAttribute << "\n";
}

void SaveXmlComponentVisitor::Visit(Entity &entity)
{
	(*file) << " " << XmlTag::startTagEntity << "\n"
		 << "    " << XmlTag::startTagId << entity.GetId() << XmlTag::endTagId << "\n"
		 << "    " << XmlTag::startTagText << entity.GetName() << XmlTag::endTagText << "\n"
		 << "    " << XmlTag::startTagPrimaryKey;
	FindAttribute(entity.GetConnectComponents());
	(*file) << XmlTag::endTagPrimaryKey << "\n"
		 << "    " << XmlTag::startTagPointX << entity.GetPointX() << XmlTag::endTagPointX << "\n"
		 << "    " << XmlTag::startTagPointY << entity.GetPointY() << XmlTag::endTagPointY << "\n"
		 << " " << XmlTag::endTagAttribute << "\n";
}

void SaveXmlComponentVisitor::Visit(Relationship &relationship)
{
	(*file) << " " << XmlTag::startTagRelationship << "\n"
		 << "    " << XmlTag::startTagId << relationship.GetId() << XmlTag::endTagId << "\n"
		 << "    " << XmlTag::startTagText << relationship.GetName() << XmlTag::endTagText << "\n"
		 << "    " << XmlTag::startTagPointX << relationship.GetPointX() << XmlTag::endTagPointX << "\n"
		 << "    " << XmlTag::startTagPointY << relationship.GetPointY() << XmlTag::endTagPointY << "\n"
		 << " " << XmlTag::endTagRelationship << "\n";
}

void SaveXmlComponentVisitor::Visit(Connection &connection)
{
	(*file) << " " << XmlTag::startTagConnector << "\n"
		 << "    " << XmlTag::startTagId << connection.GetId() << XmlTag::endTagId << "\n"
		 << "    " << XmlTag::startTagText << connection.GetName() << XmlTag::endTagText << "\n"
		 << "    " << XmlTag::startTagSource << connection.GetConnectComponents().at(0)->GetId() << XmlTag::endTagSource << "\n"
		 << "    " << XmlTag::startTagTarget << connection.GetConnectComponents().at(1)->GetId() << XmlTag::endTagTarget << "\n"
		 << " " << XmlTag::endTagConnector << "\n";
}

vector<ComponentData> SaveXmlComponentVisitor::GetComponentsData()
{
	vector<ComponentData> nullComponentsData;
	return nullComponentsData;
}

vector<EntityData> SaveXmlComponentVisitor::GetEntitiesData()
{
	vector<EntityData> nullEntitiesData;
	return nullEntitiesData;
}

vector<ConnectionData> SaveXmlComponentVisitor::GetConnectionsData()
{
	vector<ConnectionData> nullConnectionsData;
	return nullConnectionsData;
}

void SaveXmlComponentVisitor::FindAttribute(vector<Components *> connections)
{
	for(unsigned int index = 0; index < connections.size(); index++)
	{
		if(connections.at(index)->GetConnectComponents().at(0)->GetType().compare(ComponetType::ATTRIBUTE) == 0)
		{
			StorePrimaryKey(connections.at(index)->GetConnectComponents().at(0));
		}
		else if(connections.at(index)->GetConnectComponents().at(1)->GetType().compare(ComponetType::ATTRIBUTE) == 0)
		{
			StorePrimaryKey(connections.at(index)->GetConnectComponents().at(1));
		}
	}
}

//將attribute進行分類，儲存到entity Data中。
void SaveXmlComponentVisitor::StorePrimaryKey(Components *component)
{
	//將component轉型成attribute，確認是不是primaryKey，如果是放入primaryKey的tag中。
	if(dynamic_cast<Attributes *>(component)->GetPrimaryKey())
	{
		(*file) << component->GetId() << ",";
	}
}