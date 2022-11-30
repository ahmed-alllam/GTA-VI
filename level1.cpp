#include "level1.h"
#include "gamemanager.h"
#include "flyingbullet.h"

#include <QGuiApplication>
#include <QFile>
#include <QGraphicsProxyWidget>
#include <QPushButton>

level1::level1(void *gameManager, QGraphicsScene *scene)
{
    this->gameManager = gameManager;
    this->scene = scene;
    qDebug() << scene;
}

void level1::add_board_images()
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
    boardItems = new QGraphicsPixmapItem *[12];
    for (int i = 0; i < 12; i++)
    {
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

void level1::create_board()
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

void level1::create_player()
{
    franklin = new Franklin(boardData, this);
    scene->addItem(franklin);

    timer = new QTimer();
    QObject::connect(timer, &QTimer::timeout, franklin, &Franklin::focus_player);
    timer->start(350);
}

void level1::create_enemies()
{
    enemy1 = new class enemy1(boardData, this);
    scene->addItem(enemy1);

    enemy2 = new class enemy2(boardData, this);
    scene->addItem(enemy2);

    timer2 = new QTimer();
    QObject::connect(timer2, &QTimer::timeout, enemy1, &enemy1::move);
    QObject::connect(timer2, &QTimer::timeout, enemy2, &enemy2::move);
    timer2->start(400);
}

void level1::create_bullets()
{
    bullet *bullet1 = new class bullet(boardData, 1, 1);
    bullet *bullet2 = new class bullet(boardData, 10, 14);
    bullet *bullet3 = new class bullet(boardData, 10, 1);
    bullet *bullet4 = new class bullet(boardData, 1, 14);

    bullets.clear();

    bullets.push_back(bullet1);
    bullets.push_back(bullet2);
    bullets.push_back(bullet3);
    bullets.push_back(bullet4);

    for (int i = 0; i < bullets.size(); i++)
    {
        scene->addItem(bullets[i]);
    }
}

void level1::remove_bullets()
{
    for (int i = 0; i < bullets.size(); i++)
    {
        if (bullets[i] != nullptr)
        {
            scene->removeItem(bullets[i]);
            delete bullets[i];
            bullets[i] = nullptr;
        }
    }
}

void level1::create_pellets()
{
    pellet *pellet1 = new class pellet(boardData, 9, 1);
    pellet *pellet2 = new class pellet(boardData, 4, 14);

    pellets.push_back(pellet1);
    pellets.push_back(pellet2);

    drunk = new class Drunk(boardData, 1, 3);

    for (int i = 0; i < pellets.size(); i++)
    {
        scene->addItem(pellets[i]);
    }
    scene->addItem(drunk);
}

void level1::updateModeTxt()
{
    GameManager *manager = static_cast<GameManager *>(gameManager);

    if (manager->txt != nullptr && franklin != nullptr)
    {
        if (franklin->getIsPowerful() && franklin->getIsDrunk())
        {
            manager->txt->setPlainText("Powerful and Drunk Mode");
        }
        else if (franklin->getIsPowerful())
        {
            manager->txt->setPlainText("Powerful Mode");
        }
        else if (franklin->getIsDrunk())
        {
            manager->txt->setPlainText("Drunk Model");
        }
        else
        {
            manager->txt->setPlainText("Normal Model");
        }
    }
}

void level1::open_gate()
{
    boardData[9][15] = 50;
    franklin->editboard(50);
    GameManager *manager = static_cast<GameManager *>(gameManager);
    manager->open_gate();
}

void level1::close_gate()
{
    boardData[9][15] = -50;
    franklin->editboard(-50);
}

void level1::updateCounters()
{
    GameManager *manager = static_cast<GameManager *>(gameManager);

    if (manager->bulletsCounter != nullptr)
        manager->bulletsCounter->setPlainText(QString::number(franklin->getBulletsCount()));
    if (manager->coinsCounter != nullptr)
        manager->coinsCounter->setPlainText(QString::number(franklin->getCoinsCount()));
}

void level1::remove_heart()
{
    GameManager *manager = static_cast<GameManager *>(gameManager);
    int health = franklin->getHealth();

    if (health >= 0)
    {
        scene->removeItem(&(manager->hearts[health]));
    }

    if (health == 0)
    {
        manager->game_over();
        timer2->stop();
    }
}

void level1::restart_game()
{
    QList<QGraphicsItem *> items = scene->items();

    franklin = nullptr;
    enemy1 = nullptr;
    enemy2 = nullptr;

    // remove bullets
    bullets.clear();

    // remove pellets
    pellets.clear();
    drunk = nullptr;

    for (int i = 0; i < items.size(); i++)
    {
        if (typeid(*items[i]) == typeid(QGraphicsProxyWidget) || typeid(*items[i]) == typeid(QGraphicsTextItem) || typeid(*items[i]) == typeid(QPushButton) || typeid(*items[i]) == typeid(QGraphicsRectItem) || typeid(*items[i]) == typeid(bullet) || typeid(*items[i]) == typeid(class Franklin) || typeid(*items[i]) == typeid(class enemy1) || typeid(*items[i]) == typeid(class enemy2) || typeid(*items[i]) == typeid(class Drunk) || typeid(*items[i]) == typeid(class pellet) || typeid(*items[i]) == typeid(class FlyingBullet))
        {
            scene->removeItem(items[i]);
            delete items[i];
        }
    }

    // delete boardItems (2d dynamic array) from memory and scene
    for (int i = 0; i < 12; i++)
    {
        for (int j = 0; j < 16; j++)
        {
            if ((boardItems[i]+j) != nullptr)
            {
                scene->removeItem((boardItems[i]+j));
            }
        }

        delete[] boardItems[i];
        boardItems[i] = nullptr;
    }

}

void level1::player_hit()
{
    if (enemy1 != nullptr)
        enemy1->setXandY(9, 8);
    if (enemy2 != nullptr)
        enemy2->setXandY(3, 11);

    franklin->hit();
}

void level1::enemy_hit(QGraphicsItem *enemy)
{

    if (typeid(*enemy) == typeid(class enemy1) && enemy1 != nullptr)
    {
        enemy1->reduceHealth();
        if (enemy1->getHealth() == 0)
        {
            if (enemy2 == nullptr)
            {
                open_gate();
            }
            scene->removeItem(enemy1);
            enemy1 = nullptr;
            delete enemy1;
        }
    }
    else if (typeid(*enemy) == typeid(class enemy2) && enemy2 != nullptr)
    {
        enemy2->reduceHealth();
        if (enemy2->getHealth() == 0)
        {
            if (enemy1 == nullptr)
            {
                open_gate();
            }
            scene->removeItem(enemy2);
            enemy2 = nullptr;
            delete enemy2;
        }
    }
}

void level1::create_healthbar()
{
}

void level1::win()
{
    GameManager *manager = static_cast<GameManager *>(gameManager);
    manager->Win();
    timer2->stop();
}

void level1::getData(int data[12][16])
{
    data = boardData;
}

void level1::getDest(int& i, int& j)
{
    i = franklin->getX();
    j = franklin->getY();
}
