#include "gamemanager.h"

#include <QGraphicsPixmapItem>
#include "franklin.h"
#include "enemy1.h"
#include "enemy2.h"
#include "pellet.h"
#include "Drunk.h"
#include "homepage.h"
#include <QDir>
#include <QTimer>
#include <QDebug>
#include <QApplication>
#include <QGuiApplication>
#include <QGraphicsScene>
//#include <QAudioFormat>
//#include <QMediaPlayer>
//#include <QAudioOutput>
#include <QLabel>
#include <QPushButton>
#include<QProgressBar>
#include <QMessageBox>
#include <QGraphicsRectItem>
#include <QGraphicsProxyWidget>
#include<qprocess.h>
#include<qmovie.h>
#include<QMovie>
#include "enemy2.h"
#include "flyingbullet.h"


Franklin *GameManager::franklin = nullptr;
enemy1 *GameManager::enemy1 = nullptr;
enemy2 *GameManager::enemy2 = nullptr;

bullet *GameManager::bullet1 = nullptr;
bullet *GameManager::bullet2 = nullptr;
bullet *GameManager::bullet3 = nullptr;
bullet *GameManager::bullet4 = nullptr;

pellet *GameManager::pellet1 = nullptr;
pellet *GameManager::pellet2 = nullptr;



void GameManager::restart_game()
{
    QList<QGraphicsItem *> items = scene->items();

    franklin = nullptr;
    enemy1 = nullptr;
    enemy2 = nullptr;

    bullet1 = nullptr;
    bullet2 = nullptr;
    bullet3 = nullptr;
   bullet4 = nullptr;

    pellet1 = nullptr;
    pellet2 = nullptr;


    for (int i = 0; i < items.size(); i++) {
        if(typeid(*items[i]) == typeid(QGraphicsProxyWidget) || typeid(*items[i]) == typeid(QGraphicsTextItem) || typeid(*items[i]) == typeid(QPushButton) || typeid(*items[i]) == typeid(QGraphicsRectItem) || typeid(*items[i]) == typeid(bullet) || typeid(*items[i]) == typeid(class Franklin) || typeid(*items[i]) == typeid(class enemy1) || typeid(*items[i]) == typeid(class enemy2) || typeid(*items[i]) == typeid(class Drunk) || typeid(*items[i]) == typeid(class pellet)|| typeid(*items[i]) == typeid(class FlyingBullet)) {
            scene->removeItem(items[i]);
            delete items[i];
        }
    }



        for (size_t i = 0, n = scene->items().size(); i < n; i++) {
            scene->items()[i]->setEnabled(true);
        }


        create_player();
        create_enemies();
    //   create_sound();
        create_bullets();
        create_pellets();
        create_healthbar();

}

void GameManager::exit()
{
    QString program = qApp->arguments()[0];
    QStringList arguments = qApp->arguments().mid(1); // remove the 1st argument - the program name
    qApp->quit();
    QProcess::startDetached(program, arguments);

//    qApp->quit();
    //    QProcess::startDetached(qApp->arguments()[0], qApp->arguments());
}

GameManager::GameManager(QGraphicsScene *scene)
{
    this->scene = scene;

    // create and launch homepage.cpp
    homepage * home = new homepage(this, scene);
    scene->addWidget(home);
}


void GameManager::activate_mode() //displaying the progress bar
{
    QMovie* movie = new QMovie(":/assets/images/the_timer.gif");

    movie->setBackgroundColor(Qt::red);
    QLabel* l = new QLabel();
    l->setGeometry(840,20, 200,30);
    movie->setScaledSize(l->size());
    l->setMovie(movie);
    movie->start();
    scene->addWidget(l);
    float speed;
    float i=1;
    speed=i*40;
    if(speed<=0)
    {
        movie->stop();
        l->clear();
       return;
    }else if(speed==100)
    {
        return;
    }else if(speed>500)
    {
        speed=500;
    }
    movie->setSpeed(speed);
}

