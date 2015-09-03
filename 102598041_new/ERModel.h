#pragma once
#include <iostream>
#include <vector>
#include <stack>
#include "ERModeSubject.h"
#include "MessageOfConstInteger.h"
#include "Components.h"
#include "ComponentFactory.h"
#include "ObserverTextUIInterface.h"
#include "Convertor.h"
#include "ConnectionData.h"
#include "ComponentData.h"
#include "SaveFiles.h"
#include "EntityData.h"
#include "LoadFiles.h"
#include "../102598041_QT/GUIObserver.h"
//#include "../102598041_QT/GUIPresentationSubject.h"
#include "gtest/gtest_prod.h"
#include "../102598041_QT/MainWindowSubjectForERModel.h"
#include "../102598041_QT/ComponentVisitor.h"
#include "../102598041_QT/SaveComponentVisitor.h"
#include "../102598041_QT/SaveXmlComponentVisitor.h"

using namespace std;

class ERModel : public ERModeSubject, public MainWindowSubjectForERModel 
{
	friend class AddComponentCmdTest;
	FRIEND_TEST(AddComponentCmdTest, Execute);
	FRIEND_TEST(AddComponentCmdTest, Unexecute);

	friend class SetPrimaryKeyCmdTest;
	FRIEND_TEST(SetPrimaryKeyCmdTest, Execute);
	FRIEND_TEST(SetPrimaryKeyCmdTest, Unexecute);

	friend class ConnectComponentsCmdTest;
	FRIEND_TEST(ConnectComponentsCmdTest, Execute);
	FRIEND_TEST(ConnectComponentsCmdTest, Unexecute);

	friend class DeleteComponentCmdTest;
	FRIEND_TEST(DeleteComponentCmdTest, Execute);
	FRIEND_TEST(DeleteComponentCmdTest, Unexecute);

	friend class CommandManagerTest;
	FRIEND_TEST(CommandManagerTest, Execute);

	friend class ERModelTest;
	FRIEND_TEST(ERModelTest, StoreComponent);
	FRIEND_TEST(ERModelTest, GetNullComponentIndex);
	FRIEND_TEST(ERModelTest, GetSerialNumber);
	FRIEND_TEST(ERModelTest, AddNode);
	FRIEND_TEST(ERModelTest, GetNodesData);
	FRIEND_TEST(ERModelTest, GetConnectionsData);
	FRIEND_TEST(ERModelTest, StoreAttributeToComponentData);
	FRIEND_TEST(ERModelTest, CheckIdExist);
	FRIEND_TEST(ERModelTest, VerifyComponentType);
	FRIEND_TEST(ERModelTest, CheckIsAttributeBelongToEntity);
	FRIEND_TEST(ERModelTest, CheckIsAttribute);
	FRIEND_TEST(ERModelTest, AddConnection);
	FRIEND_TEST(ERModelTest, ConnectComponents);
	FRIEND_TEST(ERModelTest, SetAttributeIsPrimary);
	FRIEND_TEST(ERModelTest, DeleteComponent);
	FRIEND_TEST(ERModelTest, DeleteConnecionFromTargetToSourceComponent);
	FRIEND_TEST(ERModelTest, GetConnectComponentId);
	FRIEND_TEST(ERModelTest, DeleteConnection);
	FRIEND_TEST(ERModelTest, ConnectComponentsToConnecions);
	FRIEND_TEST(ERModelTest, RecoveryConnect);
	FRIEND_TEST(ERModelTest, RecoveryComponents);
	FRIEND_TEST(ERModelTest, GetConnectionOfComponent);
	FRIEND_TEST(ERModelTest, GetConnectionOfComponent);
	FRIEND_TEST(ERModelTest, TidyUpComponents);
	FRIEND_TEST(ERModelTest, ClearNullComponent);
	FRIEND_TEST(ERModelTest, ClassifyAttribute);
	FRIEND_TEST(ERModelTest, SetEnityData);
	FRIEND_TEST(ERModelTest, StoreAttributeToEnityData);
	FRIEND_TEST(ERModelTest, LoadFile);
	FRIEND_TEST(ERModelTest, LoadComponent);
	FRIEND_TEST(ERModelTest, IsComponentExist);
	FRIEND_TEST(ERModelTest, SetPrimaryKey);
	FRIEND_TEST(ERModelTest, CheckNameIsCardinality);
	FRIEND_TEST(ERModelTest, SetComponentName);
	FRIEND_TEST(ERModelTest, IsCardinality);
	FRIEND_TEST(ERModelTest, CheckNameIsCardinality);
	

	friend class testLoadFileNotExist;
	friend class IntegrateTest;
	FRIEND_TEST(IntegrateTest, testLoadFileNotExist);
	FRIEND_TEST(IntegrateTest, testIsPrimaryExist);
	FRIEND_TEST(IntegrateTest, testUndoDeleteComponent);
	FRIEND_TEST(IntegrateTest, testRedoConnectComponent);
	FRIEND_TEST(IntegrateTest, testCommonUsage);

