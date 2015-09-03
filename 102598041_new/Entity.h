#pragma once
#include "Node.h"
#include <vector>
#include "gtest/gtest_prod.h"

class Entity : public Node
{
	friend class EntityTest;
	FRIEND_TEST(EntityTest, DeleteConnectComponents);
	FRIEND_TEST(EntityTest, ConnectTo);
	FRIEND_TEST(ConnectionTest, DeleteConnectComponents);

	friend class ERModelTest;
	FRIEND_TEST(ERModelTest, DeleteConnection);
	FRIEND_TEST(ERModelTest, ConnectComponentsToConnecions);
	FRIEND_TEST(ERModelTest, RecoveryConnect);
	FRIEND_TEST(ERModelTest, RecoveryComponents);

private:
	vector<Components *> connections;

public:
	Entity(void);
	~Entity(void);
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

