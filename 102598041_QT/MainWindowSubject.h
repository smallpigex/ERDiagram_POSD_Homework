#pragma once
#include "MainWindowObserver.h"

class MainWindowSubject
{
public:
	MainWindowSubject(void);
	~MainWindowSubject(void);
	virtual void RegisterMainWindowObserver(MainWindowObserver *) = 0;
	virtual void NotifyObserverPointActionUpdate() = 0;
	virtual void NotifyObserverConnectError() = 0;
	virtual void NotifyObserverDeleteActionUpdate() = 0;
};

