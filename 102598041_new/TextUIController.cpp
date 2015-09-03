#include "TextUIController.h"


TextUIController::TextUIController(ERModel *erModel, Presentation *presentation)
{
	this->erModel = erModel;
	this->presentation = presentation;
	textUI = new TextUI(this, erModel);
}


TextUIController::~TextUIController(void)
{
}

void TextUIController::StartEdit()
{
	do
	{
		textUI->DisplayMenu();
	}
	while(true);
	
}

/*檢查輸入是否合法*/
 bool TextUIController::ProcessInput(string input, string menuMessage)
{
	if(menuMessage.compare(Message::MENU) == 0)
	{
		return CheckInputCommand(input);
	}
	else if(menuMessage.compare(Message::NODE_TYPE) == 0)
	{
		return CheckInputType(input);
	}
	else if(menuMessage.compare(Message::NODE_ID) == 0 || menuMessage.compare(Message::DELETE_COMPONENT) == 0)
	{
		return CheckIdExist(input);
	}
	else if(menuMessage.compare(Message::CARDINALITY) == 0)
	{
		return CheckInputCardinality(input);
	}
	else if(menuMessage.compare(Message::CHECK_ENTITY) == 0)
	{
		return CheckNodeIsEntity(input);
	}
	return true;
}

void TextUIController::ProcessMainMenu(string command)
{
	CallFunctionMenu(command);
}

void TextUIController::ProcessErrorMessage(string menuMessage)
{
	if(menuMessage.compare(Message::MENU) == 0)
	{
		textUI->DisplayInvalidCommand();
	}
	else if(menuMessage.compare(Message::NODE_TYPE) == 0)
	{
		textUI->DisplayInvalidType();
		textUI->DisplayAddNodeTypeMessage();
	}
	else if (menuMessage.compare(Message::NODE_ID) == 0)
	{

	}
}

void TextUIController::ProcessDeleteComponent(string input)
{
	presentation->DeleteComponent(input);
	textUI->DisplayDeleteSuccessMessage(input);
	textUI->DisplayAllComponent();
	textUI->DisplayAllConnection();
}

bool TextUIController::CheckInputIdFormat(string input)
{
	for(unsigned int index = 0; index < input.size(); ++index)
	{
		//檢查輸入的id是否出現文字、空格或符號
		if(isalpha(input[index]) || ispunct(input[index]) || isspace(input[index]))
		{
			return false;
		}
	}
	return true;
}

/*檢查輸入區*/
bool TextUIController::CheckInputCommand(string command)
{
	if(command.compare(Menu::LOAD_FILE) == 0 ||
	   command.compare(Menu::SAVE_FILE) == 0 ||
	   command.compare(Menu::ADD_A_NODE) == 0 ||
	   command.compare(Menu::CONNECT_TO_NODES) == 0 ||
	   command.compare(Menu::DISPLAY_DIAGRAM) == 0 ||
	   command.compare(Menu::SET_PRIMARY_KEY) == 0 ||
	   command.compare(Menu::DISPLAY_TABLE) == 0 ||
	   command.compare(Menu::DELETE_COMPONENT) == 0 ||
	   command.compare(Menu::UNDO) == 0 ||
	   command.compare(Menu::REDO) == 0 ||
	   command.compare(Menu::EXIT) == 0)
	{
		return true;
	}
	else
	{
		textUI->ShowErrorMessage(ErrorMessage::NOT_MENU);
		return false;
	}
}

bool TextUIController::CheckInputType(string type)
{
	if(type.compare(ComponetType::ATTRIBUTE) == 0 || 
	   type.compare(ComponetType::ENTITY) == 0 || 
	   type.compare(ComponetType::RELATIONSHIP) == 0)
	{
		return true;
	}
	else
	{
		textUI->ShowErrorMessage(ErrorMessage::NOT_TYPE);
		return false;
	}
}

bool TextUIController::CheckIdExist(string input)
{
	if(erModel->CheckIdExist(input) && CheckInputIdFormat(input))
	{
		return true;
	}
	else
	{
		textUI->ShowErrorMessage(ErrorMessage::NOT_ID);
		return false;
	}
}

bool TextUIController::CheckInputCardinality(string input)
{
	if(input.compare(InputNumber::ZERO) == 0 || input.compare(InputNumber::ONE) == 0)
	{
		return true;
	}
	else
	{
		textUI->ShowErrorMessage(ErrorMessage::NOT_CARDINALITY);
		return false;
	}
}

bool TextUIController::CheckNodeIsEntity(string input)
{
	if(CheckIdExist(input))
	{
		if(erModel->VerifyComponentType(input, ComponetType::ENTITY))
		{
			return true;
		}
		else
		{
			textUI->ShowErrorMessage(ErrorMessage::NOT_ENTITY, input);
		}
	}

	return false;
}

bool TextUIController::CheckIsAttributeBelongToEntity(string entity, string input)
{
	vector<string> attributes;
	attributes = split(input);
	
	//檢查attribute是否存在、格式是否正確、以及attribute是否屬於entity
	for(vector<string>::iterator attribute = attributes.begin(); attribute != attributes.end(); ++attribute)
	{
		if(!CheckInputIdFormat((*attribute)) || 
		   !erModel->CheckIdExist((*attribute)) || 
		   !erModel->CheckIsAttribute((*attribute)) ||
		   !erModel->CheckIsAttributeBelongToEntity(entity, (*attribute))
		   )
		{
			textUI->DisplayInvalidAttribute(entity, (*attribute));
			return false;
		}
	}

	return true;
}

