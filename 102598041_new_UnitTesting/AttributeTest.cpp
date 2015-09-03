#include "gtest/gtest.h"
#include <vector>
#include "..\102598041_new\Attributes.h"
#include "..\102598041_new\Entity.h"
#include "..\102598041_new\Connection.h"

using namespace std;

class AttributeTest : public ::testing::Test
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

		attributes.at(0)->ConnectTo(connections.at(0));
		connections.at(0)->ConnectTo(attributes.at(0));
		connections.at(0)->ConnectTo(entities.at(0));
		entities.at(0)->ConnectTo(connections.at(0));
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
	}

public:
	vector<Attributes *> attributes;
	vector<Entity *> entities;
	vector<Connection *> connections;
};

TEST_F(AttributeTest, ConnectTo)
{
	EXPECT_EQ(1, attributes.at(0)->connection->size());
}

TEST_F(AttributeTest, CheckHasBeenConnect)
{
	EXPECT_TRUE(attributes.at(0)->CheckHasBeenConnect(entities.at(0)));
	EXPECT_FALSE(attributes.at(0)->CheckHasBeenConnect(entities.at(1)));
}

TEST_F(AttributeTest, GetConnectComponentsId)
{
	vector<int> componentId;
	componentId = attributes.at(0)->GetConnectComponentsId();
	EXPECT_EQ(10, componentId.at(0));
	componentId = attributes.at(1)->GetConnectComponentsId();
	EXPECT_TRUE(componentId.empty());
}

TEST_F(AttributeTest, DeleteConnectComponents)
{
	EXPECT_FALSE(attributes.at(0)->connection->empty());
	attributes.at(0)->DeleteConnectComponents(connections.at(0)->GetId());
	EXPECT_TRUE(attributes.at(0)->connection->empty());
}

TEST_F(AttributeTest, GetConnectComponents)
{
	vector<Components *> components;
	components = attributes.at(0)->GetConnectComponents();
	EXPECT_FALSE(components.empty());
	EXPECT_EQ(connections.at(0)->GetId(), components.at(0)->GetId());
	components = attributes.at(1)->GetConnectComponents();
	EXPECT_TRUE(components.empty());
	
}

TEST_F(AttributeTest, CheckConnectionHasConnectComponent)
{
	EXPECT_EQ(-3, attributes.at(0)->CheckConnectionHasConnectComponent(entities.at(0)));
	EXPECT_EQ(-4, attributes.at(0)->CheckConnectionHasConnectComponent(entities.at(1)));
}

TEST_F(AttributeTest, CanConnectTo)
{
	EXPECT_EQ(-1, attributes.at(0)->CanConnectTo(attributes.at(0)));
	EXPECT_EQ(-2, attributes.at(1)->CanConnectTo(connections.at(1)));
	EXPECT_EQ(-3, attributes.at(0)->CheckConnectionHasConnectComponent(entities.at(0)));
	EXPECT_EQ(-4, attributes.at(0)->CheckConnectionHasConnectComponent(entities.at(1)));
	EXPECT_EQ(-5, attributes.at(0)->CanConnectTo(attributes.at(1)));
	EXPECT_EQ(1, attributes.at(1)->CanConnectTo(entities.at(0)));
}
