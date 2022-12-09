#include "bullet.h"
#include <QGraphicsScene>
#include <QKeyEvent>
#include <QList>
#include <QGuiApplication>

bool bullet::available=false; //related to the market

bullet::bullet(int boardData[12][16], int x, int y)
{
    QPixmap bulletImage(":assets/images/bullet.png");

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
bullet::bullet(int boardData[12][16], int x, int y, QString type)
{
    powerful = true;
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

bool bullet::is_available()
{
    return available;
}

void bullet::make_available()
{
    available = true;
}

bool bullet::is_powerful()
{
    return powerful;
}