void GameManager::launch_game() {
    create_board();
    add_board_images();
    create_player();
    create_enemies();
//   create_sound();
    create_bullets();
    create_pellets();
    create_healthbar();
}

void GameManager::add_board_images()
{
    int screenWidth = QGuiApplication::primaryScreen()->availableSize().width();
    int screenHeight = QGuiApplication::primaryScreen()->availableSize().height();
    int unitWidth = qMin(screenWidth, screenHeight) / 12;
    int unitHeight = qMin(screenWidth, screenHeight) / 12;

    QPixmap blankImage(":assets/images/blank.png");

    blankImage = blankImage.scaledToWidth(unitWidth);
    blankImage = blankImage.scaledToHeight(unitHeight);

    QPixmap brick1Image(":assets/images/car up.png");
    brick1Image = brick1Image.scaledToWidth(unitWidth);
    brick1Image = brick1Image.scaledToHeight(unitWidth);

    QPixmap brick2Image(":assets/images/water.png");
    brick2Image = brick2Image.scaledToWidth(unitWidth);
    brick2Image = brick2Image.scaledToHeight(unitWidth);

    QPixmap brick3Image(":assets/images/car bottom.png");
    brick3Image = brick3Image.scaledToWidth(unitWidth);
    brick3Image = brick3Image.scaledToHeight(unitWidth);

    QPixmap brick4Image(":assets/images/car right.png");
    brick4Image = brick4Image.scaledToWidth(unitWidth);
    brick4Image = brick4Image.scaledToHeight(unitWidth);

    QPixmap brick5Image(":assets/images/Tree.png");
    brick5Image = brick5Image.scaledToWidth(unitWidth);
    brick5Image = brick5Image.scaledToHeight(unitWidth);

    QPixmap brick6Image(":assets/images/house.png");
    brick6Image = brick6Image.scaledToWidth(unitWidth);
    brick6Image = brick6Image.scaledToHeight(unitWidth);

    QPixmap brick7Image(":assets/images/Bodygard.png");
    brick7Image = brick7Image.scaledToWidth(unitWidth);
    brick7Image = brick7Image.scaledToHeight(unitWidth);

    QPixmap homeImage(":assets/images/Home.png");
    homeImage = homeImage.scaledToWidth(unitWidth);
    homeImage = homeImage.scaledToHeight(unitWidth);

    QPixmap arrowImage(":assets/images/arrow.png");
    arrowImage = arrowImage.scaledToWidth(unitWidth);
    arrowImage = arrowImage.scaledToHeight(unitWidth);

    QPixmap VertRoadImage(":assets/images/vert.png"); // aadded for test
    VertRoadImage = VertRoadImage.scaledToWidth(unitWidth);
    VertRoadImage = VertRoadImage.scaledToHeight(unitWidth);

    QPixmap HorRoadImage(":assets/images/horz.png"); // aadded for test
    HorRoadImage = HorRoadImage.scaledToWidth(unitWidth);
    HorRoadImage = HorRoadImage.scaledToHeight(unitWidth);

    QPixmap toleft_RoadImage(":assets/images/2left.png"); // aadded
    toleft_RoadImage = toleft_RoadImage.scaledToWidth(unitWidth);
    toleft_RoadImage = toleft_RoadImage.scaledToHeight(unitWidth);

    QPixmap toright_RoadImage(":assets/images/2right.png"); // aadded
    toright_RoadImage = toright_RoadImage.scaledToWidth(unitWidth);
    toright_RoadImage = toright_RoadImage.scaledToHeight(unitWidth);

    QPixmap toleft_RoadImage2(":assets/images/2left2.png"); // aadded
    toleft_RoadImage2 = toleft_RoadImage2.scaledToWidth(unitWidth);
    toleft_RoadImage2 = toleft_RoadImage2.scaledToHeight(unitWidth);

    QPixmap toright_RoadImage2(":assets/images/2right2.png"); // aadded
    toright_RoadImage2 = toright_RoadImage2.scaledToWidth(unitWidth);
    toright_RoadImage2 = toright_RoadImage2.scaledToHeight(unitWidth);

    QPixmap TUImage(":assets/images/T Up.png"); // aadded
    TUImage = TUImage.scaledToWidth(unitWidth);
    TUImage = TUImage.scaledToHeight(unitWidth);

    QPixmap TDImage(":assets/images/T Down.png"); // aadded
    TDImage = TDImage.scaledToWidth(unitWidth);
    TDImage = TDImage.scaledToHeight(unitWidth);

    QPixmap TLImage(":assets/images/T Left.png"); // aadded
    TLImage = TLImage.scaledToWidth(unitWidth);
    TLImage = TLImage.scaledToHeight(unitWidth);

    QPixmap TRImage(":assets/images/T Right.png"); // aadded
    TRImage = TRImage.scaledToWidth(unitWidth);
    TRImage = TRImage.scaledToHeight(unitWidth);

    QPixmap CrossImage(":assets/images/cross road.png"); // aadded
    CrossImage = CrossImage.scaledToWidth(unitWidth);
    CrossImage = CrossImage.scaledToHeight(unitWidth);

    // create 2d dynamic array of type QGraphicsPixmapItem, with 12 rows and 16 columns
    QGraphicsPixmapItem **boardItems = new QGraphicsPixmapItem*[12];
    for (int i = 0; i < 12; i++) {
        boardItems[i] = new QGraphicsPixmapItem[16];
    }

    for (int i = 0; i < 12; i++)
        for (int j = 0; j < 16; j++)
        {
            // Set Image
            if (boardData[i][j] == -1)
                boardItems[i][j].setPixmap(brick1Image);
            else if (boardData[i][j] == -2)
                boardItems[i][j].setPixmap(brick2Image);
            else if (boardData[i][j] == -3)
                boardItems[i][j].setPixmap(brick3Image);
            else if (boardData[i][j] == -4)
                boardItems[i][j].setPixmap(brick4Image);
            else if (boardData[i][j] == -5)
                boardItems[i][j].setPixmap(brick5Image);
            else if (boardData[i][j] == -6)
                boardItems[i][j].setPixmap(brick6Image);
            else if (boardData[i][j] == -7)
                boardItems[i][j].setPixmap(brick7Image);
            else if (boardData[i][j] == 20)
                boardItems[i][j].setPixmap(homeImage);
            else if (boardData[i][j] == 50)
                boardItems[i][j].setPixmap(blankImage);
            else if (boardData[i][j] == -50)
                boardItems[i][j].setPixmap(blankImage);
            else if (boardData[i][j] == 4)
                boardItems[i][j].setPixmap(VertRoadImage);
            else if (boardData[i][j] == 2)
                boardItems[i][j].setPixmap(HorRoadImage);
            else if (boardData[i][j] == 7)
                boardItems[i][j].setPixmap(toright_RoadImage);
            else if (boardData[i][j] == 8)
                boardItems[i][j].setPixmap(toright_RoadImage2);
            else if (boardData[i][j] == 9)
                boardItems[i][j].setPixmap(toleft_RoadImage);
            else if (boardData[i][j] == 3)
                boardItems[i][j].setPixmap(toleft_RoadImage2);
            else if (boardData[i][j] == 13)
                boardItems[i][j].setPixmap(TRImage);
            else if (boardData[i][j] == 14)
                boardItems[i][j].setPixmap(TLImage);
            else if (boardData[i][j] == 12)
                boardItems[i][j].setPixmap(TDImage);
            else if (boardData[i][j] == 11)
                boardItems[i][j].setPixmap(TUImage);
            else if (boardData[i][j] == 15)
                boardItems[i][j].setPixmap(CrossImage);
            else
                boardItems[i][j].setPixmap(blankImage);

            // Set Position
            boardItems[i][j].setPos(unitWidth + j * unitWidth, unitHeight + i * unitHeight);
            // Add to the Scene
            scene->addItem(&boardItems[i][j]);
        }
}

