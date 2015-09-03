#include "SaveFiles.h"


SaveFiles::SaveFiles(void)
{
	format = ".erd";
	pointFormat = ".pos";
	backslash = "\\";
	colon = ":";
	comma = ",";
	xmlFormat = ".xml";
}

SaveFiles::~SaveFiles(void)
{
}

bool SaveFiles::CheckSaveFileFormat(string path)
{
	if(path.find(format) != string::npos || path.find(xmlFormat) != string::npos)
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool SaveFiles::CheckSavePathExist(string path)
{
	string folderPath;
	folderPath = splitPath(path);
	struct stat statFileInformation;
	int intStat;
	intStat = stat(folderPath.c_str(), &statFileInformation);

	if(intStat == 0)
	{
		return true;
	}
	
	return false;
}

void SaveFiles::SaveFile(string input)
{
	fstream file;
	path = input;
	SaveComponent(file);
	SaveConnection(file);
	SavePrimaryKey(file);
	SaveComponentPoint(path);
}

bool SaveFiles::SaveComponent(fstream &file)
{
	file.open(path, ios::out);

	if(!file)
	{
		return false;
	}

	for(unsigned int index = 0; index < componentData.size(); ++index)
	{
		if(componentData.at(index).GetName() != "")
		{
			file << componentData.at(index).GetType() << comma << " " << componentData.at(index).GetName() << endl;
		}
		else
		{
			file << componentData.at(index).GetType() << endl;
		}
	}

	file << endl;
	file.close();
	return true;
}

bool SaveFiles::SaveConnection(fstream &file)
{
	file.open(path, ios::out | ios::app);

	if(!file)
	{
		return false;
	}

	for(unsigned int index = 0; index < connectionData.size(); ++index)
	{
		file << connectionData.at(index).GetId() << " " << connectionData.at(index).GetConnectComponetId(0) 
			<< "," << connectionData.at(index).GetConnectComponetId(1) << endl;
	}

	file << endl;
	file.close();
	return true;
}

bool SaveFiles::SavePrimaryKey(fstream &file)
{
	file.open(path, ios::out | ios::app);

	if(!file)
	{
		return false;
	}

	for(unsigned int index = 0; index < entityData.size(); ++index)
	{
		if(entityData.at(index).CheckHasPrimayKey())
		{
			file << entityData.at(index).GetId() << " ";

			for(int primaryKeyIndex = 0; primaryKeyIndex < entityData.at(index).GetPrimaryKeySize() ; ++primaryKeyIndex)
			{
				file << entityData.at(index).GetPrimaryKeyId(primaryKeyIndex);

				if(primaryKeyIndex != (entityData.at(index).GetPrimaryKeySize() - 1))
				{
					file << comma;
				}
			}
			file << endl;
		}
	}

	file.close();
	return true;
}

string SaveFiles::splitPath(string path)
{
	int position;
	string folderPath = path;
	for(unsigned int index = path.size() - 1 ; index > 0; index--)
	{
		if(path.find(backslash, index) != string::npos)
		{
			position = path.find(backslash, index);
			folderPath = path.substr(0, position);
			break;
		}
		else if(path.find("/", index) != string::npos)
		{
			position = path.find("/", index);
			folderPath = path.substr(0, position);
			break;
		}
	}

	if(folderPath[folderPath.size() - 1] == colon[0])
	{
		folderPath += backslash;
	}

	return folderPath;
}

void SaveFiles::SetComponentData(vector<ComponentData> componentData)
{
	this->componentData = componentData;
}

void SaveFiles::SetConnectionData(vector<ConnectionData> connectionData)
{
	this->connectionData = connectionData;
}

void SaveFiles::SetPrimaryData(vector<EntityData> entityData)
{
	this->entityData = entityData;
}

bool SaveFiles::CheckComponentPoint()
{
	for(unsigned int index = 0; index < componentData.size(); index++)
	{
		if(componentData.at(index).GetType() != ComponetType::CONNECTION && (componentData.at(index).GetPointX() == -1 || componentData.at(index).GetPointY() == -1))
		{
			return false;
		}
	}
	return true;
}

void SaveFiles::SaveComponentPoint(string path)
{
	if(CheckComponentPoint())
	{
		fstream file;
		path.replace(path.find(format), format.length(), pointFormat);
		file.open(path, ios::out);

		if(!file)
		{
			return ;
		}

		for(unsigned int index = 0; index < componentData.size(); ++index)
		{
			if(componentData.at(index).GetType() != ComponetType::CONNECTION)
			{
				file << componentData.at(index).GetPointX() << " " << componentData.at(index).GetPointY() << "\n";
			}
		}

		file.close();
	}
}


