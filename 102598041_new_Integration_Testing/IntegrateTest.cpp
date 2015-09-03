#include "gtest/gtest.h"
#include "../102598041_new/CommandManager.h"
#include "../102598041_new/AddComponentCmd.h"
#include "../102598041_new/ConnectComponentsCmd.h"
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
#include "../102598041_new/Presentation.h"
#include <direct.h>

using namespace std;

class IntegrateTest : public ::testing::Test
{ 
protected:
	virtual void SetUp()
	{
		_mkdir("testdata");
		erModel = new ERModel();
		erModel->observer = nullptr;
		erModel->mainWindowObserver = nullptr;
		presentation = new Presentation(erModel);
		erModel->LoadFile("test_file1.erd");
		erModel->SaveFile("testdata\\test_file1.erd");
		/*
		fstream file("./testdata/test_file1.erd", ios::out);
		file<<"E, Engineer"<<endl; 
		file<<"A, Emp_ID"<<endl;
		file<<"A, Name"<<endl; 
		file<<"E, PC"<<endl; 
		file<<"A, PC_ID"<<endl; 
		file<<"A, Purchase_Date"<<endl; 
		file<<"C "<<endl; 
		file<<"C "<<endl; 
		file<<"C "<<endl; 
		file<<"C "<<endl; 
		file<<"C, 1"<<endl; 
		file<<"C, 1"<<endl; 
		file<<"A, Department"<<endl;
		file<<"C "<<endl;
		file<<" "<<endl;
		file<<"7 0,1 "<<endl;
		file<<"8 0,3 "<<endl;
		file<<"9 4,5 "<<endl;
		file<<"10 4,6 "<<endl;
		file<<"11 0,2 "<<endl;
		file<<"12 2,4 "<<endl;
		file<<"14 0,13"<<endl;
		file<<" "<<endl;
		file<<"0 1,3 "<<endl;
		file<<"4 5"<<endl;
		file.close();*/
	}

	virtual void TearDown()
	{
		remove("./testdata/test_file1.erd");
		_rmdir("./testdata/");
		delete erModel;
	}

public:
	ERModel *erModel;
	Presentation *presentation;
};

TEST_F(IntegrateTest, testLoadFileNotExist)
{
	EXPECT_FALSE(erModel->LoadFile("/testdata/file_not_exist.erd"));
}

TEST_F(IntegrateTest, testIsPrimaryExist)
{
	vector<EntityData> entityData;
	EXPECT_TRUE(erModel->LoadFile("testdata\\test_file1.erd"));
	entityData = erModel->GetEntitiesData();

	for(unsigned int index = 0; index < entityData.size(); index++)
	{
		if(erModel->components.at(entityData.at(index).GetId())->GetName() == "Engineer")
		{
			vector<int> primaryKeyId = entityData.at(index).primaryKeysId;
			
			for(unsigned int i = 0; i < primaryKeyId.size(); i++)
			{
				if(erModel->components.at(primaryKeyId.at(i))->GetName() == "Emp_ID")
				{
					Attributes *attribute = dynamic_cast<Attributes *>(erModel->components.at(primaryKeyId.at(i)));
					EXPECT_TRUE(attribute->primaryKey);
				}
				else if(erModel->components.at(primaryKeyId.at(i))->GetName() == "Name")
				{
					Attributes *attribute = dynamic_cast<Attributes *>(erModel->components.at(primaryKeyId.at(i)));
					EXPECT_TRUE(attribute->primaryKey);
				}
			}
		}
		else if(erModel->components.at(entityData.at(index).GetId())->GetName() == "PC")
		{
			vector<int> primaryKeyId = entityData.at(index).primaryKeysId;

			for(unsigned int i = 0; i < primaryKeyId.size(); i++)
			{
				if(erModel->components.at(primaryKeyId.at(i))->GetName() == "PC_ID")
				{
					Attributes *attribute = dynamic_cast<Attributes *>(erModel->components.at(primaryKeyId.at(i)));
					EXPECT_TRUE(attribute->primaryKey);
				}
			}

			vector<int> attributeId = entityData.at(index).attributesId;

			for(unsigned int i = 0; i < attributeId.size(); i++)
			{
				if(erModel->components.at(primaryKeyId.at(i))->GetName() == "Purchase_Date")
				{
					Attributes *attribute = dynamic_cast<Attributes *>(erModel->components.at(primaryKeyId.at(i)));
					EXPECT_FALSE(attribute->primaryKey);
				}
			}
		}
	}
}

TEST_F(IntegrateTest, testUndoDeleteComponent)
{
	EXPECT_TRUE(erModel->LoadFile("testdata\\test_file1.erd"));
	presentation->AddNode("E", "Text");
	EXPECT_EQ("Text", erModel->currentCreateComponent->GetName());
	presentation->DeleteComponent("15");
	EXPECT_EQ(-1, erModel->components.at(15)->GetId());
	presentation->Undo();
	EXPECT_EQ("Text", erModel->components.at(15)->GetName());
}

