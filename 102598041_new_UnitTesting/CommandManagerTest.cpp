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

class CommandManagerTest : public ::testing::Test
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
		commnadManager.~CommandManager();
	}

public:
	ERModel *erModel;
	CommandManager commnadManager;
};

TEST_F(CommandManagerTest, Execute)
{
	commnadManager.Execute(new AddComponentCmd(erModel, "A", "a0"));
	EXPECT_EQ(1, commnadManager.undoCommands.size());
	EXPECT_EQ(1, erModel->components.size());
	EXPECT_EQ(0, commnadManager.redoCommands.size());
	commnadManager.Undo();
	EXPECT_EQ(1, commnadManager.redoCommands.size());

	commnadManager.Redo();
	commnadManager.Execute(new DeleteComponentCmd(erModel, 0));
	EXPECT_EQ(2, commnadManager.undoCommands.size());
	EXPECT_EQ(-1, erModel->components.at(0)->GetId());
	commnadManager.Undo();
	EXPECT_EQ(0, erModel->components.at(0)->GetId());

	commnadManager.Execute(new AddComponentCmd(erModel, "E", "e0"));
	commnadManager.Execute(new ConnectComponentsCmd(erModel, "0", "1", ""));
	EXPECT_EQ(3, commnadManager.undoCommands.size());
	EXPECT_EQ(2, erModel->components.at(2)->GetId());
	commnadManager.Undo();
	EXPECT_EQ(-1, erModel->components.at(2)->GetId());
}

TEST_F(CommandManagerTest, Undo)
{
	EXPECT_FALSE(commnadManager.Undo());
	commnadManager.Execute(new AddComponentCmd(erModel, "A", "a0"));
	EXPECT_EQ(1, commnadManager.undoCommands.size());
	EXPECT_TRUE(commnadManager.Undo());
	commnadManager.Redo();
	commnadManager.Execute(new DeleteComponentCmd(erModel, 0));
	EXPECT_TRUE(commnadManager.Undo());
	commnadManager.Execute(new AddComponentCmd(erModel, "E", "e0"));
	commnadManager.Execute(new ConnectComponentsCmd(erModel, "0", "1", ""));
	EXPECT_TRUE(commnadManager.Undo());
}

TEST_F(CommandManagerTest, Redo)
{
	EXPECT_FALSE(commnadManager.Redo());
	commnadManager.Execute(new AddComponentCmd(erModel, "A", "a0"));
	commnadManager.Undo();
	EXPECT_TRUE(commnadManager.Redo());

	commnadManager.Execute(new DeleteComponentCmd(erModel, 0));
	commnadManager.Undo();
	EXPECT_TRUE(commnadManager.Redo());

	commnadManager.Execute(new AddComponentCmd(erModel, "A", "a0"));
	commnadManager.Execute(new AddComponentCmd(erModel, "E", "e0"));
	commnadManager.Execute(new ConnectComponentsCmd(erModel, "0", "1", ""));
	commnadManager.Undo();
	EXPECT_TRUE(commnadManager.Redo());
}

TEST_F(CommandManagerTest, ClearCommand)
{
	commnadManager.Execute(new AddComponentCmd(erModel, "A", "a0"));
	EXPECT_EQ(1, commnadManager.undoCommands.size());
	commnadManager.ClearCommand();
	EXPECT_EQ(0, commnadManager.undoCommands.size());
	commnadManager.Execute(new AddComponentCmd(erModel, "A", "a0"));
	EXPECT_EQ(0, commnadManager.redoCommands.size());
	commnadManager.Undo();
	EXPECT_EQ(1, commnadManager.redoCommands.size());
}