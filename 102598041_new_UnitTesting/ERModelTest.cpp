#include "gtest/gtest.h"
#include "../102598041_new/CommandManager.h"
#include "../102598041_new/AddComponentCmd.h"
#include "../102598041_new/ConnectComponentsCmd.h"
#include "../102598041_new/DeleteComponentCmd.h"
#include "../102598041_new/ERModel.h"
#include <vector>
#include "../102598041_new/MessageOfConstInteger.h"
#include "../102598041_new/Components.h"
#include "../102598041_new/ComponentFactory.h"
#include "../102598041_new/ObserverTextUIInterface.h"
#include "../102598041_new/Convertor.h"
#include "../102598041_new/ConnectionData.h"
#include "../102598041_new/ComponentData.h"
#include "../102598041_new/EntityData.h"
#include "../102598041_new/Command.h"
#include "../102598041_new/LoadFiles.h"
#include "../102598041_new/SaveFiles.h"

using namespace std;

class ERModelTest : public ::testing::Test
{ 
protected:
	virtual void SetUp()
	{
		erModel = new ERModel();
		erModel->observer = nullptr;
		erModel->mainWindowObserver = nullptr;
	}

	virtual void TearDown()
	{
		delete erModel;
	}

public:
	ERModel *erModel;
	Attributes *componentOne;
	Components *componentTwo;
	Components *componentThree;
	NullComponent *nullComponentOne;
	vector<int> componentsId;
	vector<string> componentsType;
	vector<string> componentsName;
	vector<ConnectionData> connectionsData;
	vector<ComponentData> componentsData;
	vector<Components *> components;
};

TEST_F(ERModelTest, StoreComponent)
{
	componentOne = new Attributes();
	componentOne->SetId(0);
	componentOne->SetType("A");
	componentOne->SetName("");

	componentTwo = new Attributes();
	componentTwo->SetId(3);
	componentTwo->SetType("A");
	componentTwo->SetName("");

	EXPECT_TRUE(erModel->components.empty());
	erModel->StoreComponent(componentOne);
	EXPECT_EQ(0, erModel->components.at(0)->GetId());
	erModel->components.resize(5);

	erModel->StoreComponent(componentTwo);
	EXPECT_EQ(3, erModel->components.at(3)->GetId());
}

TEST_F(ERModelTest, GetNullComponentIndex)
{
	componentTwo = new Attributes();
	componentTwo->SetId(3);
	componentTwo->SetType("A");
	componentTwo->SetName("");

	nullComponentOne = new NullComponent();
	nullComponentOne->SetId(-1);

	erModel->components.push_back(nullComponentOne);
	int index;
	EXPECT_EQ(1, erModel->components.size());
	index = erModel->GetNullComponentIndex();
	EXPECT_EQ(0, index);
	
	erModel->components.at(0) = componentTwo;
	int notGetId;
	notGetId = erModel->GetNullComponentIndex();
	EXPECT_EQ(-1, notGetId);
}

TEST_F(ERModelTest, GetSerialNumber)
{
	componentOne = new Attributes();
	componentOne->SetId(0);
	componentOne->SetType("A");
	componentOne->SetName("");

	nullComponentOne = new NullComponent();
	nullComponentOne->SetId(-1);
	
	erModel->components.push_back(componentOne);
	int id = erModel->GetSerialNumber();
	EXPECT_EQ(1, id);
	
	erModel->components.push_back(nullComponentOne);
	id = erModel->GetSerialNumber();
	EXPECT_EQ(1, id);
	
	//將資料塞回nullcomponentOne的位置以便tear down
	componentThree = new Attributes();
	componentThree->SetId(4);
	componentThree->SetType("A");
	componentThree->SetName("");
	erModel->components.at(id) = componentThree;
}

TEST_F(ERModelTest, AddNode)
{
	erModel->AddNode("A", "A123");
	EXPECT_EQ(0, erModel->components.at(0)->GetId());
	EXPECT_EQ("A", erModel->components.at(0)->GetType());
	EXPECT_EQ("A123", erModel->components.at(0)->GetName());

	erModel->AddNode("E", "E123");
	EXPECT_EQ(1, erModel->components.at(1)->GetId());
	EXPECT_EQ("E", erModel->components.at(1)->GetType());
	EXPECT_EQ("E123", erModel->components.at(1)->GetName());

	erModel->AddNode("R", "R123");
	EXPECT_EQ(2, erModel->components.at(2)->GetId());
	EXPECT_EQ("R", erModel->components.at(2)->GetType());
	EXPECT_EQ("R123", erModel->components.at(2)->GetName());

	erModel->AddNode("C", "");
	EXPECT_EQ(3, erModel->components.at(3)->GetId());
	EXPECT_EQ("C", erModel->components.at(3)->GetType());
	EXPECT_EQ("", erModel->components.at(3)->GetName());
}

