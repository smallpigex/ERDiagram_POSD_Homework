#pragma once
#include "node.h"
#include <vector>
#include "Connection.h"
#include "gtest/gtest_prod.h"

class Relationship : public Node
{
	friend class RelationshipTest;
	FRIEND_TEST(RelationshipTest, DeleteConnectComponents);
	FRIEND_TEST(RelationshipTest, ConnectTo);

private:
	vector<Components *> connections;

public:
	Relationship(void);
	~Relationship(void);
	void ConnectTo(Components *);
	int CanConnectTo(Components *);
	bool CheckHasBeenConnect(Components *);
	vector<int> GetConnectComponentsId();
	void DeleteConnectComponents(int);
	vector<Components *> GetConnectComponents();
	int VarifyComponentType(Components *);
	void Save(ComponentVisitor &);
	Components *Clone();
	void ClearConnection();
};

