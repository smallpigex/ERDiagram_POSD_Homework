#pragma once
#include <vector>
#include "gtest/gtest_prod.h"

class EntityData
{
	friend class ERModelTest;
	FRIEND_TEST(ERModelTest, ClassifyAttribute);
	FRIEND_TEST(ERModelTest, SetEnityData);
	FRIEND_TEST(ERModelTest, StoreAttributeToEnityData);

public:
	int id;
	std::vector<int> attributesId;
	std::vector<int> primaryKeysId;
	std::vector<int> foreignKeysId;

public:
	EntityData(void);
	~EntityData(void);
	void SetEntityId(int);
	void SetAttributeId(int);
	void SetPrimaryKeysId(int);
	int GetId();
	int GetPrimaryKeyId(int);
	int GetPrimaryKeySize();
	bool CheckHasPrimayKey();
	void SetForeignKeysId(std::vector<int> &);
};

