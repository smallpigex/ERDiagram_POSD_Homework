#include "TextUI.h"


TextUI::TextUI(TextUIController *controller, ERModel *erModel)
{
	this->controller = controller;
	this->erModel = erModel;
	//erModel->RegisterObserver(this);
}


TextUI::~TextUI(void)
{
}

void TextUI::DisplayMenu()
{
	string command;
	cout << "1. Load ER diagram file" << endl;
	cout << "2. Save ER diagram file" << endl;
	cout << "3. Add a node" << endl;
	cout << "4. Connect two nodes" << endl;
	cout << "5. Display the current diagram" << endl;
	cout << "6. Set a primary key" << endl;
	cout << "7. Display the table" << endl;
	cout << "8. Delete a component" << endl;
	cout << "9. Undo" << endl;
	cout << "10. Redo" << endl;
	cout << "11. Exit" << endl;
	command = InputString(Message::MENU);
	controller->ProcessMainMenu(command);
}

/*message 用來判斷是哪個介面使用此function*/
string  TextUI::InputString(string message)
{
	string input;
	int inputCondition = false;
	
	do 
	{
		cout <<">";
		getline(cin, input);

		if(controller->ProcessInput(input, message))
		{
			inputCondition = true;
		}
	}
	while(!inputCondition);

	return input;
}

void TextUI::InputAttributeId(string &input)
{
	cout << ">";
	getline(cin, input);
	controller->ProcessSetPrimaryKey(input);
}

void TextUI::DisplayLoadFileMenu()
{
	string input;
	cout << "Please input a file path:" << endl;
	input = InputString(Message::LOAD_FILE);

	if(controller->ProcessLoadFile(input))
	{

		cout << "Load Success" << endl;
	}
	else
	{
		cout << "Fail not found" << endl;
	}
}

void TextUI::DisplaySaveFileMenu()
{
	string input;
	cout << "> Please input the file name:" << endl;
	input = InputString(Message::SAVE_FILE);

	if(controller->ProcessSaveFile(input))
	{
		cout << "Save Success" << endl;
	}
	else
	{
		cout << "Save Fail" << endl;
	}
	
}

void TextUI::DisplayAddNodeMenu()
{
	string type, name;
	cout << "What kind of node do you want to add?" << endl;
	DisplayAddNodeTypeMessage();
	type = InputString(Message::NODE_TYPE);
	DisplayAddNodeNameMessage();
	name = InputString(Message::NODE_NAME);
	controller->ProcessAddNode(type, name);
	DisplayAddNodeSuccessMessage();
	DisplayAllNodes();
}

void TextUI::DisplayAddNodeTypeMessage()
{
	cout << "[A]Attribute [E]Entity [R]Relation" << endl;
}

void TextUI::DisplayAddNodeNameMessage()
{
	cout << "Enter the name of this node:" << endl;
}

void TextUI::DisplayConnectNodeMenu()
{
	string firstId, secondId;
	cout << "Please enter the first node ID" << endl;
	firstId = InputString(Message::NODE_ID);
	cout << "Please enter the second node ID" << endl;
	secondId = InputString(Message::NODE_ID);
	controller->ProcessConnectNodes(firstId, secondId);
}

void TextUI::DisplayCardinalityMenu()
{
	cout << "Enter the type of the cardinality:" << endl;
	cout << "[0]1 [1]N" << endl;
}

void TextUI::DisplayDiagram()
{
	DisplayAllComponent();
	DisplayAllConnection();
}

void TextUI::DisplayPrimaryKeyMenu()
{
	DisplayEntityNodes();	
	string entityId;
	cout << "Enter the ID of the entity:" << endl;
	entityId = InputString(Message::CHECK_ENTITY);
	DisplaySetPrimaryKeyMenu(entityId);
}

void TextUI::DisplaySetPrimaryKeyMenu(string entityId)
{
	string input;
	DisplayAttribtuteOfEntity(entityId);
	cout << "Enter the IDs of the attributes (use a comma to separate two attributes):" << endl;
	
	do
	{
		cout << ">";
		getline(cin, input);
	}
	while(!controller->CheckIsAttributeBelongToEntity(entityId, input));

	controller->ProcessSetPrimaryKey(input);
	cout << "The entity '" << entityId << "' has the primary key (" << input << ")." << endl;
}

void TextUI::DisplayTable()
{
}

void TextUI::DisplayDeleteMenu()
{
	string input;
	cout << "Please enter the component ID" << endl;
	input = InputString(Message::DELETE_COMPONENT);
	controller->ProcessDeleteComponent(input);
}

