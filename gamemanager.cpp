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
#include <QGraphicsRectItem> //added
#include<qprocess.h>


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
    launch_game();
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

void GameManager::shoot()
{
    int dis_1 = pow((franklin->getX() - enemy1->getX()),2);
    dis_1 += pow((franklin->getY() - enemy1->getY()),2);
    dis_1 = sqrt(dis_1);
    int dis_2 = pow((franklin->getX() - enemy2->getX()),2);
    dis_2 += pow((franklin->getY() - enemy2->getY()),2);
    dis_2 = sqrt(dis_2);
    if(dis_1 < dis_2)
    {
        enemy1->reduceHealth();
    }
    else
    {
        enemy2->reduceHealth();
    }
//    QMediaPlayer *player1 = new QMediaPlayer;
//    QAudioOutput *audioOutput1 = new QAudioOutput;
//    player1->setAudioOutput(audioOutput1);
//    player1->setSource(QUrl("qrc:/assets/sounds/shot.mp3"));
//    player1->play();
}

void GameManager::launch_game() {
    scene->clear();

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
                boardItems[i][j].setPixmap(arrowImage);
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

void enemy1_move()
{
    if (GameManager::enemy1 != nullptr)
    {
        GameManager::enemy1->move();
    }
}

void enemy2_move()
{
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

    QTimer *timer = new QTimer();
    QObject::connect(timer, &QTimer::timeout, player_focus);
    timer->start(350);
}

void GameManager::create_enemies()
{
    enemy1 = new class enemy1(boardData, this);
    scene->addItem(enemy1);

    QTimer *timer2 = new QTimer();
    QObject::connect(timer2, &QTimer::timeout, enemy1_move);
    timer2->start(400);

    enemy2 = new class enemy2(boardData, this);
    scene->addItem(enemy2);

    QTimer *timer4 = new QTimer();
    QObject::connect(timer4, &QTimer::timeout, enemy2_move);
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

void GameManager::create_pellets()
{
    pellet1 = new class pellet(boardData, 9, 1);
    pellet2 = new class pellet(boardData, 4, 14);
    drunk = new class Drunk(boardData, 1, 3);
    scene->addItem(pellet1);
    scene->addItem(pellet2);
    scene->addItem(drunk);
}

void GameManager::create_healthbar() {
    int screenWidth = QGuiApplication::primaryScreen()->availableSize().width();
    int screenHeight = QGuiApplication::primaryScreen()->availableSize().height();
    int unitWidth = qMin(screenWidth, screenHeight) / 17;
    int unitHeight = qMin(screenWidth, screenHeight) / 17;
    int unitHeight2 = qMin(screenWidth, screenHeight) / 12;

    QGraphicsRectItem*panel=new QGraphicsRectItem(65,0,1070,70);
    QBrush brush;
    brush.setColor(Qt::darkGray);
    brush.setStyle(Qt::SolidPattern);
    panel->setBrush(brush);
    scene->addItem(panel);

    if(franklin->getIsPowerful() && franklin->getIsDrunk())
    {
        QGraphicsTextItem *txt= new QGraphicsTextItem("Powerful and Drunk Mode");
        QFont fonty("Arial", 20, QFont::StyleNormal);
        txt->setPos(500,20);
        txt->setFont(fonty);
        txt->setDefaultTextColor(Qt::darkBlue);
        scene->addItem(txt);
    }
    else if(franklin->getIsPowerful())
    {
        QGraphicsTextItem *txt= new QGraphicsTextItem("Powerful Mode");
        QFont fonty("Arial", 20, QFont::StyleNormal);
        txt->setPos(500,20);
        txt->setFont(fonty);
        txt->setDefaultTextColor(Qt::darkBlue);
        scene->addItem(txt);
    }
    else if(franklin->getIsDrunk())
    {
        QGraphicsTextItem *txt= new QGraphicsTextItem("Drunk Mode");
        QFont fonty("Arial", 20, QFont::StyleNormal);
        txt->setPos(500,20);
        txt->setFont(fonty);
        txt->setDefaultTextColor(Qt::darkBlue);
        scene->addItem(txt);
    }
    else
    {
        QGraphicsTextItem *txt= new QGraphicsTextItem("NORMAL MODE");
        QFont fonty("Arial", 20, QFont::StyleNormal);
        txt->setPos(500,20);
        txt->setFont(fonty);
        txt->setDefaultTextColor(Qt::darkBlue);
        scene->addItem(txt);
    }


  /* Creating Hearts */
    hearts= new QGraphicsPixmapItem[3];


    QPixmap blankImage(":assets/images/extra.png");

    blankImage = blankImage.scaledToWidth(unitWidth);
    blankImage = blankImage.scaledToHeight(unitHeight);
    for (int i = 0; i<franklin->getHealth() ; i++)
    {
        hearts[i].setPixmap(blankImage);
        hearts[i].setPos(80*(i+1), 15);
        scene->addItem( &hearts[i]);
    }


    /*Drunk and label part */

//    QLabel *label = new QLabel();
//    if(franklin->getIsPowerful())
//    {
//        label->setText("Powerful Mode");
//    }
//    else
//    {
//        label->setText("Normal Mode");
//    }

//    label->setAlignment(Qt::AlignCenter);
//    label->move(-1.5*unitWidth, 3 *unitHeight2);

//    scene->addWidget(label);

//    QLabel *label2 = new QLabel();
//    if(franklin->getIsDrunk())
//    {
//        label2->setText("Drunk");
//    }
//    else
//    {
//        label2->setText("Not Drunk");
//    }

//    label2->setAlignment(Qt::AlignCenter);
//    label2->move(-1.5*unitWidth, 6 *unitHeight2);

//    scene->addWidget(label2);

}

void GameManager::remove_heart()
{

        int health = franklin->getHealth();

        if (health >= 0){
            scene->removeItem(&hearts[health]);
        }

        if(health == 2){

            game_over();
        }
}

void GameManager::franklin_hit() {
    franklin->hit();
}


void GameManager::drawPanel(int x, int y, int width, int height, QColor color, double opacity){
    // draws a panel at the specified location with the specified properties
    QGraphicsRectItem* panel = new QGraphicsRectItem(x,y,width,height);
    QBrush brush;
    brush.setStyle(Qt::SolidPattern);
    brush.setColor(color);
    panel->setBrush(brush);
    panel->setOpacity(opacity);
    scene->addItem(panel);
}



void GameManager::game_over()
{
    int screenWidth = QGuiApplication::primaryScreen()->availableSize().width();
    int screenHeight = QGuiApplication::primaryScreen()->availableSize().height();
    for (size_t i = 0, n = scene->items().size(); i < n; i++){
            scene->items()[i]->setEnabled(false);
        }
    // back ground panel and main
    drawPanel(0,0,screenWidth,screenHeight+100,Qt::black,0.65);
    drawPanel(screenWidth/3,screenHeight/3,400,400,Qt::lightGray,0.85);

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
    QObject::connect(p,&QPushButton::clicked,p,std::move([=](){restart_game();}), Qt::QueuedConnection);

    QPushButton* quit;
    quit=new QPushButton("Quit");
    quit->setGeometry(screenWidth/3+230,screenHeight/3+250, 100,50);
    scene->addWidget(quit);

     QObject::connect(quit,&QPushButton::clicked,[=](){exit();});
}




