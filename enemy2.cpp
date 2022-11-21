#include "enemy2.h"
#include "franklin.h"
#include <QGraphicsScene>
#include <QKeyEvent>
#include <QList>
#include <QGuiApplication>
#include <QTimer>
#include "gamemanager.h"


enemy2::enemy2(int boardData[12][16], void * gameManager)
{
    this->gameManager = gameManager;

    QPixmap enemy2FLImage(":assets/images/GangsterFL.png");

    int screenWidth = QGuiApplication::primaryScreen()->availableSize().width();
    int screenHeight = QGuiApplication::primaryScreen()->availableSize().height();
    int unitWidth = qMin(screenWidth, screenHeight) / 12;
    int unitHeight = qMin(screenWidth, screenHeight) / 12;

    enemy2FLImage = enemy2FLImage.scaledToWidth(unitWidth);
    enemy2FLImage = enemy2FLImage.scaledToHeight(unitHeight);

    setPixmap(enemy2FLImage);
    health = 2;
    x = 3;
    y = 11;
    direction = 0;

    setPos(unitWidth + y * unitWidth, unitHeight + x * unitHeight);

    for(int i = 0; i < 12; i++){
        for(int j = 0; j < 16; j++){
            this->boardData[i][j] = boardData[i][j];
        }
    }
}

void enemy2::move(){
    int screenWidth = QGuiApplication::primaryScreen()->availableSize().width();
    int screenHeight = QGuiApplication::primaryScreen()->availableSize().height();
    int unitWidth = qMin(screenWidth, screenHeight) / 12;
    int unitHeight = qMin(screenWidth, screenHeight) / 12;
    QPixmap enemy2FLImage(":assets/images/GangsterFL.png");
    QPixmap enemy2FRImage(":assets/images/GangsterFR.png");
    QPixmap enemy2HLImage(":assets/images/GangsterHL.png");
    QPixmap enemy2HRImage(":assets/images/GangsterHR.png");

    enemy2FLImage = enemy2FLImage.scaledToWidth(unitWidth);
    enemy2FLImage = enemy2FLImage.scaledToHeight(unitHeight);

    enemy2FRImage = enemy2FRImage.scaledToWidth(unitWidth);
    enemy2FRImage = enemy2FRImage.scaledToHeight(unitHeight);

    enemy2HLImage = enemy2HLImage.scaledToWidth(unitWidth);
    enemy2HLImage = enemy2HLImage.scaledToHeight(unitHeight);

    enemy2HRImage = enemy2HRImage.scaledToWidth(unitWidth);
    enemy2HRImage = enemy2HRImage.scaledToHeight(unitHeight);

    if (direction == 0 && boardData[x - 1][y] >= 0)
    {
        x--;
    }
    else if (direction == 1 && boardData[x + 1][y] >= 0)
    {
        x++;
    }
    else if (direction == 2 && boardData[x][y + 1] >= 0)
    {
        y++;
        if(health == 2)
        {
            setPixmap(enemy2FRImage);
        }
        else if(health == 1)
        {
            setPixmap(enemy2HRImage);
        }
    }
    else if (direction == 3 && boardData[x][y - 1] >= 0)
    {
        y--;
        if(health == 2)
        {
            setPixmap(enemy2FLImage);
        }
        else if(health == 1)
        {
            setPixmap(enemy2HLImage);
        }
    }
    else
    {
        direction = rand() % 4;
    }

    setPos(unitWidth + y * unitWidth, unitHeight + x * unitHeight);

    checkCollision();
}

void enemy2::checkCollision(){
    int screenWidth = QGuiApplication::primaryScreen()->availableSize().width();
    int screenHeight = QGuiApplication::primaryScreen()->availableSize().height();
    int unitWidth = qMin(screenWidth, screenHeight) / 12;
    int unitHeight = qMin(screenWidth, screenHeight) / 12;
    QList<QGraphicsItem *> colliding_items = collidingItems();
    for (int i = 0, n = colliding_items.size(); i < n; ++i)
    {
        if (typeid(*(colliding_items[i])) == typeid(Franklin))
        {
            this->x = 3;
            this->y = 11;

            GameManager * manager = static_cast<GameManager *>(gameManager);
            manager->franklin_hit();
            setPos(unitWidth + y * unitWidth, unitHeight + x * unitHeight);
        }
    }
}

int enemy2::getX()
{
    return this->x;
}

int enemy2::getY()
{
    return this->y;
}

void enemy2::reduceHealth()
{
    this->health--;
    if (health == 0)
    {
        this->setVisible(false);
    }
}
