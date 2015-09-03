#pragma once
#include "GUIComponent.h"
#include <QPointF>
#include "../102598041_new/Connection.h"
#include <QMessageBox>

class GUIConnection :public GUIComponent
{
private:
	
	QPainterPath connectionPainterPath;
	QLineF line;
	string type;
	string name;
	int id;

public:
	GUIConnection(Components *);
	GUIConnection();
	~GUIConnection(void);
	int GetLeftNodeId();
	int GetRightNodeId();
	void SetLeftNodePosition(QPointF);
	void SetRightNodePosition(QPointF);
	void DrawShap(QPainter *);
	QPointF leftNodePosition;
	QPointF rightNodePosition;
	void UpdateShape();
	string GetType();
	int GetComponentId();
	void SetPointX(int);
	void SetPointY(int);
	string GetName();
	void RefreshName();
	void ResetPoint();
};

