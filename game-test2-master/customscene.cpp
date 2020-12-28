#include "customscene.h"

CustomScene::CustomScene(QObject *parent)
    :QGraphicsScene(parent) {}
CustomScene::~CustomScene() {}

void CustomScene::keyPressEvent(QKeyEvent *event)
{
    first_item->keysPressed += event->key();
    signalKeyPressEvent(event);
}

void CustomScene::keyReleaseEvent(QKeyEvent *event)
{
    first_item->keysPressed -= event->key();
}

void CustomScene::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    signalTargetCoordinate(event->scenePos());
}

void CustomScene::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    if (event->button() == Qt::MouseButton::LeftButton)
    first_item->shot = true;
}

void CustomScene::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    first_item->shot = false;
    Q_UNUSED(event);
}
