#include <QApplication>
#include <QMainWindow>
#include <QMenuBar>
#include <QAction>
#include <QToolBar>
#include "GUIMainWindow.h"
#include "../102598041_new/TextUIController.h"

int main(int argc, char *argv[])
{
	QApplication app(argc, argv);
	cout << "If input [textmode] open Command line, else open GUI" << endl;
	string input;
	cout << ">";
	getline(cin, input);
	ERModel *erModel = new ERModel();
	Presentation *presentation = new Presentation(erModel);

	if(input.compare("textmode") == 0)
	{
		TextUIController *controller = new TextUIController(erModel, presentation);
		controller->StartEdit();
		return app.exec();
	}
	else
	{
		GUIMainWindow mainWindow(&app, erModel, presentation);
		mainWindow.CreateMainWindow();
		mainWindow.Show();
		return app.exec();
	}

	delete erModel;
	delete presentation;
	return app.exec();
}
