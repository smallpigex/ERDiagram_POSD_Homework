#include "ComponentPoint.h"


ComponentPoint::ComponentPoint(void)
{
}


ComponentPoint::~ComponentPoint(void)
{
}

int ComponentPoint::GetId()
{
	return id;
}

void ComponentPoint::SetId(int id)
{
	this->id = id;
}

void ComponentPoint::SetPointX(int pointX)
{
	this->pointX = pointX;
}

void ComponentPoint::SetPointY(int pointY)
{
	this->pointY = pointY;
}

int ComponentPoint::GetPointX()
{
	return pointX;
}

int ComponentPoint::GetPointY()
{
	return pointY;
}
