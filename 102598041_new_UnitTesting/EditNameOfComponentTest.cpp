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
#include "../102598041_QT/EditNameOfComponent.h"

using namespace std;

class EditNameOfComponentTest : public ::testing::Test
{ 
protected:
	virtual void SetUp()
	{
		erModel = new ERModel();
		erModel->observer = nullptr;
		erModel->mainWindowObserver = nullptr;
		erModel->AddNode("A", "ccc");
	}

	virtual void TearDown()
	{
		delete erModel;
		delete editName;
	}

public:
	ERModel *erModel;
	EditNameOfComponent *editName;
};

TEST_F(EditNameOfComponentTest, Execute)
{
	
	editName =  new EditNameOfComponent(erModel, 0, "test");
	editName->Execute();
	EXPECT_EQ("test", erModel->components.at(0)->GetName());
}

TEST_F(EditNameOfComponentTest, Unexecute)
{
	editName =  new EditNameOfComponent(erModel, 0, "test");
	editName->Execute();
	editName->Unexecute();
	EXPECT_EQ("ccc", erModel->components.at(0)->GetName());
}
