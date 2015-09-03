#include "ComponentData.h"


ComponentData::ComponentData(void)
{
}


ComponentData::~ComponentData(void)
{
}

void ComponentData::SetId(int id)
{
	this->id = id;
}

void ComponentData::SetType(std::string type)
{
	this->type = type;
}

void ComponentData::SetName(std::string name)
{
	this->name = name;
}

int ComponentData::GetId()
{
	return this->id;
}

std::string ComponentData::GetType()
{
	return this->type;
}

std::string ComponentData::GetName()
{
	return this->name;
}

void ComponentData::SetPointX(int x)
{
	this->pointX = x;
}

void ComponentData::SetPointY(int y)
{
	this->pointY = y;
}

int ComponentData::GetPointX()
{
	return pointX;
}

int ComponentData::GetPointY()
{
	return pointY;
}