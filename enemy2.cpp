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

    QPixmap enemy2Image(":assets/images/Gangster-Wars-2D-Game-Kit14.png");

    int screenWidth = QGuiApplication::primaryScreen()->availableSize().width();
    int screenHeight = QGuiApplication::primaryScreen()->availableSize().height();
    int unitWidth = qMin(screenWidth, screenHeight) / 12;
    int unitHeight = qMin(screenWidth, screenHeight) / 12;

    enemy2Image = enemy2Image.scaledToWidth(unitWidth);
    enemy2Image = enemy2Image.scaledToHeight(unitHeight);

    setPixmap(enemy2Image);
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
