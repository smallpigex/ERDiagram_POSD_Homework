#include "ERModel.h"


ERModel::ERModel(void)
{
	serialNumber = 0;
	componentPointX = -1;
	componentPointY = -1;
	observer = nullptr;
	mainWindowObserver = nullptr;
}


ERModel::~ERModel(void)
{
	for(unsigned int index = 0; index < components.size(); ++index)
	{
		Components *component = components.at(index);
		delete component;
	}
	
	components.clear();
}

void ERModel::RegisterObserver(GUIObserver *observer)
{
	this->observer = observer;
}

void ERModel::SetComponentPointX(int componentPointX)
{
	this->componentPointX = componentPointX;
}

void ERModel::SetComponentPointY(int componentPointY)
{
	this->componentPointY = componentPointY;
}
/*
void ERModel::RemoveObserver(ObserverTextUIInterface *obserber)
{
	this->observer = NULL;
}
*/

void ERModel::NotifyObserverGUIComponentUpdate()
{
	if(observer != nullptr)
	{
		observer->UpdateNode(currentCreateComponent->GetId());
	}
	//observer->UpdatePreviewPos();
}

void ERModel::NotifyObserverUpateGUIConnection()
{
	if(observer != nullptr)
	{
		observer->UpdateConnection(currentCreateConnection->GetId());
	}
}

void ERModel::NotifyObserverUpdatePrimaryKey()
{
	if(observer != nullptr)
	{
		observer->UpdatePrimaryKey();
	}
}

void ERModel::NotifyObserverDeleteGUIComponent()
{
	if(observer != nullptr)
	{
		observer->DeleteGUIComponent();
	}
	
}

void ERModel::NotifyObserverResetPoint()
{
	if(observer != nullptr)
	{
		observer->ResetComponentsPoint();
	}
}

void ERModel::RegisterMainWindowObserver(MainWindowObserver *mainWindowObserver)
{
	this->mainWindowObserver = mainWindowObserver;
}

void ERModel::NotifyMainWindowUpdateTable()
{
	if(mainWindowObserver != nullptr)
	{
		mainWindowObserver->UpdateTable();
	}
}

void ERModel::NotifyRefreshTable()
{
	if(mainWindowObserver != nullptr)
	{
		mainWindowObserver->RefreshTable();
	}
}
/*
void ERModel::NotifyObserverConnectionUpdate(int firstId, int secondId, string cardinality)
{
	observer->UpdateConnection(firstId, secondId, cardinality);
}*/

void ERModel::AddNode(string componentType, string ComponentName)
{
	int id = GetSerialNumber();
	currentCreateComponent = componentFactory.CreateComponent(componentType);
	currentCreateComponent->SetId(id);
	currentCreateComponent->SetType(componentType);
	currentCreateComponent->SetName(ComponentName);
	currentCreateComponent->SetPointX(componentPointX);
	currentCreateComponent->SetPointY(componentPointY);
	StoreComponent(currentCreateComponent);
	NotifyObserverGUIComponentUpdate();
}

void ERModel::StoreComponent(Components *newComponent)
{
	if(newComponent->GetId() != components.size())
	{
		components.at(newComponent->GetId()) = newComponent;
	}
	else
	{
		components.push_back(newComponent);
		//NotifyObserverComponentUpdate();
	}
}

int ERModel::GetSerialNumber()
{
	int id;
	id = GetNullComponentIndex();

	if(id != NotGet::ID)
	{
		return id;
	}
	else
	{
		id = components.size();
		return id;
	}
}

int ERModel::GetNullComponentIndex()
{
	for(unsigned int index = 0; index < components.size(); ++index)
	{
		if(components.at(index)->GetId() == nullComponentId)
		{
			delete components.at(index);
			return index;
		}
	}

	return NotGet::ID;
}

void ERModel::GetNodesData(vector<int> &id, vector<string> &type, vector<string> &name)
{
	for(vector<Components *>::iterator iter = components.begin(); iter != components.end(); ++iter)
	{
		id.push_back((*iter)->GetId());
		type.push_back((*iter)->GetType());
		name.push_back((*iter)->GetName());
	}
}

vector<ConnectionData> ERModel::GetConnectionsData()
{
	vector<ConnectionData> connectionsData;
	ConnectionData connectionData;

	for(vector<Components *>::iterator component = components.begin(); component != components.end(); ++component)
	{
		if((*component)->GetType().compare(ComponetType::CONNECTION) == 0)
		{
			connectionData.SetId((*component)->GetId());
			connectionData.SetComponents((*component)->GetConnectComponentsId());
			connectionsData.push_back(connectionData);
		}
	}

	return connectionsData;
}

