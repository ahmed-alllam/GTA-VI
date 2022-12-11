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
#include <QLabel>
#include <QPushButton>
#include <QProgressBar>
#include <QMessageBox>
#include <QUiLoader>
#include <QGraphicsRectItem>
#include <QGraphicsProxyWidget>
#include <qprocess.h>
#include <qmovie.h>
#include <QMovie>


GameManager::GameManager(QGraphicsScene *scene)
{
    this->scene = scene;
    levelNum = 1;
    timer = new QTimer;
    currentLevel = new level1(this, scene);
    create_sound();
}

void GameManager::launch_game()
{
    l = new QLabel();
    l->setGeometry(900, 20, 200, 30);
    create_board();
    add_board_images();
    create_player();
    create_enemies();
    create_bullets();
    if(bomb::is_available())
        create_bombs();
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
    int unitWidth2 = qMin(screenWidth, screenHeight) / 13;
    int unitHeight2 = qMin(screenWidth, screenHeight) / 13;

    QGraphicsRectItem *panel = new QGraphicsRectItem(65, 0, 1130, 70);
    QBrush *brush = new QBrush();
    brush->setColor(Qt::darkGray);
    brush->setStyle(Qt::SolidPattern);
    panel->setBrush(*brush);
    scene->addItem(panel);

    txt = new QGraphicsTextItem("NORMAL MODE");
    QFont fonty("Arial", 20, QFont::StyleNormal);
    txt->setPos(640, 20);
    txt->setFont(fonty);
    txt->setDefaultTextColor(Qt::white);
    scene->addItem(txt);

//    counter = new QGraphicsTextItem("00:00");
//    QFont fontc("Arial", 20, QFont::StyleNormal);
//    counter->setPos(1020, 20);
//    counter->setFont(fonty);
//    counter->setDefaultTextColor(Qt::white);
//    scene->addItem(counter);
//    counter->setVisible(false);

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

    if(bomb::is_available())  //checking availablity
    {
        QPixmap bombImage(":assets/images/time-bomb.png");
        bombImage = bombImage.scaledToWidth(unitWidth);
        bombImage = bombImage.scaledToHeight(unitHeight);

        QGraphicsPixmapItem *bombItem = new QGraphicsPixmapItem();
        bombItem->setPos(500, 15);
        bombItem->setPixmap(bombImage);
        scene->addItem(bombItem);

        bombsCounter= new QGraphicsTextItem("0");
        bombsCounter->setPos(560, 20);
        bombsCounter->setFont(fonty);
        bombsCounter->setDefaultTextColor(Qt::white);
        scene->addItem(bombsCounter);

    }


    /*Drunk and label part */

    scene->addWidget(lab);

    gate->setSpeed(40);

    gate->start();
    gate->setPaused(true);

}

//void GameManager::set_counter(int n)
//{
//    countdown = n;
//}

//void GameManager::update()
//{
//    if (timer != nullptr)
//    {
//        timer->stop();
//    }
//    countdown--;
//    activate_mode();
//}

