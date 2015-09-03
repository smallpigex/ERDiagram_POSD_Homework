#include "GUIMainWindow.h"


GUIMainWindow::GUIMainWindow(QApplication *app, ERModel *erModel, Presentation *presentation)
{
	mainWindow = new QMainWindow();
	this->app = app;
	height = 600;
	weight = 800;
	this->erModel = erModel;
	erModel->RegisterMainWindowObserver(this);
	this->presentation = presentation;
	guiPresentation = new GUIPresentation(presentation);
	guiPresentation->RegisterMainWindowObserver(this);
	scene = new Scene(guiPresentation);
	connect(scene, SIGNAL(selectionChanged()), this, SLOT(ChangeComponentState()));
	guiComponentManager = new GUIComponentManager(scene, guiPresentation);
	erModel->RegisterObserver(guiComponentManager);
	tableColumn = 2;
	columnOneTitle = "Type";
	columnTwoTitle = "Text";
	canRefreshTable = false;
}


GUIMainWindow::~GUIMainWindow(void)
{
	delete openFileAction;
	delete exitAction;
	delete selectAction;
	delete connectAction;
	delete deleteAction;
	delete undoAction;
	delete redoAction;
	delete primarykeyAction;
	delete addAttributeAction;
	delete addEntityAction;
	delete addRelationshipAction;
	delete fileMenu;
	delete addComponentMenu;
	delete scene;
	delete guiComponentManager;
	delete presentation;
	//delete erModel;
	delete view;
	delete mainWindow;
}

void GUIMainWindow::CreateMainWindow()
{
	mainWindow->setMinimumSize(weight, height);
	mainWindow->setWindowTitle(QTstring::TITLE);
	AddAction();
	SetShortcut();	
	SetActionIcon();
	AddGroupAction();
	AddMenuBar();
	AddToolBar();
	AddGraphicView();
	CreateTable();
	SetSignalAndSlot();
}

void GUIMainWindow::LoadDialog()
{
	string format = ".erd";
	string pointFormat = ".pos";
	QString fileName = QFileDialog::getOpenFileName(this, 
													QTstring::LOAD_DIALOG_TITLE,
		                                            QTstring::FILES_PATH, 
													QTstring::FILES_OF_TYPE
													);

	if (!fileName.isEmpty())
	{
		string path = fileName.toStdString();
		string positionFilePath = path.replace(path.find(format), format.length(), pointFormat);
		scene->clear();
		guiComponentManager->ClearGUIComponents();
		guiPresentation->LoadFile(fileName.toStdString());
		guiComponentManager->DesroyPreview();
		selectAction->setChecked(true);

		if(presentation->LoadPositionFile(path))
		{
			guiComponentManager->ResetComponentsPoint();
		}
		else
		{
			DrawERDiagram();
		}
	}
}

void GUIMainWindow::AddAction()
{
	openFileAction = new QAction(QTstring::OPEN, this);
	exitAction = new QAction(QTstring::EXIT, this);
	selectAction = new QAction(QTstring::SELECT, this);
	selectAction->setCheckable(true);
	selectAction->setChecked(true);	
	connectAction = new QAction(QTstring::CONNECT, this);
	connectAction->setCheckable(true);	
	addAttributeAction = new QAction(QTstring::ADD_ATTRIBUTE, this);
	addAttributeAction->setCheckable(true);
	addEntityAction = new QAction(QTstring::ADD_ENTITY, this);
	addEntityAction->setCheckable(true);	
	addRelationshipAction = new QAction(QTstring::ADD_RELATIONSHIP, this);
	addRelationshipAction->setCheckable(true);	
	deleteAction = new QAction(QTstring::DELETE_COMPONENT, this);
	deleteAction->setDisabled(true);
	undoAction = new QAction(QTstring::UNDO, this);
	redoAction = new QAction(QTstring::REDO, this);
	primarykeyAction = new QAction(QTstring::PRIMARYKEY, this);
	primarykeyAction->setCheckable(true);
	saveFileAction = new QAction(QTstring::SAVE_FILE, this);
	saveXmlFileAction = new QAction(QTstring::SAVE_Xml_FILE, this);
	cutAction = new QAction(QTstring::CUT, this);
	cutAction->setDisabled(false);
	copyAction = new QAction(QTstring::COPY, this);
	copyAction->setDisabled(false);
	pasteAction = new QAction(QTstring::PASTE, this);
	pasteAction->setDisabled(false);
	aboutAction = new QAction(QTstring::ABOUT, this);
}

