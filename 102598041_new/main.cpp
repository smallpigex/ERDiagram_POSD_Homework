#include <iostream>
#include "TextUIController.h"
#include "ERModel.h"

using namespace std;

int main()
{
	ERModel *erModel = new ERModel();
	Presentation *presentation = new Presentation(erModel);
	TextUIController *controller = new TextUIController(erModel, presentation);
	do 
	{
		controller->StartEdit();
	}
	while (true);
	
	delete erModel;
	delete presentation;
	delete controller;
	system("pause");
	return 0;
}