void ERModel::StoreAttributeToComponentData(string entityId, vector<ComponentData> &attributes)
{
	Convertor convertor;
	vector<int> connectionsId;

	//取得entity相連的conneciotn
	connectionsId = components.at(convertor.ConvertStringToInteger(entityId))->GetConnectComponentsId();

	for(vector<int>::iterator connectionId = connectionsId.begin(); connectionId != connectionsId.end(); ++connectionId)
	{
		//將components轉型成connection
		int attributeId = dynamic_cast<Connection *>(components.at(*connectionId))->GetEntityConnectAttributeId();

		//如果attributeId != -1，表示有資料，則將此attribute資料存起來
		if(attributeId != NotGet::ID)
		{
			//將資料存放在componentData裡
			ComponentData componentData;
			componentData.SetId(components.at(attributeId)->GetId());
			componentData.SetType(components.at(attributeId)->GetType());
			componentData.SetName(components.at(attributeId)->GetName());
			attributes.push_back(componentData);
		}
	}
}

bool ERModel::CheckIdExist(string input)
{
	Convertor convertor;
	int id = convertor.ConvertStringToInteger(input);

	for(vector<Components *>::iterator component = components.begin(); component != components.end(); ++component)
	{
		if(id == (*component)->GetId())
		{
			return true;
		}
	}

	return false;
}

bool ERModel::IsComponentExist(int id)
{
	for(vector<Components *>::iterator component = components.begin(); component != components.end(); ++component)
	{
		if(id == (*component)->GetId())
		{
			return true;
		}
	}

	return false;
}

