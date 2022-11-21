#include "enemy1.h"
#include "franklin.h"
#include <QGraphicsScene>
#include <QKeyEvent>
#include <QList>
#include <QGuiApplication>
#include <QTimer>
#include "gamemanager.h"


enemy1::enemy1(int boardData[12][16], void * gameManager)
{
    this->gameManager = gameManager;

    QPixmap enemy1FLImage(":assets/images/GangsterFL.png");

    int screenWidth = QGuiApplication::primaryScreen()->availableSize().width();
    int screenHeight = QGuiApplication::primaryScreen()->availableSize().height();
    int unitWidth = qMin(screenWidth, screenHeight) / 12;
    int unitHeight = qMin(screenWidth, screenHeight) / 12;

    enemy1FLImage = enemy1FLImage.scaledToWidth(unitWidth);
    enemy1FLImage = enemy1FLImage.scaledToHeight(unitHeight);

    setPixmap(enemy1FLImage);
	health = 2;
    x = 9;
    y = 8;
    direction = 0;

    setPos(unitWidth + y * unitWidth, unitHeight + x * unitHeight);

    for(int i = 0; i < 12; i++){
        for(int j = 0; j < 16; j++){
            this->boardData[i][j] = boardData[i][j];
        }
    }
}

void enemy1::move(){
    int screenWidth = QGuiApplication::primaryScreen()->availableSize().width();
    int screenHeight = QGuiApplication::primaryScreen()->availableSize().height();
    int unitWidth = qMin(screenWidth, screenHeight) / 12;
    int unitHeight = qMin(screenWidth, screenHeight) / 12;
    QPixmap enemy1FLImage(":assets/images/GangsterFL.png");
    QPixmap enemy1FRImage(":assets/images/GangsterFR.png");
    QPixmap enemy1HLImage(":assets/images/GangsterHL.png");
    QPixmap enemy1HRImage(":assets/images/GangsterHR.png");

    enemy1FLImage = enemy1FLImage.scaledToWidth(unitWidth);
    enemy1FLImage = enemy1FLImage.scaledToHeight(unitHeight);

    enemy1FRImage = enemy1FRImage.scaledToWidth(unitWidth);
    enemy1FRImage = enemy1FRImage.scaledToHeight(unitHeight);

    enemy1HLImage = enemy1HLImage.scaledToWidth(unitWidth);
    enemy1HLImage = enemy1HLImage.scaledToHeight(unitHeight);

    enemy1HRImage = enemy1HRImage.scaledToWidth(unitWidth);
    enemy1HRImage = enemy1HRImage.scaledToHeight(unitHeight);

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
            setPixmap(enemy1FRImage);
        }
        else if(health == 1)
        {
            setPixmap(enemy1HRImage);
        }
    }
    else if (direction == 3 && boardData[x][y - 1] >= 0)
    {
        y--;
        if(health == 2)
        {
            setPixmap(enemy1FLImage);
        }
        else if(health == 1)
        {
            setPixmap(enemy1HLImage);
        }
    }
    else
    {
        direction = rand() % 4;
    }

    setPos(unitWidth + y * unitWidth, unitHeight + x * unitHeight);

    checkCollision();
}

void enemy1::checkCollision(){
    int screenWidth = QGuiApplication::primaryScreen()->availableSize().width();
    int screenHeight = QGuiApplication::primaryScreen()->availableSize().height();
    int unitWidth = qMin(screenWidth, screenHeight) / 12;
    int unitHeight = qMin(screenWidth, screenHeight) / 12;
    QList<QGraphicsItem *> colliding_items = collidingItems();
    for (int i = 0, n = colliding_items.size(); i < n; ++i)
    {
        if (typeid(*(colliding_items[i])) == typeid(Franklin))
        {
            this->x = 9;
            this->y = 8;

            GameManager * manager = static_cast<GameManager *>(gameManager);
            manager->franklin_hit();
            setPos(unitWidth + y * unitWidth, unitHeight + x * unitHeight);
        }
    }
}

int enemy1::getX()
{
    return this->x;
}

int enemy1::getY()
{
    return this->y;
}

void enemy1::reduceHealth()
{
    this->health--;
    if (health == 0)
    {
        this->setVisible(false);
    }
}
