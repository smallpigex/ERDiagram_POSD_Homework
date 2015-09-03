#pragma once
#include <iostream>
#include <cctype>
#include "TextUI.h"
#include "MessageOfConstString.h"
#include "Presentation.h"

using namespace std;

class TextUI;
class ERModel;

class TextUIController
{
private:
	TextUI *textUI;
	ERModel *erModel;
	Presentation *presentation;

public:
	TextUIController(ERModel *, Presentation *);
	~TextUIController(void);
	void StartEdit();
	void ProcessMainMenu(string);
	bool ProcessInput(string, string);
	void ProcessErrorMessage(string);
	void ProcessDeleteComponent(string);

	/*檢查輸入是否正確*/
	bool CheckInputIdFormat(string);
	bool CheckInputCommand(string);
	bool CheckInputType(string);
	bool CheckIdExist(string);
	bool CheckInputCardinality(string);
	bool CheckNodeIsEntity(string);
	bool CheckIsAttributeBelongToEntity(string ,string);

	/*功能區*/
	void ProcessAddNode(string, string);
	void ProcessConnectNodes(string, string);
	void ProcessSetPrimaryKey(string input);
	bool ProcessSaveFile(string);
	bool ProcessLoadFile(string);

	/*Convert*/
	string ConvertStringToCardinalityFormat(string);

	//分解字串
	vector<string> split(string idList);

	/*Undo and Redo*/
	bool Undo();
	bool Redo();

	//call function menu
	void CallFunctionMenu(string);
	void DisplayLoadFile(string);
	void DisplaySaveFile(string);
	void DisplayAddNode(string);
	void DisplayConnectNodes(string);
	void DisplayDiagram(string);
	void DisplaySetPrimaryKey(string);
	void DisplayTable(string);
	void DisplayDeleteComponent(string);
	void DisplayUndo(string);
	void DisplayRedo(string);
	void DisplayExit(string);
};