bool ERModel::VerifyComponentType(string input, string type)
{
	Convertor convertor;
	int id = convertor.ConvertStringToInteger(input);

	if(components.at(id)->GetType().compare(type) == 0)
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool ERModel::CheckIsAttributeBelongToEntity(string entityId, string attributeId)
{
	vector<int> connections;

	//取出entity的connections
	connections = components.at(convertor.ConvertStringToInteger(entityId))->GetConnectComponentsId();

	//檢查connection是否和attribute相連
	for(vector<int>::iterator connection = connections.begin(); connection != connections.end(); ++connection)
	{
		if(components.at((*connection))->CheckHasBeenConnect(components.at(convertor.ConvertStringToInteger(attributeId))))
		{
			return true;
		}
	}

	return false;
}

bool ERModel::CheckIsAttribute(string componentId)
{
	if(components.at(convertor.ConvertStringToInteger(componentId))->GetType().compare(ComponetType::ATTRIBUTE) == 0)
	{
		return true;
	}

	return false;
}

void ERModel::ConnectComponents(string firstId, string secondId, string cardinality)
{
	//將string 轉換成 integer
	Convertor convertor;
	int firstIdOfint = convertor.ConvertStringToInteger(firstId);
	int secondIdOfInt = convertor.ConvertStringToInteger(secondId);

	//將component連起來
	AddConnection(components.at(firstIdOfint), components.at(secondIdOfInt));

	//設定cardinality，1、N表示有E和R相連，空字串表示沒有E和R相連
	currentCreateConnection->SetName(cardinality);

	//SetCardinality(cardinality);
	//NotifyObserverConnectionUpdate(firstIdOfint, secondIdOfInt, cardinality);
	NotifyObserverUpateGUIConnection();
	NotifyRefreshTable();
}

void ERModel::AddConnection(Components *firstComponent, Components *secondComponent)
{
	int id = GetSerialNumber();
	currentCreateConnection = componentFactory.CreateComponent(ComponetType::CONNECTION);
	currentCreateConnection->SetId(id);
	currentCreateConnection->SetType(ComponetType::CONNECTION);

	//將兩個node透過connection連結起來
	firstComponent->ConnectTo(currentCreateConnection);
	currentCreateConnection->ConnectTo(firstComponent);
	secondComponent->ConnectTo(currentCreateConnection);
	currentCreateConnection->ConnectTo(secondComponent);
	StoreComponent(currentCreateConnection);
}

int ERModel::CanConneciont(string firstId, string secondId)
{
	//將string 轉換成 integer
	Convertor convertor;
	int firstIdOfint = convertor.ConvertStringToInteger(firstId);
	int secondIdOfInt = convertor.ConvertStringToInteger(secondId);

	if(components.at(firstIdOfint)->CanConnectTo(components.at(secondIdOfInt)) == ConnectMessage::CAN_CONNECT || components.at(firstIdOfint)->CanConnectTo(components.at(secondIdOfInt)) == ConnectMessage::IS_CARDINALITY)
	{
		return components.at(secondIdOfInt)->CanConnectTo(components.at(firstIdOfint));
	}

	//檢查是否可以相連
	return components.at(firstIdOfint)->CanConnectTo(components.at(secondIdOfInt));
}

void ERModel::SetCardinality(string cardinality)
{
	//currentCreateConnection一定為connection，所以直接轉型
	dynamic_cast<Connection * >(currentCreateConnection)->SetCardinality(cardinality);
}

void ERModel::SetAttributeIsPrimary(vector<string> attributesId)
{
	for(unsigned int index = 0; index < attributesId.size(); ++index)
	{
		//一一取出要設定成primary key 的 attribute，並設定成primary key
		dynamic_cast<Attributes *>(components[convertor.ConvertStringToInteger(attributesId.at(index))])->SetPrimaryKey(true);
	}
}

void ERModel::DeleteSpecifiedComponent(int id)
{
	if(components.at(id)->GetType().compare(ComponetType::CONNECTION) == 0)
	{
		DeleteConnection(id);
	}
	else
	{
		DeleteComponent(id);
	}

	NotifyObserverDeleteGUIComponent();
	NotifyRefreshTable();
}

void ERModel::DeleteComponent(int id)
{
	//將切斷相連component的連結
	DeleteConnecionFromTargetToSourceComponent(id);

	//tmpComponents.push(components.at(id));
	Components *nullComponent = componentFactory.CreateComponent(ComponetType::NULL_COMPONENT);
	nullComponent->SetId(nullComponentId);
	components.at(id) = nullComponent;
}

void ERModel::DeleteConnecionFromTargetToSourceComponent(int sourceComponentId)
{
	vector<int> connctionsIdOfComponent;
	connctionsIdOfComponent = components.at(sourceComponentId)->GetConnectComponentsId();

	/*找出刪除component相連的component，請它將connection刪除*/
	for(unsigned int index = 0; index < connctionsIdOfComponent.size(); ++index)
	{
		Components *nullComponent = componentFactory.CreateComponent(ComponetType::NULL_COMPONENT);
		Components *sourceConnection = components.at(connctionsIdOfComponent.at(index));
		nullComponent->SetId(nullComponentId);

		//取得相連的componentId
		int connectComponentId = GetConnectComponentId(sourceComponentId, sourceConnection);

		//請相連的component刪除connection
		components.at(connctionsIdOfComponent.at(index))->DeleteConnectComponents(connectComponentId);

		//將儲存connection的空間，指向一個null component;
		components.at(connctionsIdOfComponent.at(index)) = nullComponent;
	}
}

//傳進來的sourceConnectionOfComponent必須為connection，由connection找出相連結的componentId
int  ERModel::GetConnectComponentId(int sourceComponentId, Components *sourceConnectionOfComponent)
{
	//取得和Connection相連的componentId
	vector<int> connectComponentsId = sourceConnectionOfComponent->GetConnectComponentsId();
	int componentId;

	for(unsigned int index = 0; index < connectComponentsId.size(); ++index)
	{
		//找到的id為sourceComponentId，不做任何事
		if(connectComponentsId.at(index) != sourceComponentId)
		{
			componentId = connectComponentsId.at(index);
		}
	}

	return componentId;
}

void ERModel::DeleteConnection(int id)
{
	vector<int> connectComponents;

	//create一個nullcomponent 物件
	Components *nullComponent = componentFactory.CreateComponent(ComponetType::NULL_COMPONENT);
	nullComponent->SetId(nullComponentId);

	//取得相連的componentId
	connectComponents = components.at(id)->GetConnectComponentsId();

	for(unsigned int index = 0; index < connectComponents.size(); ++index)
	{
		//找出與connection相連的component，叫他們把connection刪除
		components.at(id)->DeleteConnectComponents(connectComponents.at(index));
	}

	//將此connection的位置指向一個null component
	components.at(id) = nullComponent;
}

int ERModel::GetLastComponentId()
{
	return components.back()->GetId();
}

void ERModel::RecoveryComponents(Components *recoveryComponent)
{
	
	//取出要復原的component的id，此id為index
	int index = recoveryComponent->GetId();

	//將null component刪除
	if(components.at(index)->GetId() == nullComponentId)
	{
		delete components.at(index);
	}

	//將component復原
	components.at(index) = recoveryComponent;

	//復原連結此component的connection
	RecoveryConnect(recoveryComponent);
	NotifyObserverRecoveryGUIComponent();
}

void ERModel::NotifyObserverRecoveryGUIComponent()
{
	if(observer != nullptr)
	{
		observer->RecoveryGUIComponent();
	}
	
	if(mainWindowObserver != nullptr)
	{
		mainWindowObserver->RefreshTable();
	}
}

void ERModel::RecoveryConnect(Components *recoveryComponent)
{
	vector<Components *> connections;
	vector<Components *> tmpComponents;

	//取得與要回復component相連的connection
	connections = GetConnectionOfComponent(recoveryComponent);
	
	//透過connection將之前所相連的components取出來並且重新連接起來;
	for(unsigned index = 0; index < connections.size(); ++index)
	{
		//取得和connection相連的component
		tmpComponents = connections.at(index)->GetConnectComponents();

		//將原本相連的component和connection連結起來
		ConnectComponentsToConnecions(tmpComponents, connections.at(index));

		//將connection放回原來儲存的位置上;
		components.at(connections.at(index)->GetId()) = connections.at(index);
	}
}


void ERModel::ConnectComponentsToConnecions(vector<Components *> component, Components *connection)
{
	//找出component，將該component和之前連結過的connection連起來
	for(unsigned int componentIndex = 0; componentIndex < component.size(); ++componentIndex)
	{
		//將component和connection重新連起來
		components.at(component.at(componentIndex)->GetId())->ConnectTo(connection);
	}
}

vector<Components *> ERModel::GetConnectionOfComponent(Components *component)
{
	vector<Components *> connections;

	if(component->GetType().compare(ComponetType::CONNECTION) != 0)
	{
		//取得相連的connections
		connections = component->GetConnectComponents();
	}
	else
	{
		connections.push_back(component);
	}

	return connections;
}

int ERModel::GetCurrentCreateConnectionId()
{
	return currentCreateConnection->GetId();
}

Components *ERModel::GetComponent(int id)
{
	return components.at(id);
}

Components *ERModel::GetNewComponent()
{
	return currentCreateComponent;
}

Components *ERModel::GetCurrentCreateConnection()
{
	return currentCreateConnection;
}

int ERModel::GetCurrentCreateComponentId()
{
	return currentCreateComponent->GetId();
}

string ERModel::GetCurrentCreateComponentType()
{
	return currentCreateComponent->GetType();
}

string ERModel::GetCurrentCreateComponentName()
{
	return currentCreateComponent->GetName();
}

bool ERModel::SaveFile(string path)
{
	ComponentVisitor *componentVisitor = new SaveComponentVisitor();
	SaveFiles saveFile;
	vector<ConnectionData> connectionData;
	vector<ComponentData> componentData;
	vector<EntityData> entityData;

	//檢查存檔格式及磁碟是否存在
	if(saveFile.CheckSaveFileFormat(path) && saveFile.CheckSavePathExist(path))
	{
		//整理component的位置和id
		TidyUpComponents();
		StoreComponentData(componentVisitor);
		componentData = componentVisitor->GetComponentsData();
		connectionData = componentVisitor->GetConnectionsData();
		entityData = componentVisitor->GetEntitiesData();
		/*
		componentData = GetComponentsData();
		connectionData = GetConnectionsData();
		entityData = GetEntitiesData();
		*/
		//存檔
		saveFile.SetComponentData(componentData);
		saveFile.SetConnectionData(connectionData);
		saveFile.SetPrimaryData(entityData);
		saveFile.SaveFile(path);
		return true;
	}

	return false;
}

bool ERModel::SaveXmlFile(string path)
{
	SaveFiles saveFile;
	
	//檢查存檔格式及磁碟是否存在
	if(saveFile.CheckSaveFileFormat(path) && saveFile.CheckSavePathExist(path))
	{
		fstream file;
		file.open(path, ios::out);
		file << XmlTag::xmlTitle;
		file << endl;
		file << XmlTag::startTagERDiagram;
		file << endl;
		file.close();
		ComponentVisitor *componentVisitor = new SaveXmlComponentVisitor(&file, path);
		//整理component的位置和id
		TidyUpComponents();
		StoreComponentData(componentVisitor);
		file << XmlTag::endTagERDiagram;
		file.close();
		delete componentVisitor;
		return true;
	}

	return false;
}

void ERModel::StoreComponentData(ComponentVisitor *componentVisitor)
{
	for(unsigned int index = 0; index < components.size(); index++)
	{
		components.at(index)->Save(*componentVisitor);
	}
}

void ERModel::TidyUpComponents()
{
	ClearNullComponent();

	//整理id
	for(unsigned int index = 0; index < components.size(); ++index)
	{
		components.at(index)->SetId(index);
	}

	NotifyObserverResetComponent();
}

void ERModel::ClearNullComponent()
{
	unsigned int index = 0;

	//將nullComponent清除
	while(index < components.size())
	{
		if(components.at(index)->GetId() == nullComponentId)
		{
			components.erase(components.begin() + index);
		}
		else
		{
			index++;
		}
	} 
}

vector<ComponentData> ERModel::GetComponentsData()
{
	vector<ComponentData> componentsData;

	for(unsigned int index = 0; index < components.size(); ++index)
	{
		ComponentData componentData;
		componentData.SetId(components.at(index)->GetId());
		componentData.SetType(components.at(index)->GetType());
		componentData.SetName(components.at(index)->GetName());
		componentsData.push_back(componentData);
	}

	return componentsData;
}

vector<EntityData> ERModel::GetEntitiesData()
{
	vector<EntityData> entitiesData;
	vector<int> connectionsId;

	for(unsigned int index = 0; index < components.size(); ++index)
	{
		if(components.at(index)->GetType().compare(ComponetType::ENTITY) == 0)
		{
			//找出取出entity相連的componentId，和entity相連的是connection;
			connectionsId = components.at(index)->GetConnectComponentsId();
			StoreAttributeToEnityData(components.at(index)->GetId(), connectionsId, entitiesData);
		}
	}

	return entitiesData;
}

void ERModel::StoreAttributeToEnityData(int entityId, vector<int> connectionsId, vector<EntityData> &entitiesData)
{
	EntityData entityData;
	
	for(unsigned int index = 0; index < connectionsId.size(); ++index)
	{
		vector<int> componentsId;
		int componentIndex = GetComponentIndex(connectionsId.at(index));
		componentsId = components.at(componentIndex)->GetConnectComponentsId();
		SetEnityData(entityData, componentsId);
	}

	entityData.SetEntityId(entityId);
	entitiesData.push_back(entityData);
}

void ERModel::SetEnityData(EntityData &entityData, vector<int> componentsId)
{
	//取得和connection相連的component，確認是否為attribute
	for(unsigned int componentIndex = 0; componentIndex < componentsId.size(); ++componentIndex)
	{
		if(components.at(componentsId.at(componentIndex))->GetType().compare(ComponetType::ATTRIBUTE) == 0)
		{		
			Components *component = components.at(componentsId.at(componentIndex));
			ClassifyAttribute(entityData, component);
		}		
	}
}

//將attribute進行分類，儲存到entity Data中。
void ERModel::ClassifyAttribute(EntityData &entityData, Components *component)
{
	//將component轉型成attribute，確認是不是primaryKey，如果是放入primaryKey的vector中。
	if(dynamic_cast<Attributes *>(component)->GetPrimaryKey())
	{
		entityData.SetPrimaryKeysId(component->GetId());
	}
	else
	{
		entityData.SetAttributeId(component->GetId());
	}
}
//#include <QDebug>
bool ERModel::LoadFile(string path)
{
	ClearComponents();
	LoadFiles loadFile;

	if(loadFile.LoadFile(path))
	{
		LoadComponent(loadFile);
		LoadPrimaryKey(loadFile);
		NotifyObserverUpdatePrimaryKey();
		NotifyRefreshTable();

		return true;
	}

	return false;
}

void ERModel::LoadComponent(LoadFiles &file)
{
	const int loadConnectionPos = 2;
	const int loadTypeLength = 3;
	vector<string> component = file.GetComponents();
	vector<string> connection = file.GetConnections();
	int pos = 0;

	for(unsigned int index = 0; index < component.size(); ++index)
	{
		string type = component.at(index).substr(0,1);
		string name = "";

		if(component.at(index).size() > loadTypeLength)
		{
			name = component.at(index).substr(loadTypeLength, component.at(index).size() - loadTypeLength);
		}

		if(type != ComponetType::CONNECTION)
		{
			AddNode(type, name);
		}
		else
		{
			vector<string> tempConnect;
			tempConnect = split(connection.at(pos).substr(loadConnectionPos, connection.at(pos).size() - loadConnectionPos), Pattern::comma);
			ConnectComponents(tempConnect.at(0), tempConnect.at(1), name);
			pos++;
		}
	}
}

void ERModel::LoadPrimaryKey(LoadFiles &file)
{
	vector<string> entity = file.GetEntity();
	const int loadConnectionLength = 2;

	for(unsigned int index = 0; index < entity.size(); ++index)
	{
		vector<string> primaryKeys;
		string entityId = entity.at(index).substr(0,1);
		primaryKeys = split(entity.at(index).substr(loadConnectionLength, entity.at(index).size() - loadConnectionLength), Pattern::comma);
		SetAttributeIsPrimary(primaryKeys);
	}

}

vector<string> ERModel::split(string idList, string pattern)
{
	
	string::size_type pos;
	vector<string> result;
	string finalString;

	//檢查最後一個字是不是,;
	finalString.assign(&idList[idList.size() - 1]);

	//如果不是,，就加上,以便切割
	if( finalString != pattern)
	{
		idList += pattern;
	}

	for(unsigned int index = 0; index < idList.size(); index++)
	{
		pos = idList.find(pattern, index);

		if(pos < idList.size())
		{
			string str = idList.substr(index, pos - index);
			index = pos + pattern.size() - 1;
			result.push_back(str);
		}
	}
	return result;
}

void ERModel::ClearComponents()
{
	for (unsigned int index = 0; index < components.size(); ++index)
	{
		Components *component = components.at(index);
		delete component;
	}
	components.clear();
}

int ERModel::GetComponentIndex(int componentId)
{
	for (unsigned int index = 0; index < components.size(); ++index)
	{
		if(components.at(index)->GetId() == componentId)
		{
			return index;
		}
	}
	return NotGet::ID;
}

int	ERModel::GetComponentsSize()
{
	return components.size();
}

void ERModel::SetConnectMessage(int message)
{
	connectMessage = message;
}

int ERModel::GetConnectMessage()
{
	return connectMessage;
}

void ERModel::SetPrimaryKey(int id)
{
	dynamic_cast<Attributes *>(components.at(id))->SetPrimaryKey(!dynamic_cast<Attributes *>(components.at(id))->GetPrimaryKey());
	NotifyObserverUpdatePrimaryKey();
}


void ERModel::SetComponentName(int id, string name)
{
	components.at(id)->SetName(name);
	NotifyObserverUpdateComponentName();
	NotifyRefreshTable();
}

void ERModel::NotifyObserverUpdateComponentName()
{
	if(observer != nullptr)
	{
		observer->UpdateComponentsName();
	}
}

void ERModel::NotifyObserverResetComponent()
{
	if(observer != nullptr)
	{
		observer->ResetGUIComponents();
	}
}

bool ERModel::IsCardinality(Components *connection)
{
	Connection *tmpConnection = dynamic_cast<Connection *>(connection);
	vector<Components *> components = tmpConnection->GetConnectComponents();
	
	if(components.at(0)->GetType().compare(ComponetType::ENTITY) == 0 || components.at(1)->GetType().compare(ComponetType::ENTITY) == 0)
	{
		if(components.at(0)->GetType().compare(ComponetType::RELATIONSHIP) == 0 || components.at(1)->GetType().compare(ComponetType::RELATIONSHIP) == 0)
		{
			return true;
		}
	}
	return false;
}

bool ERModel::CheckNameIsCardinality(string name)
{
	if(name.compare(Cardinality::CARDINALITY_ONE) == 0 || name.compare(Cardinality::CARDINALITY_MANY) == 0)
	{
		return true;
	}

	return false;
}

bool ERModel::LoadPositionFile(string path)
{
	LoadFiles loadFile;
	int positionCount = 0;

	if(loadFile.LoadPositionFile(path))
	{
		vector<string> componentPosition = loadFile.GetComponentPosition();

		for(unsigned int index = 0; index < components.size(); index++)
		{
			if(components.at(index)->GetType() != ComponetType::CONNECTION)
			{
				SetComponentPosition(components.at(index), componentPosition.at(positionCount));
				positionCount++;
			}
		}
		return true;
	}
	return false;
}

void ERModel::SetComponentPosition(Components *component, string componentPosition)
{
	vector<string> componentPositions = split(componentPosition, " ");
	component->SetPointX(convertor.ConvertStringToInteger(componentPositions.at(0)));
	component->SetPointY(convertor.ConvertStringToInteger(componentPositions.at(1)));
}

void ERModel::StoreCutComponents(int id)
{
	tmpCutComponents.push_back(components.at(id));
}

void ERModel::ClearCutComponents()
{
	CleartempComponents(tmpCutComponents);
}

void ERModel::ClearCopyComponents()
{
	CleartempComponents(tmpCopyComponents);
}

void ERModel::CleartempComponents(vector<Components *> &tempComponents)
{
	for(unsigned int index = 0; index < tempComponents.size(); index++)
	{
		Components *component = new NullComponent();
		tempComponents.at(index) = component;
	}
	tempComponents.clear();
}

vector<Components *> ERModel::GetCutComponents()
{
	return tmpCutComponents;
}

void ERModel::RecoveryCutComponents(vector<Components *> cutComponents)
{
	for(unsigned int index = 0; index < cutComponents.size(); index++)
	{
		unsigned int id = GetSerialNumber();
		cutComponents.at(index)->SetId(id);
		if(components.at(id)->GetId() == nullComponentId)
		{
			delete components.at(id);
		}


		//將component復原
		if(id > components.size())
		{
			components.push_back(cutComponents.at(index));
		}
		else
		{
			components.at(id) = cutComponents.at(index);
		}
	}

	for(unsigned int index = 0; index < cutComponents.size(); index++)
	{
		RecoveryConnect(components.at(cutComponents.at(index)->GetId()));
	}
	NotifyObserverRecoveryGUIComponent();
	NotifyRefreshTable();
}

void ERModel::PastebyCopyComponents()
{
	for(unsigned int index = 0; index < tmpCopyComponents.size(); index++)
	{
		unsigned int id = GetSerialNumber();
		Components *componentClone = tmpCopyComponents.at(index)->Clone();
		componentClone->SetId(id);
		if(id >= components.size())
		{
			components.push_back(componentClone);
		}
		else
		{
			components.at(id) = componentClone;
		}
		observer->UpdateComponent(id);
		NotifyRefreshTable();
	}
}

void ERModel::CopyComponents(vector<int> componentsId)
{
	tmpCopyComponents.clear();
	for(unsigned int index = 0; index < componentsId.size(); index++)
	{
		if(components.at(componentsId.at(index))->GetType().compare(ComponetType::CONNECTION) != 0)
		{
			tmpCopyComponents.push_back(components.at(componentsId.at(index)));
		}
	}
}

 void ERModel::PastebyCutComponents()
 {
	 for(unsigned int index = 0; index < tmpCutComponents.size(); index++)
	 {
		 unsigned int id = GetSerialNumber();

		 if(id >= components.size())
		 {
			 components.push_back(tmpCutComponents.at(index));
		 }
		 else
		 {
			 components.at(id) = tmpCutComponents.at(index);
		 }
		 observer->UpdateComponent(id);
		 NotifyRefreshTable();
	 }
	 tmpCutComponents.clear();
 }

 void ERModel::PasteComponent()
 {
	 //tmpCopyComponents.clear();
	 PastebyCutComponents();
	 PastebyCopyComponents();
 }

 void ERModel::DeleteConnectConnection(Components *component)
 {
	 vector<Components *> connections = component->GetConnectComponents();
	 
	 for(unsigned int index = 0; index < connections.size(); index++)
	 {
		 Components *connection = connections.at(index);
		 delete connection;
	 }
	 connections.clear();
	 component->ClearConnection();
 }

/*
vector<EntityData> ERModel::GetTables()
{
	int previousComponentId;
	vector<EntityData> entitiesData;
	vector<int> previousComponentPrimaryKeys;
	//記錄走過的Entities
	vector<bool> recordEntities(components.size(), false);

	for(unsigned int index = 0; index < components.size(); ++index)
	{
		if(recordEntities.at(index) == false && components.at(index)->GetType() == ComponetType::ENTITY)
		{
			previousComponentId = components.at(index)->GetId();
			//searchTables
		}
	}
}

void SearchTable(int previousComponentId, vector<EntityData> entitiesData, vector<int> previousComponentPrimaryKeys, vector<bool> recordEntities)
{

}*/
