#include "artefact.h"
#include <QDateTime>
#include <QPainter>

static int randomBetween(int low, int high)
{
    return (qrand() % ((high + 1) - low) + low);
}
Artefact::Artefact()
{
    p = new QPixmap(":/sprites/gems.png");
    aX = randomBetween(0, 1);
    aY = randomBetween(0, 1);
}

Artefact::~Artefact() {
    qDebug() << "destroy art";
}

void Artefact::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter->drawPixmap(-20,-20, *p, 40 * aX, 40 * aY, 40,40);
}

QRectF Artefact::boundingRect() const
{
    return QRectF(-20, -20, 40, 40);
}

QPainterPath Artefact::shape() const
{
    QPainterPath path;
    path.addEllipse(QRectF(-15,-15,30,30));
    return path;
}
