#ifndef BULLET_H
#define BULLET_H

#include <QObject>
#include <QGraphicsItem>
#include <QGraphicsEllipseItem>
#include <QTimer>
#include <QPainter>
#include <cmath>


#include "enemy.h"
#include "wall.h"
#include "customscene.h"


class CustomScene;
class Enemy;

static qreal normalizeAngle(qreal angle)
{
    while (angle < 0)
        angle += M_PI * 2 ;
    while (angle > M_PI * 2 )
        angle -= M_PI * 2 ;
    return angle;
}

class Bullet : public QObject, public QGraphicsEllipseItem
{
    Q_OBJECT
public:
    Bullet(QPointF start, QPointF end, qreal a = 0, qreal b = 0, qreal c = -2.5, qreal d = 2.5, QGraphicsItem *parent = 0);

    ~Bullet()
    {
        delete timer;
    };

public:
    int speed = 4;
    QTimer *timer;

signals:
    void deleteEnemy();

public slots:
    void slotBulletMotion();
};

#endif // BULLET_H
