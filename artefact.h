#ifndef ARTIFACT_H
#define ARTIFACT_H

#include <QObject>
#include <QGraphicsItem>
#include <QDebug>

class Artefact: public QObject, public QGraphicsItem
{
public:
    Artefact();
    void paint(QPainter *painter,
               const QStyleOptionGraphicsItem *option, QWidget *widget = nullptr) override;
    QRectF boundingRect() const override;
    QPainterPath shape() const override;
    int aX;
    int aY;
    QPixmap *p;
    ~Artefact();
};

#endif // ARTIFACT_H
