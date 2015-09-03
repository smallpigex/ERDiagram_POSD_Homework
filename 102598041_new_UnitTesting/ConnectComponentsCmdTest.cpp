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

using namespace std;

class ConnectComponentsCmdTest : public ::testing::Test
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
		delete connectComponentsCmd;
	}

public:
	ConnectComponentsCmd *connectComponentsCmd;
	ERModel *erModel;
};

TEST_F(ConnectComponentsCmdTest, Execute)
{
	connectComponentsCmd = new ConnectComponentsCmd(erModel, "0", "1", "");
	connectComponentsCmd->Execute();
	EXPECT_EQ(3, erModel->components.at(3)->GetId());
	EXPECT_TRUE(erModel->components.at(3)->CheckHasBeenConnect(erModel->components.at(0)));
	EXPECT_TRUE(erModel->components.at(3)->CheckHasBeenConnect(erModel->components.at(1)));
	EXPECT_EQ(3, connectComponentsCmd->connection->GetId());
}

TEST_F(ConnectComponentsCmdTest, Unexecute)
{
	connectComponentsCmd = new ConnectComponentsCmd(erModel, "0", "1", "");
	connectComponentsCmd->Execute();
	connectComponentsCmd->Unexecute();
	EXPECT_EQ(-1, erModel->components.at(3)->GetId());
}
