#pragma once
#include "GUIComponent.h"
class GUIEntity : public GUIComponent
{
private:
	int rectWidth;
	int rectHeight;
	string type;
	string name;
	int id;

public:
	GUIEntity(Components *);
	GUIEntity();
	~GUIEntity(void);
	//QPainterPath shape() const;
	void DrawShap(QPainter *);
	string GetType();
	int GetComponentId();
	void SetPointX(int);
	void SetPointY(int);
	string GetName();
	void RefreshName();
	void ResetPoint();
};