	friend class EditNameOfComponentTest;
	FRIEND_TEST(EditNameOfComponentTest, Execute);
	FRIEND_TEST(EditNameOfComponentTest, Unexecute);

private:
	vector<Components *> components;
	MainWindowObserver *mainWindowObserver;
	vector<Components *> tmpCutComponents;
	vector<Components *> tmpCopyComponents;
	//用來暫存被Delete的components以便做recovery動作
	//stack<Components *> tmpComponents;

	//用來暫存被Delete的components Id以便做redo的動作
	stack<int> tmpComponentsId;
	ComponentFactory componentFactory;
	Components *currentCreateComponent;
	Components *currentCreateConnection;
	//ObserverTextUIInterface *observer;
	Convertor convertor;
	int serialNumber;
	int connectMessage;
	GUIObserver *observer;
	int componentPointX;
	int componentPointY;

public:
	ERModel(void);
	~ERModel(void);
	void RegisterObserver(GUIObserver *);
	void NotifyObserverGUIComponentUpdate();
	void NotifyObserverUpateGUIConnection();
	void NotifyObserverRecoveryGUIComponent();
	void NotifyObserverUpdatePrimaryKey();
	void NotifyObserverDeleteGUIComponent();
	void NotifyObserverResetPoint();
	void RegisterMainWindowObserver(MainWindowObserver *);
	void NotifyMainWindowUpdateTable();
	void NotifyRefreshTable();
	void NotifyObserverUpdateComponentName();
	void NotifyObserverResetComponent();
	//void NotifyObserverGUIConnectionUpdate();
	
	/*
	void RegisterObserver(ObserverTextUIInterface *);
	void RemoveObserver(ObserverTextUIInterface *);
	void NotifyObserverComponentUpdate();
	void NotifyObserverConnectionUpdate(int, int, string);
	*/
	void SetComponentPointX(int);
	void SetComponentPointY(int);
	void AddNode(string, string);
	void StoreComponent(Components *);
	void GetNodesData(vector<int> &, vector<string> &, vector<string> &);
	vector<Components *> GetConnectionOfComponent(Components *);
	void ConnectComponentsToConnecions(vector<Components *>, Components *);
	void DeleteConnecionFromTargetToSourceComponent(int);
	void StoreAttributeToComponentData(string, vector<ComponentData> &);
	bool CheckIdExist(string);
	bool IsComponentExist(int);
	bool VerifyComponentType(string, string);
	bool CheckIsAttributeBelongToEntity(string, string);
	bool CheckIsAttribute(string);
	int CanConneciont(string, string);
	void ConnectComponents(string, string, string cardinality = "");
	void AddConnection(Components *, Components *);
	void SetCardinality(string);
	void SetAttributeIsPrimary(vector<string>);
	void DeleteSpecifiedComponent(int);
	void DeleteComponent(int);
	void DeleteConnection(int);
	void RecoveryComponents(Components *);
	void RecoveryConnect(Components *);
	int CheckNullComponent();
	void TidyUpComponents();
	bool LoadFile(string);
	bool SaveFile(string);
	void SetPrimaryKey(int);
	void SetComponentName(int, string);
	bool IsCardinality(Components *);
	bool CheckNameIsCardinality(string);

	//Get區
	int GetSerialNumber();
	int GetNullComponentIndex();
	int GetConnectComponentId(int, Components *);
	ComponentData GetAttributeOfEntity(string, vector<ComponentData> &);
	int GetLastComponentId();
	Components *GetComponent(int);
	Components *GetNewComponent();
	Components *GetCurrentCreateConnection();
	int GetCurrentCreateConnectionId();
	int GetCurrentCreateComponentId();
	string GetCurrentCreateComponentType();
	string GetCurrentCreateComponentName();
	int GetComponentIndex(int );
	vector<EntityData> GetEntitiesData();
	vector<ConnectionData> GetConnectionsData();
	vector<ComponentData> GetComponentsData();
	int GetComponentsSize();
	void SetConnectMessage(int);
	int GetConnectMessage();
	//end Get區(return)


	void StoreAttributeToEnityData(int, vector<int>, vector<EntityData> &);
	vector<string> split(string, string);
	void ClearComponents();
	void SetEnityData(EntityData &, vector<int>);
	void ClearNullComponent();
	void ClassifyAttribute(EntityData &, Components *);
	void LoadPrimaryKey(LoadFiles &);
	void LoadComponent(LoadFiles &);
	vector<EntityData> GetTables();
	void SearchTable(int, vector<EntityData> , vector<int> , vector<bool>);
	void StoreComponentData(ComponentVisitor *);
	bool SaveXmlFile(string);
	bool LoadPositionFile(string);
	void SetComponentPosition(Components *, string);
	void StoreCutComponents(int);
	void ClearCutComponents();
	void ClearCopyComponents();
	void CleartempComponents(vector<Components *> &);
	vector<Components *> GetCutComponents();
	void RecoveryCutComponents(vector<Components *>);
	void PasteComponent();
	void PastebyCopyComponents();
    void PastebyCutComponents();
	void CopyComponents(vector<int>);
	void DeleteConnectConnection(Components *);
	//void LoadConnection(SaveAndLoadFile &, int);
};

