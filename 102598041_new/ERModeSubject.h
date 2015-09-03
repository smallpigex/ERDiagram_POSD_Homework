#pragma once
#include "../102598041_QT/GUIObserver.h"
#include "gtest/gtest_prod.h"

class ERModeSubject
{
public:
	ERModeSubject(void);
	~ERModeSubject(void);
	virtual void RegisterObserver(GUIObserver *) = 0;
	//virtual void RemoveObserver(GUIObserver * ) = 0;
	virtual void NotifyObserverGUIComponentUpdate() = 0;
	virtual void NotifyObserverUpateGUIConnection() = 0;
	virtual void NotifyObserverRecoveryGUIComponent() = 0;
	virtual void NotifyObserverUpdatePrimaryKey() = 0;
	virtual void NotifyObserverDeleteGUIComponent() = 0;
	virtual void NotifyObserverUpdateComponentName() = 0;
	//virtual void NotifyObserverConnectionUpdate(int, int, string) = 0;
};

