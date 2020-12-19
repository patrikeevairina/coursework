#ifndef SHADOW_H
#define SHADOW_H

#include <QObject>
#include <QGraphicsItem>
#include <QGraphicsRectItem>
#include "player.h"

class Shadow : public QGraphicsRectItem, public QObject
{
public:
    Shadow(Player *player, QObject *parent = 0);
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = nullptr) override;
    QRectF boundingRect() const override;
    Player *player;
    QTimer *timer;
    ~Shadow();
public slots:
    void slotTimer();
};

#endif // SHADOW_H
