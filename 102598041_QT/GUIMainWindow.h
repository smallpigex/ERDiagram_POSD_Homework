#pragma once
#include <QApplication>
#include <QMainWindow>
#include <QMenuBar>
#include <QObject>
#include <QAction>
#include <QToolBar>
#include <QFileDialog>
#include <QGraphicsScene>
#include <QGraphicsView>
#include "GUIPresentation.h"
#include "QTConstString.h"
#include "../102598041_new/ComponentData.h"
#include "GUIComponentManager.h"
#include "QMessageBox"
#include "../102598041_new/ERModel.h"
#include "../102598041_new/Presentation.h"
#include "../102598041_new/MessageOfConstString.h"
#include "../102598041_QT/GUIComponent.h"
#include "Scene.h"
#include <QmouseEvent>
#include <QDebug>
#include <QTableWidget>
#include <QTableWidgetItem>
#include <QDockWidget>

class GUIMainWindow : public QMainWindow, public MainWindowObserver
{
	Q_OBJECT

private:
	QMainWindow *mainWindow;
	QApplication *app;
	QAction *openFileAction;
	QAction *exitAction;
	QAction *selectAction;
	QAction *connectAction;
	QAction *deleteAction;
	QAction *undoAction;
	QAction *redoAction;
	QAction *primarykeyAction;
	QAction *addAttributeAction;
	QAction *addEntityAction;
	QAction *addRelationshipAction;
	QAction *saveFileAction;
	QAction *saveXmlFileAction;
	QAction *cutAction;
	QAction *copyAction;
	QAction *pasteAction;
	QAction *aboutAction;
	QGraphicsScene *scene;
	QGraphicsView *view;
	GUIComponentManager *guiComponentManager;
	GUIPresentation *guiPresentation;
	int height;
	int weight;
	ERModel *erModel;
	Presentation *presentation;
	QMenu *addComponentMenu;
	QMenu *fileMenu;
	QMenu *editMenu;
	QMenu *helpMenu;
	QTableWidget *tableView;
	QStringList tableHeader;
	QDockWidget *dockWidget;
	int tableColumn;
	QString columnOneTitle;
	QString columnTwoTitle;
	bool canRefreshTable;

public:
	GUIMainWindow(QApplication *,ERModel *, Presentation *);
	~GUIMainWindow(void);
	void CreateMainWindow();
	void AddAction();
	void AddMenuBar();
	void AddToolBar();
	void AddDockWidget();
	void AddGraphicView();
	void ChangeState(string);
	void DrawERDiagram();
	void Show();
	void AddGroupAction();
	void SetActionIcon();
	void UpdatePointActionState(bool);
	void UpdateDeleteActionDiable();
	void SetComponentIsSelect(bool);
	void UpdateConnectErrorMessage();
	void SetSignalAndSlot();
	void SetShortcut();
	void CreateTable();
	void RefreshTableContext();
	void RemoveTableRow();
	void UpdateTable();
	void AddDataInTable();
	void RefreshTable();
	void SetCanRefresh(bool);
	vector<int> GetSelectedComponentsId();

public slots:
	void LoadDialog();
	void ChangeComponentState();
	void PointComponent();
	void AddAttribute();
	void AddEntity();
	void AddRelationship();
	void ConnectNode();
	void DeleteComponent();
	void Undo();
	void Redo();
	void SetPrimaryKey();
	void ChangeComponentName(QTableWidgetItem *);
	void ShowAbout();
	void SaveFileDialog();
	void SaveXmlFileDialog();
	void CutComponents();
	void PasteComponents();
	void CopyComponent();
};

