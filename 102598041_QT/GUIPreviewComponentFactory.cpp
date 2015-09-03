#include "GUIPreviewComponentFactory.h"


GUIPreviewComponentFactory::GUIPreviewComponentFactory(void)
{
}


GUIPreviewComponentFactory::~GUIPreviewComponentFactory(void)
{
}

GUIComponent *GUIPreviewComponentFactory::CreateGUIComponent(string type)
{
	if(type.compare(ComponetType::ATTRIBUTE) == 0)
	{
		return  new GUIAttribute();
	}
	else if (type.compare(ComponetType::ENTITY) == 0)
	{
		return new GUIEntity();
	}
	else if(type.compare(ComponetType::RELATIONSHIP) == 0)
	{
		return new GUIRelationship();
	}
	else
	{
		return new GUIConnection();
	}
}
