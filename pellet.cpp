#include "pellet.h"
#include <QGraphicsScene>
#include <QKeyEvent>
#include <QList>
#include <QGuiApplication>

pellet::pellet(int boardData[12][16], int x, int y)
{
    QPixmap pelletImage(":assets/images/coin.png");

    int screenWidth = QGuiApplication::primaryScreen()->availableSize().width();
    int screenHeight = QGuiApplication::primaryScreen()->availableSize().height();
    int unitWidth = qMin(screenWidth, screenHeight) / 13;
    int unitHeight = qMin(screenWidth, screenHeight) / 13;

    pelletImage = pelletImage.scaledToWidth(unitWidth);
    pelletImage = pelletImage.scaledToHeight(unitHeight);

    setPixmap(pelletImage);
    taken = false;

    this->x = x;
    this->y = y;

    setPos(unitWidth + y * unitWidth, unitHeight + x * unitHeight);
}
