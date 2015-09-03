#include "GUIComponentManager.h"
#include "QDebug"

GUIComponentManager::GUIComponentManager(QGraphicsScene *scene, GUIPresentation *guiPresentation)
{
	this->scene = scene;
	this->guiPresentation = guiPresentation;
	guiPresentation->RegisterObserver(this);
	x = 0;
	y = 0;
}


GUIComponentManager::~GUIComponentManager(void)
{
}

void GUIComponentManager::SetGUIComponents()
{
	int componentSize = guiPresentation->GetComponentsSize();

	for(int index = 0; index < componentSize; index++)
	{
		guiComponents.push_back(guiComponentFactory.CreateGUIComponent(guiPresentation->GetComponent(index)));
	}
}

void GUIComponentManager::DrawERDiagram()
{
	SetGUINodePosition();
	SetConnection();
}

void GUIComponentManager::SetConnection()
{
	for(unsigned int index = 0; index < guiComponents.size(); index++)
	{
		if(guiComponents.at(index)->GetType().compare(ComponetType::CONNECTION) == 0)
		{
			SetConnectionPosition(guiComponents.at(index));
		}
	}
}

void GUIComponentManager::SetGUINodePosition()
{
	for(unsigned int index = 0; index < guiComponents.size(); index++)
	{
		if(guiComponents.at(index)->GetType().compare(ComponetType::CONNECTION) != 0)
		{
			//qDebug() << guiPresentation->GetPosition(guiComponents.at(index)->GetType());
			guiComponents.at(index)->setPos(guiPresentation->GetPosition(guiComponents.at(index)->GetType()));
			guiComponents.at(index)->UpdatePoint();
		}
	}
}

void GUIComponentManager::SetConnectionPosition(GUIComponent *guiConnection)
{
	int leftNodeId = dynamic_cast<GUIConnection *>(guiConnection)->GetLeftNodeId();
	int leftGUINodeIndex = GetCurrentComponentIndex(leftNodeId);
	int rightNodeId = dynamic_cast<GUIConnection *>(guiConnection)->GetRightNodeId();
	int rightGUINodeIndex = GetCurrentComponentIndex(rightNodeId);
	QPointF leftNodePosition = guiComponents.at(leftGUINodeIndex)->pos() + guiComponents.at(leftGUINodeIndex)->boundingRect().center();
	QPointF rightNodePosition = guiComponents.at(rightGUINodeIndex)->pos() + guiComponents.at(rightGUINodeIndex)->boundingRect().center();
	dynamic_cast<GUIConnection *>(guiConnection)->SetLeftNodePosition(leftNodePosition);
	dynamic_cast<GUIConnection *>(guiConnection)->SetRightNodePosition(rightNodePosition);
	dynamic_cast<GUIConnection *>(guiConnection)->UpdateShape();
}

int GUIComponentManager::GetCurrentComponentIndex(int id)
{
	for(unsigned int index = 0; index < guiComponents.size(); index++)
	{
		if(guiComponents.at(index)->GetId() == id)
		{
			return index;
		}
	}

	return -1;
}

void GUIComponentManager::ClearGUIComponents()
{
	guiPresentation->RestPosition();
	guiComponents.clear();
}

void GUIComponentManager::UpdateNode(int index)
{
	GUIComponent *currentCreateGUIComponent = guiComponentFactory.CreateGUIComponent(guiPresentation->GetNewComponent());
	StoreGUIComponent(currentCreateGUIComponent, index);
	//qDebug() << guiComponents.at(index)->GetPosition();

	if(!CheckPoint(guiComponents.at(index)->GetPosition()))
	{
		QPointF point = guiPresentation->GetMousePoint();
		guiComponents.at(index)->setPos(point);
	}
	else
	{
		guiComponents.at(index)->setPos(guiComponents.at(index)->GetPosition());
	}
	
	guiComponents.at(index)->UpdatePoint();
	//qDebug() << guiComponents.at(index)->GetPosition();
	DrawNode(guiComponents.at(index));
	DesroyPreview();
}

bool GUIComponentManager::CheckPoint(QPoint point)
{
	QPoint errorPoint(-1,-1);

	if(errorPoint == point)
	{
		return false;
	}
	return true;
}

void GUIComponentManager::StoreGUIComponent(GUIComponent *guiComponent, int index)
{
	InsertGUIComponent(guiComponent, index);
}

void GUIComponentManager::InsertGUIComponent(GUIComponent *guiComponent, int index)
{
	for(unsigned int guiIndex = 0; guiIndex < guiComponents.size(); guiIndex++)
	{
		if(guiComponents.at(guiIndex)->GetId() > index)
		{
			guiComponents.insert(guiIndex, guiComponent);
			return;
		}
	}
	guiComponents.push_back(guiComponent);
}

void GUIComponentManager::DrawNode(GUIComponent *guiComponent)
{
	scene->addItem(guiComponent);
}

void GUIComponentManager::SetComponentMoveable(bool isMove)
{
	for(unsigned int index = 0; index < guiComponents.size(); index++)
	{
		if(guiComponents.at(index)->GetType().compare(ComponetType::CONNECTION) != 0)
		{
			guiComponents.at(index)->SetMoveable(isMove);
		}
	}
}

