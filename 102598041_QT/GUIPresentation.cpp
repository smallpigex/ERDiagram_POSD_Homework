#include "GUIPresentation.h"
#include <QDebug>

GUIPresentation::GUIPresentation(Presentation *presentation)
{
	this->presentation = presentation;
	attributesRow = 0;
	entitesRow = 400;
	relationshipsRow = 800;
	attributesColumn = 0;
	entitesColumn = 0;
	relationshipsColumn = 0;
	height = 200;
	addNodeState = new AddNodeState(this);
	connectState = new ConnectState(this);
	pointState  = new PointState(this);
	//deleteState = new DeleteComponentState(this);
	setPrimaryKeyState = new PrimaryKeyState(this);
	state = pointState;
	checked = true;
	isMove = true;
	stateMessage = StringState::POINT_NODE_STATE;
	//delectActionDisable = false;
}


GUIPresentation::~GUIPresentation(void)
{
	delete addNodeState;
	delete connectState;
	delete pointState;
	delete state;
}

void GUIPresentation::LoadFile(string filePath)
{
	presentation->LoadFile(filePath);
	
}

int GUIPresentation::GetComponentsSize()
{
	return presentation->GetComponentsSize();
}

Components *GUIPresentation::GetComponent(int index)
{
	return presentation->GetComponent(index);
}

QPoint GUIPresentation::GetPosition(string type)
{
	if(type.compare(ComponetType::ATTRIBUTE) == 0)
	{
		QPoint point(attributesRow, attributesColumn * height);
		attributesColumn++;
		return point;
	}
	else if(type.compare(ComponetType::ENTITY) == 0)
	{
		QPoint point(entitesRow, entitesColumn * height);
		entitesColumn++;
		return point;
	}
	else
	{
		QPoint point(relationshipsRow, relationshipsColumn * height);
		relationshipsColumn++;
		return point;
	}

}

void GUIPresentation::RestPosition()
{
	attributesColumn = 0;
	entitesColumn = 0;
	relationshipsColumn = 0;
}

void GUIPresentation::AddNode(string name)
{
	presentation->AddNode(nodeType, name);
	//NotifyObserverDrawGUIComponent();
	NotifyObserverPointActionUpdate();
	mainWindowObserver->UpdateTable();
}

void GUIPresentation::ConnectNode()
{
	//qDebug() << presentation->CanConnect(firstId, secondId);
	if(VarifyId(firstId) && VarifyId(secondId))
	{
		if(presentation->CanConnect(firstId, secondId) == ConnectMessage::CAN_CONNECT || 
		   presentation->CanConnect(firstId, secondId) == ConnectMessage::IS_CARDINALITY)
		{
			presentation->ConnectComponents(firstId, secondId);
			NotifyObserverDrawGUIConnection();
		}
		else
		{
			NotifyObserverConnectError();
		}
	}
}

void GUIPresentation::PointNode()
{
	
}

void GUIPresentation::SetState(State *state)
{
	this->state = state;
}

void GUIPresentation::SetNodeType(string type)
{
	nodeType = type;
}

void GUIPresentation::ChangeState(string state)
{
	if(state.compare(StringState::ADD_NODE_STATE) == 0)
	{
		SetStateMessage(StringState::ADD_NODE_STATE);
		this->state = addNodeState;
	}
	else if(state.compare(StringState::CONNECT_NODE_STATE) == 0)
	{
		SetStateMessage(StringState::CONNECT_NODE_STATE);
		this->state = connectState;
	}
	else if(state.compare(StringState::POINT_NODE_STATE) == 0)
	{
		SetStateMessage(StringState::POINT_NODE_STATE);
		this->state = pointState;
	}
	else
	{
		SetStateMessage(StringState::PRIMARY_KEY_STATE);
		this->state = setPrimaryKeyState;
	}
}

void GUIPresentation::MousePressEvent()
{
	state->MousePressEvent();
}

void GUIPresentation::MouseReleaseEvent()
{
	state->MouseReleaseEvent();
}

void GUIPresentation::MoseMoveEvent()
{
	state->MouseMoveEvent();
}

void GUIPresentation::SetMousePoint(QPointF point)
{
	mousePoint = point;
}

Components *GUIPresentation::GetNewComponent()
{
	return presentation->GetNewComponent();
}

QPointF GUIPresentation::GetMousePoint()
{
	return mousePoint;
}

void GUIPresentation::RegisterObserver(GUIObserver *observer)
{
	this->observer = observer;
}

void GUIPresentation::NotifyObserverDrawGUIComponent()
{

	observer->UpdateNode(GetNewComponent()->GetId());
}

State *GUIPresentation::GetPointState()
{
	return pointState;
}

