#include "gtest/gtest.h"
#include <vector>
#include "..\102598041_new\Attributes.h"
#include "..\102598041_new\Entity.h"
#include "..\102598041_new\Connection.h"
#include "..\102598041_new\Relationship.h"

using namespace std;

class EntityTest : public ::testing::Test
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
		relationship = new Relationship();
		relationship->SetId(id);
		relationship->SetType("R");

		attributes.at(0)->ConnectTo(connections.at(0));
		connections.at(0)->ConnectTo(attributes.at(0));
		entities.at(0)->ConnectTo(connections.at(0));
		connections.at(0)->ConnectTo(entities.at(0));

		entities.at(0)->ConnectTo(connections.at(1));
		connections.at(1)->ConnectTo(entities.at(0));
		relationship->ConnectTo(connections.at(1));
		connections.at(1)->ConnectTo(relationship);

		entities.at(1)->ConnectTo(connections.at(2));
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
		delete relationship;
	}

public:
	Relationship *relationship;
	vector<Attributes *> attributes;
	vector<Entity *> entities;
	vector<Connection *> connections;
};

TEST_F(EntityTest, VarifyComponentType)
{
	EXPECT_EQ(2, entities.at(1)->VarifyComponentType(relationship));
	EXPECT_EQ(-5, entities.at(1)->VarifyComponentType(entities.at(2)));
	EXPECT_EQ(-2, entities.at(1)->VarifyComponentType(connections.at(3)));
	EXPECT_EQ(1, entities.at(1)->VarifyComponentType(attributes.at(2)));
}

TEST_F(EntityTest, GetConnectComponents)
{
	vector<Components *> components;
	components = entities.at(0)->GetConnectComponents();
	EXPECT_EQ(2, components.size());
}

TEST_F(EntityTest, DeleteConnectComponents)
{
	entities.at(0)->DeleteConnectComponents(connections.at(0)->GetId());
	EXPECT_EQ(1, entities.at(0)->connections.size());

	for(unsigned int index = 0; index < entities.at(0)->connections.size(); index++)
	{
		EXPECT_FALSE(connections.at(0)->GetId() == entities.at(0)->connections.at(index)->GetId());
	}

	entities.at(0)->DeleteConnectComponents(connections.at(1)->GetId());
	EXPECT_EQ(0, entities.at(0)->connections.size());
}

TEST_F(EntityTest, GetConnectComponentsId)
{
	vector<int> componentsId;
	componentsId = entities.at(0)->GetConnectComponentsId();
	EXPECT_EQ(2, componentsId.size());
	EXPECT_EQ(connections.at(0)->GetId(), componentsId.at(0));
	EXPECT_EQ(connections.at(1)->GetId(), componentsId.at(1));

	entities.at(0)->DeleteConnectComponents(connections.at(0)->GetId());
	componentsId = entities.at(0)->GetConnectComponentsId();
	EXPECT_EQ(1, componentsId.size());
	EXPECT_EQ(connections.at(1)->GetId(), componentsId.at(0));
	entities.at(0)->DeleteConnectComponents(connections.at(1)->GetId());
	componentsId = entities.at(0)->GetConnectComponentsId();
	EXPECT_EQ(0, componentsId.size());
}

TEST_F(EntityTest, CheckHasBeenConnect)
{
	EXPECT_TRUE(entities.at(0)->CheckHasBeenConnect(attributes.at(0)));
	EXPECT_FALSE(entities.at(0)->CheckHasBeenConnect(attributes.at(1)));
}

TEST_F(EntityTest, CanConnectTo)
{
	EXPECT_EQ(-1, entities.at(0)->CanConnectTo(entities.at(0)));
	EXPECT_EQ(-3, entities.at(0)->CanConnectTo(attributes.at(0)));
	EXPECT_EQ(2, entities.at(1)->VarifyComponentType(relationship));
	EXPECT_EQ(-5, entities.at(1)->VarifyComponentType(entities.at(2)));
	EXPECT_EQ(-2, entities.at(1)->VarifyComponentType(connections.at(3)));
	EXPECT_EQ(1, entities.at(1)->VarifyComponentType(attributes.at(2)));
}

TEST_F(EntityTest, ConnectTo)
{
	EXPECT_EQ(0, entities.at(3)->connections.size());
	entities.at(3)->ConnectTo(connections.at(3));
	EXPECT_EQ(1, entities.at(3)->connections.size());
	entities.at(3)->ConnectTo(connections.at(4));
	EXPECT_EQ(2, entities.at(3)->connections.size());
}