TEST_F(ERModelTest, GetNodesData)
{
	erModel->AddNode("A", "A123");
	erModel->GetNodesData(componentsId, componentsType, componentsName);
	EXPECT_EQ(0, componentsId.at(0));
	EXPECT_EQ("A", componentsType.at(0));
	EXPECT_EQ("A123", componentsName.at(0));
	componentsId.clear();
	componentsType.clear();
	componentsName.clear();
	erModel->AddNode("E", "E123");
	erModel->GetNodesData(componentsId, componentsType, componentsName);
	EXPECT_EQ(0, componentsId.at(0));
	EXPECT_EQ("A", componentsType.at(0));
	EXPECT_EQ("A123", componentsName.at(0));
	EXPECT_EQ(1, componentsId.at(1));
	EXPECT_EQ("E", componentsType.at(1));
	EXPECT_EQ("E123", componentsName.at(1));
}

TEST_F(ERModelTest, GetConnectionsData)
{
	erModel->AddNode("A", "A123");
	erModel->AddNode("E", "E123");
	erModel->AddConnection(erModel->components.at(0), erModel->components.at(1));
	connectionsData = erModel->GetConnectionsData();
	EXPECT_EQ(2, connectionsData.at(0).GetId());
	EXPECT_EQ(0, connectionsData.at(0).connectComponens.at(0));
	EXPECT_EQ(1, connectionsData.at(0).connectComponens.at(1));
}

TEST_F(ERModelTest, StoreAttributeToComponentData)
{
	erModel->AddNode("A", "A123");
	erModel->AddNode("E", "E123");
	erModel->AddConnection(erModel->components.at(0), erModel->components.at(1));
	erModel->AddNode("E", "AA123");
	erModel->AddNode("R", "RR123");
	erModel->AddConnection(erModel->components.at(3), erModel->components.at(4));
	erModel->StoreAttributeToComponentData("1", componentsData);
	EXPECT_EQ(0, componentsData.at(0).GetId());
	EXPECT_EQ("A", componentsData.at(0).GetType());
	EXPECT_EQ("A123", componentsData.at(0).GetName());
	componentsData.clear();
	erModel->StoreAttributeToComponentData("3", componentsData);
	EXPECT_TRUE(componentsData.empty());
}

TEST_F(ERModelTest, CheckIdExist)
{
	erModel->AddNode("A", "A123");
	EXPECT_TRUE(erModel->CheckIdExist("0"));
	EXPECT_FALSE(erModel->CheckIdExist("12"));
}

TEST_F(ERModelTest, VerifyComponentType)
{
	erModel->AddNode("A", "A123");
	EXPECT_TRUE(erModel->VerifyComponentType("0", "A"));
	EXPECT_FALSE(erModel->VerifyComponentType("0", "E"));
}

TEST_F(ERModelTest, CheckIsAttributeBelongToEntity)
{
	erModel->AddNode("A", "A123");
	erModel->AddNode("E", "E123");
	erModel->AddConnection(erModel->components.at(0), erModel->components.at(1));
	erModel->AddNode("A", "AA123");
	EXPECT_TRUE(erModel->CheckIsAttributeBelongToEntity("1", "0"));
	EXPECT_FALSE(erModel->VerifyComponentType("1", "3"));
}

TEST_F(ERModelTest, CheckIsAttribute)
{
	erModel->AddNode("A", "A123");
	erModel->AddNode("E", "E123");
	EXPECT_TRUE(erModel->CheckIsAttribute("0"));
	EXPECT_FALSE(erModel->CheckIsAttribute("1"));
}

TEST_F(ERModelTest, AddConnection)
{
	erModel->AddNode("A", "A123");
	erModel->AddNode("E", "E123");
	erModel->AddConnection(erModel->components.at(0), erModel->components.at(1));
	EXPECT_EQ("C", erModel->components.at(2)->GetType());
	Connection *connection = dynamic_cast<Connection *>(erModel->components.at(2));
	vector<int> nodesId = connection->GetConnectComponentsId();
	EXPECT_EQ(0, nodesId.at(0));
	EXPECT_EQ(1, nodesId.at(1));
}

