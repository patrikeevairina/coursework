#include "widget.h"
#include "generator.h"


Widget::Widget(QWidget *parent)
    : QWidget(parent)
{
    this->resize(_width,_height);
    this->setMouseTracking(true);
    this->setFocusPolicy(Qt::StrongFocus);
    loadSettings();

    QMediaPlaylist *playlist = new QMediaPlaylist();
    playlist->addMedia(QUrl("qrc:/sounds/game.mp3"));
    playlist->setPlaybackMode(QMediaPlaylist::Loop);

    music = new QMediaPlayer();
    music->setPlaylist(playlist);
    music->setVolume(musicVolume);
    music->play();

    gameScene = new CustomScene(this);

    sound = new QSoundEffect();
    sound->setSource(QUrl::fromLocalFile(":/sounds/shot.wav"));
    sound->setLoopCount(1);
    sound->setVolume(effectVolume);

    sound2 = new QSoundEffect();
    sound2->setSource(QUrl::fromLocalFile(":/sounds/failure.wav"));
    sound2->setLoopCount(1);
    sound2->setVolume(effectVolume);


    gameView = new QGraphicsView(gameScene);
    gameView->setRenderHint(QPainter::Antialiasing);
    gameView->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    gameView->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    gameView->resize(_width, _height);
    gameView->setFixedSize(_width, _height);
    gameView->setStyleSheet("background-color: #625248");
    gameView->setMouseTracking(true);
    gameView->show();

    player = new Player();
    player->weapon = new Weapon(-3, -10, 5, -15, *&player);
    player->setPos(1080, 620);
    gameScene->addItem(new Shadow(player));
    gameScene->addItem(player);
    gameScene->first_item = player;



    auto qPushButtonStyleSheet = "QPushButton{"
                                 "color: white;"
                                 "background-color: rgb(60, 60, 60);"
                                 "border-radius: 4px transparent;"
                                 "border-bottom: 3px transparent;"
                                 "border-right: 2px transparent;"
                                 "border-left: 2px transparent;}"
                                 "QPushButton:hover{"
                                 "background-color: rgb(255,130,00);} "
                                 "QPushButton:pressed  {"
                                 "background-color: rgb(232,95,76); } ";

    auto qSliderStyleSheet = "QSlider::groove:horizontal {"
                                "border: 1px solid #999999;"
                                "height: 8px;"
                                "background: qlineargradient(x1:0, y1:0, x2:0, y2:1, stop:0 #B1B1B1, stop:1 #c4c4c4);"
                                "margin: 2px 0;"
                            "}"
                            "QSlider::handle:horizontal {"
                                "background: qlineargradient(x1:0, y1:0, x2:1, y2:1, stop:0 #b4b4b4, stop:1 #8f8f8f);"
                                "border: 1px solid #5c5c5c;"
                                "width: 18px;"
                                "margin: -2px 0;"
                                "border-radius: 3px;"
                            "}";

    //mainMenu
    menu = new QWidget(gameView);
    menu->setGeometry(20, 20, 170, 90);
    menu->setStyleSheet("QWidget {background-color: rgb(88,88,88);}");
    menu->show();

    auto *b1 = new QPushButton(QString("Уровни"), menu);
    connect(b1, &QPushButton::clicked, [=]()
    {
        hideShow(buttonsMenu);
        if (!settingsMenu->isHidden())
            hideMenu(settingsMenu);
    });
    b1->setGeometry(10, 10, 150, 20);
    b1->setStyleSheet(qPushButtonStyleSheet);
    b1->show();

    auto *b2 = new QPushButton(QString("Настройки"), menu);
    connect(b2, &QPushButton::clicked, [=]()
    {
        hideShow(settingsMenu);
        if (!buttonsMenu->isHidden())
            hideMenu(buttonsMenu);
    });
    b2->setGeometry(10, 35, 150, 20);
    b2->setStyleSheet(qPushButtonStyleSheet);
    b2->show();

    auto *b3 = new QPushButton(QString("Выход"), menu);
    connect(b3, &QPushButton::clicked, [=]()
    {
        exit(0);
    });
    b3->setGeometry(10, 60, 150, 20);
    b3->setStyleSheet(qPushButtonStyleSheet);
    b3->show();


    //settingsMenu
    settingsMenu = new QWidget(gameView);
    settingsMenu->setGeometry(200, 20, 140, 85);
    settingsMenu->setStyleSheet("QWidget {background-color: rgb(88,88,88);}");

    auto *q1 = new QLabel(QString("Громкость музыки: "), settingsMenu);
    q1->setGeometry(10, 10, 120, 10);
    q1->setStyleSheet("QLabel {color: rgb(255,255,255);}");
    q1->show();

    auto *q2 = new QLabel(QString("Громкость эффектов: "), settingsMenu);
    q2->setGeometry(10, 45, 120, 10);
    q2->setStyleSheet("QLabel {color: rgb(255,255,255);}");
    q2->show();

    auto *s1 = new QSlider(Qt::Orientation::Horizontal, settingsMenu);
    s1->setGeometry(10, 25, 120, 10);
    s1->setStyleSheet(qSliderStyleSheet);
    s1->setValue(musicVolume);
    s1->setMinimum(0);
    s1->setMaximum(100);
    connect(s1, &QSlider::sliderMoved, [=](int position)
    {
        musicVolume = position;
        music->setVolume(musicVolume);
    });
    s1->show();

    auto *s2 = new QSlider(Qt::Orientation::Horizontal, settingsMenu);
    s2->setGeometry(10, 60, 120, 10);
    s2->setStyleSheet(qSliderStyleSheet);
    s2->setValue(effectVolume * 100);
    s2->setMinimum(0);
    s2->setMaximum(100);
    connect(s2, &QSlider::sliderMoved, [=](int position)
    {

        effectVolume = position / 100.0;
        player->sound->setVolume(effectVolume);
        player->sound2->setVolume(effectVolume);
        player->sound3->setVolume(effectVolume);
        sound->setVolume(effectVolume);
        sound2->setVolume(effectVolume);
    });
    s2->show();

    int l = QDir(":/levels/").count();
    QFile file(QString("../save"));
    if (file.exists()) {
        file.open(QIODevice::ReadOnly);
        QTextStream in(&file);

        auto s = in.readAll();
        int i = 1;
        if (s.size() > 0) {
            for (QChar a: s ) {
                saves[i] = (bool) a.digitValue();
                i++;
            }
        } else {
            for (int i = 1; i <= l; i++ ) {
                saves[i] = false;
            }
        }
    }
    file.close();

    buttonsMenu = new QWidget(gameView);
    buttonsMenu->setGeometry(200, 20, 170, l*30 + 10);
    buttonsMenu->setStyleSheet("QWidget {background-color: rgb(88,88,88);}");
    for (int i = 1; i <= l; i++ )
    {
        auto *b = new QPushButton(QString("Уровень %1 (%2)").arg(i).arg(saves[i] ? "пройден" : "не пройден"), buttonsMenu);
        b->setEnabled(i == 1 ? true : saves[i - 1]);
        buttons.append(b);
        connect(b, &QPushButton::clicked, [=]()
        {
            startLevel(i);

        });

        b->setGeometry(10, 10 + (i - 1) * 30, 150, 20);
        b->setStyleSheet(qPushButtonStyleSheet);

        b->show();
    }

    connect(gameScene, &CustomScene::signalKeyPressEvent, this, &Widget::slotKeyPressEvent);
    connect(gameScene, &CustomScene::signalTargetCoordinate, player, &Player::slotTarget);

    connect(player, &Player::signalBullet, this, &Widget::slotShots);
    connect(player, &Player::signalGameOver, this, &Widget::slotGameOver);
    connect(player, &Player::signalWin, [=]()
    {
        auto b = static_cast<QPushButton*>(buttons[currentLevel - 1]);
        b->setText(QString("Уровень %1 (%2)").arg(currentLevel).arg(saves[currentLevel] ? "пройден" : "не пройден"));
        b->setFocusPolicy(Qt::NoFocus);

        QFile file("../save");
        file.open(QIODevice::WriteOnly);
        QTextStream stream(&file);

        saves[currentLevel] = true;

        for (int i = 1; i <= l; i++)
        {
            stream << QString::number(saves[i]);
        }

        file.close();
        currentLevel++;

        static_cast<QPushButton*>(buttons[currentLevel - 1])->setEnabled(true);
        startLevel(currentLevel);
    });
}

