#pragma once
class ComponentPoint
{
private:
	int id;
	int pointX;
	int pointY;

public:
	ComponentPoint(void);
	~ComponentPoint(void);
	int GetId();
	void SetId(int);
	void SetPointX(int);
	void SetPointY(int);
	int GetPointX();
	int GetPointY();
};

