#pragma once
#include <iostream>
#include <vector>
#include "MessageOfConstString.h"
#include "MessageOfConstInteger.h"
#include "gtest/gtest_prod.h"

using namespace std;

class ComponentVisitor;

class Components
{
	friend class ERModelTest;
	FRIEND_TEST(ERModelTest, ConnectComponents);

private:
	int id;
	string type;
	string name;
	int pointX;
	int pointY;

public:
	Components(void);
	virtual~Components(void);
	int GetId();
	string GetType();
	string GetName();
	void SetId(int);
	void SetType(string);
	void SetName(string);
	void SetPointX(int);
	void SetPointY(int);
	int GetPointX();
	int GetPointY();
	virtual void ConnectTo(Components *) = 0;
	virtual int CanConnectTo(Components *) = 0;
	virtual bool CheckHasBeenConnect(Components *) = 0;
	virtual vector<int> GetConnectComponentsId() = 0;
	virtual vector<Components *> GetConnectComponents() = 0;
	virtual void DeleteConnectComponents(int) = 0;
	virtual void Save(ComponentVisitor &) = 0;
	virtual Components *Clone() = 0;
	virtual void ClearConnection() = 0;
};

