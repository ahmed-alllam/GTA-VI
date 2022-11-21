#include "dog.h"
#include "franklin.h"
#include <QGraphicsScene>
#include <QKeyEvent>
#include <QList>
#include <QGuiApplication>
#include <QTimer>
#include "gamemanager.h"


dog::dog(int boardData[12][16], void * gameManager)
{
    this->gameManager = gameManager;

    QPixmap dogImage(":assets/images/dog-muzzle-animation-pet-dog-footage-160116428_iconl.png");

    int screenWidth = QGuiApplication::primaryScreen()->availableSize().width();
    int screenHeight = QGuiApplication::primaryScreen()->availableSize().height();
    int unitWidth = qMin(screenWidth, screenHeight) / 12;
    int unitHeight = qMin(screenWidth, screenHeight) / 12;

    dogImage = dogImage.scaledToWidth(unitWidth);
    dogImage = dogImage.scaledToHeight(unitHeight);

    setPixmap(dogImage);
	health = 2;
    x = 1;
    y = 14;
    direction = 0;

    setPos(unitWidth + y * unitWidth, unitHeight + x * unitHeight);

    for(int i = 0; i < 12; i++){
        for(int j = 0; j < 16; j++){
            this->boardData[i][j] = boardData[i][j];
        }
    }
}

void dog::move(){
    int screenWidth = QGuiApplication::primaryScreen()->availableSize().width();
    int screenHeight = QGuiApplication::primaryScreen()->availableSize().height();
    int unitWidth = qMin(screenWidth, screenHeight) / 12;
    int unitHeight = qMin(screenWidth, screenHeight) / 12;

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
    }
    else if (direction == 3 && boardData[x][y - 1] >= 0)
    {
        y--;
    }
    else
    {
        direction = rand() % 4;
    }

    setPos(unitWidth + y * unitWidth, unitHeight + x * unitHeight);

    checkCollision();
}

void dog::checkCollision(){
    int screenWidth = QGuiApplication::primaryScreen()->availableSize().width();
    int screenHeight = QGuiApplication::primaryScreen()->availableSize().height();
    int unitWidth = qMin(screenWidth, screenHeight) / 12;
    int unitHeight = qMin(screenWidth, screenHeight) / 12;
    QList<QGraphicsItem *> colliding_items = collidingItems();
    for (int i = 0, n = colliding_items.size(); i < n; ++i)
    {
        if (typeid(*(colliding_items[i])) == typeid(Franklin))
        {
            this->x = 1;
            this->y = 14;

            GameManager * manager = static_cast<GameManager *>(gameManager);
            manager->franklin_hit();
            setPos(unitWidth + y * unitWidth, unitHeight + x * unitHeight);
        }
    }
}

int dog::getX()
{
    return this->x;
}

int dog::getY()
{
    return this->y;
}

void dog::reduceHealth()
{
    this->health--;
    if (health == 0)
    {
        this->setVisible(false);
    }
}
