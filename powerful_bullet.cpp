#include "powerful_bullet.h"
#include <QGraphicsScene>
#include <QKeyEvent>
#include <QList>
#include <QGuiApplication>
bool powerful_bullet::available=false; //buyed  or not

powerful_bullet::powerful_bullet(int boardData[12][16], int x, int y)
{
    QPixmap bulletImage(":/assets/images/powerfull-bulletsU.png");

    int screenWidth = QGuiApplication::primaryScreen()->availableSize().width();
    int screenHeight = QGuiApplication::primaryScreen()->availableSize().height();
    int unitWidth = qMin(screenWidth, screenHeight) / 13;
    int unitHeight = qMin(screenWidth, screenHeight) / 13;

    bulletImage = bulletImage.scaledToWidth(unitWidth);
    bulletImage = bulletImage.scaledToHeight(unitHeight);
    setPixmap(bulletImage);
    this->x = x;
    this->y = y;

    setPos(unitWidth + y * unitWidth, unitHeight + x * unitHeight);
}

bool powerful_bullet::is_available()
{
    return available;
}

void powerful_bullet::make_available()
{
    available=true;
}