TEST_F(ERModelTest, ConnectComponents)
{
	erModel->AddNode("A", "A123");
	erModel->AddNode("E", "E123");
	erModel->ConnectComponents("0","1", "");
	EXPECT_EQ("C", erModel->components.at(2)->GetType());
	Connection *connection = dynamic_cast<Connection *>(erModel->components.at(2));
	vector<int> nodesId = connection->GetConnectComponentsId();
	EXPECT_EQ(0, nodesId.at(0));
	EXPECT_EQ(1, nodesId.at(1));

	erModel->AddNode("E", "EE123");
	erModel->AddNode("R", "RR123");
	erModel->ConnectComponents("3", "4", "1");
	EXPECT_EQ("C", erModel->components.at(5)->GetType());
	connection = dynamic_cast<Connection *>(erModel->components.at(5));
	EXPECT_EQ("1", connection->name);
}

TEST_F(ERModelTest, CanConneciont)
{
	erModel->AddNode("A", "A123");
	erModel->AddNode("E", "E123");
	EXPECT_EQ(-1, erModel->CanConneciont("0", "0"));
	EXPECT_EQ(1, erModel->CanConneciont("0", "1"));
	erModel->ConnectComponents("0","1", "");
	EXPECT_EQ(-3, erModel->CanConneciont("0", "1"));
	erModel->AddNode("E", "EE123");
	erModel->AddNode("R", "RR123");
	EXPECT_EQ(2, erModel->CanConneciont("3", "4"));
	erModel->AddNode("R", "RR123");
	erModel->AddNode("R", "RR123");
	EXPECT_EQ(-5, erModel->CanConneciont("5", "6"));
	EXPECT_EQ(-2, erModel->CanConneciont("2", "5"));
}

TEST_F(ERModelTest, SetAttributeIsPrimary)
{
	vector<string> attributesId;
	attributesId.push_back("0");
	erModel->AddNode("A", "A123");
	erModel->AddNode("A", "AA123");
	erModel->SetAttributeIsPrimary(attributesId);
	EXPECT_TRUE(dynamic_cast<Attributes *>(erModel->components.at(0))->primaryKey);
	EXPECT_FALSE(dynamic_cast<Attributes *>(erModel->components.at(1))->primaryKey);
}

TEST_F(ERModelTest, DeleteComponent)
{
	erModel->AddNode("A", "A123");
	erModel->DeleteComponent(0);
	EXPECT_EQ(-1, erModel->components.at(0)->GetId());
}

TEST_F(ERModelTest, DeleteConnecionFromTargetToSourceComponent)
{
	erModel->AddNode("A", "A123");
	erModel->AddNode("E", "AA123");
	erModel->ConnectComponents("0", "1");
	erModel->DeleteConnecionFromTargetToSourceComponent(1);
	Attributes *attribute = dynamic_cast<Attributes *>(erModel->components.at(0));
	EXPECT_TRUE(attribute->connection->empty());
}

TEST_F(ERModelTest, GetConnectComponentId)
{
	erModel->AddNode("A", "A123");
	erModel->AddNode("E", "AA123");
	erModel->ConnectComponents("0", "1");
	EXPECT_EQ(1, erModel->GetConnectComponentId(0, erModel->components.at(2)));
	EXPECT_EQ(0, erModel->GetConnectComponentId(1, erModel->components.at(2)));
}

TEST_F(ERModelTest, DeleteConnection)
{
	erModel->AddNode("A", "A123");
	erModel->AddNode("E", "AA123");
	erModel->ConnectComponents("0", "1");
	erModel->DeleteConnection(2);
	EXPECT_EQ(-1, erModel->components.at(2)->GetId());
	Attributes *attribute = dynamic_cast<Attributes *>(erModel->components.at(0));
	EXPECT_TRUE(attribute->connection->empty());
	Entity *entity = dynamic_cast<Entity *>(erModel->components.at(1));
	EXPECT_TRUE(entity->connections.empty());
}