void GameManager::create_board() // to create and display the board
{
    QFile file(":Maze.txt");
    file.open(QIODevice::ReadOnly);
    QTextStream stream(&file);
    QString temp;
    for (int i = 0; i < 12; i++)
        for (int j = 0; j < 16; j++)
        {
            stream >> temp;
            boardData[i][j] = temp.toInt();
        }
}

//void GameManager::create_sound() // to create and display the sound
//{
//    QMediaPlayer *player = new QMediaPlayer;
//    QAudioOutput *audioOutput = new QAudioOutput;
//    player->setAudioOutput(audioOutput);
//    player->setLoops(QMediaPlayer::Infinite);
//    player->setSource(QUrl("qrc:/assets/sounds/backsound.mp3"));
//    player->play();
//}

void move_enemies()
{
    if (GameManager::enemy1 != nullptr)
    {
        GameManager::enemy1->move();
    }

    if (GameManager::enemy2 != nullptr)
    {
        GameManager::enemy2->move();
    }
}


void player_focus()
{
    if (GameManager::franklin != nullptr)
    {
        GameManager::franklin->focus_player();
    }
}

void GameManager::create_player()
{
    franklin = new Franklin(boardData, this);
    scene->addItem(franklin);

    timer = new QTimer();
    QObject::connect(timer, &QTimer::timeout, player_focus);
    timer->start(350);
}

