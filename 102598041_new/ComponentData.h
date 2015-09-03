#pragma once
#include <iostream>

class ComponentData
{
private:
	int id;
	std::string type;
	std::string name;
	int pointX;
	int pointY;

public:
	ComponentData(void);
	~ComponentData(void);
	void SetId(int);
	void SetType(std::string);
	void SetName(std::string);
	void SetPointX(int);
	void SetPointY(int);
	int GetId();
	std::string GetType();
	std::string GetName();
	int GetPointX();
	int GetPointY();
};

