#include "GUIAttribute.h"
#include "qdebug.h"

GUIAttribute::GUIAttribute(Components *component)
{
	ellipseWidth = 100;
	ellipseHeight = 100;
	this->component = component;
	QFontMetrics fontMetrics(QApplication::font());
	width = fontMetrics.width(QString::fromStdString(component->GetName()));
	painterPath.addEllipse(0, 0, ellipseWidth + width, ellipseHeight);
	id = component->GetId();
	type = component->GetType();
	name = component->GetName();
	primaryKey = false;
	//primaryKey = dynamic_cast<Attributes *>(component)->GetPrimaryKey();
}

GUIAttribute::GUIAttribute()
{
	ellipseWidth = 100;
	ellipseHeight = 100;
	type = "";
	name = "";
	painterPath.addEllipse(0, 0, ellipseWidth, ellipseHeight);
	id = tmpComponentId;
	primaryKey = false;
}

GUIAttribute::~GUIAttribute(void)
{
	component = nullptr;
}

int GUIAttribute::GetComponentId()
{
	return id;
}

QRectF GUIAttribute::boundingRect() const
{
	return painterPath.boundingRect();
}

void GUIAttribute::DrawShap(QPainter *painter)
{
	painter->drawPath(painterPath);
	QFont font(fontType, fontSize);

	if(primaryKey)
	{
		font.setUnderline(true);
	}

	painter->setFont(font);
	painter->drawText(boundingRect(), Qt::AlignCenter | Qt::AlignTop, QString::fromStdString(name));
}

void GUIAttribute::ResetPrimaryKey()
{
	primaryKey = dynamic_cast<Attributes *>(component)->GetPrimaryKey();
	update();
}

string GUIAttribute::GetType()
{
	return component->GetType();
}

void GUIAttribute::SetPointX(int pointX)
{
	component->SetPointX(pointX);
	//qDebug() << component->GetPointX();
}

void GUIAttribute::SetPointY(int pointY)
{
	component->SetPointY(pointY);
	//qDebug() << component->GetPointY();
}

string GUIAttribute::GetName()
{
	return component->GetName();
}

void GUIAttribute::RefreshName()
{
	name = component->GetName();
}

void GUIAttribute::ResetPoint()
{
	pos().setX(component->GetPointX());
	pos().setY(component->GetPointY());
	update();
}