void GameManager::create_enemies()
{
    enemy1 = new class enemy1(boardData, this);
    scene->addItem(enemy1);

    enemy2 = new class enemy2(boardData, this);
    scene->addItem(enemy2);

    timer2 = new QTimer();
    QObject::connect(timer2, &QTimer::timeout, move_enemies);
    timer2->start(400);
}

void GameManager::create_bullets() {
    bullet1 = new class bullet(boardData, 1, 1);
    bullet2 = new class bullet(boardData, 10, 14);
    bullet3 = new class bullet(boardData, 10, 1);
    bullet4 = new class bullet(boardData, 1, 14);
    scene->addItem(bullet1);
    scene->addItem(bullet2);
    scene->addItem(bullet3);
    scene->addItem(bullet4);
}

void GameManager::remove_bullets() {
    if(bullet1 != nullptr){
        scene->removeItem(bullet1);
        bullet1 = nullptr;
        delete bullet1;
    }

    if(bullet2 != nullptr){
        scene->removeItem(bullet2);
        bullet2 = nullptr;
        delete bullet2;
    }

    if(bullet3 != nullptr){
        scene->removeItem(bullet3);
        bullet3 = nullptr;
        delete bullet3;
    }

    if(bullet4 != nullptr){
        scene->removeItem(bullet4);
        bullet4 = nullptr;
        delete bullet4;
    }
}

void GameManager::create_pellets()
{
    pellet1 = new class pellet(boardData, 9, 1);
    pellet2 = new class pellet(boardData, 4, 14);
    drunk = new class Drunk(boardData, 1, 3);
    scene->addItem(pellet1);
    scene->addItem(pellet2);
    scene->addItem(drunk);
}

void GameManager::updateModeTxt() {
    if(txt != nullptr && franklin != nullptr) {
        if(franklin->getIsPowerful() && franklin->getIsDrunk())
        {
            txt->setPlainText("Powerful and Drunk Mode");
        }
        else if(franklin->getIsPowerful())
        {
            txt->setPlainText("Powerful Mode");
        }
        else if(franklin->getIsDrunk())
        {
            txt->setPlainText("Drunk Model");
        }
        else
        {
            txt->setPlainText("Normal Model");
        }
    }
}