TEST_F(ERModelTest, ConnectComponentsToConnecions)
{
	erModel->AddNode("A", "A123");
	erModel->AddNode("E", "AA123");
	erModel->AddNode("C", "");
	components.push_back(erModel->components.at(0));
	components.push_back(erModel->components.at(1));
	erModel->ConnectComponentsToConnecions(components, erModel->components.at(2));
	Attributes *attribute = dynamic_cast<Attributes *>(erModel->components.at(0));
	EXPECT_EQ(2, attribute->connection->at(0)->GetId());
	Entity *entity = dynamic_cast<Entity *>(erModel->components.at(1));
	EXPECT_EQ(2, entity->connections.at(0)->GetId());
}

TEST_F(ERModelTest, RecoveryConnect)
{
	erModel->AddNode("A", "A123");
	erModel->AddNode("E", "AA123");
	erModel->AddNode("C", "");
	Attributes *attribute = dynamic_cast<Attributes *>(erModel->components.at(0));
	attribute->connection->push_back(erModel->components.at(2));
	Connection *connection = dynamic_cast<Connection *>(erModel->components.at(2));
	connection->nodes->push_back(erModel->components.at(0));
	connection->nodes->push_back(erModel->components.at(1));
	erModel->RecoveryConnect(erModel->components.at(0));
	Entity *entity = dynamic_cast<Entity *>(erModel->components.at(1));
	EXPECT_EQ(1, entity->connections.size());
}

TEST_F(ERModelTest, RecoveryComponents)
{
	erModel->AddNode("A", "A123");
	erModel->AddNode("E", "AA123");
	erModel->AddNode("C", "");
	Attributes *attribute = dynamic_cast<Attributes *>(erModel->components.at(0));
	attribute->connection->push_back(erModel->components.at(2));
	Connection *connection = dynamic_cast<Connection *>(erModel->components.at(2));
	connection->nodes->push_back(erModel->components.at(0));
	connection->nodes->push_back(erModel->components.at(1));
	erModel->RecoveryComponents(erModel->components.at(0));
	Entity *entity = dynamic_cast<Entity *>(erModel->components.at(1));
	EXPECT_EQ(1, entity->connections.size());
}

TEST_F(ERModelTest, GetConnectionOfComponent)
{
	erModel->AddNode("A", "A123");
	erModel->AddNode("E", "AA123");
	erModel->AddNode("A", "A123");
	erModel->AddConnection(erModel->components.at(1), erModel->components.at(2));
	components = erModel->GetConnectionOfComponent(erModel->components.at(0));
	EXPECT_TRUE(components.empty());
	components = erModel->GetConnectionOfComponent(erModel->components.at(3));
	EXPECT_EQ(1, components.size());
}

TEST_F(ERModelTest, SaveFile)
{
	erModel->AddNode("A", "A123");
	erModel->AddNode("E", "AA123");
	EXPECT_FALSE(erModel->SaveFile(""));
	EXPECT_TRUE(erModel->SaveFile("Debug\\estdata.erd"));
}

TEST_F(ERModelTest, TidyUpComponents)
{
	erModel->AddNode("A", "A123");
	erModel->components.resize(2);
	NullComponent *nullComponent = new NullComponent();
	nullComponent->SetId(-1);
	erModel->components.at(1) = nullComponent;
	erModel->AddNode("E", "AA123");
	erModel->TidyUpComponents();
	EXPECT_EQ("E", erModel->components.at(1)->GetType());
}

TEST_F(ERModelTest, ClearNullComponent)
{
	erModel->AddNode("A", "A123");
	erModel->components.resize(2);
	NullComponent *nullComponent = new NullComponent();
	nullComponent->SetId(-1);
	erModel->components.at(1) = nullComponent;
	erModel->ClearNullComponent();
	EXPECT_EQ(1, erModel->components.size());
}

TEST_F(ERModelTest, GetComponentsData)
{
	erModel->AddNode("A", "A123");
	componentsData = erModel->GetComponentsData();
	EXPECT_EQ(0, componentsData.at(0).GetId());
	EXPECT_EQ("A", componentsData.at(0).GetType());
	EXPECT_EQ("A123", componentsData.at(0).GetName());
}

