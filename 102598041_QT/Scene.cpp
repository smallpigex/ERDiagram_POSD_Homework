#include "Scene.h"
#include "QDebug"

Scene::Scene(GUIPresentation *guiPresentation)
{
	this->guiPresentation = guiPresentation;
}


Scene::~Scene(void)
{
}

void Scene::mousePressEvent(QGraphicsSceneMouseEvent *mouseEvent)
{
	
	string message;
	//qDebug()<<mouseEvent->scenePos();
	guiPresentation->SetMousePoint(mouseEvent->scenePos());
	message = guiPresentation->GetStateMessage();
	

	if(message.compare(StringState::POINT_NODE_STATE) == 0)
	{
		QGraphicsScene::mousePressEvent(mouseEvent);
		//QGraphicsScene::mouseMoveEvent(mouseEvent);
	}
	else if(message.compare(StringState::CONNECT_NODE_STATE) == 0)
	{
		int id = GetSelectComponent();
		guiPresentation->SetFirstId(id);
		//qDebug() << id;
	}/*
	else if(message.compare(StringState::DELETE_STATE) == 0)
	{
		QGraphicsScene::mousePressEvent(mouseEvent);
	}*/
	guiPresentation->MousePressEvent();
}

void Scene::mouseMoveEvent(QGraphicsSceneMouseEvent *mouseEvent)
{
	//qDebug() << "aaaaaaaa";
	string message = guiPresentation->GetStateMessage();

	if(message.compare(StringState::POINT_NODE_STATE) == 0)
	{
		guiPresentation->SetMousePoint(mouseEvent->scenePos());
		QGraphicsScene::mouseMoveEvent(mouseEvent);
		update();
	}
	else if(message.compare(StringState::CONNECT_NODE_STATE) == 0)
	{
		QGraphicsScene::mouseMoveEvent(mouseEvent);
		update();
	}
	else
	{
		guiPresentation->SetMousePoint(mouseEvent->scenePos());
		QGraphicsScene::mouseMoveEvent(mouseEvent);
		//qDebug() << mouseEvent->scenePos();
		update();
	}
	guiPresentation->MoseMoveEvent();
}

void Scene::mouseReleaseEvent(QGraphicsSceneMouseEvent *mouseEvent)
{
	string message;
	message = guiPresentation->GetStateMessage();
	
	if(message.compare(StringState::POINT_NODE_STATE) == 0)
	{
		QGraphicsScene::mouseReleaseEvent(mouseEvent);
	}
	else if(message.compare(StringState::CONNECT_NODE_STATE) == 0)
	{
		int id = GetSelectComponent();
		guiPresentation->SetSecondId(id);
		//qDebug() << id;
	}
	/*
	else if(message.compare(StringState::DELETE_STATE) == 0)
	{
		int id = GetSelectedComponent();
		guiPresentation->SetDeleteComponentId(id);
		
	}*/
	else if(message.compare(StringState::PRIMARY_KEY_STATE) == 0)
	{
		int id = GetSelectComponent();
		guiPresentation->SetPrimaryKeyId(id);
		//qDebug() << id;
	}
	guiPresentation->MouseReleaseEvent();
}

int Scene::GetSelectComponent()
{
	QList<QGraphicsItem *> guiComponentImtes = QGraphicsScene::items();

	for(unsigned int index = 0; index < guiComponentImtes.size(); index++)
	{
		if(guiComponentImtes.at(index)->isUnderMouse())
		{
			return dynamic_cast<GUIComponent *>(guiComponentImtes.at(index))->GetId();
		}
	}

	return -1;
}

int Scene::GetSelectedComponent()
{
	QList<QGraphicsItem *> guiComponentImtes = QGraphicsScene::items();

	for(unsigned int index = 0; index < guiComponentImtes.size(); index++)
	{
		if(guiComponentImtes.at(index)->isSelected())
		{
			return dynamic_cast<GUIComponent *>(guiComponentImtes.at(index))->GetId();
		}
	}

	return -1;
}