void GUIComponentManager::UpdateComponentMoveable(bool isMove)
{
	SetComponentMoveable(isMove);
}

void GUIComponentManager::UpdateConnectionPos()
{
	SetConnection();
	SetComponentPoint();
}

void GUIComponentManager::UpdateConnection(int index)
{
	GUIComponent *currentCreateGUIComponent = guiComponentFactory.CreateGUIComponent(guiPresentation->GetNewConnection());
	StoreGUIComponent(currentCreateGUIComponent, index);
	SetConnectionPosition(guiComponents.at(index));
	DrawNode(guiComponents.at(index));
}

void GUIComponentManager::DisplayPreview(string type)
{
	
	GUIPreviewComponentFactory previewFactory;
	previewComponent = previewFactory.CreateGUIComponent(type);
	previewComponent->setPos(guiPresentation->GetMousePoint());
	scene->addItem(previewComponent);
}

void GUIComponentManager::UpdatePreviewPos()
{
	previewComponent->setPos(guiPresentation->GetMousePoint());
}

void GUIComponentManager::DesroyPreview()
{
	for(unsigned int index = 0; index < scene->items().size(); index++)
	{
		if(dynamic_cast<GUIComponent *>(scene->items().at(index))->GetId() == tmpComponentId)
		{
			scene->removeItem(scene->items().at(index));
		}
	}
}

void GUIComponentManager::DisplayEditText()
{
	bool isOK;
	QWidget *parent = 0;
	QString text = QInputDialog::getText(parent, QTstring::INPUT_DIALOG_TITLE, QTstring::INPUT_DIALOG_CONTEXT, QLineEdit::Normal, "", &isOK);

	if(isOK)
	{
		guiPresentation->AddNode(text.toStdString());
	}
	else
	{
		guiPresentation->NotifyObserverPointActionUpdate();
	}
}

void  GUIComponentManager::DeleteGUIComponent()
{
	RemoveItem();
	RemoveGUIComponent();
}

void GUIComponentManager::RecoveryGUIComponent()
{
	int componentSize = guiPresentation->GetComponentsSize();

	for(int index = 0; index < componentSize; index++)
	{
		int id = guiPresentation->GetComponent(index)->GetId();

		if(id != -1 && !IsGUIComponentExist(id))
		{
			GUIComponent *currentCreateGUIComponent = guiComponentFactory.CreateGUIComponent(guiPresentation->GetComponent(index));
			StoreGUIComponent(currentCreateGUIComponent, index);
		}
	}

	for(unsigned int index = 0; index < guiComponents.size(); index++)
	{
		int id = guiComponents.at(index)->GetId();

		if(id != -1 && !IsGUIComponentItemExist(id))
		{
			
			if(guiComponents.at(index)->GetType().compare(ComponetType::CONNECTION) == 0)
			{
				SetConnectionPosition(guiComponents.at(index));
			}
			else
			{
				guiComponents.at(index)->setPos(guiComponents.at(index)->GetPosition());
			}
			scene->addItem(guiComponents.at(index));
		}
	}
}

bool GUIComponentManager::IsGUIComponentExist(int id)
{
	for(unsigned int index = 0; index < guiComponents.size(); index++)
	{
		if(guiComponents.at(index)->GetId() == id)
		{
			return true;
		}
	}

	return false;
}

bool GUIComponentManager::IsGUIComponentItemExist(int id)
{
	QList<QGraphicsItem *> items = scene->items(Qt::AscendingOrder);

	for(unsigned int index = 0; index < items.size(); index++)
	{
		if(dynamic_cast<GUIComponent *>(items.at(index))->GetId() == id)
		{
			return true;
		}
	}

	return false;
}

void GUIComponentManager::UpdateGUIComponentPos()
{
	QList<QGraphicsItem *> items = scene->items(Qt::AscendingOrder);

	for(unsigned int index = 0; index < items.size(); index++)
	{
		if(items.at(index)->isSelected())
		{
			dynamic_cast<GUIComponent *>(items.at(index))->UpdatePoint();
		}
	}
}

void GUIComponentManager::SetComponentPoint()
{
	QList<QGraphicsItem *> items = scene->items(Qt::AscendingOrder);

	for(unsigned int index = 0; index < items.size(); index++)
	{
		if(items.at(index)->isSelected())
		{
			dynamic_cast<GUIComponent *>(items.at(index))->UpdatePoint();
		}
	}
}

void GUIComponentManager::RemoveItem()
{
	QList<QGraphicsItem *> items = scene->items(Qt::AscendingOrder);

	for(unsigned int index = 0; index < items.length(); index++)
	{
		int id = dynamic_cast<GUIComponent *>(items.at(index))->GetId();

		if(!guiPresentation->IsComponentExist(id))
		{
			scene->removeItem(items.at(index));
		}
	}
}

void GUIComponentManager::RemoveGUIComponent()
{
	int index = 0;

	while(index < guiComponents.size())
	{
		int id = guiComponents.at(index)->GetId();

		if(!guiPresentation->IsComponentExist(id))
		{
			guiComponents.erase(guiComponents.begin() + index);
		}
		else
		{
			index++;
		}
	}
}