void GUIMainWindow::SetShortcut()
{
	openFileAction->setShortcut(Qt::CTRL + Qt::Key_O);
	saveFileAction->setShortcut(Qt::CTRL + Qt::Key_S);
	exitAction->setShortcut(Qt::CTRL + Qt::Key_E);	
	undoAction->setShortcut(Qt::CTRL + Qt::Key_Z);
	cutAction->setShortcut(Qt::CTRL + Qt::Key_X);
	copyAction->setShortcut(Qt::CTRL + Qt::Key_C);
	pasteAction->setShortcut(Qt::CTRL + Qt::Key_V);
	redoAction->setShortcut(Qt::CTRL + Qt::Key_Y);
	deleteAction->setShortcut(Qt::Key_Delete);
}

void GUIMainWindow::SetSignalAndSlot()
{
	QObject::connect(openFileAction, SIGNAL(triggered()), this, SLOT(LoadDialog()));
	QObject::connect(exitAction, SIGNAL(triggered()), app, SLOT(quit()));
	QObject::connect(selectAction, SIGNAL(triggered()), this, SLOT(PointComponent()));
	QObject::connect(connectAction, SIGNAL(triggered()), this, SLOT(ConnectNode()));
	QObject::connect(addAttributeAction, SIGNAL(triggered()), this, SLOT(AddAttribute()));
	QObject::connect(addEntityAction, SIGNAL(triggered()), this, SLOT(AddEntity()));
	QObject::connect(addRelationshipAction, SIGNAL(triggered()), this, SLOT(AddRelationship()));
	QObject::connect(deleteAction, SIGNAL(triggered()), this, SLOT(DeleteComponent()));
	QObject::connect(undoAction, SIGNAL(triggered()), this, SLOT(Undo()));
	QObject::connect(redoAction, SIGNAL(triggered()), this, SLOT(Redo()));
	QObject::connect(primarykeyAction, SIGNAL(triggered()), this, SLOT(SetPrimaryKey()));
	QObject::connect(tableView, SIGNAL(itemChanged(QTableWidgetItem *)), this, SLOT(ChangeComponentName(QTableWidgetItem *)));
	QObject::connect(aboutAction, SIGNAL(triggered()), this, SLOT(ShowAbout()));
	QObject::connect(saveFileAction, SIGNAL(triggered()), this, SLOT(SaveFileDialog()));
	QObject::connect(saveXmlFileAction, SIGNAL(triggered()), this, SLOT(SaveXmlFileDialog()));
	QObject::connect(cutAction, SIGNAL(triggered()), this, SLOT(CutComponents()));
	QObject::connect(copyAction, SIGNAL(triggered()), this, SLOT(CopyComponent()));
	QObject::connect(pasteAction, SIGNAL(triggered()), this, SLOT(PasteComponents()));
}

void GUIMainWindow::SetActionIcon()
{
	openFileAction->setIcon(QIcon("Icon/open.png"));
	exitAction->setIcon(QIcon("Icon/exit.png"));
	selectAction->setIcon(QIcon("Icon/select.png"));
	connectAction->setIcon(QIcon("Icon/connection.png"));
	addAttributeAction->setIcon(QIcon("Icon/attribute.png"));
	addEntityAction->setIcon(QIcon("Icon/entity.png"));
	addRelationshipAction->setIcon(QIcon("Icon/relationship.png"));
	deleteAction->setIcon(QIcon("Icon/delete.png"));
	undoAction->setIcon(QIcon("Icon/undo.png"));
	redoAction->setIcon(QIcon("Icon/redo.png"));
	primarykeyAction->setIcon(QIcon("Icon/primary_key.png"));
	saveFileAction->setIcon(QIcon("Icon/save.png"));
	cutAction->setIcon(QIcon("Icon/cut.png"));
	copyAction->setIcon(QIcon("Icon/copy.png"));
	pasteAction->setIcon(QIcon("Icon/paste.png"));
}

