#pragma once
#include "../102598041_QT/MainWindowObserver.h"

class MainWindowSubjectForERModel
{
public:
	MainWindowSubjectForERModel(void);
	~MainWindowSubjectForERModel(void);
	virtual void RegisterMainWindowObserver(MainWindowObserver *) = 0;
	virtual void NotifyMainWindowUpdateTable() = 0;
	virtual void NotifyRefreshTable() = 0;
};

