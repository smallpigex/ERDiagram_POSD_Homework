#pragma once
#include "Node.h"
#include <vector>
#include "Connection.h"
#include "gtest/gtest_prod.h"

class Attributes : public Node
{
	friend class AttributeTest;
	FRIEND_TEST(AttributeTest, ConnectTo);
	FRIEND_TEST(AttributeTest, DeleteConnectComponents);

	friend class ERModelTest;
	FRIEND_TEST(ERModelTest, SetAttributeIsPrimary);
	FRIEND_TEST(ERModelTest, DeleteConnecionFromTargetToSourceComponent);
	FRIEND_TEST(ERModelTest, DeleteConnection);
	FRIEND_TEST(ERModelTest, ConnectComponentsToConnecions);
	FRIEND_TEST(ERModelTest, RecoveryConnect);
	FRIEND_TEST(ERModelTest, RecoveryComponents);

	friend class testLoadFileNotExist;
	FRIEND_TEST(IntegrateTest, testIsPrimaryExist);
	FRIEND_TEST(IntegrateTest, testCommonUsage);

private:
	vector<Components *> connection[1];
	bool primaryKey;

public:
	Attributes(void);
	~Attributes(void);
	void ConnectTo(Components *);
	int CanConnectTo(Components *);
	bool CheckHasBeenConnect(Components *);
	vector<int> GetConnectComponentsId();
	void SetPrimaryKey(bool);
	bool GetPrimaryKey();
	void DeleteConnectComponents(int);
	vector<Components *> GetConnectComponents();
	int CheckConnectionHasConnectComponent(Components *);
	void Save(ComponentVisitor &);
	Components *Clone();
	void ClearConnection();
};