void GUIMainWindow::AddGroupAction()
{
	QActionGroup *groupAction = new QActionGroup(this);
	groupAction->addAction(selectAction);
	groupAction->addAction(connectAction);
	groupAction->addAction(addAttributeAction);
	groupAction->addAction(addEntityAction);
	groupAction->addAction(addRelationshipAction);
	groupAction->addAction(deleteAction);
	groupAction->addAction(primarykeyAction);
	groupAction->setExclusive(true);
}

void GUIMainWindow::AddMenuBar()
{
	 fileMenu = new QMenu(QTstring::FILE);
	 fileMenu->addAction(openFileAction);
	 fileMenu->addAction(saveFileAction);
	 fileMenu->addAction(saveXmlFileAction);
	 fileMenu->addAction(exitAction);
	 mainWindow->menuBar()->addMenu(fileMenu);
	 addComponentMenu = new QMenu(QTstring::ADD);
	 addComponentMenu->addAction(selectAction);
	 addComponentMenu->addAction(connectAction);
	 addComponentMenu->addAction(addAttributeAction);
	 addComponentMenu->addAction(addEntityAction);
	 addComponentMenu->addAction(addRelationshipAction);
	 mainWindow->menuBar()->addMenu(addComponentMenu);
	 editMenu = new QMenu(QTstring::EDIT);
	 editMenu->addAction(undoAction);
	 editMenu->addAction(redoAction);
	 editMenu->addAction(deleteAction);
	 editMenu->addAction(cutAction);
	 editMenu->addAction(copyAction);
	 editMenu->addAction(pasteAction);
	 mainWindow->menuBar()->addMenu(editMenu);
	 helpMenu = new QMenu(QTstring::HELP);
	 helpMenu->addAction(aboutAction);
	 mainWindow->menuBar()->addMenu(helpMenu);
}

void GUIMainWindow::AddToolBar()
{
	QToolBar *toolBar = new QToolBar(QTstring::QTOOLBAR);
	toolBar->addAction(openFileAction);
	toolBar->addAction(saveFileAction);
	toolBar->addAction(exitAction);
	QToolBar *erModeltoolBar = new QToolBar(QTstring::QTOOLBAR);
	erModeltoolBar->addAction(undoAction);
	erModeltoolBar->addAction(redoAction);
	erModeltoolBar->addSeparator();
	erModeltoolBar->addAction(deleteAction);
	erModeltoolBar->addSeparator();
	erModeltoolBar->addAction(cutAction);
	erModeltoolBar->addSeparator();
	erModeltoolBar->addAction(copyAction);
	erModeltoolBar->addSeparator();
	erModeltoolBar->addAction(pasteAction);
	erModeltoolBar->addSeparator();
	erModeltoolBar->addAction(selectAction);
	erModeltoolBar->addAction(connectAction);
	erModeltoolBar->addSeparator();
	erModeltoolBar->addAction(addAttributeAction);
	erModeltoolBar->addAction(addEntityAction);
	erModeltoolBar->addAction(addRelationshipAction);
	erModeltoolBar->addSeparator();
	erModeltoolBar->addAction(primarykeyAction);
	mainWindow->addToolBar(toolBar);
	mainWindow->addToolBar(erModeltoolBar);
}

void GUIMainWindow::AddGraphicView()
{
	view = new QGraphicsView();
	view->setScene(scene);
	view->setAlignment(Qt::AlignLeft | Qt::AlignTop);
	view->setMouseTracking(true);
	mainWindow->setCentralWidget(view);
}

void GUIMainWindow::ChangeComponentState()
{
	QList<QGraphicsItem *> items = scene->items();

	for(unsigned int index = 0; index < items.size(); index++)
	{
		if(!items.at(index)->isSelected())
		{
			dynamic_cast<GUIComponent *>(items.at(index))->mousePressed = false;
		}
	}
}

void GUIMainWindow::DrawERDiagram()
{
	//guiComponentManager->SetGUIComponents();
	guiComponentManager->DrawERDiagram();
	PointComponent();
}

void GUIMainWindow::Show()
{
	scene->update();
	view->update();
	mainWindow->show();
}

void GUIMainWindow::ChangeState(string state)
{
	guiPresentation->ChangeState(state);
}

void GUIMainWindow::PointComponent()
{
	ChangeState(StringState::POINT_NODE_STATE);
	guiComponentManager->SetComponentMoveable(true);
	guiComponentManager->DesroyPreview();
}