void Widget::startLevel(int level) {
    for(auto i: gameScene->level) {
        i->deleteLater();
    }
    gameScene->level.clear();
    gameScene->targetArtifacts = 0;
    currentLevel = level;
    generator = new Generator(gameScene, this, level);

    qDebug() << "ok";
}

void Widget::slotKeyPressEvent(QKeyEvent *e) {
    if (!e->isAutoRepeat()) {
        if (e->key() == Qt::Key::Key_Escape) {
            hideShow(menu);

            if (menu->isHidden()) {
                hideMenu(settingsMenu);
                hideMenu(buttonsMenu);
            }
        }
    }
}



void Widget::slotShots(QPointF start, QPointF end)
{
    sound->play();
    gameScene->addItem(new Bullet(start, end, 0, 0, -2.5, 2.5, player->weapon));
}

void Widget::slotGameOver()
{

    sound2->play();
    player->hp = 10;
    startLevel(currentLevel);
}

void Widget::hideShow(QWidget *q) {
    q->isHidden() ? showMenu(q) : hideMenu(q);
}

void Widget::hideMenu(QWidget *q) {
    q->hide();
}

void Widget::showMenu(QWidget *q) {
    q->show();
}

void Widget::loadSettings()
{
    QByteArray arr;
    QFile file(QString("../settings"));
    if (file.exists()) {
        file.open(QIODevice::ReadOnly);
        QTextStream in(&file);

        auto s = in.readLine();
        auto s2 = in.readLine();
        musicVolume = s.toInt();
        effectVolume = s2.toDouble();
        file.close();
    } else {
        file.close();
        musicVolume = 100;
        effectVolume = 1;
        saveSettings();
    }
}

void Widget::saveSettings()
{
    QFile file("../settings");
    file.open(QIODevice::WriteOnly);
    QTextStream stream(&file);

    stream << musicVolume << "\n";
    stream << effectVolume;

    file.close();
}

Widget::~Widget()
{
    //delete timer;
    qDebug() << "d";
    saveSettings();
}