void GUIComponentManager::DrawPrimaryKey()
{
	for(unsigned int index = 0; index < guiComponents.size(); index++)
	{
		if(guiComponents.at(index)->GetType().compare(ComponetType::ATTRIBUTE) == 0)
		{
			dynamic_cast<GUIAttribute *>(guiComponents.at(index))->ResetPrimaryKey();
		}
	}
}

void GUIComponentManager::UpdatePrimaryKey()
{
	DrawPrimaryKey();
}

int GUIComponentManager::GetGUIComponentSize()
{
	return guiComponents.size();
}

int GUIComponentManager::GetComponentId(int index)
{
	return guiComponents.at(index)->GetId();
}

string GUIComponentManager::GetComponentType(int index)
{
	return guiComponents.at(index)->GetType();
}

string GUIComponentManager::GetComponentName(int index)
{
	return guiComponents.at(index)->GetComponentName();
}

void GUIComponentManager::UpdateComponentsName()
{
	for(unsigned int index = 0; index < guiComponents.size(); index ++)
	{
		guiComponents.at(index)->RefreshComponetName();
	}
}

void GUIComponentManager::ResetComponentsPoint()
{
	QList<QGraphicsItem *> items = scene->items(Qt::AscendingOrder);

	for(unsigned int index = 0; index < items.size(); index++)
	{
		dynamic_cast<GUIComponent *>(items.at(index))->DoResetPoint();
		items.at(index)->setPos(dynamic_cast<GUIComponent *>(items.at(index))->GetPosition());
	}
}

void GUIComponentManager::StoreOldComponentsPoint()
{
	vector<ComponentPoint> oldComponentsPoint;
	StoreComponentPoint(oldComponentsPoint);
	guiPresentation->SetOldComponentPoint(oldComponentsPoint);
}

void GUIComponentManager::StoreNewComponentsPoint()
{
	vector<ComponentPoint> newComponentsPoint;
	StoreComponentPoint(newComponentsPoint);
	guiPresentation->SetNewComponentPoint(newComponentsPoint);
}

void GUIComponentManager::StoreComponentPoint(vector<ComponentPoint> &componentsPoint)
{
	QList<QGraphicsItem *> items = scene->items(Qt::AscendingOrder);

	for(unsigned int index = 0; index < items.size(); index++)
	{
		if(items.at(index)->isSelected())
		{
			ComponentPoint componentPoint;
			componentPoint.SetId(dynamic_cast<GUIComponent *>(items.at(index))->GetId());
			componentPoint.SetPointX(items.at(index)->pos().x());
			componentPoint.SetPointY(items.at(index)->pos().y());
			componentsPoint.push_back(componentPoint);
		}
	}
}

void GUIComponentManager::UpdateComponent(int id)
{
	GUIComponent *currentCreateGUIComponent = guiComponentFactory.CreateGUIComponent(guiPresentation->GetComponent(id));
	StoreGUIComponent(currentCreateGUIComponent, id);
	//qDebug() << guiComponents.at(index)->GetPosition();

	if(!CheckPoint(guiComponents.at(id)->GetPosition()))
	{
		QPointF point = guiPresentation->GetMousePoint();
		guiComponents.at(id)->setPos(point);
	}
	else
	{
		guiComponents.at(id)->setPos(guiComponents.at(id)->GetPosition());
	}

	guiComponents.at(id)->UpdatePoint();
	//qDebug() << guiComponents.at(index)->GetPosition();
	DrawNode(guiComponents.at(id));
	ClearSelected();
}

void GUIComponentManager::ClearSelected()
{
	QList<QGraphicsItem *> items = scene->items(Qt::AscendingOrder);

	for(unsigned int index = 0; index < items.size(); index++)
	{
		if(items.at(index)->isSelected())
		{
			items.at(index)->setSelected(false);
		}
	}
}

void GUIComponentManager::ClearGUIComponent()
{
	for(unsigned int index = 0; index < guiComponents.size(); index++)
	{
		GUIComponent *tempGUIComponent = guiComponents.at(index);
		delete tempGUIComponent;
	}
	guiComponents.clear();
}

void GUIComponentManager::RemoveSceneItem()
{
	QList<QGraphicsItem *> items = scene->items(Qt::AscendingOrder);

	for(unsigned int index = 0; index < items.size(); index++)
	{
		scene->removeItem(items.at(index));
	}
}

void GUIComponentManager::ResetGUIComponents()
{
	RemoveSceneItem();
	ClearGUIComponent();
	SetGUIComponents();
	RedrawERDiagram();
}

void GUIComponentManager::RedrawERDiagram()
{
	for(unsigned int index = 0; index < guiComponents.size(); index++)
	{
		if(guiComponents.at(index)->GetType().compare(ComponetType::CONNECTION) == 0)
		{
			SetConnectionPosition(guiComponents.at(index));
		}
		else
		{
			guiComponents.at(index)->setPos(guiComponents.at(index)->GetPosition());
		}
		scene->addItem(guiComponents.at(index));
	}
}