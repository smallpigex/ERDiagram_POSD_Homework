#include "ComponentFactory.h"

ComponentFactory::ComponentFactory(void)
{
}


ComponentFactory::~ComponentFactory(void)
{
}

Components *ComponentFactory::CreateComponent(string componentType)
{
	//���string�O�_�ۦP�A�ۦP�hnew�X�ӫ��A
	if(componentType.compare(ComponetType::ATTRIBUTE) == 0)
	{
		return  new Attributes();
	}
	else if (componentType.compare(ComponetType::ENTITY) == 0)
	{
		return new Entity();
	}
	else if(componentType.compare(ComponetType::RELATIONSHIP) == 0)
	{
		return new Relationship();
	}
	else if(componentType.compare(ComponetType::CONNECTION) == 0)
	{
		return new Connection();
	}
	else
	{
		return new NullComponent();
	}
}