void GUIMainWindow::AddAttribute()
{
	ChangeState(StringState::ADD_NODE_STATE);
	guiPresentation->SetNodeType(ComponetType::ATTRIBUTE);
	SetComponentIsSelect(false);
	guiComponentManager->DesroyPreview();
	guiComponentManager->DisplayPreview(ComponetType::ATTRIBUTE);
	//guiPresentation->MousePressEvent();
}

void GUIMainWindow::AddEntity()
{
	ChangeState(StringState::ADD_NODE_STATE);
	guiPresentation->SetNodeType(ComponetType::ENTITY);
	SetComponentIsSelect(false);
	guiComponentManager->DesroyPreview();
	guiComponentManager->DisplayPreview(ComponetType::ENTITY);
}

void GUIMainWindow::AddRelationship()
{
	ChangeState(StringState::ADD_NODE_STATE);
	guiPresentation->SetNodeType(ComponetType::RELATIONSHIP);
	SetComponentIsSelect(false);
	guiComponentManager->DesroyPreview();
	guiComponentManager->DisplayPreview(ComponetType::RELATIONSHIP);
}

void GUIMainWindow::ConnectNode()
{
	ChangeState(StringState::CONNECT_NODE_STATE);
	SetComponentIsSelect(false);
	guiComponentManager->DesroyPreview();
}

void GUIMainWindow::UpdatePointActionState(bool checked)
{
	selectAction->setChecked(checked);
	guiComponentManager->DesroyPreview();
}

void GUIMainWindow::SetComponentIsSelect(bool isSelect)
{
	QList<QGraphicsItem *> items = scene->items();

	for(unsigned int index = 0; index < items.size(); index++)
	{
		if(items.at(index)->isSelected())
		{
			items.at(index)->setSelected(isSelect);
		}
	}
}

void GUIMainWindow::UpdateConnectErrorMessage()
{
	QMessageBox::warning(NULL, "Warning", "Error", QMessageBox::Ok);
}

void GUIMainWindow::DeleteComponent()
{
	//ChangeState(StringState::DELETE_STATE);
	QList<QGraphicsItem *> items = scene->items(Qt::AscendingOrder);

	for(unsigned int index = 0; index < items.size(); index++)
	{
		if(items.at(index)->isSelected() && guiPresentation->IsComponentExist(dynamic_cast<GUIComponent *>(items.at(index))->GetId()))
		{
			guiPresentation->DeleteComponent(dynamic_cast<GUIComponent *>(items.at(index))->GetId());
		}
	}

	deleteAction->setDisabled(true);
	guiComponentManager->DesroyPreview();
}
void GUIMainWindow::UpdateDeleteActionDiable()
{
	QList<QGraphicsItem *> items = scene->items();

	for(unsigned int index = 0; index < items.size(); index++)
	{
		if(items.at(index)->isSelected())
		{
			deleteAction->setDisabled(false);
			return;
		}
	}

	deleteAction->setDisabled(true);
}

void GUIMainWindow::Undo()
{
	guiComponentManager->DesroyPreview();

	if(!guiPresentation->Undo())
	{
		//QMessageBox::warning(NULL, "Warning", "Error", QMessageBox::Ok);
	}
}

void GUIMainWindow::Redo()
{
	guiComponentManager->DesroyPreview();
	
	if(!guiPresentation->Redo())
	{

	}
}

void GUIMainWindow::SetPrimaryKey()
{
	ChangeState(StringState::PRIMARY_KEY_STATE);
	guiComponentManager->DesroyPreview();
}

void GUIMainWindow::CreateTable()
{
	tableView = new QTableWidget(guiComponentManager->GetGUIComponentSize(), tableColumn, mainWindow);
	tableHeader << columnOneTitle << columnTwoTitle;
	tableView->setHorizontalHeaderLabels(tableHeader);
	dockWidget = new QDockWidget("Component", mainWindow);
	dockWidget->setWidget(tableView);
	mainWindow->addDockWidget(Qt::RightDockWidgetArea, dockWidget);
}

