#include "gtest/gtest.h"
#include "../102598041_new/ConnectComponentsCmd.h"
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
#include "../102598041_QT/SetPrimaryKeyCmd.h"

using namespace std;

class SetPrimaryKeyCmdTest : public ::testing::Test
{ 
protected:
	virtual void SetUp()
	{
		erModel = new ERModel();
		erModel->observer = nullptr;
		erModel->mainWindowObserver = nullptr;
		erModel->AddNode("A", "aa");
		erModel->AddNode("E", "ee");
		erModel->AddNode("R", "rr");
	}

	virtual void TearDown()
	{
		delete erModel;
		delete setPrimaryKeyCmd;
	}

public:
	SetPrimaryKeyCmd *setPrimaryKeyCmd;
	ERModel *erModel;
};

TEST_F(SetPrimaryKeyCmdTest, Execute)
{
	setPrimaryKeyCmd = new SetPrimaryKeyCmd(erModel, 0);
	EXPECT_FALSE(dynamic_cast<Attributes *>(erModel->components.at(0))->GetPrimaryKey());
	setPrimaryKeyCmd->Execute();
	EXPECT_TRUE(dynamic_cast<Attributes *>(erModel->components.at(0))->GetPrimaryKey());
}

TEST_F(SetPrimaryKeyCmdTest, Unexecute)
{
	setPrimaryKeyCmd = new SetPrimaryKeyCmd(erModel, 0);
	EXPECT_FALSE(dynamic_cast<Attributes *>(erModel->components.at(0))->GetPrimaryKey());
	setPrimaryKeyCmd->Execute();
	EXPECT_TRUE(dynamic_cast<Attributes *>(erModel->components.at(0))->GetPrimaryKey());
	setPrimaryKeyCmd->Unexecute();
	EXPECT_FALSE(dynamic_cast<Attributes *>(erModel->components.at(0))->GetPrimaryKey());
}
