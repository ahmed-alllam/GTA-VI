#include "gamemanager.h"
#include "level1.h"
#include "level2.h"
#include "level3.h"
#include <QGraphicsPixmapItem>
#include "homepage.h"
#include <QDir>
#include <QTimer>
#include <QDebug>
#include <QApplication>
#include <QGuiApplication>
#include <QGraphicsScene>
#include <QAudioFormat>
#include <QMediaPlayer>
#include <QAudioOutput>
#include <QLabel>
#include <QPushButton>
#include <QProgressBar>
#include <QMessageBox>
#include <QGraphicsRectItem>
#include <QGraphicsProxyWidget>
#include <qprocess.h>
#include <qmovie.h>
#include <QMovie>


GameManager::GameManager(QGraphicsScene *scene)
{
    this->scene = scene;
    levelNum = 1;
    currentLevel = new level1(this, scene);
}

void GameManager::launch_game()
{
    create_board();
    add_board_images();
    create_player();
    create_enemies();
    create_sound();
    create_bullets();
    create_pellets();
    create_healthbar();
}

void GameManager::add_board_images()
{
    currentLevel->add_board_images();
}

void GameManager::create_board() // to create and display the board
{
    currentLevel->create_board();
}

void GameManager::create_sound() // to create and display the sound
{
    QMediaPlayer *player = new QMediaPlayer;
    QAudioOutput *audioOutput = new QAudioOutput;
    player->setAudioOutput(audioOutput);
    player->setLoops(QMediaPlayer::Infinite);
    player->setSource(QUrl("qrc:/assets/sounds/backsound.mp3"));
    player->play();
}

void GameManager::create_player()
{
    currentLevel->create_player();
}

void GameManager::create_enemies()
{
    currentLevel->create_enemies();
}

void GameManager::create_bullets()
{
    currentLevel->create_bullets();
}

void GameManager::remove_bullets()
{
    currentLevel->remove_bullets();
}

void GameManager::create_pellets()
{
    currentLevel->create_pellets();
}

void GameManager::updateModeTxt()
{
    currentLevel->updateModeTxt();
}

void GameManager::create_healthbar()
{
    int screenWidth = QGuiApplication::primaryScreen()->availableSize().width();
    int screenHeight = QGuiApplication::primaryScreen()->availableSize().height();
    int unitWidth = qMin(screenWidth, screenHeight) / 17;
    int unitHeight = qMin(screenWidth, screenHeight) / 17;
    int unitWidth2 = qMin(screenWidth, screenHeight) / 12;
    int unitHeight2 = qMin(screenWidth, screenHeight) / 12;

    QGraphicsRectItem *panel = new QGraphicsRectItem(65, 0, 1130, 70);
    QBrush *brush = new QBrush();
    brush->setColor(Qt::darkGray);
    brush->setStyle(Qt::SolidPattern);
    panel->setBrush(*brush);
    scene->addItem(panel);

    txt = new QGraphicsTextItem("NORMAL MODE");
    QFont fonty("Arial", 20, QFont::StyleNormal);
    txt->setPos(540, 20);
    txt->setFont(fonty);
    txt->setDefaultTextColor(Qt::white);
    scene->addItem(txt);

    /* Creating Hearts */
    hearts = new QGraphicsPixmapItem[3];

    QPixmap blankImage(":assets/images/extra.png");

    blankImage = blankImage.scaledToWidth(unitWidth);
    blankImage = blankImage.scaledToHeight(unitHeight);
    for (int i = 0; i < 3; i++)
    {
        hearts[i].setPixmap(blankImage);
        hearts[i].setPos(80 * (i + 1), 15);
        scene->addItem(&hearts[i]);
    }

    /* adding the gate static photo*/
    gate = new QMovie(":/assets/images/gate2.gif");
    QLabel *lab = new QLabel();
    lab->setGeometry(unitWidth2 + 15 * unitWidth2, unitHeight2 + 9 * unitHeight2, unitWidth2, unitHeight2);
    lab->setBackgroundRole(QPalette::Base);
    gate->setScaledSize(lab->size());
    lab->setMovie(gate);

    QPixmap bulletImage(":assets/images/bullet.png");
    bulletImage = bulletImage.scaledToWidth(unitWidth);
    bulletImage = bulletImage.scaledToHeight(unitHeight);

    QGraphicsPixmapItem *bulletItem = new QGraphicsPixmapItem();
    bulletItem->setPos(300, 15);
    bulletItem->setPixmap(bulletImage);
    scene->addItem(bulletItem);

    bulletsCounter = new QGraphicsTextItem("0");
    bulletsCounter->setPos(360, 20);
    bulletsCounter->setFont(fonty);
    bulletsCounter->setDefaultTextColor(Qt::white);
    scene->addItem(bulletsCounter);

    QPixmap coinImage(":assets/images/coin.png");

    coinImage = coinImage.scaledToWidth(unitWidth);
    coinImage = coinImage.scaledToHeight(unitHeight);

    QGraphicsPixmapItem *coinItem = new QGraphicsPixmapItem();
    coinItem->setPos(400, 15);
    coinItem->setPixmap(coinImage);
    scene->addItem(coinItem);

    coinsCounter = new QGraphicsTextItem("0");
    coinsCounter->setPos(460, 20);
    coinsCounter->setFont(fonty);
    coinsCounter->setDefaultTextColor(Qt::white);
    scene->addItem(coinsCounter);

    /*Drunk and label part */

    scene->addWidget(lab);

    gate->setSpeed(40);

    gate->start();
    gate->setPaused(true);
}

