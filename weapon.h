#ifndef WEAPON_H
#define WEAPON_H

#include <QObject>
#include <QGraphicsRectItem>
#include <QRectF>
#include <QTimer>
#include <QDebug>
#include <cmath>

#include "bullet.h"


class Weapon: public QObject, public QGraphicsRectItem
{
    Q_OBJECT
public:
    Weapon(QGraphicsItem *parent = 0);
    Weapon(qreal, qreal, qreal, qreal, QGraphicsItem *parent = 0);
    virtual ~Weapon() {};
};

#endif // WEAPON_H