void TextUI::DisplayUndo()
{
	if(controller->Undo())
	{
		cout << "Undo succeed!" << endl;
		DisplayAllComponent();
		DisplayAllConnection();
	}
	else
	{
		cout << "Cannot undo." << endl;
	}
}

void TextUI::DisplayRedo()
{
	if(controller->Redo())
	{
		cout << "Redo succeed!" << endl;
		DisplayAllNodes();
		DisplayAllComponent();
	}
	else
	{
		cout << "Cannot Redo." << endl;
	}
}

void TextUI::DisplayExit()
{
	cout << "Goodbye" << endl;
}

/*Success Message*/
void TextUI::DisplayAddNodeSuccessMessage()
{
	cout << "A node [" << ConvertTypeToTypeName(erModel->GetCurrentCreateComponentType()) 
		 << "] has been added. ID: " << erModel->GetCurrentCreateComponentId() 
		 << ", Name: " << erModel->GetCurrentCreateComponentName() << "\"" << endl;
}

void TextUI::DisplayConnectSuccessMessage(string firstId, string secondId)
{
	cout << "The node '" << firstId << "' has been connected to the node '" << secondId << "'." << endl;
}

void TextUI::DisplayCardinalitySuccessMessage(string cardinality)
{
	cout << "Its cardinality of the relationship is '" << cardinality << "'." << endl;
}

void TextUI::DisplayDeleteSuccessMessage(string id)
{
	cout << "The component \"" << id << "\" has been deleted." << endl;
}

/*//Error Message*/
void TextUI::ShowErrorMessage(string message, string id)
{
	if(message.compare(ErrorMessage::NOT_MENU) == 0)
	{
		DisplayInvalidCommand();
	}
	else if(message.compare(ErrorMessage::NOT_TYPE) == 0)
	{
		DisplayInvalidType();
		DisplayAddNodeTypeMessage();
	}
	else if(message.compare(ErrorMessage::NOT_ID) == 0)
	{
		DisplayInvalidId();
	}
	else if(message.compare(ErrorMessage::NOT_CARDINALITY) == 0)
	{
		DisplayInvalidCardinality();
	}
	else if(message.compare(ErrorMessage::NOT_ENTITY) == 0)
	{
		DisplayInvalidEntity(id);
	}
}

void TextUI::DisplayInvalidCommand()
{
	cout << "You entered an invalid command. Please enter a valid one again." << endl;
}


void TextUI::DisplayInvalidType()
{
	cout << "You entered an invalid node. Please enter a valid one again." << endl;
}

void TextUI::DisplayInvalidId()
{
	cout << "The node ID you entered does not exist. Please enter a valid one again." << endl;
}

void TextUI::DisplayInvalidCardinality()
{
	cout << "You entered an invalid cardinality. Please enter a valid one again." << endl;
}

void TextUI::DisplayInvalidEntity(string id)
{
	cout << "The node '" << id << "' is not an entity. Please enter a valid one again." << endl;
}

void TextUI::DisplayInvalidAttribute(string entityId, string attributeId)
{
	cout << "The node '" << attributeId << "' does not belong to Entity '" << entityId << "'. Please enter a valid one again." << endl;
}

void TextUI::ShowErrorConnectMessage(int message, string firstId, string secondId)
{
	if(message == ConnectMessage::ITSELF)
	{
		cout << "The node '" << firstId << "' cannot be connected to itself." << endl;
	}
	else if(message == ConnectMessage::SAME_TYPE || message == ConnectMessage::CAN_NOT_CONNECT)
	{
		cout << "The node '" << secondId << "' cannot be connected by the node '" << firstId << "'." << endl;
	}
	else if(message == ConnectMessage::HAS_BEEN_CONNECT_OTHER_NODE)
	{
		cout << "The node '" << firstId << "' has already been connected to other component" << endl;
	}
	else
	{
		cout << "The node '" << secondId << "' has already been connected to component '" << firstId << "'." << endl;
	}
}

/*update*/
void TextUI::UpdateComponents(int id, string type, string name)
{
	//DisplayAddNodeSuccessMessage(id, type, name);
	//DisplayAllNodes();
}

void TextUI::UpdateConnection(int firstId, int secondId, string cardinality)
{
	/*
	DisplayConnectSuccessMessage(firstId, secondId);

	if(cardinality.compare("") != 0)
	{
		DisplayCardinalitySuccessMessage(cardinality);
	}

	DisplayAllConnection();*/
}