/*功能區*/
void TextUIController::ProcessAddNode(string type, string name)
{
	presentation->AddNode(type, name);
}

void TextUIController::ProcessConnectNodes(string firstId, string secondId)
{
	int message;
	message = erModel->CanConneciont(firstId, secondId);

	if(message == ConnectMessage::CAN_CONNECT)
	{
		presentation->ConnectComponents(firstId, secondId);
		textUI->DisplayConnectSuccessMessage(firstId, secondId);
	}
	else if(message == ConnectMessage::IS_CARDINALITY)
	{
		string input;
		textUI->DisplayCardinalityMenu();
		input = textUI->InputString(Message::CARDINALITY);
		presentation->ConnectComponents(firstId, secondId, ConvertStringToCardinalityFormat(input));
		textUI->DisplayConnectSuccessMessage(firstId, secondId);
		textUI->DisplayCardinalitySuccessMessage(ConvertStringToCardinalityFormat(input));
	}
	else
	{
		textUI->ShowErrorConnectMessage(message, firstId, secondId);
	}
}

string TextUIController::ConvertStringToCardinalityFormat(string input)
{
	//將input轉成對應的cardinality
	if(input.compare(InputNumber::ZERO) == 0)
	{
		return Cardinality::CARDINALITY_ONE;
	}
	else
	{
		return Cardinality::CARDINALITY_MANY;
	}
}

void TextUIController::ProcessSetPrimaryKey(string input)
{
	vector<string> attributes;
	attributes = split(input);

	presentation->SetAttributeIsPrimary(attributes);
}

bool TextUIController::ProcessSaveFile(string input)
{
	return presentation->SaveFile(input);
}

bool TextUIController::ProcessLoadFile(string path)
{
	return presentation->LoadFile(path);
}

vector<string> TextUIController::split(string idList)
{
	const string pattern = ",";
	string::size_type pos;
	vector<string> result;
	string finalString;

	//檢查最後一個字是不是,;
	finalString.assign(&idList[idList.size() - 1]);

	//如果不是,，就加上,以便切割
	if( finalString != pattern)
	{
		idList += pattern;
	}

	for(unsigned int index = 0; index < idList.size(); index++)
	{
		pos = idList.find(pattern, index);

		if(pos < idList.size())
		{
			string str = idList.substr(index, pos - index);
			index = pos + pattern.size() - 1;
			result.push_back(str);
		}
	}

	return result;
}

bool TextUIController::Undo()
{
	return presentation->Undo();
}

bool TextUIController::Redo()
{
	return presentation->Redo();
}

void  TextUIController::CallFunctionMenu(string menuCommand)
{
	DisplayLoadFile(menuCommand);
}

void TextUIController::DisplayLoadFile(string menuCommand)
{
	if(menuCommand.compare(Menu::LOAD_FILE) == 0)
	{
		textUI->DisplayLoadFileMenu();
	}
	else
	{
		DisplaySaveFile(menuCommand);
	}
}

void TextUIController::DisplaySaveFile(string menuCommand)
{
	if (menuCommand.compare(Menu::SAVE_FILE) == 0)
	{
		textUI->DisplaySaveFileMenu();
	}
	else
	{
		DisplayAddNode(menuCommand);
	}
}

void TextUIController::DisplayAddNode(string menuCommand)
{
	if(menuCommand.compare(Menu::ADD_A_NODE) == 0)
	{
		textUI->DisplayAddNodeMenu();
	}
	else
	{
		DisplayConnectNodes(menuCommand);
	}
}

void TextUIController::DisplayConnectNodes(string menuCommand)
{
	if(menuCommand.compare(Menu::CONNECT_TO_NODES) == 0)
	{
		textUI->DisplayConnectNodeMenu();
	}
	else
	{
		DisplayDiagram(menuCommand);
	}
}

void TextUIController::DisplayDiagram(string menuCommand)
{
	if(menuCommand.compare(Menu::DISPLAY_DIAGRAM) == 0)
	{
		textUI->DisplayDiagram();
	}
	else
	{
		DisplaySetPrimaryKey(menuCommand);
	}
}

void TextUIController::DisplaySetPrimaryKey(string menuCommand)
{
	if(menuCommand.compare(Menu::SET_PRIMARY_KEY) == 0)
	{
		textUI->DisplayPrimaryKeyMenu();
	}
	else
	{
		DisplayTable(menuCommand);
	}
}

void TextUIController::DisplayTable(string menuCommand)
{
	if(menuCommand.compare(Menu::DISPLAY_TABLE) == 0)
	{
	}
	else
	{
		DisplayDeleteComponent(menuCommand);
	}
}

void TextUIController::DisplayDeleteComponent(string menuCommand)
{
	if(menuCommand.compare(Menu::DELETE_COMPONENT) == 0)
	{
		textUI->DisplayDeleteMenu();
	}
	else
	{
		DisplayUndo(menuCommand);
	}
}

void TextUIController::DisplayUndo(string menuCommand)
{
	if(menuCommand.compare(Menu::UNDO) == 0)
	{
		textUI->DisplayUndo();
	}
	else
	{
		DisplayRedo(menuCommand);
	}
}

void TextUIController::DisplayRedo(string menuCommand)
{
	if(menuCommand.compare(Menu::REDO) == 0)
	{
		textUI->DisplayRedo();
	}
	else
	{
		DisplayExit(menuCommand);
	}
}

void TextUIController::DisplayExit(string menuCommand)
{
	if(menuCommand.compare(Menu::EXIT) == 0)
	{
		textUI->DisplayExit();
		system("pause");
		exit(0);
	}
}

