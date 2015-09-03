#pragma once
#include <QGraphicsScene>
#include <QGraphicsSceneMouseEvent>
#include <Qinputdialog>
#include <QGraphicsItem>
#include "GUIComponent.h"
#include "GUIPresentation.h"

class Scene : public QGraphicsScene
{
private:
	GUIPresentation *guiPresentation;

public:
	Scene(GUIPresentation *);
	~Scene(void);
	void mousePressEvent(QGraphicsSceneMouseEvent *);
	void mouseMoveEvent(QGraphicsSceneMouseEvent *);	
	void mouseReleaseEvent(QGraphicsSceneMouseEvent *);
	void ShowInputDialog();
	int GetSelectComponent();
	int GetSelectedComponent();
};

