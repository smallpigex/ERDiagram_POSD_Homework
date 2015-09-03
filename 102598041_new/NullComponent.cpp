#include "NullComponent.h"


NullComponent::NullComponent(void)
{
	this->SetType(ComponetType::NULL_COMPONENT);
}


NullComponent::~NullComponent(void)
{
}

void NullComponent::ConnectTo(Components *component)
{
}

int NullComponent::CanConnectTo(Components *component)
{
	return 0;
}
bool NullComponent::CheckHasBeenConnect(Components *component)
{
	return 0;
}

vector<int> NullComponent::GetConnectComponentsId()
{
	vector<int> nullVector;
	return nullVector;
}

void NullComponent::DeleteConnectComponents(int)
{
}

vector<Components *>  NullComponent::GetConnectComponents()
{
	vector<Components *> nullVector;
	return nullVector;
}

void NullComponent::Save(ComponentVisitor &componentVisitor)
{
}

Components *NullComponent::Clone()
{
	Components *nullcomponent = new NullComponent();
	return nullcomponent;
}

void NullComponent::ClearConnection()
{

}