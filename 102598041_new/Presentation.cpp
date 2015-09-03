#include "Presentation.h"


Presentation::Presentation(ERModel *erModel)
{
	this->erModel = erModel;
}


Presentation::~Presentation(void)
{
}

void Presentation::AddNode(string componentType, string componentName)
{
	commandManager.Execute(new AddComponentCmd(erModel, componentType, componentName));
}

void Presentation::DeleteComponent(string id)
{
	commandManager.Execute(new DeleteComponentCmd(erModel, convertor.ConvertStringToInteger(id)));
}

void Presentation::ConnectComponents(string firstId, string secondId, string cardinality)
{
	commandManager.Execute(new ConnectComponentsCmd(erModel, firstId, secondId, cardinality));
}

void Presentation::SetPrimaryKey(int id)
{
	commandManager.Execute(new SetPrimaryKeyCmd(erModel, id));
}

void  Presentation::MoveComponent(vector<ComponentPoint> oldComponentPoint, vector<ComponentPoint> newComponentPoint)
{
	commandManager.Execute(new MoveComponents(erModel, oldComponentPoint, newComponentPoint));
}

void Presentation::EditComponentName(int id, string name)
{
	commandManager.Execute(new EditNameOfComponent(erModel, id, name));
}

bool Presentation::LoadFile(string path)
{
	bool isLoadFile = erModel->LoadFile(path);

	if(isLoadFile)
	{
		commandManager.ClearCommand();
	}

	return isLoadFile;
}

bool Presentation::SaveFile(string path)
{
	if(erModel->SaveFile(path))
	{
		//save檔案後，無法redo和undo，所以直接將command清除
		commandManager.ClearCommand();
		return true;
	}

	return false;
}

bool Presentation::SaveXmlFile(string path)
{
	if(erModel->SaveXmlFile(path))
	{
		//save檔案後，無法redo和undo，所以直接將command清除
		commandManager.ClearCommand();
		return true;
	}

	return false;
}

bool Presentation::Redo()
{
	return commandManager.Redo();
}

bool Presentation::Undo()
{
	return commandManager.Undo();
}

void Presentation::SetAttributeIsPrimary(vector<string> attributesId)
{
	erModel->SetAttributeIsPrimary(attributesId);
}

vector<ComponentData> Presentation::GetComponentsData()
{
	return erModel->GetComponentsData();
}

int Presentation::GetComponentsSize()
{
	return erModel->GetComponentsSize();
}

Components *Presentation::GetComponent(int index)
{
	return erModel->GetComponent(index);
}

Components *Presentation::GetNewComponent()
{
	return erModel->GetNewComponent();
}

int Presentation::GetConnectMessage()
{
	return erModel->GetConnectMessage();
}

Components *Presentation::GetNewConnection()
{
	return erModel->GetCurrentCreateConnection();
}

int Presentation::CanConnect(string firsId, string secondId)
{
	return erModel->CanConneciont(firsId, secondId);
}

bool Presentation::IsComponentExist(int id)
{
	return erModel->IsComponentExist(id);
}

bool Presentation::CanReName(int id, string name)
{
	if(erModel->GetComponent(id)->GetType().compare(ComponetType::CONNECTION) == 0)
	{
		if(erModel->IsCardinality(erModel->GetComponent(id)) && erModel->CheckNameIsCardinality(name))
		{
			return true;
		}
		else
		{
			return false;
		}
	}
	
	return true;
}

bool Presentation::LoadPositionFile(string path)
{
	return erModel->LoadPositionFile(path);
}

void Presentation::CutComponent(vector<int> cutComponentsId)
{
	commandManager.Execute(new CutComponents(erModel, cutComponentsId));
}

void Presentation::PasteComponents()
{
	erModel->PasteComponent();
}

void Presentation::CopyComponent(vector<int> componentsId)
{
	erModel->CopyComponents(componentsId);
}