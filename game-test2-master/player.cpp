#include "player.h"

Player::Player(QObject *parent)
    :QObject(parent), QGraphicsItem()
{
    setRotation(0);

    p = new QPixmap(":/sprites/player.png");

    sound = new QSoundEffect();
    sound->setSource(QUrl::fromLocalFile(":/sounds/step.wav"));
    sound->setLoopCount(-2);
    sound->setVolume(0.8);

    sound2 = new QSoundEffect();
    sound2->setSource(QUrl::fromLocalFile(":/sounds/collect.wav"));
    sound2->setLoopCount(0);
    sound2->setVolume(0.7);

    sound3 = new QSoundEffect();
    sound3->setSource(QUrl::fromLocalFile(":/sounds/success.wav"));
    sound3->setLoopCount(0);
    sound3->setVolume(0.8);

    gameTimer = new QTimer();
    connect(gameTimer, &QTimer::timeout, this, &Player::slotGameTimer);
    gameTimer->start(10);
    target = QPointF(0,0);

    bulletTimer = new QTimer();
    connect(bulletTimer, &QTimer::timeout, this, &Player::slotBulletTimer);
    bulletTimer->start(1000/6);
}


Player::~Player()
{
    qDebug() << "delete player";
    delete gameTimer;
    delete bulletTimer;
    delete sound;
    delete sound2;
    delete sound3;
}

QRectF Player::boundingRect() const
{
    return QRectF(-25,-25,50,50);
}

QPainterPath Player::shape() const
{
    QPainterPath path;
    path.addEllipse(boundingRect());
    return path;
}

void Player::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{

    painter->drawPixmap(-25,-25, *p, 0, 0, 50,50);
    painter->rotate(-rotation());
    painter->setPen(Qt::NoPen);
    painter->setBrush(Qt::red);
    int w = 50 * hp / maxHp;
    painter->drawRect(-w / 2, -50, w,3);

    Q_UNUSED(option);
    Q_UNUSED(widget);
}

void Player::slotGameTimer()
{

    QList<QGraphicsItem*> collidings = scene()->collidingItems(this);
    if (!keysPressed.empty())
    {
        qreal x;
        qreal y;
        for (auto key: keysPressed)
        {
            switch(key)
            {
            case Qt::Key::Key_A:
            case Qt::Key::Key_Left:
                x = this->scenePos().x();
                y = this->scenePos().y();
                moveBy(-playerSpeed, 0);
                if(!collides(x,y))
                    moveBy(playerSpeed, 0);
                break;
            case Qt::Key::Key_Down:
            case Qt::Key::Key_S:
                x = this->scenePos().x();
                y = this->scenePos().y();
                moveBy(0, playerSpeed);
                if(!collides(x,y))
                    moveBy(0, -playerSpeed);
                break;
            case Qt::Key::Key_Right:
            case Qt::Key::Key_D:
                x = this->scenePos().x();
                y = this->scenePos().y();
                moveBy(playerSpeed, 0);
                if(!collides(x,y))
                    moveBy(-playerSpeed, 0);
                break;
            case Qt::Key::Key_W:
            case Qt::Key::Key_Up:
                x = this->scenePos().x();
                y = this->scenePos().y();
                moveBy(0, -playerSpeed);
                if(!collides(x,y))
                    moveBy(0, playerSpeed);
                break;
            }

        }
    } else {
        sound->stop();
    }

    playerRotation();
}

bool Player::collides( qreal x, qreal y)
{
    if (!sound->isPlaying()){
        sound->play();
    }

    for (auto item:  scene()->collidingItems(this))
    {
        if (dynamic_cast<Wall*>(item))
        {
            setPos(x,y);
            return false;
        }
        if (dynamic_cast<Artefact*>(item))
        {
            auto s = static_cast<CustomScene*>(scene());
            s->targetArtifacts--;

            if (s->targetArtifacts == 0)
            {
                sound3->play();
                qDebug() << "you gay";
                signalWin();

            }
            else
            {
                sound2->play();
                item->hide();
            }

        }

    }
    return true;
}

void Player::shoot()
{
    hp -= 2;
    this->update(QRectF(-25,-50, 50, 3));
    if (hp <= 0)
    {
        signalGameOver();
        qDebug() << "gay over";
    }
}

void Player::slotTarget(QPointF point)
{
    target = point;
    playerRotation();
}

void Player::slotBulletTimer()
{
    if (shot)
    {
        signalBullet(QPointF(this->x(),this->y()), target);
    }
}

void Player::playerRotation()
{
    QLineF lineToTarget(QPointF(0, 0), mapFromScene(target));
    qreal angleToTarget = ::acos(lineToTarget.dx() / lineToTarget.length());
    if (lineToTarget.dy() < 0)
        angleToTarget = M_PI * 2  - angleToTarget;
    angleToTarget = normalizeAngle((M_PI - angleToTarget) + M_PI_2);

    if (angleToTarget >= 0 && angleToTarget < M_PI)
    {
        setRotation(rotation() - angleToTarget * 180 /M_PI);
    }
    else if (angleToTarget <= M_PI * 2  && angleToTarget > M_PI)
    {
        setRotation(rotation() + (angleToTarget - M_PI * 2  )* (-180) /M_PI);
    }
}
