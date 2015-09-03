#pragma once
class MainWindowObserver
{
public:
	MainWindowObserver(void);
	~MainWindowObserver(void);
	virtual void UpdatePointActionState(bool) = 0;
	virtual void UpdateConnectErrorMessage() = 0;
	virtual void UpdateTable() = 0;
	virtual void RefreshTable() = 0;
	virtual void UpdateDeleteActionDiable() = 0;
};

