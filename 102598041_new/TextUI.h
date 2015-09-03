#pragma once
#include <iostream>
#include <string>
#include <vector>
#include "ObserverTextUIInterface.h"
#include "TextUIController.h"
#include "ERModel.h"
#include "ConnectionData.h"
#include "ComponentData.h"
#include <iomanip>

using namespace std;

class TextUIController;

class TextUI : public ObserverTextUIInterface
{
private:
	TextUIController *controller;
	ERModel *erModel;

public:
	TextUI(TextUIController *, ERModel *);
	~TextUI(void);
	void DisplayMenu();
	string InputString(string);
	void InputAttributeId(string &);
	void DisplayLoadFileMenu();
	void DisplaySaveFileMenu();
	void DisplayAddNodeMenu();
	void DisplayAddNodeTypeMessage();
	void DisplayAddNodeNameMessage();
	void DisplayConnectNodeMenu();
	void DisplayCardinalityMenu();
	void DisplayDiagram();
	void DisplayPrimaryKeyMenu();
	void DisplaySetPrimaryKeyMenu(string);
	void DisplayTable();
	void DisplayDeleteMenu();
	void DisplayUndo();
	void DisplayRedo();
	void DisplayExit();

	//Success Message
	void DisplayAddNodeSuccessMessage();
	void DisplayConnectSuccessMessage(string, string);
	void DisplayCardinalitySuccessMessage(string);
	void DisplayDeleteSuccessMessage(string);

	//DisplayGraph;
	void DisplayAllNodes();
	void DisplayAllComponent();
	void DisplayAllConnection();
	void DisplayEntityNodes();
	void DisplayAttribtuteOfEntity(string);

	//Error Message
	void ShowErrorMessage(string, string id = "");
	void ShowErrorConnectMessage(int, string, string);
	void DisplayInvalidCommand();
	void DisplayInvalidType();
	void DisplayInvalidId();
	void DisplayInvalidCardinality();
	void DisplayInvalidEntity(string);
	void DisplayInvalidAttribute(string, string);
	//void DisplayInvalidSave();

	//update date
	void UpdateComponents(int, string ,string);
	void UpdateConnection(int, int, string);

	//將type回復成完整的名稱
	string ConvertTypeToTypeName(string);

	//Graph Title
	void DisplayGraphTitle(string);
	void ShowTitleData(string);
	void ShowGraphBottom();

};