TEST_F(IntegrateTest, testRedoConnectComponent)
{
	EXPECT_TRUE(erModel->LoadFile("testdata\\test_file1.erd"));
	presentation->AddNode("E", "Text");
	EXPECT_EQ("Text", erModel->currentCreateComponent->GetName());
	presentation->AddNode("A", "Test Attr");
	EXPECT_EQ("Test Attr", erModel->currentCreateComponent->GetName());
	presentation->ConnectComponents("15", "16");
	vector<int> componentsId = erModel->components.back()->GetConnectComponentsId();
	EXPECT_EQ(15, componentsId.at(0));
	EXPECT_EQ(16, componentsId.at(1));
	presentation->Undo();
	componentsId = erModel->components.back()->GetConnectComponentsId();
	EXPECT_EQ(0, componentsId.size());
	presentation->Redo();
	componentsId = erModel->components.back()->GetConnectComponentsId();
	EXPECT_EQ(15, componentsId.at(0));
	EXPECT_EQ(16, componentsId.at(1));
}

TEST_F(IntegrateTest, testCommonUsage)
{
	EXPECT_TRUE(erModel->LoadFile("testdata\\test_file1.erd"));
	presentation->AddNode("E", "Work Diary"); //15
	EXPECT_EQ("Work Diary", erModel->currentCreateComponent->GetName());
	presentation->AddNode("R", "Write"); //16
	EXPECT_EQ("Write", erModel->currentCreateComponent->GetName());
	presentation->ConnectComponents("0", "16", "1"); //17
	vector<int> componentsId = erModel->components.back()->GetConnectComponentsId();
	EXPECT_EQ(0, componentsId.at(0));
	EXPECT_EQ(16, componentsId.at(1));
	presentation->ConnectComponents("15", "16"); //18
	componentsId = erModel->components.back()->GetConnectComponentsId();
	EXPECT_EQ(15, componentsId.at(0));
	EXPECT_EQ(16, componentsId.at(1));
	presentation->AddNode("A", "Content"); //19
	EXPECT_EQ("Content", erModel->currentCreateComponent->GetName());
	presentation->AddNode("A", "WD_ID"); //20
	EXPECT_EQ("WD_ID", erModel->currentCreateComponent->GetName());
	presentation->AddNode("A", "WD_date");  //21
	EXPECT_EQ("WD_date", erModel->currentCreateComponent->GetName());
	presentation->ConnectComponents("15", "19"); //22
	componentsId = erModel->components.back()->GetConnectComponentsId();
	EXPECT_EQ(15, componentsId.at(0));
	EXPECT_EQ(19, componentsId.at(1));
	presentation->ConnectComponents("15", "20"); //23
	componentsId = erModel->components.back()->GetConnectComponentsId();
	EXPECT_EQ(15, componentsId.at(0));
	EXPECT_EQ(20, componentsId.at(1));
	presentation->ConnectComponents("15", "21"); //24
	componentsId = erModel->components.back()->GetConnectComponentsId();
	EXPECT_EQ(15, componentsId.at(0));
	EXPECT_EQ(21, componentsId.at(1));
	vector<string> attributes;
	attributes.push_back("20");
	presentation->SetAttributeIsPrimary(attributes);

	Components *entity;
	for(vector<Components *>::iterator components = erModel->components.begin(); components != erModel->components.end(); components++)
	{
		if((*components)->GetName() == "Work Diary")
		{
			entity = (*components);
		}
	}
	EXPECT_EQ("Work Diary", entity->GetName());
	vector<int> connectionsId;
	vector<int> attributesId;
	connectionsId = dynamic_cast<Entity *>(entity)->GetConnectComponentsId();

	for(unsigned int index = 0; index < connectionsId.size(); index++)
	{
		attributesId.push_back(dynamic_cast<Connection *>(erModel->components.at(connectionsId.at(index)))->GetEntityConnectAttributeId());
	}
	
	Components *attribute;
	for(unsigned int index = 0; index < attributesId.size(); index++)
	{
		if(attributesId.at(index) != -1 && erModel->components.at(attributesId.at(index))->GetName() == "WD_ID")
		{
			attribute = erModel->components.at(attributesId.at(index));
		}
	}

	EXPECT_TRUE(dynamic_cast<Attributes *>(attribute)->primaryKey);

	presentation->DeleteComponent("15");
	EXPECT_EQ(-1, erModel->components.at(15)->GetId());
	EXPECT_EQ(-1, erModel->components.at(18)->GetId());
	EXPECT_EQ(-1, erModel->components.at(22)->GetId());
	EXPECT_EQ(-1, erModel->components.at(23)->GetId());
	EXPECT_EQ(-1, erModel->components.at(24)->GetId());
}