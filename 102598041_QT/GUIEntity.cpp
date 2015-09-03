#include "GUIEntity.h"


GUIEntity::GUIEntity(Components *component)
{
	rectWidth = 100;
	rectHeight = 100;
	this->component = component;
	id = component->GetId();
	type = component->GetType();
	name = component->GetName();
	QFontMetrics fontMetrics(QApplication::font());
	width = fontMetrics.width(QString::fromStdString(component->GetName()));
	painterPath.addRect(0, 0, rectWidth + width, rectHeight);
}

GUIEntity::GUIEntity()
{
	rectWidth = 100;
	rectHeight = 100;
	id = tmpComponentId;
	type = "";
	painterPath.addRect(0, 0, rectWidth, rectHeight);
}

GUIEntity::~GUIEntity(void)
{
	component = nullptr;
}

int GUIEntity::GetComponentId()
{
	return id;
}

void GUIEntity::DrawShap(QPainter *painter)
{
	painter->drawPath(painterPath);
	QFont font(fontType, fontSize);
	painter->setFont(font);
	painter->drawText(boundingRect(), Qt::AlignCenter, QString::fromStdString(name));
}

string GUIEntity::GetType()
{
	return component->GetType();
}
/*
QPainterPath GUIEntity::shape() const 
{
	return painterPath;
}*/

void GUIEntity::SetPointX(int pointX)
{
	component->SetPointX(pointX);
}

void GUIEntity::SetPointY(int pointY)
{
	component->SetPointY(pointY);
}

string GUIEntity::GetName()
{
	return component->GetName();
}

void GUIEntity::RefreshName()
{
	name = component->GetName();
}

void GUIEntity::ResetPoint()
{
	pos().setX(component->GetPointX());
	pos().setY(component->GetPointY());
}