#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QTimer>
#include <cmath>
#include <QFile>
#include <QTextStream>
#include <QByteArray>
#include <QBitmap>
#include <QIcon>
#include <QMediaPlayer>
#include <QMap>
#include <QSlider>
#include <QPushButton>
#include <QDir>
#include <QLabel>

#include "customscene.h"
#include "bullet.h"
#include "enemy.h"
#include "shadow.h"
#include "artefact.h"

class Enemy;
class Generator;

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();
    qreal effectVolume = 1;
    int musicVolume = 100;
    int currentLevel = 0;



public slots:
    void slotShots(QPointF, QPointF);
    void slotGameOver();
    void slotKeyPressEvent(QKeyEvent *e);

private:
    QGraphicsScene *scene = nullptr;
    Generator *generator;
    CustomScene *gameScene;
    QGraphicsView *gameView;
    QGraphicsView *view;
    QTimer *timer;
    Player *player;
    Enemy *enemy;
    QSoundEffect *sound;
    QSoundEffect *sound2;
    QMediaPlayer *music;

    int _height = 720;
    int _width = 1280;

    QMap<int, bool> saves;

    void showMenu(QWidget *q);
    void hideMenu(QWidget *q);
    void hideShow(QWidget *q);
    void loadSettings();
    void saveSettings();
    void startLevel(int level = 1);

    QList<QWidget*> buttons;
    //menus...
    QWidget *buttonsMenu;
    QWidget *settingsMenu;
    QWidget *menu;
};
#endif // WIDGET_H
