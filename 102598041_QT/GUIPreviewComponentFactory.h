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

class GUIPreviewComponentFactory
{
public:
	GUIPreviewComponentFactory(void);
	~GUIPreviewComponentFactory(void);
	GUIComponent *CreateGUIComponent(string);
};