void GameManager::activate_mode() // displaying the progress bar
{
    movie = new QMovie(":/assets/images/the_timer.gif");

    movie->setBackgroundColor(Qt::red);
    QLabel *l = new QLabel();
    l->setGeometry(840, 20, 200, 30);
    movie->setScaledSize(l->size());
    l->setMovie(movie);
    movie->start();
    scene->addWidget(l);
    movie->setSpeed(35);

    connect(timer, &QTimer::timeout, movie, &QMovie::stop);
    connect(timer, &QTimer::timeout, l,
            [l]()
            {
                // For some reason == movie->frameCount() crashes, so... *
                l->setVisible(false);
            });
    timer->start(10000);
}

void GameManager::open_gate()
{
    gate->setPaused(false);
    connect(gate, &QMovie::frameChanged, this,
            [this]()
            {
                // For some reason == movie->frameCount() crashes, so... *
                if (this->gate->currentFrameNumber() == (gate->frameCount() - 1 - gate->frameCount() / 2 + 1))
                {
                    this->gate->stop();
                    // Explicity emit finished signal so that label **
                    // can show the image instead of a frozen gif
                    // Also, double check that movie stopped before emiting
                    if (this->gate->state() == QMovie::NotRunning)
                    {
                        emit this->gate->finished();
                        gate->setPaused(true);
                    }
                }
            });
}

void GameManager::close_gate()
{
    currentLevel->close_gate();
}

void GameManager::updateCounters()
{
    currentLevel->updateCounters();
}

void GameManager::remove_heart()
{
    currentLevel->remove_heart();
}

QGraphicsRectItem *GameManager::drawPanel(int x, int y, int width, int height, QColor color, double opacity)
{
    // draws a panel at the specified location with the specified properties

    QGraphicsRectItem *panel = new QGraphicsRectItem(x, y, width, height);
    QBrush brush;
    brush.setStyle(Qt::SolidPattern);
    brush.setColor(color);
    panel->setBrush(brush);
    panel->setOpacity(opacity);
    scene->addItem(panel);

    return panel;
}

