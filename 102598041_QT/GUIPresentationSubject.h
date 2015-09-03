#pragma once
#include "GUIObserver.h"

class GUIPresentationSubject
{	
public:
	GUIPresentationSubject(void);
	~GUIPresentationSubject(void);
	virtual void RegisterObserver(GUIObserver *) = 0;
	virtual void NotifyObserverDrawGUIComponent() = 0;
	virtual void NotifyObserverGUIConnectionUpdate() = 0;
	virtual void NotifyObserverDrawGUIConnection() = 0;
	virtual void NotifyObserverConnectError() = 0;
	virtual void NotifyObserverUpdatePreviewPos() = 0;
	virtual void NotifyObserverDisplayEditText() = 0;
	virtual void NotifyObserverUpdateGUIComponent() = 0;
	virtual void NotifyObserverUpdateGUIComponentPos() = 0;
	virtual void NotifyRefreshTable() = 0;
	virtual void NotifyObserverResetPoint() = 0;
	virtual void NotifyObserverResetComponent() = 0;
};

