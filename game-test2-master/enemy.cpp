#include "enemy.h"
#include "widget.h"

#include <QApplication>
Enemy::Enemy(Player* player, Widget* widget, QObject *parent)
    : QObject(parent), QGraphicsItem()
{
    this->player = player;
    setRotation(0);

    sound = new QSoundEffect();
    sound->setSource(QUrl::fromLocalFile(":/sounds/bite.wav"));
    sound->setLoopCount(1);
    sound->setVolume(0.6);

    spriteImage = new QPixmap(":/sprites/mummy.png");
    currentSize = 8;

    gameTimer = new QTimer();
    connect(gameTimer, &QTimer::timeout, this, &Enemy::slotEnemyTimer);
    gameTimer->start(10);

    frameTimer = new QTimer();
    connect(frameTimer, &QTimer::timeout, this, &Enemy::nextFrame);
    frameTimer->start(1000/7);

    eTimer.start();
    attackTimer = new QTimer();
    connect(attackTimer, &QTimer::timeout, this, &Enemy::attack);
    attackTimer->start(100);

    setFlag(ItemIgnoresTransformations, false);
    w = widget;
    hp = maxHp = w->currentLevel * 4 + 10;
    //qDebug() << *&(static_cast<Widget*>(QApplication::allWidgets()[1]))->currentLevel;
    qDebug() << maxHp;
    Q_UNUSED(parent);
}
void Enemy::attack() {
    if (eTimer.elapsed() > frameTimer->interval() * 7 && !isAttack) {
        eTimer.restart();
        isAttack = true;
        //dangerous

        sound->setVolume(w->effectVolume);
        sound->play();
    }
}

QRectF Enemy::boundingRect() const
{
    return QRectF(-45,-60,90,120);
}

QPainterPath Enemy::shape() const
{
    QPainterPath path;
    path.addEllipse(QRectF(-45,-60,90,120));
    return path;
}

void Enemy::paint(QPainter *painter,
                  const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter->rotate(-fangle);

    if (player->x() < x())
        painter->scale(-1, 1);

    if (player->y() > y())
        painter->scale(-1, 1);

    painter->drawPixmap(-45, -60, *spriteImage, currentFrameX, currentFrameY, 90, 120);
    painter->setPen(Qt::NoPen);
    painter->setBrush(Qt::red);
    int w = 60 * hp / maxHp;
    painter->drawRect(-w / 2, -60, w,3);

    Q_UNUSED(option);
    Q_UNUSED(widget);
}

void Enemy::nextFrame()
{
    currentFrameX += 90;
    if (currentFrameX >= 90*currentSize ) currentFrameX = 0;
    this->update(boundingRect());
}

void Enemy::shot()
{
    hp -= 2;
    this->update(QRectF(-30,-60, 60, 3));
    if (hp <= 0) {
        hide();
        d();
    }
}

void Enemy::slotEnemyTimer()
{
    int angle = 0;
    QLineF lineToTarget(QPointF(0, 0), mapFromItem(player, 0, 0));
    double angleToTarget = ::acos(lineToTarget.dx() / lineToTarget.length());
    if (lineToTarget.dy() < 0)
        angleToTarget = M_PI * 2  - angleToTarget;
    angleToTarget = normalizeAngle((M_PI - angleToTarget) + M_PI_2);

    if (angleToTarget > 0 && angleToTarget < M_PI)
    {
        if(angleToTarget > M_PI / 5)
        {
            angle = -15;
        } else if(angleToTarget > M_PI / 10)
        {
            angle = -5;
        } else
        {
            angle = -1;
        }
    }
    else if (angleToTarget <=  M_PI * 2 && angleToTarget > ( M_PI * 2 - M_PI))
    {
        if(angleToTarget < ( M_PI * 2 - M_PI / 5))
        {
            angle = 15;
        }
        else if(angleToTarget < ( M_PI * 2 - M_PI / 10))
        {
            angle = 5;
        }
        else
        {
            angle = 1;
        }
    }
    else if (angleToTarget == 0)
    {
        angle = 0;
    }

    fangle = rotation() + angle;
    setRotation(fangle);

    bool f = abs(fangle) % 361 <= 270 && abs(fangle) % 361 >= 90;
    currentFrameY = f ? 0 : 120;

    currentSize = 6;
    
    if(lineToTarget.length() <= 200 && lineToTarget.length() >= 1)
    {
        currentSize = 8;
        currentFrameY = f ? 240 : 360;


        setPos(mapToParent(0, -enemySpeed));
        if (lineToTarget.length() <= 40) {
            currentSize = 7;
            currentFrameY = f ? 480 : 600;

            setPos(mapToParent(0, enemySpeed));
            QList<QGraphicsItem *> foundPlayer = scene()->items(QPolygonF()
                                                                       << mapToScene(0, 0)
                                                                       << mapToScene(-20, -20)
                                                                       << mapToScene(20, -20));
                foreach (QGraphicsItem *item, foundPlayer)
                {
                    if (item == this)
                        continue;
                    if(item == player && isAttack)
                    {
                        player->shoot();
                        isAttack = false;
                    }
                }
        }
    }



        QList<QGraphicsItem *> foundWalls = scene()->items(QPolygonF()
                                                                   << mapToScene(0, 0)
                                                                   << mapToScene(-30, -30)
                                                                   << mapToScene(30, -30));
        foreach (QGraphicsItem *item, foundWalls)
        {
            if (item == this)
                continue;
            if(dynamic_cast<Wall*>(item))
            {
               setPos(mapToParent(0, enemySpeed));
            }
        }
}

void Enemy::d() {
    delete attackTimer;
    delete frameTimer;
    delete gameTimer;
    delete sound;
}

Enemy::~Enemy()
{
    qDebug() << "destroy enemy";
}
