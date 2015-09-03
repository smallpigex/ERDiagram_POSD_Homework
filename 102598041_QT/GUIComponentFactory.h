#pragma once
#include "GUIAttribute.h"
#include "GUIEntity.h"
#include "GUIComponent.h"
#include "GUIConnection.h"
#include "GUIRelationship.h"
#include "../102598041_new/Components.h"
#include "../102598041_new/MessageOfConstString.h"
#include <iostream>
#include <string>

using namespace std;

class GUIComponentFactory
{
public:
	GUIComponentFactory(void);
	~GUIComponentFactory(void);
	GUIComponent *CreateGUIComponent(Components *);
};

