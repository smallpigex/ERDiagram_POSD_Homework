#pragma once
#include "components.h"
#include <vector>
#include "Node.h"
#include "gtest/gtest_prod.h"

const int SIZES = 2;


class Connection : public Components
{
	friend class ConnectionTest;
	FRIEND_TEST(ConnectionTest, DeleteConnectComponents);
	FRIEND_TEST(ConnectionTest, ConnectTo);

	friend class ERModelTest;
	FRIEND_TEST(ERModelTest, AddConnection);
	FRIEND_TEST(ERModelTest, ConnectComponents);
	FRIEND_TEST(ERModelTest, RecoveryConnect);
	FRIEND_TEST(ERModelTest, RecoveryComponents);

private:
	vector<Components *> nodes[SIZES];
	string cadinality;

public:
	Connection(void);
	~Connection(void);
	void ConnectTo(Components *);
	int CanConnectTo(Components *);
	bool CheckHasBeenConnect(Components *);
	vector<int> GetConnectComponentsId();
	void SetCardinality(string);
	int GetEntityConnectAttributeId();
	void DeleteConnectComponents(int);
	vector<Components *> GetConnectComponents();
	void Save(ComponentVisitor &);
	Components *Clone();
	void ClearConnection();
};

