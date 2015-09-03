#include "gtest/gtest.h"
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

class DeleteComponentCmdTest : public ::testing::Test
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
		erModel->AddNode("E", "ee");
		erModel->AddNode("R", "rr");
		erModel->AddNode("A", "a2");
		erModel->ConnectComponents("5", "1", "1");
		erModel->ConnectComponents("1", "2", "1");
		erModel->ConnectComponents("3", "4", "N");
	}

	virtual void TearDown()
	{
		delete erModel;
		delete deleteComponentCmd;
	}

public:
	DeleteComponentCmd *deleteComponentCmd;
	ERModel *erModel;
};

TEST_F(DeleteComponentCmdTest, Execute)
{
	deleteComponentCmd = new DeleteComponentCmd(erModel, 0);
	deleteComponentCmd->Execute();
	EXPECT_EQ(0, deleteComponentCmd->tempComponents->GetId());
	EXPECT_EQ(-1, erModel->components.at(0)->GetId());

	deleteComponentCmd = new DeleteComponentCmd(erModel, 1);
	deleteComponentCmd->Execute();
	EXPECT_EQ(1, deleteComponentCmd->tempComponents->GetId());
	EXPECT_EQ(-1, erModel->components.at(1)->GetId());

	deleteComponentCmd = new DeleteComponentCmd(erModel, 8);
	deleteComponentCmd->Execute();
	EXPECT_EQ(8, deleteComponentCmd->tempComponents->GetId());
	EXPECT_EQ(-1, erModel->components.at(8)->GetId());
}

TEST_F(DeleteComponentCmdTest, Unexecute)
{
	deleteComponentCmd = new DeleteComponentCmd(erModel, 0);
	deleteComponentCmd->Execute();
	deleteComponentCmd->Unexecute();
	EXPECT_EQ(0, erModel->components.at(0)->GetId());

	deleteComponentCmd = new DeleteComponentCmd(erModel, 1);
	deleteComponentCmd->Execute();
	deleteComponentCmd->Unexecute();
	EXPECT_EQ(1, erModel->components.at(1)->GetId());

	deleteComponentCmd = new DeleteComponentCmd(erModel, 8);
	deleteComponentCmd->Execute();
	deleteComponentCmd->Unexecute();
	EXPECT_EQ(8, erModel->components.at(8)->GetId());
}
