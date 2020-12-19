#include "bullet.h"

Bullet::Bullet(QPointF start, QPointF end, qreal a, qreal b, qreal c, qreal d, QGraphicsItem *parent)
    :QGraphicsEllipseItem(a, b, c, d )
{
    //this->setParentItem(parent);
    this->setPos(parent->mapToScene(parent->pos()));


    QLineF lineToTarget(start, end);
    qreal angleToTarget = ::acos(lineToTarget.dx() / lineToTarget.length());
    if (lineToTarget.dy() < 0)
    {
        angleToTarget = M_PI * 2 - angleToTarget;
    }
    angleToTarget = normalizeAngle((M_PI - angleToTarget) + M_PI / 2);


    if (angleToTarget >= 0 && angleToTarget <= M_PI)
    {
        setRotation(rotation() - angleToTarget * 180 /M_PI);
    }
    else if (angleToTarget <= M_PI * 2 && angleToTarget > M_PI)
    {
        setRotation(rotation() + (angleToTarget - M_PI * 2 )* (-180) /M_PI);
    }

    this->setPos(mapToParent(0, -40));
    timer = new QTimer();
    connect(timer, &QTimer::timeout, this, &Bullet::slotBulletMotion);

    timer->start(speed);
}

void Bullet::slotBulletMotion()
{
    this->setPos(mapToParent(0, -speed));
    QList<QGraphicsItem *> foundItems = scene()->items(
        QPolygonF() << mapToScene(0, 0)
                << mapToScene(-1, -1)
                << mapToScene(1, -1));
    for (auto item : foundItems)
    {
        if (dynamic_cast<Wall*>(item))
        {
            this->deleteLater();
        }
        else if (dynamic_cast<Enemy*>(item))
        {
            static_cast<Enemy*>(item)->shot();
            qDebug() <<"shot";

            this->deleteLater();
        }
    }

    if(x() < 0 || x() > 1280
            || y() < 0 || y() > 720)
    {
        this->deleteLater();
    }

}

