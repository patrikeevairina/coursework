#ifndef ENEMY_H
#define ENEMY_H

#include <QObject>
#include <QDebug>
#include <QGraphicsRectItem>
#include <QGraphicsItem>
#include <QPainter>
#include <QTimer>
#include <QElapsedTimer>
#include <qrandom.h>
#include <QSoundEffect>


#include "player.h"
#include "wall.h"


class Wall;
class Player;
class Widget;

class Enemy: public QObject, public QGraphicsItem
{
    Q_OBJECT
public:
    Enemy(Player* player, Widget *widget,  QObject *parent = nullptr);
    ~Enemy();
   // void pause();
    QPainterPath shape() const override;

public:
    void shot();
signals:
    void signalGameOver();

public slots:
    void slotEnemyTimer();



protected:
    QRectF boundingRect() const override;
    void paint(QPainter *painter,
               const QStyleOptionGraphicsItem *option, QWidget *widget = nullptr) override;
private:
    QTimer *gameTimer;
    Player *player;
    Widget *w;
    qreal enemySpeed = 0.5;
    int currentFrameX = 0;
    int currentFrameY = 240;
    int currentSize = 6;
    int hp = 10;
    int maxHp = 10;

    QTimer *frameTimer;
    QElapsedTimer eTimer;
    QTimer *attackTimer;
    QSoundEffect *sound;
    bool isAttack = true;
    void nextFrame();
    QPixmap *spriteImage;
    void attack();
    void d();
    int fangle;

};

#endif // ENEMY_H
