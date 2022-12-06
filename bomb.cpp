#include "bomb.h"
#include <QGraphicsScene>
#include <QKeyEvent>
//#include <QList>
#include <QGuiApplication>
bomb::bomb(int boardData[12][16], int x, int y)
{
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
