#include "GUIComponentFactory.h"


GUIComponentFactory::GUIComponentFactory(void)
{
}


GUIComponentFactory::~GUIComponentFactory(void)
{
}

GUIComponent *GUIComponentFactory::CreateGUIComponent(Components *component)
{
	if(component->GetType().compare(ComponetType::ATTRIBUTE) == 0)
	{
		return  new GUIAttribute(component);
	}
	else if (component->GetType().compare(ComponetType::ENTITY) == 0)
	{
		return new GUIEntity(component);
	}
	else if(component->GetType().compare(ComponetType::RELATIONSHIP) == 0)
	{
		return new GUIRelationship(component);
	}
	else
	{
		return new GUIConnection(component);
	}
}
