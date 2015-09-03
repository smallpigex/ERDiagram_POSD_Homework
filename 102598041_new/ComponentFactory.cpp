#include "ComponentFactory.h"

ComponentFactory::ComponentFactory(void)
{
}


ComponentFactory::~ComponentFactory(void)
{
}

Components *ComponentFactory::CreateComponent(string componentType)
{
	//比較string是否相同，相同則new出該型態
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