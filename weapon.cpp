#include "weapon.h"

Weapon::Weapon(QGraphicsItem *parent)
{
    setParentItem(parent);
}

Weapon::Weapon(qreal x, qreal y, qreal z, qreal w, QGraphicsItem *parent)
    :QGraphicsRectItem(x, y, z, w)
{
    setParentItem(parent);
}



