#include "wall.h"

Wall::Wall(QGraphicsItem *parent)

{
    QGraphicsRectItem(0, 0, _cellWidth, _cellHeight);
    setParentItem(parent);
    pic.load(":/sprites/wall.png");
    setZValue(-1);

}
Wall::~Wall() {
    qDebug() << "destroy wall";
}

void Wall::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter->drawPixmap(boundingRect(), pic, QRectF(0,0, 40, 40));
    Q_UNUSED(option);
    Q_UNUSED(widget);
}

QRectF Wall::boundingRect() const
{
    return QRectF(0, 0, _cellWidth, _cellHeight);
}

QPainterPath Wall::shape() const
{
    QPainterPath path;
    path.addRect(boundingRect());
    return path;
}
