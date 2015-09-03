#pragma once
#include <iostream>
#include <vector>
#include <string>
#include "ComponentData.h"
#include "ConnectionData.h"
#include "EntityData.h"
#include <fstream>
#include <windows.h>
#include "gtest/gtest_prod.h"
#include <sys/stat.h>
#include "MessageOfConstString.h"
using namespace std;

class SaveFiles
{
	friend class SaveFileTest;
	FRIEND_TEST(SaveFileTest, SaveComponent);
	FRIEND_TEST(SaveFileTest, SaveConnection);
	FRIEND_TEST(SaveFileTest, SavePrimaryKey);

private:
	string path;
	vector<ComponentData> componentData;
	vector<ConnectionData> connectionData;
	vector<EntityData> entityData;
	string format;
	string pointFormat;
	string xmlFormat;
	string backslash;
	string colon;
	string comma;

public:
	SaveFiles(void);
	~SaveFiles(void);
	bool CheckSaveFileFormat(string);
	bool CheckSavePathExist(string);
	void SaveFile(string);
	bool SaveComponent(fstream &);
	bool SaveConnection(fstream &);
	bool SavePrimaryKey(fstream &);
	void SaveComponentPoint(string);
	string splitPath(string);
	void SetComponentData(vector<ComponentData>);
	void SetConnectionData(vector<ConnectionData>);
	void SetPrimaryData(vector<EntityData>);
	bool CheckComponentPoint();
};