void GameManager::activate_mode(bool d, bool p) // displaying the progress bar
{
    if(d || p) {
    movie = new QMovie(":/assets/images/the_timer.gif");

    movie->setBackgroundColor(Qt::red);
    movie->setScaledSize(l->size());
    l->setGeometry(900, 20, 200, 30);
    l->setMovie(movie);
    l->setVisible(true);
    l->setGeometry(900, 20, 200, 30);
    movie->start();
    scene->addWidget(l);

    connect(timer, &QTimer::timeout, movie, &QMovie::stop);
    connect(timer, &QTimer::timeout, l,
            [this]()
            {
                // For some reason == movie->frameCount() crashes, so... *
                this->l->setVisible(false);
            });
    if (p && (timer != nullptr && movie != nullptr))
    {
        timer->start(30000);
        movie->setSpeed(10);
    }
    else if (d && (timer != nullptr && movie != nullptr))
    {

        timer->start(15000);
        movie->setSpeed(20);
    }
    }

    qDebug() << "wfe in updatemode txt";
    if(!p && !d) {
        qDebug() << "wfe in if condi";
        if(movie != nullptr && l != nullptr) {
        movie->stop();
        l->setVisible(false);
        }

    }
//    connect(timer, &QTimer::timeout, this, &GameManager::update);
//    counter->setPlainText("00:" + QString::number(countdown));
//    if(countdown > 0)
//    {
//        counter->setVisible(true);
//        timer->start(1000);
//    }
//    else
//    {
//        counter->setVisible(false);
//    }
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

void GameManager::delete_released_bomb(int a, int b)
{
    currentLevel->delete_released_bomb(a,b);
}


void GameManager::updateCounters()
{
    currentLevel->updateCounters();

}

void GameManager::remove_heart()
{
    currentLevel->remove_heart();
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
    //    panels[0] = drawPanel(0,0,screenWidth,screenHeight,Qt::black,0.65);
    QFile gameoverUI(":/forms/gameover.ui");
    gameoverUI.open(QFile::ReadOnly);
    QUiLoader loader;
    QWidget *gameover = loader.load(&gameoverUI);
    gameoverUI.close();
    gameover->setGeometry((screenWidth / 2) - (gameover->width() * 3 / 4), (screenHeight / 2) - (gameover->height() / 2), gameover->width(), gameover->height());
    gameover->setStyleSheet("QWidget {border: 5px solid white; border-radius: 10px; background-color: qradialgradient(spread:pad, cx:0.5, cy:0.5, radius:0.5, fx:0.5, fy:0.5, stop:0.09589655 rgba(80, 150, 1, 255), stop:1 rgba(51, 95, 63, 255));}");
    scene->addWidget(gameover);

    QPushButton *nextButton = gameover->findChild<QPushButton *>("next");
    QPushButton *quitButton = gameover->findChild<QPushButton *>("quit");
    QLabel *label = gameover->findChild<QLabel *>("text");

    label->setText("Game Over!");
    nextButton->setText("Play Again");

    win = false;

    QObject::connect(
        nextButton, &QPushButton::clicked, this, [=]()
        {
//        gameover->setVisible(false);
        restart_game(); },
        Qt::QueuedConnection);

    QObject::connect(quitButton, &QPushButton::clicked, [=]()
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
    // using uiloader to load the gameover ui file
    QFile gameoverUI(":/forms/gameover.ui");
    gameoverUI.open(QFile::ReadOnly);
    QUiLoader loader;
    QWidget *gameover = loader.load(&gameoverUI);
    gameoverUI.close();
    // add gameover to the middle of the screen
    gameover->setStyleSheet("QWidget {border: 5px solid white; border-radius: 10px; background-color: qradialgradient(spread:pad, cx:0.5, cy:0.5, radius:0.5, fx:0.5, fy:0.5, stop:0.09589655 rgba(80, 150, 1, 255), stop:1 rgba(51, 95, 63, 255));}");

    gameover->setGeometry((screenWidth / 2) - (gameover->width() * 3 / 4), (screenHeight / 2) - (gameover->height() / 2), gameover->width(), gameover->height());

    scene->addWidget(gameover);

    QPushButton *nextButton = gameover->findChild<QPushButton *>("next");
    QPushButton *quitButton = gameover->findChild<QPushButton *>("quit");
    QLabel *label = gameover->findChild<QLabel *>("text");

    label->setText("You Won!");

    win = true;

    if(levelNum != 3)
        nextButton->setText("Next Level");
    else
        nextButton->setText("Play Again");

    QObject::connect(
        nextButton, &QPushButton::clicked, this, [=]()
        {
//        gameover->setVisible(false);
        restart_game(); },
        Qt::QueuedConnection);

    QObject::connect(quitButton, &QPushButton::clicked, [=]()
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
    qDebug() << "win : " << win << " level num " << levelNum;
    if(win)
    {
        if (levelNum == 1)
        {
            levelNum++;
            currentLevel = new level2(this, scene);
        }
        else if (levelNum == 2)
        {
            levelNum++;
            currentLevel = new level3(this, scene);
        }
        else if (levelNum == 3)
        {
            levelNum = 1;
            currentLevel = new level1(this, scene);
        }
    }
    else
    {
        levelNum = 1;
        currentLevel = new level1(this, scene);
    }
    this->launch_game();

//    create_board();
//    add_board_images();
//    create_player();
//    close_gate();
//    create_enemies();
//    create_bullets();
//    create_pellets();
//    create_healthbar();
//    updateCounters();
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
void GameManager::create_bombs()
{
    currentLevel->create_bombs();
}

void GameManager::remove_bombs()
{
    currentLevel->remove_bombs();
}
void GameManager::exit()
{
    QString program = qApp->arguments()[0];
    QStringList arguments = qApp->arguments().mid(1);
    qApp->quit();
    QProcess::startDetached(program, arguments);
}
