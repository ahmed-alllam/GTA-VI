#include "bomb.h"
#include <QGraphicsScene>
#include <QKeyEvent>
#include <QList>
#include <QGuiApplication>
#include <QTimer>
#include "enemy1.h"
#include "enemy2.h"
#include "level.h"
#include "gamemanager.h"
bomb::bomb(int boardData[12][16], int x, int y)
{
    //available=false;
    QPixmap bombimage(":/assets/images/time-bomb.png");

    int screenWidth = QGuiApplication::primaryScreen()->availableSize().width();
    int screenHeight = QGuiApplication::primaryScreen()->availableSize().height();
    int unitWidth = qMin(screenWidth, screenHeight) / 12;
    int unitHeight = qMin(screenWidth, screenHeight) / 12;

    bombimage = bombimage.scaledToWidth(unitWidth);
    bombimage = bombimage.scaledToHeight(unitHeight);

    setPixmap(bombimage);

    this->x = x;
    this->y = y;

    setPos(unitWidth + y * unitWidth, unitHeight + x * unitHeight);
}

bomb::bomb(int boardData[12][16], int x, int y, void *manager)
{

   QPixmap bombimage(":/assets/images/coin.png");

    int screenWidth = QGuiApplication::primaryScreen()->availableSize().width();
    int screenHeight = QGuiApplication::primaryScreen()->availableSize().height();
    int unitWidth = qMin(screenWidth, screenHeight) / 12;
  int unitHeight = qMin(screenWidth, screenHeight) / 12;

    bombimage = bombimage.scaledToWidth(unitWidth);
    bombimage = bombimage.scaledToHeight(unitHeight);

    setPixmap(bombimage);// that line causes an issue in the counter of bombs

    this->x = x;
    this->y = y;
    this->manager= manager;
    setPos(unitWidth + y * unitWidth, unitHeight + x * unitHeight);
    for (int i = 0; i < 12; i++)
    {
        for (int j = 0; j < 16; j++)
        {
            this->boardData[i][j] = boardData[i][j];
        }
    }

}

//bool bomb::is_available()
//{
//    return available;
//}

void bomb::waiting_to_bomb()
{
    QList<QGraphicsItem *> colliding_items = collidingItems();
    level *manager2 = static_cast<level *>(manager);

    for (int i = 0; i < colliding_items.size(); i++)
    {
        if (typeid(*colliding_items[i]) == typeid(enemy1) || typeid(*colliding_items[i]) == typeid(enemy2))
        {
            scene()->removeItem(this);
            delete this;
            manager2->enemy_hit(colliding_items[i]);
            return;
        }
    }
}

//bomb::~bomb()
//{

//}

