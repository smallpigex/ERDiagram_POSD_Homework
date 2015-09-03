#include "Components.h"


Components::Components(void)
{
	pointX = -1;
	pointY = -1;
}

Components::~Components(void)
{
}

int Components::GetId()
{
	return id;
}

string Components::GetType()
{
	return type;
}

string Components::GetName()
{
	return name;
}

void Components::SetId(int id)
{
	this->id = id;
}

void Components::SetType(string type)
{
	this->type = type;
}

void Components::SetName(string name)
{
	this->name = name;
}

void Components::SetPointX(int pointX)
{
	this->pointX = pointX;
}

void Components::SetPointY(int pointY)
{
	this->pointY = pointY;
}

int Components::GetPointX()
{
	return pointX;
}

int Components::GetPointY()
{
	return pointY;
}