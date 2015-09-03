#pragma once
#include "../102598041_new/ComponentData.h"
#include "../102598041_new/MessageOfConstString.h"
//#include "../102598041_new/Connection.h"
#include "GUIComponentFactory.h"
#include "GUIPreviewComponentFactory.h"
#include "GUIPresentation.h"
#include <QGraphicsItem>
#include <iostream>
#include <QGraphicsScene>
#include <vector>
#include "GUIConnection.h"
#include "GUIComponent.h"
#include "GUIObserver.h"
#include <Qinputdialog>
#include "../102598041_QT/ComponentPoint.h"
#include "../102598041_new/MessageOfConstString.h"

using namespace std;

class GUIComponentManager : public GUIObserver
{
private:
	QVector<GUIComponent *> guiComponents;
	QGraphicsScene *scene;
	GUIPresentation *guiPresentation;
	GUIComponentFactory guiComponentFactory;
	GUIComponent *previewComponent;
	qreal x;
	qreal y;
	
public:
	GUIComponentManager(QGraphicsScene *, GUIPresentation *);
	~GUIComponentManager(void);
	void SetConnectionPosition(GUIComponent *);
	void SetConnection();
	void SetGUINodePosition();
	void SetGUIComponents();
	void DrawERDiagram();
	void ClearGUIComponents();
	void UpdateNode(int);
	void StoreGUIComponent(GUIComponent *, int);
	void DrawNode(GUIComponent *);
	void SetComponentMoveable(bool);
	void UpdateComponentMoveable(bool);
	void UpdateConnectionPos();
	void UpdateConnection(int);
	void DisplayPreview(string);
	void UpdatePreviewPos();
	void DesroyPreview();
	void DisplayEditText();
	void DeleteGUIComponent();
	void SetComponentPoint();
	void RecoveryGUIComponent();
	void UpdateGUIComponentPos();
	void RemoveItem();
	void RemoveGUIComponent();
	bool IsGUIComponentItemExist(int);
	bool IsGUIComponentExist(int);
	bool CheckPoint(QPoint);
	void DrawPrimaryKey();
	void UpdatePrimaryKey();
	int GetGUIComponentSize();
	int GetComponentId(int);
	string GetComponentType(int);
	string GetComponentName(int);
	void InsertGUIComponent(GUIComponent *, int);
	void RefreshComponentsName();
	void UpdateComponentsName();
	int GetCurrentComponentIndex(int);
	void ResetComponentsPoint();
	void StoreComponentPoint(vector<ComponentPoint> &);
	void StoreOldComponentsPoint();
	void StoreNewComponentsPoint();
	void UpdateComponent(int);
	void ClearSelected();
	void ClearGUIComponent();
	void RemoveSceneItem();
	void ResetGUIComponents();
	void RedrawERDiagram();
	//void DrawERDiagram();
};

