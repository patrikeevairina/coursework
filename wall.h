#ifndef WALL_H
#define WALL_H

#include <QObject>
#include <QGraphicsRectItem>
#include <QPainter>
#include <QPixmap>
#include <QDebug>


class Wall: public QObject, public QGraphicsRectItem
{
    Q_OBJECT
public:
    Wall(QGraphicsItem *parent = nullptr);

    ~Wall();
protected:
    void paint(QPainter *painter,
               const QStyleOptionGraphicsItem *option, QWidget *widget = nullptr) override;
    QRectF boundingRect() const override;
    QPainterPath shape() const override;

private:
    int _cellHeight = 40;
    int _cellWidth = 40;
    QPixmap pic;
};

#endif // WALL_H