void GameManager::game_over()
{
    int screenWidth = QGuiApplication::primaryScreen()->availableSize().width();
    int screenHeight = QGuiApplication::primaryScreen()->availableSize().height();
    for (size_t i = 0, n = scene->items().size(); i < n; i++)
    {
        scene->items()[i]->setEnabled(false);
    }
    // back ground panel and main
    panels = new QGraphicsRectItem *[2];

    //    panels[0] = drawPanel(0,0,screenWidth,screenHeight,Qt::black,0.65);
    panels[1] = drawPanel(screenWidth / 3 - 20, screenHeight / 3 - 20, 400, 400, Qt::lightGray, 1);

    /* Gmae Over Text*/
    QGraphicsTextItem *overText = new QGraphicsTextItem("GAME OVER");
    QFont fonty("Arial", 20, QFont::StyleNormal);
    overText->setPos(screenWidth / 3 + 100, screenHeight / 3 + 80);
    overText->setFont(fonty);
    scene->addItem(overText);

    QPushButton *p = new QPushButton;
    p->setText("PLAY AGAIN");
    p->setGeometry(screenWidth / 3 + 40, screenHeight / 3 + 250, 100, 50);
    scene->addWidget(p);

    QObject::connect(
        p, &QPushButton::clicked, this, [=]()
        { restart_game(); },
        Qt::QueuedConnection);

    QPushButton *quit;
    quit = new QPushButton("Quit");
    quit->setGeometry(screenWidth / 3 + 230, screenHeight / 3 + 250, 100, 50);
    scene->addWidget(quit);

    QObject::connect(quit, &QPushButton::clicked, [=]()
                     { exit(); });
}

void GameManager::Win()
{
    int screenWidth = QGuiApplication::primaryScreen()->availableSize().width();
    int screenHeight = QGuiApplication::primaryScreen()->availableSize().height();
    for (size_t i = 0, n = scene->items().size(); i < n; i++)
    {
        scene->items()[i]->setEnabled(false);
    }
    // back ground panel and main
    panels = new QGraphicsRectItem *[2];

    //    panels[0] = drawPanel(0,0,screenWidth,screenHeight,Qt::black,0.65);
    panels[1] = drawPanel(screenWidth / 3 - 20, screenHeight / 3 - 20, 400, 400, Qt::lightGray, 1);

    /* Gmae Over Text*/
    QGraphicsTextItem *overText = new QGraphicsTextItem("You WON!!!!!!");
    QFont fonty("Arial", 20, QFont::StyleNormal);
    overText->setPos(screenWidth / 3 + 100, screenHeight / 3 + 80);
    overText->setFont(fonty);
    scene->addItem(overText);

    QPushButton *p = new QPushButton;
    p->setText("NEXT LEVEL");
    levelNum++;
    p->setGeometry(screenWidth / 3 + 40, screenHeight / 3 + 250, 100, 50);
    // update the level
    // level =
    scene->addWidget(p);

    QObject::connect(
        p, &QPushButton::clicked, this, [=]()
        { restart_game(); },
        Qt::QueuedConnection);

    QPushButton *quit;
    quit = new QPushButton("Quit");
    quit->setGeometry(screenWidth / 3 + 230, screenHeight / 3 + 250, 100, 50);
    scene->addWidget(quit);

    QObject::connect(quit, &QPushButton::clicked, [=]()
                     { exit(); });

}

void GameManager::restart_game()
{

    for (size_t i = 0, n = scene->items().size(); i < n; i++)
    {
        scene->items()[i]->setEnabled(true);
    }

    currentLevel->restart_game();
    delete currentLevel;

    if (levelNum == 1)
    {
        currentLevel = new level1(this, scene);
        qDebug() << "level 1";
    }
    else if (levelNum == 2)
    {
        qDebug() << "level 2";
         currentLevel = new level2(this, scene);
    }
    else if (levelNum == 3)
    {
        currentLevel = new level1(this, scene); //todo
        qDebug() << "level 3";
        // currentLevel = new level3();
    }

    create_board();
    add_board_images();
    create_player();
    close_gate();
    create_enemies();
    create_bullets();
    create_pellets();
    create_healthbar();
    updateCounters();
}

//void GameManager::Next_level()
//{
//    if (levelNum == 1)
//    {
//        delete currentLevel;
//        levelNum++;
//        currentLevel = new level2(this, scene);
//    }
//    else if (levelNum == 2)
//    {
//        delete currentLevel;
//        levelNum++;
//        currentLevel = new level3(this, scene);
//    }
//    launch_game();
//}

void GameManager::exit()
{
    QString program = qApp->arguments()[0];
    QStringList arguments = qApp->arguments().mid(1);
    qApp->quit();
    QProcess::startDetached(program, arguments);
}
