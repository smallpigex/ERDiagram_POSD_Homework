#include "EntityData.h"


EntityData::EntityData(void)
{
}


EntityData::~EntityData(void)
{
}

void EntityData::SetEntityId(int id)
{
	this->id = id;
}

void EntityData::SetPrimaryKeysId(int primaryKeyId)
{
	primaryKeysId.push_back(primaryKeyId);
}


void EntityData::SetAttributeId(int attributeId)
{
	attributesId.push_back(attributeId);
}

int EntityData::GetPrimaryKeySize()
{
	return primaryKeysId.size();
}

int EntityData::GetPrimaryKeyId(int index)
{
	return primaryKeysId.at(index);
}

bool EntityData::CheckHasPrimayKey()
{
	if(primaryKeysId.size() == 0)
	{
		return false;
	}
	return true;
}

int EntityData::GetId()
{
	return id;
}

void EntityData::SetForeignKeysId(std::vector<int> &foreignKey)
{
	this->foreignKeysId = foreignKey;
}