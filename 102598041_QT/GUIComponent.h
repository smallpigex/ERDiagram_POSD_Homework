#pragma once
#include <QGraphicsScene>
#include <Qpainter>
#include <QGraphicsItem>
#include <iostream>
#include <Qmessagebox>
#include <QFont>
#include <QApplication>
#include <QPoint>
#include "../102598041_new/Components.h"
#include "../102598041_new//MessageOfConstInteger.h"

using namespace std;

class GUIComponent : public QGraphicsItem
{
public:
	GUIComponent(void);
	virtual ~GUIComponent(void);
	int GetId();
	virtual int GetComponentId() = 0;
	bool mousePressed;
	//string GetName();
	virtual string GetType() = 0;
	QPoint GetPosition();
	virtual QPainterPath shape() const;
	virtual QRectF boundingRect() const;
	void mouseReleaseEvent(QGraphicsSceneMouseEvent *);
	//void mousePressEvent(QGraphicsSceneMouseEvent *);
	void paint(QPainter *,const QStyleOptionGraphicsItem *,QWidget *);
	void SetMoveable(bool);
	void UpdatePoint();
	string GetComponentName();
	void RefreshComponetName();
	void DoResetPoint();
	virtual void RefreshName() = 0;
	virtual string GetName() = 0;
	virtual void DrawShap(QPainter *) = 0;
	virtual void DrawSelectDiagram(QPainter *);
	virtual void SetPointX(int) = 0;
	virtual void SetPointY(int) = 0;
	virtual void ResetPoint() = 0;

protected:
	QPainterPath painterPath;
	Components *component;
	int width;
	int height;
	int fontSize;
	QString fontType;
};

