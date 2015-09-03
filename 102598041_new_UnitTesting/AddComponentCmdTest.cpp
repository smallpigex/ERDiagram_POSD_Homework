#include "gtest/gtest.h"
#include "../102598041_new/AddComponentCmd.h"
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

class AddComponentCmdTest : public ::testing::Test
{ 
protected:
	virtual void SetUp()
	{
		typeA = "A";
		typeC = "C";
		typeE = "E";
		typeR = "R";
		nameA = "aa";
		nameC = "";
		nameE = "ee";
		nameR = "rr";
		erModel = new ERModel();
		erModel->observer = nullptr;
		erModel->mainWindowObserver = nullptr;
	}

	virtual void TearDown()
	{
		delete addComonentCmd;
		delete erModel;
	}

public:
	AddComponentCmd *addComonentCmd;
	ERModel *erModel;
	string typeA;
	string typeE;
	string typeR;
	string typeC;
	string nameA;
	string nameE;
	string nameR;
	string nameC;
};

TEST_F(AddComponentCmdTest, Execute)
{
	addComonentCmd = new AddComponentCmd(erModel, typeA, nameA);
	addComonentCmd->Execute();
	EXPECT_EQ(1, erModel->components.size());
	EXPECT_EQ(0, erModel->components.at(0)->GetId());
	EXPECT_EQ("A", erModel->components.at(0)->GetType());
	EXPECT_EQ(0, addComonentCmd->tmpComponentId);
	
	addComonentCmd = new AddComponentCmd(erModel, typeE, nameE);
	addComonentCmd->Execute();
	EXPECT_EQ(2, erModel->components.size());
	EXPECT_EQ(1, erModel->components.at(1)->GetId());
	EXPECT_EQ("E", erModel->components.at(1)->GetType());
	EXPECT_EQ(1, addComonentCmd->tmpComponentId);

	
	addComonentCmd = new AddComponentCmd(erModel, typeR, nameR);
	addComonentCmd->Execute();
	EXPECT_EQ(3, erModel->components.size());
	EXPECT_EQ(2, erModel->components.at(2)->GetId());
	EXPECT_EQ("R", erModel->components.at(2)->GetType());
	EXPECT_EQ(2, addComonentCmd->tmpComponentId);

	addComonentCmd = new AddComponentCmd(erModel, typeC, nameC);
	addComonentCmd->Execute();
	EXPECT_EQ(4, erModel->components.size());
	EXPECT_EQ(3, erModel->components.at(3)->GetId());
	EXPECT_EQ("C", erModel->components.at(3)->GetType());
	EXPECT_EQ(3, addComonentCmd->tmpComponentId);
}

TEST_F(AddComponentCmdTest, Unexecute)
{
	addComonentCmd = new AddComponentCmd(erModel, typeA, nameA);
	addComonentCmd->Execute();
	addComonentCmd->Unexecute();
	EXPECT_EQ(1, erModel->components.size());
	//nullComponent id = -1;
	EXPECT_EQ(-1, erModel->components.at(0)->GetId());
}
