#pragma once
#include "Attributes.h"
#include "Entity.h"
#include "Relationship.h"
#include "Connection.h"
#include "MessageOfConstString.h"
#include "NullComponent.h"

class ComponentFactory
{
public:
	ComponentFactory(void);
	~ComponentFactory(void);
	Components *CreateComponent(string);
};

