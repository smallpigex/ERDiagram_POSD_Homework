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

class LoadFileTest : public ::testing::Test
{ 
protected:
	virtual void SetUp()
	{
		
	}

	virtual void TearDown()
	{
	
	}

public:
	LoadFiles loadFile;
	vector<string> testData;
};

TEST_F(LoadFileTest, StoreData)
{
	fstream file;
	file.open("dataOne.erd", ios::in);
	loadFile.StoreData(file, testData);
	EXPECT_EQ("Show me the money", testData.at(0));
}

TEST_F(LoadFileTest, LoadFile)
{
	EXPECT_FALSE(loadFile.LoadFile(""));
	EXPECT_TRUE(loadFile.LoadFile("dataTwo.erd"));
	EXPECT_EQ(15, loadFile.component.size());
	EXPECT_EQ(7, loadFile.connection.size());
	EXPECT_EQ(2, loadFile.entity.size());
}