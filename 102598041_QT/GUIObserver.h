#pragma once
#include "gtest\gtest_prod.h"

class GUIObserver
{
public:
	GUIObserver(void);
	~GUIObserver(void);
	virtual void UpdateNode(int) = 0;
	virtual void UpdateComponentMoveable(bool) = 0;
	virtual void UpdateConnectionPos() = 0;
	virtual void UpdateConnection(int) = 0;
	virtual void UpdatePreviewPos() = 0;
	virtual void UpdateGUIComponentPos() = 0;
	virtual void DeleteGUIComponent() = 0;
	virtual void DisplayEditText() = 0;
	virtual void RecoveryGUIComponent() = 0;
	virtual void UpdatePrimaryKey() = 0;
	virtual void UpdateComponentsName() = 0;
	virtual void ResetComponentsPoint() = 0;
	virtual void StoreOldComponentsPoint() = 0;
	virtual void StoreNewComponentsPoint() = 0;
	virtual void UpdateComponent(int) = 0;
	virtual void ResetGUIComponents() = 0;
};

