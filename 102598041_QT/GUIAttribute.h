#pragma once
#include "GUIComponent.h"
#include "../102598041_new/Attributes.h"
#include <iostream>
#include <qmessagebox.h>

class GUIAttribute : public GUIComponent
{
private:
	int ellipseWidth;
	int ellipseHeight;
	string type;
	string name;
	int id;
	bool primaryKey;

public:
	GUIAttribute();
	GUIAttribute(Components *);
	~GUIAttribute(void);
	int GetComponentId();
	QRectF boundingRect() const;
	void DrawShap(QPainter *);
	string GetType();
	void SetPointX(int);
	void SetPointY(int);
	void ResetPrimaryKey();
	string GetName();
	void RefreshName();
	void ResetPoint();
};

