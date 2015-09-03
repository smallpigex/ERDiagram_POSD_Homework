#pragma once
#include "GUIComponent.h"

class GUIRelationship : public GUIComponent
{
private:
	int pointX;
	int pointY;
	string type;
	string name;
	int id;

public:
	GUIRelationship(Components *);
	GUIRelationship();
	~GUIRelationship(void);
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

