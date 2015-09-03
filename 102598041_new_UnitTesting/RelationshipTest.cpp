#include "gtest/gtest.h"
#include <vector>
#include "..\102598041_new\Attributes.h"
#include "..\102598041_new\Entity.h"
#include "..\102598041_new\Connection.h"
#include "..\102598041_new\Relationship.h"

using namespace std;

class RelationshipTest : public ::testing::Test
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

TEST_F(RelationshipTest, VarifyComponentType)
{
	EXPECT_EQ(2, relationships.at(0)->VarifyComponentType(entities.at(0)));
	EXPECT_EQ(-5, relationships.at(0)->VarifyComponentType(relationships.at(1)));
	EXPECT_EQ(-2, relationships.at(1)->VarifyComponentType(connections.at(0)));
	EXPECT_EQ(1, relationships.at(0)->VarifyComponentType(attributes.at(0)));
}

TEST_F(RelationshipTest, GetConnectComponents)
{
	vector<Components *> components;
	components = relationships.at(3)->GetConnectComponents();
	EXPECT_EQ(0, components.size());
	components = relationships.at(0)->GetConnectComponents();
	EXPECT_EQ(1, components.size());
	components = relationships.at(1)->GetConnectComponents();
	EXPECT_EQ(2, components.size());
}

TEST_F(RelationshipTest, DeleteConnectComponents)
{
	relationships.at(0)->DeleteConnectComponents(connections.at(0)->GetId());
	EXPECT_EQ(0, relationships.at(0)->connections.size());
	relationships.at(1)->DeleteConnectComponents(connections.at(1)->GetId());
	EXPECT_EQ(1, relationships.at(1)->connections.size());

	for(unsigned int index = 0; index < relationships.at(0)->connections.size(); index++)
	{
		EXPECT_FALSE(connections.at(1)->GetId() == relationships.at(1)->connections.at(index)->GetId());
	}
}

TEST_F(RelationshipTest, GetConnectComponentsId)
{
	vector<int> componentsId;
	componentsId = relationships.at(0)->GetConnectComponentsId();
	EXPECT_EQ(1, componentsId.size());
	EXPECT_EQ(connections.at(0)->GetId(), componentsId.at(0));

	componentsId = relationships.at(1)->GetConnectComponentsId();
	EXPECT_EQ(2, componentsId.size());
	EXPECT_EQ(connections.at(1)->GetId(), componentsId.at(0));
	EXPECT_EQ(connections.at(2)->GetId(), componentsId.at(1));
}

TEST_F(RelationshipTest, CheckHasBeenConnect)
{
	EXPECT_TRUE(relationships.at(1)->CheckHasBeenConnect(attributes.at(1)));
	EXPECT_FALSE(relationships.at(0)->CheckHasBeenConnect(relationships.at(1)));
}

TEST_F(RelationshipTest, CanConnectTo)
{
	EXPECT_EQ(-1, relationships.at(0)->CanConnectTo(relationships.at(0)));
	EXPECT_EQ(-3, relationships.at(1)->CanConnectTo(entities.at(1)));
	EXPECT_EQ(2, relationships.at(0)->VarifyComponentType(entities.at(0)));
	EXPECT_EQ(-5, relationships.at(0)->VarifyComponentType(relationships.at(1)));
	EXPECT_EQ(-2, relationships.at(1)->VarifyComponentType(connections.at(0)));
	EXPECT_EQ(1, relationships.at(0)->VarifyComponentType(attributes.at(0)));
}

TEST_F(RelationshipTest, ConnectTo)
{
	EXPECT_EQ(0, relationships.at(3)->connections.size());
	relationships.at(3)->ConnectTo(connections.at(3));
	EXPECT_EQ(1, relationships.at(3)->connections.size());
	relationships.at(3)->ConnectTo(connections.at(4));
	EXPECT_EQ(2, relationships.at(3)->connections.size());
}