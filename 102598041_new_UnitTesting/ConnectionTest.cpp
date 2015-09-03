#include "gtest/gtest.h"
#include <vector>
#include "..\102598041_new\Attributes.h"
#include "..\102598041_new\Entity.h"
#include "..\102598041_new\Connection.h"
#include "..\102598041_new\Relationship.h"

using namespace std;

class ConnectionTest : public ::testing::Test
{ 
protected:
	virtual void SetUp()
	{
		int id = 0;

		for (int index = 0; index < 5; index++)
		{
			attributes.push_back(new Attributes());
			attributes.at(index)->SetId(id);
			attributes.at(index)->SetType("A");
			id++;
		}

		for (int index = 0; index < 5; index++)
		{
			entities.push_back(new Entity());
			entities.at(index)->SetId(id);
			entities.at(index)->SetType("E");
			id++;
		}

		for (int index = 0; index < 5; index++)
		{
			connections.push_back(new Connection());
			connections.at(index)->SetId(id);
			connections.at(index)->SetType("C");
			id++;
		}

		for(int index = 0; index < 5; index++)
		{
			relationships.push_back(new Relationship());
			relationships.at(index)->SetId(id);
			relationships.at(index)->SetType("R");
			id++;
		}

		//set connect component
		//R0 <-> E0
		relationships.at(0)->ConnectTo(connections.at(0));
		connections.at(0)->ConnectTo(relationships.at(0));
		entities.at(0)->ConnectTo(connections.at(0));
		connections.at(0)->ConnectTo(entities.at(0));

		// R1 <-> A1
		relationships.at(1)->ConnectTo(connections.at(1));
		connections.at(1)->ConnectTo(relationships.at(1));
		attributes.at(1)->ConnectTo(connections.at(1));
		connections.at(1)->ConnectTo(attributes.at(1));

		//R1 <-> E1
		relationships.at(1)->ConnectTo(connections.at(2));
		connections.at(2)->ConnectTo(relationships.at(1));
		entities.at(1)->ConnectTo(connections.at(2));
		connections.at(2)->ConnectTo(entities.at(1));
	}

	virtual void TearDown()
	{
		for(unsigned int index = 0; index < attributes.size(); index++)
		{
			delete attributes.at(index);
		}

		attributes.clear();

		for(unsigned int index = 0; index < entities.size(); index++)
		{
			delete entities.at(index);
		}

		entities.clear();

		for(unsigned int index = 0; index < connections.size(); index++)
		{
			delete connections.at(index);
		}

		connections.clear();

		for(unsigned int index = 0; index < relationships.size(); index++)
		{
			delete relationships.at(index);
		}

		relationships.clear();
	}

public:
	vector<Attributes *> attributes;
	vector<Entity *> entities;
	vector<Connection *> connections;
	vector<Relationship *> relationships;
};

TEST_F(ConnectionTest, GetConnectComponents)
{
	vector<Components *> components;
	components = connections.at(3)->GetConnectComponents();
	EXPECT_EQ(0, components.size());
	components = connections.at(1)->GetConnectComponents();
	EXPECT_EQ(2, components.size());
	EXPECT_EQ(relationships.at(1)->GetId(), components.at(0)->GetId());
	EXPECT_EQ(attributes.at(1)->GetId(), components.at(1)->GetId());
}

TEST_F(ConnectionTest, DeleteConnectComponents)
{
	//因為connection只會請對方刪掉自己，所以驗證對方的size是否變小，以及connection是否存放在對方的vector中
	EXPECT_EQ(1, entities.at(0)->connections.size());
	connections.at(0)->DeleteConnectComponents(entities.at(0)->GetId());
	EXPECT_EQ(2, connections.at(0)->nodes->size());
	EXPECT_EQ(0, entities.at(0)->connections.size());

	for(unsigned int index = 0; index < entities.at(0)->connections.size(); index++)
	{
		EXPECT_FALSE(connections.at(0)->GetId() ==  entities.at(0)->connections.at(index)->GetId());
	}

	connections.at(0)->DeleteConnectComponents(entities.at(1)->GetId());
	EXPECT_EQ(1, entities.at(1)->connections.size());
}

TEST_F(ConnectionTest, GetEntityConnectAttributeId)
{
	int attributeId;
	attributeId = connections.at(1)->GetEntityConnectAttributeId();
	EXPECT_EQ(attributes.at(1)->GetId(), attributeId);
	attributeId = connections.at(2)->GetEntityConnectAttributeId();
	EXPECT_EQ(-1, attributeId);
}

TEST_F(ConnectionTest, GetConnectComponentsId)
{
	vector<int> componentsId;
	componentsId = connections.at(3)->GetConnectComponentsId();
	EXPECT_TRUE(componentsId.empty());
	componentsId = connections.at(2)->GetConnectComponentsId();
	EXPECT_EQ(relationships.at(1)->GetId(), componentsId.at(0));
	EXPECT_EQ(entities.at(1)->GetId(), componentsId.at(1));
}

TEST_F(ConnectionTest, CheckHasBeenConnect)
{
	EXPECT_TRUE(connections.at(0)->CheckHasBeenConnect(relationships.at(0)));
	EXPECT_TRUE(connections.at(0)->CheckHasBeenConnect(entities.at(0)));
	EXPECT_FALSE(connections.at(2)->CheckHasBeenConnect(entities.at(0)));
}

TEST_F(ConnectionTest, CanConnectTo)
{
	EXPECT_EQ(-2, connections.at(4)->CanConnectTo(attributes.at(4)));
	EXPECT_EQ(-2, connections.at(4)->CanConnectTo(entities.at(4)));
	EXPECT_EQ(-2, connections.at(4)->CanConnectTo(relationships.at(4)));
	EXPECT_EQ(-2, connections.at(4)->CanConnectTo(connections.at(4)));
}

TEST_F(ConnectionTest, ConnectTo)
{
	EXPECT_EQ(0, connections.at(4)->nodes->size());
	connections.at(4)->ConnectTo(attributes.at(4));
	EXPECT_EQ(1, connections.at(4)->nodes->size());
	connections.at(4)->ConnectTo(entities.at(4));
	EXPECT_EQ(2, connections.at(4)->nodes->size());
}