void TextUI::DisplayAllNodes()
{
	vector<int> id;
	vector<string> type;
	vector<string> name;
	cout << "Components:" << endl;
	DisplayGraphTitle(DataTitle::COMPONENT_DATA);
	erModel->GetNodesData(id, type, name);

	for(vector<int>::size_type index = 0; index < id.size(); index++)
	{
		if(id[index] != nullComponentId && type[index] != ComponetType::CONNECTION)
		{
			cout << setw(3) << type[index] << setw(6) << "|" << setw(2) << id[index]
			<< setw(8) << "|" << setw(4) << name[index] << endl;
		}
	}

	ShowGraphBottom();
}

void TextUI::DisplayAllComponent()
{
	vector<int> id;
	vector<string> type;
	vector<string> name;
	cout << "Components:" << endl;
	DisplayGraphTitle(DataTitle::COMPONENT_DATA);
	erModel->GetNodesData(id, type, name);

	for(vector<int>::size_type index = 0; index < id.size(); index++)
	{
		if(id[index] != nullComponentId)
		{
			cout << setw(3) << type[index] << setw(6) << "|" << setw(2) << id[index]
			<< setw(8) << "|" << setw(4) << name[index] << endl;
		}
	}

	ShowGraphBottom();
}

void TextUI::DisplayAllConnection()
{
	vector<ConnectionData> connceciontData;
	cout << "Connection:" << endl;
	DisplayGraphTitle(DataTitle::CONNECTION_DATA);
	connceciontData = erModel->GetConnectionsData();

	for(vector<int>::size_type index = 0; index < connceciontData.size(); index++)
	{
		if(connceciontData[index].GetId() != nullComponentId)
		{
			cout << setw(3) << connceciontData[index].GetId() << setw(6) << "|" << setw(2) << connceciontData[index].GetConnectComponetId(0)
				 << setw(8) << "|" << setw(4) << connceciontData[index].GetConnectComponetId(1) << endl;
		}
	}

	ShowGraphBottom();
}

void TextUI::DisplayEntityNodes()
{
	vector<int> id;
	vector<string> type;
	vector<string> name;
	cout << "Entities:" << endl;
	DisplayGraphTitle(DataTitle::COMPONENT_DATA);
	erModel->GetNodesData(id, type, name);

	for(vector<int>::size_type index = 0; index < id.size(); index++)
	{
		if(type[index].compare(ComponetType::ENTITY) == 0)
		{
			cout << setw(3) << type[index] << setw(6) << "|" << setw(2) << id[index]
			<< setw(8) << "|" << setw(4) << name[index] << endl;
		}
	}

	ShowGraphBottom();
}

void TextUI::DisplayAttribtuteOfEntity(string entityId)
{
	vector<ComponentData> attributesData;
	cout << "Attributes of the entity '" << entityId << "'" << endl;
	erModel->StoreAttributeToComponentData(entityId, attributesData);
	DisplayGraphTitle(DataTitle::COMPONENT_DATA);

	for(vector<int>::size_type index = 0; index < attributesData.size(); index++)
	{
		cout << setw(3) << attributesData[index].GetType() << setw(6) << "|" << setw(2) << attributesData[index].GetId()
			 << setw(8) << "|" << setw(4) << attributesData[index].GetName() << endl;
	}

	ShowGraphBottom();
}

string TextUI::ConvertTypeToTypeName(string type)
{
	if(type.compare(ComponetType::ATTRIBUTE) == 0)
	{
		return ComponetTypeName::ATTRIBUTE;
	}
	else if(type.compare(ComponetType::RELATIONSHIP) == 0)
	{
		return ComponetTypeName::RELATIONSHIP;
	}
	else
	{
		return ComponetTypeName::ENTITY;
	}
}

void TextUI::DisplayGraphTitle(string message)
{
	cout << "----------------------------------------------" << endl;
	ShowTitleData(message);
	cout << "--------+---------+---------------------------" << endl;
}

void TextUI::ShowTitleData(string message)
{
	if(message.compare(DataTitle::COMPONENT_DATA) == 0)
	{
		cout << "Type" << setw(5) << "|" << setw(3) << "ID" << setw(7) << "|" << setw(5) <<"Name" << endl;
	}
	else if(message.compare(DataTitle::CONNECTION_DATA) == 0)
	{
		cout << "Connection"<< setw(5) << "|" << setw(3) << "Node" << setw(7) <<"|"<< setw(5) << "Node" << endl;
	}
	else if(message.compare(DataTitle::TABLE) == 0)
	{
		cout << "Entity \t|\tAttribute" << endl;
	}
}

void TextUI::ShowGraphBottom()
{
	cout << "---------------------------------------------" << endl << endl;
}

