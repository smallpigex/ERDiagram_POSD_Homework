#include "GUIComponent.h"


GUIComponent::GUIComponent(void)
{
	setFlag(QGraphicsItem::ItemIsSelectable, true);
	//setFlag(QGraphicsItem::ItemIsMovable, true);
	mousePressed = false;
	fontSize = 16;
	fontType = "Arial";
}


 GUIComponent::~GUIComponent(void)
{
}

 
int GUIComponent::GetId()
{
	return GetComponentId();
}
/*
string GUIComponent::GetName()
{
	return component->GetName();
}*/
/*
string GUIComponent::GetType()
{
	return GetType();
}*/

QRectF GUIComponent::boundingRect() const
{
	return painterPath.boundingRect();
}

QPainterPath GUIComponent::shape() const 
{
	return painterPath;
}

void GUIComponent::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
	QGraphicsItem::mouseReleaseEvent(event);

	if(isSelected() && !mousePressed)
	{
		mousePressed = true;
	}
	else if(isSelected() && mousePressed)
	{
		setSelected(false);
	}
}

void GUIComponent::paint(QPainter *painter, const QStyleOptionGraphicsItem * option, QWidget *widget = 0)
{
	DrawShap(painter);
	DrawSelectDiagram(painter);
}

void GUIComponent::DrawSelectDiagram(QPainter *painter)
{
	if(isSelected())
	{
		QPen pen;
		pen.setColor(Qt::red);
		pen.setWidth(4);
		painter->setPen(pen);
		painter->drawPath(shape());
	}
	//painter->drawText(boundingRect(), Qt::AlignCenter, QString::number(mousePressed));
    //painter->drawText(boundingRect(), Qt::AlignLeft, QString::number(isSelected()));
	
}

QPoint GUIComponent::GetPosition()
{
	//QPoint position(pos().rx(), pos().ry());
	QPoint position(component->GetPointX(), component->GetPointY());
	return position;
}

void GUIComponent::SetMoveable(bool isMove)
{
	setFlag(QGraphicsItem::ItemIsMovable, isMove);
}

#include <QDebug>
void GUIComponent::UpdatePoint()
{
	QPointF point = pos();
	//qDebug() << "posx = " << pos().x();
	//qDebug() << "posy = " << pos().y();
	SetPointX(pos().x());
	SetPointY(pos().y());
}

string GUIComponent::GetComponentName()
{
	return GetName();
}

void GUIComponent::RefreshComponetName()
{
	RefreshName();
	update();
}

void GUIComponent::DoResetPoint()
{
	ResetPoint();
}
