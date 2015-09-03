#pragma once
#include <vector>
#include "gtest/gtest_prod.h"

class ConnectionData
{
	friend class ERModelTest;
	FRIEND_TEST(ERModelTest, GetConnectionsData);

private:
	int conneciontId;
	std::vector<int> connectComponens;

public:
	ConnectionData(void);
	~ConnectionData(void);
	void SetId(int);
	void SetComponents(std::vector<int> &);
	void SetComponentForIndex(int , int);
	int GetId();
	int GetConnectComponetId(int);
};

