#pragma once
#include <iostream>
#include "CommandManager.h"
#include "ERModel.h"
#include "Components.h"
#include "AddComponentCmd.h"
#include "DeleteComponentCmd.h"
#include "ConnectComponentsCmd.h"
#include "MessageOfConstString.h"
#include "../102598041_QT/SetPrimaryKeyCmd.h"
#include "../102598041_QT/EditNameOfComponent.h"
#include "Convertor.h"
#include "ComponentData.h"
#include "../102598041_QT/ComponentPoint.h"
#include "../102598041_QT/MoveComponents.h"
#include "../102598041_QT/CutComponents.h"

using namespace std;

class Presentation
{
private:
	ERModel *erModel;
	CommandManager commandManager;
	Convertor convertor;
	//vector<int> componentsId;

public:
	Presentation(ERModel *);
	~Presentation(void);
	void AddNode(string, string);
	void DeleteComponent(string);
	void ConnectComponents(string, string, string cardinality = "");
	void SetPrimaryKey(int);
	void EditComponentName(int, string);
	void SetAttributeIsPrimary(vector<string>);
	bool LoadFile(string);
	bool SaveFile(string);
	bool SaveXmlFile(string);
	bool Redo();
	bool Undo();
	vector<ComponentData> GetComponentsData();
	int GetComponentsSize();
	Components *GetComponent(int);
	Components *GetNewComponent();
	Components *GetNewConnection();
	int CanConnect(string, string);
	int GetConnectMessage();
	bool IsComponentExist(int);
	bool CanReName(int, string);
	void MoveComponent(vector<ComponentPoint>, vector<ComponentPoint>);
	bool LoadPositionFile(string);
	void CutComponent(vector<int>);
	void PasteComponents();
	void CopyComponent(vector<int>);
};

