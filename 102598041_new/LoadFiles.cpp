#include "LoadFiles.h"


LoadFiles::LoadFiles(void)
{
}


LoadFiles::~LoadFiles(void)
{
}

bool LoadFiles::LoadFile(string path)
{
	fstream file;

	file.open(path, ios::in);

	if(!file)
	{
		return false;
	}

	StoreData(file, component);
	StoreData(file, connection);
	StoreData(file, entity);
	
	file.close();
	return true;
}

bool LoadFiles::LoadPositionFile(string path)
{
	fstream file;

	file.open(path, ios::in);

	if(!file)
	{
		return false;
	}

	StoreData(file, componentPosition);
	return true;
}

void LoadFiles::StoreData(fstream &file, vector<string> &storeSpace)
{
	string input;

	do 
	{
		getline(file, input);

		if(input != "")
		{
			storeSpace.push_back(input);
		}

		if(file.eof())
		{
			break;
		}
	}
	while(input != "");
}

vector<string> LoadFiles::GetComponents()
{
	return component;
}


vector<string> LoadFiles::GetConnections()
{
	return connection;
}

vector<string> LoadFiles::GetEntity()
{
	return entity;
}

vector<string> LoadFiles::GetComponentPosition()
{
	return componentPosition;
}