#include "GUIConnection.h"


GUIConnection::GUIConnection(Components *component)
{
	this->component = component;
	type = component->GetType();
	id = component->GetId();
	name = component->GetName();
}

GUIConnection::GUIConnection()
{
	id = tmpComponentId;
	type = "";
	name = "";
}

GUIConnection::~GUIConnection(void)
{
	component = nullptr;
}

int GUIConnection::GetComponentId()
{
	return id;
}

void GUIConnection::DrawShap(QPainter *painter)
{
	painter->drawPath(painterPath);
	QFont font(fontType, fontSize);
	painter->setFont(font);
	painter->drawText(boundingRect(), Qt::AlignCenter | Qt::AlignTop, QString::fromStdString(name));
}

void GUIConnection::SetLeftNodePosition(QPointF position)
{
	leftNodePosition =  position;
	line.setP1(leftNodePosition);
}

void GUIConnection::SetRightNodePosition(QPointF position)
{
	rightNodePosition = position;
	line.setP2(rightNodePosition);
}

int GUIConnection::GetLeftNodeId()
{
	return dynamic_cast<Connection *>(component)->GetConnectComponentsId().at(0);
}

int GUIConnection::GetRightNodeId()
{
	return dynamic_cast<Connection *>(component)->GetConnectComponentsId().at(1);
}

void GUIConnection::UpdateShape()
{
	prepareGeometryChange();
	painterPath = QPainterPath();
	painterPath.moveTo(line.p1());
	painterPath.lineTo(line.p2());
}

string GUIConnection::GetType()
{
	return type;
}

void GUIConnection::SetPointX(int pointX)
{
	component->SetPointX(pointX);
}

void GUIConnection::SetPointY(int pointY)
{
	component->SetPointY(pointY);
}

string GUIConnection::GetName()
{
	return component->GetName();
}

void GUIConnection::RefreshName()
{
	name = component->GetName();
}

void GUIConnection::ResetPoint()
{
}