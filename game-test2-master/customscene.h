#ifndef CUSTOMSCENE_H
#define CUSTOMSCENE_H

#include <QObject>
#include <QGraphicsScene>
#include <QKeyEvent>
#include <QMouseEvent>
#include <QGraphicsSceneMouseEvent>
#include <QDebug>
#include <QSet>
#include <cmath>
#include <QCursor>

#include "player.h"
#include "enemy.h"

class Player;

class Enemy;

class CustomScene: public QGraphicsScene
{
    Q_OBJECT
public:
    CustomScene(QObject *parent = 0);
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event) override;
    void mousePressEvent(QGraphicsSceneMouseEvent *event) override;
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event) override;
    void keyPressEvent(QKeyEvent *event) override;
    void keyReleaseEvent(QKeyEvent *event) override;



public:
    Player *first_item;
    QList<Enemy*> enemies;
    int artifacts = 0;
    int targetArtifacts = 0;
    QList<QObject*> level;
    QList<QObject*> mainMenu;

    ~CustomScene();

signals:
    void signalTargetCoordinate(QPointF point);
    void signalKeyPressEvent(QKeyEvent *event);
};

#endif // CUSTOMSCENE_H