void GameManager::create_healthbar() {
    int screenWidth = QGuiApplication::primaryScreen()->availableSize().width();
    int screenHeight = QGuiApplication::primaryScreen()->availableSize().height();
    int unitWidth = qMin(screenWidth, screenHeight) / 17;
    int unitHeight = qMin(screenWidth, screenHeight) / 17;

    QGraphicsRectItem*panel=new QGraphicsRectItem(65,0,1130,70);
    QBrush * brush = new QBrush();
    brush->setColor(Qt::darkGray);
    brush->setStyle(Qt::SolidPattern);
    panel->setBrush(*brush);
    scene->addItem(panel);



    txt = new QGraphicsTextItem("NORMAL MODE");
    QFont fonty("Arial", 20, QFont::StyleNormal);
    txt->setPos(540,20);
    txt->setFont(fonty);
    txt->setDefaultTextColor(Qt::white);
    scene->addItem(txt);


  /* Creating Hearts */
    hearts = new QGraphicsPixmapItem[3];

    QPixmap blankImage(":assets/images/extra.png");

    blankImage = blankImage.scaledToWidth(unitWidth);
    blankImage = blankImage.scaledToHeight(unitHeight);
    for (int i = 0; i<franklin->getHealth() ; i++)
    {
        hearts[i].setPixmap(blankImage);
        hearts[i].setPos(80*(i+1), 15);
        scene->addItem(&hearts[i]);
    }



    /* adding the gate static photo*/
    gate= new QMovie(":/assets/images/gate2.gif");
    QLabel* lab = new QLabel();
    lab->setGeometry(1100,680, 50,90);
    lab->setBackgroundRole(QPalette::Base);
    gate->setScaledSize(lab->size());
    lab->setMovie(gate);

    QPixmap bulletImage(":assets/images/bullet.png");
    bulletImage = bulletImage.scaledToWidth(unitWidth);
    bulletImage = bulletImage.scaledToHeight(unitHeight);

    QGraphicsPixmapItem * bulletItem = new QGraphicsPixmapItem();
    bulletItem->setPos(300 , 15);
    bulletItem->setPixmap(bulletImage);
    scene->addItem(bulletItem);

    bulletsCounter = new QGraphicsTextItem("0");
    bulletsCounter->setPos(360,20);
    bulletsCounter->setFont(fonty);
    bulletsCounter->setDefaultTextColor(Qt::white);
    scene->addItem(bulletsCounter);



    QPixmap coinImage(":assets/images/coin.png");

    coinImage = coinImage.scaledToWidth(unitWidth);
    coinImage = coinImage.scaledToHeight(unitHeight);

    QGraphicsPixmapItem * coinItem = new QGraphicsPixmapItem();
    coinItem->setPos(400 , 15);
    coinItem->setPixmap(coinImage);
    scene->addItem(coinItem);

    coinsCounter = new QGraphicsTextItem("0");
    coinsCounter->setPos(460,20);
    coinsCounter->setFont(fonty);
    coinsCounter->setDefaultTextColor(Qt::white);
    scene->addItem(coinsCounter);






    /*Drunk and label part */


    scene->addWidget(lab);

    gate->setSpeed(40);

    gate->start();
    gate->setPaused(true);

}


void GameManager::open_gate()
{
    gate->setPaused(false);
    boardData[9][15] = 50;
    franklin->editboard();
    connect(gate, &QMovie::frameChanged, this,
        [this]()
        {
             //For some reason == movie->frameCount() crashes, so... *
            if(this->gate->currentFrameNumber() == (gate->frameCount() - 1-gate->frameCount()/2+1))
            {
                this->gate->stop();
                //Explicity emit finished signal so that label **
                //can show the image instead of a frozen gif
                //Also, double check that movie stopped before emiting
                if (this->gate->state() == QMovie::NotRunning)
                {
                    emit this->gate->finished();
                     gate->setPaused(true);
                }
            }
        }
);
}



void GameManager::updateCounters() {
    qDebug() << "updateing " << QString::number(franklin->getBulletsCount()) << QString::number(franklin->getCoinsCount());
    if(bulletsCounter != nullptr)
        bulletsCounter->setPlainText(QString::number(franklin->getBulletsCount()));
    if(coinsCounter != nullptr)
        coinsCounter->setPlainText(QString::number(franklin->getCoinsCount()));
}
void GameManager::remove_heart()
{

        int health = franklin->getHealth();

        if (health >= 0){
            scene->removeItem(&hearts[health]);
        }

        if(health == 0){

            game_over();
        }
}

