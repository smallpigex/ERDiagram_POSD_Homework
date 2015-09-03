#pragma once
#include <iostream>

using namespace std;

namespace Menu
{
	const string MAIN_MENU = "0";
	const string LOAD_FILE = "1";
	const string SAVE_FILE = "2";
	const string ADD_A_NODE = "3";
	const string CONNECT_TO_NODES = "4";
	const string DISPLAY_DIAGRAM = "5";
	const string SET_PRIMARY_KEY = "6";
	const string DISPLAY_TABLE = "7";
	const string DELETE_COMPONENT = "8";
	const string UNDO = "9";
	const string REDO = "10";
	const string EXIT = "11";
}

namespace ComponetType
{
	const string ATTRIBUTE = "A";
	const string RELATIONSHIP = "R";
	const string ENTITY = "E";
	const string CONNECTION = "C";
	const string NULL_COMPONENT = "Null";
}

namespace Message
{
	const string MENU = "Menu";
	const string LOAD_FILE = "Load file";
	const string SAVE_FILE = "Save file";
	const string NODE_TYPE = "Type";
	const string NODE_NAME = "Name";
	const string NODE_ID = "Id";
	const string CARDINALITY = "Cardinality";
	const string CHECK_ENTITY = "Is entity";
	const string SET_PRIMARY_KEY = "Set primary key";
	const string DELETE_COMPONENT = "Delete component";
	const string UNDO = "9";
	const string REDO = "10";
	const string EXIT = "11";
}

namespace ErrorMessage
{
	const string NOT_MENU = "Not menu";
	const string NOT_TYPE = "Not type";
	const string NOT_ID = "Not id";
	const string NOT_CARDINALITY = "Not cardinality";
	const string NOT_ENTITY = "Not entity";
}

namespace ComponetTypeName
{
	const string ATTRIBUTE = "Attribute";
	const string RELATIONSHIP = "Relationship";
	const string ENTITY = "Entity";
}

namespace DataTitle
{
	const string COMPONENT_DATA = "Component Data";
	const string CONNECTION_DATA = "Connection Data";
	const string TABLE = "Table";
}

namespace Cardinality
{
	const string CARDINALITY_ONE = "1";
	const string CARDINALITY_MANY = "N";
}

namespace InputNumber
{
	const string ZERO = "0";
	const string ONE = "1";
}

namespace XmlTag
{
	const string xmlTitle = "<?xml version=\"1.0\"?>";
	const string startTagERDiagram = "<ERDiagram>";
	const string endTagERDiagram = "</ERDiagram>";
	const string startTagAttribute = "<Attribute>";
	const string endTagAttribute = "</Attribute>";
	const string startTagEntity = "<Entity>";
	const string endTagEntity = "</Entity>";
	const string startTagRelationship = "<Relationship>";
	const string endTagRelationship = "</Relationship>";
	const string startTagConnector = "<Connector>";
	const string endTagConnector = "</Connector>";
	const string startTagId = "<Id>";
	const string endTagId = "</Id>";
	const string startTagText = "<Text>";
	const string endTagText = "</Text>";
	const string startTagPointX = "<PointX>";
	const string endTagPointX = "</PointX>";
	const string startTagPointY = "<PointY>";
	const string endTagPointY = "</PointY>";
	const string startTagSource = "<Source>";
	const string endTagSource = "</Source>";
	const string startTagTarget = "<Target>";
	const string endTagTarget = "</Target>";
	const string startTagPrimaryKey = "<PrimaryKey>";
	const string endTagPrimaryKey = "</PrimaryKey>";
}

namespace Pattern
{
	const string comma = ",";
}