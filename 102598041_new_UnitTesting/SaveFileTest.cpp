#include "gtest/gtest.h"
#include "../102598041_new/DeleteComponentCmd.h"
#include "../102598041_new/ERModel.h"
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

class SaveFileTest : public ::testing::Test
{ 
protected:
	virtual void SetUp()
	{
		ComponentData componentOne;
		componentOne.SetId(0);
		componentOne.SetType("A");
		componentOne.SetName("");

		ComponentData componentTwo;
		componentTwo.SetId(1);
		componentTwo.SetType("E");
		componentTwo.SetName("123");

		componentsData.push_back(componentOne);
		componentsData.push_back(componentTwo);

		vector<int> componentsId;
		componentsId.push_back(0);
		componentsId.push_back(1);

		ConnectionData connectionData;
		connectionData.SetId(3);
		connectionData.SetComponents(componentsId);
		connectionsData.push_back(connectionData);

		EntityData entityData;
		entityData.SetPrimaryKeysId(0);
		entityData.SetPrimaryKeysId(1);
		entityData.SetAttributeId(2);
		entityData.SetAttributeId(3);
		entitiesData.push_back(entityData);
		entitiesData.at(0).SetEntityId(0);

		EntityData entityDataTwo;
		entityData.SetAttributeId(4);
		entityData.SetAttributeId(5);
		entitiesDataTwo.push_back(entityDataTwo);
		entitiesDataTwo.at(0).SetEntityId(6);
	}

	virtual void TearDown()
	{
	}

public:
	SaveFiles saveFile;
	vector<ComponentData> componentsData;
	vector<ConnectionData> connectionsData;
	vector<EntityData> entitiesData;
	vector<EntityData> entitiesDataTwo;
};

TEST_F(SaveFileTest, splitPath)
{
	string str;
	string path = "C:\\test\\a.erd";
	string pathTwo = "123";
	str = saveFile.splitPath(path);
	EXPECT_EQ("C:\\test", str);
	str = saveFile.splitPath(pathTwo);
	EXPECT_EQ("123", str);
}

/*
TEST_F(SaveFileTest, CreateFolder)
{
	vector<string> str;
	string path = "C:\\test\\a.erd";
	EXPECT_TRUE(saveFile.CreateFolder(path));
}*/

TEST_F(SaveFileTest, CheckSavePathExist)
{
	string pathOne = "C:\\";
	string pathTwo = "b313";
	string pathTree = "Debug";
	EXPECT_TRUE(saveFile.CheckSavePathExist(pathOne));
	EXPECT_FALSE(saveFile.CheckSavePathExist(pathTwo));
	EXPECT_TRUE(saveFile.CheckSavePathExist(pathTree));
}

TEST_F(SaveFileTest, CheckSaveFileFormat)
{
	string path = "C:\\aa.erd";
	string pathTwo = "C:\\aa\\uyyuy";
	EXPECT_TRUE(saveFile.CheckSaveFileFormat(path));
	EXPECT_FALSE(saveFile.CheckSaveFileFormat(pathTwo));
}


TEST_F(SaveFileTest, SaveComponent)
{
	fstream file;
	EXPECT_FALSE(saveFile.SaveComponent(file));

	saveFile.path = "test.erd";
	saveFile.componentData = componentsData;
	EXPECT_TRUE(saveFile.SaveComponent(file));
}

TEST_F(SaveFileTest, SaveConnection)
{
	fstream file;
	EXPECT_FALSE(saveFile.SaveConnection(file));

	saveFile.path = "test.erd";
	saveFile.connectionData = connectionsData;
	EXPECT_TRUE(saveFile.SaveConnection(file));
}

TEST_F(SaveFileTest, SavePrimaryKey)
{
	fstream file;
	EXPECT_FALSE(saveFile.SaveConnection(file));

	saveFile.path = "test.erd";
	saveFile.SetPrimaryData(entitiesData);
	EXPECT_TRUE(saveFile.SavePrimaryKey(file));

	saveFile.SetPrimaryData(entitiesDataTwo);
	EXPECT_TRUE(saveFile.SavePrimaryKey(file));
}