void GameManager::franklin_hit() {
    if(enemy1 != nullptr)
        enemy1->setXandY(9, 8);
    if(enemy2 != nullptr)
        enemy2->setXandY(3, 11);

    franklin->hit();
}


QGraphicsRectItem* GameManager::drawPanel(int x, int y, int width, int height, QColor color, double opacity){
    // draws a panel at the specified location with the specified properties

    QGraphicsRectItem* panel = new QGraphicsRectItem(x,y,width,height);
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
    for (size_t i = 0, n = scene->items().size(); i < n; i++){
            scene->items()[i]->setEnabled(false);
        }
    // back ground panel and main
     panels = new QGraphicsRectItem*[2];

//    panels[0] = drawPanel(0,0,screenWidth,screenHeight,Qt::black,0.65);
    panels[1] = drawPanel(screenWidth/3-20,screenHeight/3-20,400,400,Qt::lightGray,1);

    /* Gmae Over Text*/
    QGraphicsTextItem* overText = new QGraphicsTextItem("GAME OVER");
     QFont fonty("Arial", 20, QFont::StyleNormal);
    overText->setPos(screenWidth/3 + 100,screenHeight/3+80);
    overText->setFont(fonty);
    scene->addItem(overText);

    QPushButton *p =new QPushButton;
    p->setText("PLAY AGAIN");
    p->setGeometry(screenWidth/3+40,screenHeight/3+250, 100,50);
    scene->addWidget(p);

    QObject::connect(p, &QPushButton::clicked, this, [=] () {
            restart_game();
        }, Qt::QueuedConnection);

    QPushButton* quit;
    quit=new QPushButton("Quit");
    quit->setGeometry(screenWidth/3+230,screenHeight/3+250, 100,50);
    scene->addWidget(quit);

     QObject::connect(quit,&QPushButton::clicked,[=](){exit();});

     timer->stop();
     timer2->stop();
}

void GameManager::Win()
{
    int screenWidth = QGuiApplication::primaryScreen()->availableSize().width();
    int screenHeight = QGuiApplication::primaryScreen()->availableSize().height();
    for (size_t i = 0, n = scene->items().size(); i < n; i++){
            scene->items()[i]->setEnabled(false);
        }
    // back ground panel and main
     panels = new QGraphicsRectItem*[2];

//    panels[0] = drawPanel(0,0,screenWidth,screenHeight,Qt::black,0.65);
    panels[1] = drawPanel(screenWidth/3-20,screenHeight/3-20,400,400,Qt::lightGray,1);

    /* Gmae Over Text*/
    QGraphicsTextItem* overText = new QGraphicsTextItem("You WON!!!!!!");
     QFont fonty("Arial", 20, QFont::StyleNormal);
    overText->setPos(screenWidth/3 + 100,screenHeight/3+80);
    overText->setFont(fonty);
    scene->addItem(overText);

    QPushButton *p =new QPushButton;
    p->setText("PLAY AGAIN");
    p->setGeometry(screenWidth/3+40,screenHeight/3+250, 100,50);
    scene->addWidget(p);

    QObject::connect(p, &QPushButton::clicked, this, [=] () {
            restart_game();
        }, Qt::QueuedConnection);

    QPushButton* quit;
    quit=new QPushButton("Quit");
    quit->setGeometry(screenWidth/3+230,screenHeight/3+250, 100,50);
    scene->addWidget(quit);

     QObject::connect(quit,&QPushButton::clicked,[=](){exit();});

     timer->stop();
     timer2->stop();
}

class enemy1* GameManager::retenemy1()
{
    return enemy1;
}
class enemy2* GameManager::retenemy2()
{
    return enemy2;
}
