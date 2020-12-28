#ifndef PLAYER_H
#define PLAYER_H

#include <QGraphicsItem>
#include <QPainter>
#include <QObject>
#include <QDebug>
#include <QGraphicsScene>
#include <QTimer>
#include <cmath>
#include <QSound>
#include <QMediaPlayer>
#include <QMediaPlaylist>
#include <QSoundEffect>

#include "weapon.h"
#include "wall.h"
#include "artefact.h"
#include <QGraphicsWidget>

class Wall;

class Weapon;

class Player: public QObject, public QGraphicsItem
{
    Q_OBJECT
    Q_INTERFACES(QGraphicsItem)
public:
    Player(QObject *parent = 0);
    ~Player();
    QPainterPath shape() const override;
    bool collides(qreal, qreal);
    void shoot();

signals:
    void signalBullet(QPointF, QPointF);
    void signalWin();
    void signalGameOver();


public slots:
    void slotGameTimer();
    void slotTarget(QPointF point);
    void slotBulletTimer();


public:
    qreal playerSpeed = 1;
    QSet<int> keysPressed;
    Weapon *weapon;
    QPointF target;
    bool shot = 0;
    bool _win = 0;
    int hp = 10;
    int maxHp = 10;
    QSoundEffect *sound;
    QSoundEffect *sound2;
    QSoundEffect *sound3;
    QRectF boundingRect() const override;
protected:
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = nullptr) override;
    void playerRotation();

private:
    QTimer *gameTimer;
    QTimer *bulletTimer;
    QPixmap *p;


};

#endif // PLAYER_H
