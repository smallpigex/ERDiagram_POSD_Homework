#pragma once
#include "../102598041_new/Presentation.h"
#include "../102598041_new/Components.h"
#include "../102598041_new/MessageOfConstString.h"
#include <QPoint>
#include "State.h"
#include "AddNodeState.h"
#include "ConnectState.h"
#include "PointState.h"
#include "PrimaryKeyState.h"
#include <iostream>
#include <string>
#include "QTConstString.h"
#include "GUIPresentationSubject.h"
#include "MainWindowSubject.h"
#include <sstream>
#include <vector>
#include "../102598041_new/MessageOfConstInteger.h"
#include "../102598041_QT/ComponentPoint.h"

using namespace std;

class GUIPresentation : public GUIPresentationSubject, public MainWindowSubject
{
private:
	GUIObserver *observer;
	MainWindowObserver *mainWindowObserver;
	Presentation *presentation;
	State *state;
	State *addNodeState;
	State *connectState;
	State *pointState;
	State *deleteState;
	State *setPrimaryKeyState;
	string nodeType;
	int height;
	int attributesRow;
	int attributesColumn;
	int entitesRow;
	int entitesColumn;
	int relationshipsRow;
	int relationshipsColumn;
	QPointF mousePoint;
	bool checked;
	bool isMove;
	string stateMessage;
	string firstId;
	string secondId;
	//string deleteComponentId;
	int primaryKeyId;
	vector<ComponentPoint> oldComponentsPoint;
	vector<ComponentPoint> newComponentsPoint;
	//bool delectActionDisable;

public:
	GUIPresentation(Presentation *);
	~GUIPresentation(void);
	void RestPosition();
	void LoadFile(string);
	int GetComponentsSize();
	Components *GetNewComponent();
	Components *GetNewConnection();
	Components *GetComponent(int);
	QPoint GetPosition(string);
	void AddNode(string);
	void ConnectNode();
	void PointNode();
	void SetState(State *);
	void SetNodeType(string);
	void ChangeState(string);
	void MousePressEvent();
	void MouseReleaseEvent();
	void MoseMoveEvent();
	void SetMousePoint(QPointF);
	QPointF GetMousePoint();
	void RegisterObserver(GUIObserver *);
	void NotifyObserverDrawGUIComponent();
	void NotifyObserverMoveable();
	void RegisterMainWindowObserver(MainWindowObserver *);
	void NotifyObserverPointActionUpdate();
	void NotifyObserverDrawGUIConnection();
	void NotifyObserverUpdatePreviewPos();
	void NotifyObserverDisplayEditText();
	void NotifyObserverUpdateGUIComponent();
	//void NotifyObserverCutActionUpdate();
	State *GetPointState();
	void SetIsMove(bool );
	void SetStateMessage(string);
	string GetStateMessage();
	void NotifyObserverGUIConnectionUpdate();
	void NotifyObserverConnectError();
	void SetFirstId(int);
	void SetSecondId(int);
	bool VarifyId(string);
	void DeleteComponent(int);
	string IntToString(int);
	bool IsComponentExist(int);
	void NotifyObserverUpdateGUIComponentPos();
	bool Undo();
	bool Redo();
	void SetPrimaryKeyId(int);
	void SetPrimaryKey();
	void SetComponentName(int, string);
	void NotifyRefreshTable();
	void setDeleteActionDisabled();
	void NotifyObserverDeleteActionUpdate();
	void SetOldComponentPoint(vector<ComponentPoint>);
	void SetNewComponentPoint(vector<ComponentPoint>);
	void MoveComponents();
	void NotifyObserverStoreOldComponentPoint();
	void NotifyObserverStoreNewComponentPoint();
	void NotifyObserverResetPoint();
	void NotifyObserverResetComponent();
};