void GUIPresentation::NotifyObserverPointActionUpdate()
{
	mainWindowObserver->UpdatePointActionState(checked);
}

void GUIPresentation::RegisterMainWindowObserver(MainWindowObserver *mainWindowObserver)
{
	this->mainWindowObserver = mainWindowObserver;
}

void GUIPresentation::NotifyObserverMoveable()
{
	observer->UpdateComponentMoveable(isMove);
}

void GUIPresentation::SetIsMove(bool isMove)
{
	this->isMove = isMove;
	NotifyObserverMoveable();
}

void GUIPresentation::SetStateMessage(string stateMessage)
{
	this->stateMessage = stateMessage;
}

string GUIPresentation::GetStateMessage()
{
	return stateMessage;
}

void GUIPresentation::NotifyObserverGUIConnectionUpdate()
{
	observer->UpdateConnectionPos();
}

void GUIPresentation::SetFirstId(int id)
{
	firstId = IntToString(id);
}

void GUIPresentation::SetSecondId(int id)
{
	secondId = IntToString(id);
}

void GUIPresentation::NotifyObserverDrawGUIConnection()
{
	//observer->UpdateConnection();
}

Components *GUIPresentation::GetNewConnection()
{
	return presentation->GetNewConnection();
}

bool GUIPresentation::VarifyId(string id)
{
	string errorId = "-1";
	if(id == errorId)
	{
		return false;
	}
	return true;
}

void GUIPresentation::NotifyObserverConnectError()
{
	mainWindowObserver->UpdateConnectErrorMessage();
}

void GUIPresentation::NotifyObserverUpdatePreviewPos()
{
	observer->UpdatePreviewPos();
}

void GUIPresentation::NotifyObserverDisplayEditText()
{
	observer->DisplayEditText();
}

void GUIPresentation::DeleteComponent(int deleteComponentId)
{
	if(VarifyId(IntToString(deleteComponentId)))
	{
		presentation->DeleteComponent(IntToString(deleteComponentId));
		NotifyObserverUpdateGUIComponent();
	}
}


string GUIPresentation::IntToString(int id)
{
	stringstream stringStream;
	stringStream << id;
	return stringStream.str();
}

void GUIPresentation::NotifyObserverUpdateGUIComponent()
{
	//observer->UpdateGUIComponent();
}

bool GUIPresentation::IsComponentExist(int id)
{
	return presentation->IsComponentExist(id);
}

void GUIPresentation::NotifyObserverUpdateGUIComponentPos()
{
	observer->UpdateGUIComponentPos();
}

bool GUIPresentation::Undo()
{
	return presentation->Undo();
}

bool GUIPresentation::Redo()
{
	return presentation->Redo();
}

void GUIPresentation::SetPrimaryKeyId(int id)
{
	primaryKeyId = id;
}

void GUIPresentation::SetPrimaryKey()
{
	if(primaryKeyId != -1 && presentation->GetComponent(primaryKeyId)->GetType().compare(ComponetType::ATTRIBUTE) == 0)
	{
		presentation->SetPrimaryKey(primaryKeyId);
	}
}

void GUIPresentation::SetComponentName(int id, string name)
{
	if(presentation->CanReName(id, name))
	{
		presentation->EditComponentName(id, name);
	}

	NotifyRefreshTable();
}

void GUIPresentation::NotifyRefreshTable()
{
	mainWindowObserver->RefreshTable();
}

void GUIPresentation::setDeleteActionDisabled()
{
	//this->delectActionDisable = disable;
	NotifyObserverDeleteActionUpdate();
}

void GUIPresentation::NotifyObserverDeleteActionUpdate()
{
	mainWindowObserver->UpdateDeleteActionDiable();
}

void GUIPresentation::SetOldComponentPoint(vector<ComponentPoint> oldComponentsPoint)
{
	this->oldComponentsPoint = oldComponentsPoint;
}

void GUIPresentation::SetNewComponentPoint(vector<ComponentPoint> newComponentsPoint)
{
	this->newComponentsPoint = newComponentsPoint;
}

void GUIPresentation::MoveComponents()
{
	if(oldComponentsPoint.size() != 0 && newComponentsPoint.size() != 0)
	{
		presentation->MoveComponent(oldComponentsPoint, newComponentsPoint);
	}
}

void GUIPresentation::NotifyObserverStoreOldComponentPoint()
{
	observer->StoreOldComponentsPoint();
}

void GUIPresentation::NotifyObserverStoreNewComponentPoint()
{
	observer->StoreNewComponentsPoint();
}

void GUIPresentation::NotifyObserverResetPoint()
{
}

void GUIPresentation::NotifyObserverResetComponent()
{
}