TEST_F(ERModelTest, ClassifyAttribute)
{
	Attributes *attributeOne = new Attributes();
	attributeOne->SetId(0);
	attributeOne->SetType("A");
	attributeOne->SetName("AA123");
	attributeOne->SetPrimaryKey(true);

	Attributes *attributeTwo = new Attributes();
	attributeTwo->SetId(1);
	attributeTwo->SetType("A");
	attributeTwo->SetName("AA1234");
	
	erModel->components.push_back(attributeOne);
	erModel->components.push_back(attributeTwo);
	EntityData entityData;
	erModel->ClassifyAttribute(entityData, attributeOne);
	EXPECT_EQ(0, entityData.GetPrimaryKeyId(0));
	erModel->ClassifyAttribute(entityData, attributeTwo);
	EXPECT_EQ(1, entityData.attributesId.at(0));
}

TEST_F(ERModelTest, SetEnityData)
{
	erModel->AddNode("A", "A123");
	erModel->AddNode("E", "AA123");
	erModel->AddNode("R", "a123");
	erModel->AddConnection(erModel->components.at(0), erModel->components.at(1));
	erModel->AddConnection(erModel->components.at(1), erModel->components.at(2));
	componentsId.push_back(0);
	componentsId.push_back(2);
	EntityData entityData;
	erModel->SetEnityData(entityData, componentsId);
	EXPECT_EQ(0, entityData.attributesId.at(0));
}

TEST_F(ERModelTest, StoreAttributeToEnityData)
{
	erModel->AddNode("A", "A123");
	erModel->AddNode("E", "AA123");
	erModel->AddConnection(erModel->components.at(0), erModel->components.at(1));
	vector<int> connectionId;
	connectionId.push_back(2);
	vector<EntityData> entityData;
	erModel->StoreAttributeToEnityData(1, connectionId, entityData);
	EXPECT_EQ(0, entityData.at(0).attributesId.at(0));
}

TEST_F(ERModelTest, LoadFile)
{
	EXPECT_FALSE(erModel->LoadFile(""));
	EXPECT_TRUE(erModel->LoadFile("dataThree.erd"));
}

TEST_F(ERModelTest, IsComponentExist)
{
	erModel->AddNode("A", "A123");
	EXPECT_TRUE(erModel->IsComponentExist(0));
	EXPECT_FALSE(erModel->IsComponentExist(1));
}

TEST_F(ERModelTest, SetPrimaryKey)
{
	erModel->AddNode("A", "A123");
	erModel->SetPrimaryKey(0);
	EXPECT_TRUE(dynamic_cast<Attributes *>(erModel->components.at(0))->GetPrimaryKey());
	erModel->SetPrimaryKey(0);
	EXPECT_FALSE(dynamic_cast<Attributes *>(erModel->components.at(0))->GetPrimaryKey());
}

TEST_F(ERModelTest, CheckNameIsCardinality)
{
	EXPECT_TRUE(erModel->CheckNameIsCardinality("1"));
	EXPECT_TRUE(erModel->CheckNameIsCardinality("N"));
	EXPECT_FALSE(erModel->CheckNameIsCardinality("a"));
}

TEST_F(ERModelTest, IsCardinality)
{
	erModel->AddNode("R", "A123");
	erModel->AddNode("E", "AA123");
	erModel->AddConnection(erModel->components.at(0), erModel->components.at(1));
	EXPECT_TRUE(erModel->IsCardinality(erModel->components.at(2)));
	erModel->AddNode("A", "A123");
	erModel->AddNode("E", "AA123");
	erModel->AddConnection(erModel->components.at(3), erModel->components.at(4));
	EXPECT_FALSE(erModel->IsCardinality(erModel->components.at(5)));
	erModel->AddNode("A", "A123");
	erModel->AddNode("R", "AA123");
	erModel->AddConnection(erModel->components.at(6), erModel->components.at(7));
	EXPECT_FALSE(erModel->IsCardinality(erModel->components.at(8)));
}


TEST_F(ERModelTest, SetComponentName)
{
	erModel->AddNode("R", "A123");
	erModel->AddNode("E", "AA123");
	erModel->AddConnection(erModel->components.at(0), erModel->components.at(1));
	EXPECT_EQ("A123", erModel->components.at(0)->GetName());
	erModel->SetComponentName(0, "a");
	EXPECT_EQ("a", erModel->components.at(0)->GetName());
	EXPECT_EQ("", erModel->components.at(2)->GetName());
	erModel->SetComponentName(2, "1");
	EXPECT_EQ("1", erModel->components.at(2)->GetName());
	erModel->SetComponentName(2, "N");
	EXPECT_EQ("N", erModel->components.at(2)->GetName());
}
