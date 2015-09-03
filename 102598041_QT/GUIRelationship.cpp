#include "GUIRelationship.h"


GUIRelationship::GUIRelationship(Components *component)
{
	pointX = 50;
	pointY = 50;
	this->component = component;
	QFontMetrics fontMetrics(QApplication::font());
	width = fontMetrics.width(QString::fromStdString(component->GetName()));
	QVector<QPointF> polygon;
    polygon.push_back(QPointF(pointX + width, 0));
    polygon.push_back(QPointF(0, pointY + width));
    polygon.push_back(QPointF(-pointX - width, 0));
    polygon.push_back(QPointF(0, -pointY - width));
	polygon.push_back(QPointF(pointX + width, 0));
    painterPath.addPolygon(QPolygonF(polygon));
	type = component->GetType();
	id = component->GetId();
	name = component->GetName();
}

GUIRelationship::GUIRelationship()
{
	type = "";
	id = tmpComponentId;
	name = "";
	pointX = 50;
	pointY = 50;
	QVector<QPointF> polygon;
	polygon.push_back(QPointF(pointX, 0));
	polygon.push_back(QPointF(0, pointY));
	polygon.push_back(QPointF(-pointX, 0));
	polygon.push_back(QPointF(0, -pointY));
	polygon.push_back(QPointF(pointX, 0));
	painterPath.addPolygon(QPolygonF(polygon));
}

GUIRelationship::~GUIRelationship(void)
{
	component = nullptr;
}

int GUIRelationship::GetComponentId()
{
	return id;
}

void GUIRelationship::DrawShap(QPainter *painter)
{
	painter->drawPath(painterPath);
	QFont font(fontType, fontSize);
	painter->setFont(font);
	painter->drawText(boundingRect(), Qt::AlignCenter, QString::fromStdString(name));
}

string GUIRelationship::GetType()
{
	return type;
}
/*
QPainterPath GUIRelationship::shape() const 
{
	return painterPath;
}*/

void GUIRelationship::SetPointX(int pointX)
{
	component->SetPointX(pointX);
}

void GUIRelationship::SetPointY(int pointY)
{
	component->SetPointY(pointY);
}

string GUIRelationship::GetName()
{
	return component->GetName();
}

void GUIRelationship::RefreshName()
{
	name = component->GetName();
}

void GUIRelationship::ResetPoint()
{
	pos().setX(component->GetPointX());
	pos().setY(component->GetPointY());
}