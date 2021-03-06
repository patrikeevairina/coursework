#include "shadow.h"
#include "QPainter"
#include "QRegion"
#include "QRgba64"


Shadow::Shadow( Player *player, QObject *parent)
{
    this->player = player;
    timer = new QTimer();
    connect(timer, &QTimer::timeout, this, &Shadow::slotTimer);
    timer->start(1000/60);
    this->setZValue(2);
}
Shadow::~Shadow() {
    delete timer;
}

void Shadow::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    QRadialGradient radialGrad(QPoint(player->x(), player->y()), 250);
    radialGrad.setColorAt(0, Qt::transparent);
    radialGrad.setColorAt(0.3, Qt::transparent);
    radialGrad.setColorAt(1, Qt::black);
    painter->setBrush(radialGrad);
    painter->drawRect(QRectF(0,0,1280,720));
    Q_UNUSED(option);
    Q_UNUSED(widget);
}

QRectF Shadow::boundingRect() const
{
    return QRectF(0, 0, 1280, 720);
}

void Shadow::slotTimer()
{
    update();
}
