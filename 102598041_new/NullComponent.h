#pragma once
#include "Components.h"
#include "MessageOfConstString.h"

class NullComponent : public Components
{
public:
	NullComponent(void);
	~NullComponent(void);
	void ConnectTo(Components *);
	int CanConnectTo(Components *);
	bool CheckHasBeenConnect(Components *);
	vector<int> GetConnectComponentsId();
	void DeleteConnectComponents(int);
	vector<Components *> GetConnectComponents();
	void Save(ComponentVisitor &);
	Components *Clone();
	void ClearConnection();
};

