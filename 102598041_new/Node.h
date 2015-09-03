#pragma once
#include "Components.h"

class Node : public Components
{
public:
	Node(void);
	virtual ~Node(void);
	virtual void ConnectTo(Components *) = 0;
	virtual int CanConnectTo(Components *) = 0;
	virtual bool CheckHasBeenConnect(Components *) = 0;
	virtual vector<int> GetConnectComponentsId() = 0;
	virtual void DeleteConnectComponents(int) = 0;
	virtual vector<Components *> GetConnectComponents() = 0;
	virtual void Save(ComponentVisitor &) = 0;
	virtual Components *Clone() = 0;
	virtual void ClearConnection() = 0;
};

