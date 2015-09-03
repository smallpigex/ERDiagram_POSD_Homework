#pragma once
#include <iostream>
#include <QString>
#include <QToolBar>

using namespace std;

namespace QTstring
{
	const QString TITLE = "Entity Relation Diagramming Tool";
	const QString FILE = "&File";
	const QString HELP = "&Help";
	const QString OPEN = "&Open";
	const QString EXIT = "&Exit";
	const QString QTOOLBAR = "QToolBar";
	const QString LOAD_DIALOG_TITLE = "Open ERD Files";
	const QString FILES_OF_TYPE = "ERD Files (*.erd)";
	const QString FILES_PATH = "C:\\";
	const QString SELECT = "Select";
	const QString CONNECT = "Connection";
	const QString ADD_ATTRIBUTE = "Attribute";
	const QString ADD_ENTITY = "Entity";
	const QString ADD_RELATIONSHIP = "Relationship";
	const QString DELETE_COMPONENT = "Delete component";
	const QString UNDO = "Undo";
	const QString REDO = "Redo";
	const QString PRIMARYKEY = "Primary key";
	const QString ADD = "Add";
	const QString INPUT_DIALOG_TITLE = "Enter text";
	const QString INPUT_DIALOG_CONTEXT = "Please enter the text";
	const QString SAVE_FILE = "Save";
	const QString SAVE_Xml_FILE = "Save as xml";
	const QString EDIT = "Edit";
	const QString CUT = "Cut";
	const QString COPY = "Copy";
	const QString PASTE = "Paste";
	const QString ABOUT = "About";
}

namespace StringState
{
	const string ADD_NODE_STATE = "Add state";
	const string CONNECT_NODE_STATE = "Connect state";
	const string POINT_NODE_STATE = "Point state";
	const string INPUT_DIALOG = "Input dialog";
	const string DELETE_STATE = "Delete state";
	const string PRIMARY_KEY_STATE = "Set primary key state";
}

namespace AboutContext
{
	const QString TOOL_NAME = "About Relation Diagraming Tool";
	const QString VERSION = "1.0";
	const QString AUTHOR = "Author:102598041@ntut";
}
