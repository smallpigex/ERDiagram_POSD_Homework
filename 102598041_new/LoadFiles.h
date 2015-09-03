#pragma once
#include <vector>
#include <string>
#include <fstream>
#include "gtest/gtest_prod.h"

using namespace std;

class LoadFiles
{
	friend class LoadFileTest;
	FRIEND_TEST(LoadFileTest, StoreData);
	FRIEND_TEST(LoadFileTest, LoadFile);

private:
	vector<string> component;
	vector<string> connection;
	vector<string> entity;
	vector<string> componentPosition;

public:
	LoadFiles(void);
	~LoadFiles(void);
	bool LoadFile(string);
	bool LoadPositionFile(string path);
	vector<string> GetComponents();
	vector<string> GetConnections();
	vector<string> GetEntity();
	vector<string> GetComponentPosition();
	void StoreData(fstream &, vector<string> &);
};