void GUIMainWindow::RefreshTableContext()
{
	//tableView->clear();
	RemoveTableRow();

	for(int index = 0; index < guiComponentManager->GetGUIComponentSize(); index++)
	{
		int rowCount = tableView->rowCount();
		int id = guiComponentManager->GetComponentId(index);
		string type = guiComponentManager->GetComponentType(index);
		string name = guiComponentManager->GetComponentName(index);
		QTableWidgetItem *itemOfType = new QTableWidgetItem(QString::fromStdString(type));
		itemOfType->setFlags(itemOfType->flags() & ~Qt::ItemIsEditable);
		QTableWidgetItem *itemOfName = new QTableWidgetItem(QString::fromStdString(name));
		itemOfName->setWhatsThis(QString::number(id));
		tableView->insertRow(rowCount);
		tableView->setItem(rowCount, 0, itemOfType);
		tableView->setItem(rowCount, 1, itemOfName);
	}
}

void GUIMainWindow::UpdateTable()
{
	AddDataInTable();
}

void GUIMainWindow::RemoveTableRow()
{
	for(int index = tableView->rowCount(); index >= 0; index--)
	{
		tableView->removeRow(index);
	}
}

void GUIMainWindow::AddDataInTable()
{
	int index = tableView->rowCount();
	int id = guiComponentManager->GetComponentId(index);
	string type = guiComponentManager->GetComponentType(index);
	string name = guiComponentManager->GetComponentName(index);
	QTableWidgetItem *itemOfType = new QTableWidgetItem(QString::fromStdString(type));
	itemOfType->setFlags(itemOfType->flags() & ~Qt::ItemIsEditable & ~Qt::ItemIsSelectable);
	QTableWidgetItem *itemOfName = new QTableWidgetItem(QString::fromStdString(name));
	itemOfName->setWhatsThis(QString::number(id));
	tableView->insertRow(index);
	tableView->setItem(index, 0, itemOfType);
	tableView->setItem(index, 1, itemOfName);
}

void GUIMainWindow::RefreshTable()
{
	RefreshTableContext();
}

void GUIMainWindow::ChangeComponentName(QTableWidgetItem *tableItem)
{
	if(tableItem->isSelected())
	{
		guiPresentation->SetComponentName(tableItem->whatsThis().toInt(), tableItem->text().toStdString());
	}
}

void GUIMainWindow::SetCanRefresh(bool canRefreshTable)
{
	this->canRefreshTable = canRefreshTable;
}

void GUIMainWindow::ShowAbout()
{
	 QMessageBox::about(NULL, AboutContext::TOOL_NAME, AboutContext::TOOL_NAME + "\n" 
		 + AboutContext::VERSION + "\n" + AboutContext::AUTHOR);
}

void GUIMainWindow::SaveFileDialog()
{
	QString path = QFileDialog::getSaveFileName(this, 
													QTstring::LOAD_DIALOG_TITLE,
		                                            QTstring::FILES_PATH, 
													QTstring::FILES_OF_TYPE
													);
	if(presentation->SaveFile(path.toStdString()))
	{
		view->update();
	}
}

void GUIMainWindow::SaveXmlFileDialog()
{
	QString path = QFileDialog::getSaveFileName(this, 
													QTstring::LOAD_DIALOG_TITLE,
		                                            QTstring::FILES_PATH, 
													tr("Xml Files (.xml)")
													);
	if(presentation->SaveXmlFile(path.toStdString()))
	{
		view->update();
	}
}

void GUIMainWindow::CutComponents()
{
	vector<int> cutComponentsId = GetSelectedComponentsId();

	if(cutComponentsId.size() > 0)
	{
		presentation->CutComponent(cutComponentsId);
	}
}

void GUIMainWindow::PasteComponents()
{
	presentation->PasteComponents();
}

void GUIMainWindow::CopyComponent()
{
	vector<int> copyComponentsId = GetSelectedComponentsId();

	if(copyComponentsId.size() > 0)
	{
		presentation->CopyComponent(copyComponentsId);
	}
}

vector<int> GUIMainWindow::GetSelectedComponentsId()
{
	QList<QGraphicsItem *> items = scene->items(Qt::AscendingOrder);
	vector<int> componentsId;

	for(unsigned int index = 0; index < items.size(); index++)
	{
		if(items.at(index)->isSelected() && guiPresentation->IsComponentExist(dynamic_cast<GUIComponent *>(items.at(index))->GetId()))
		{
			componentsId.push_back(dynamic_cast<GUIComponent *>(items.at(index))->GetId());
		}
	}
	return componentsId;
}