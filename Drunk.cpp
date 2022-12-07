#include "Drunk.h"
#include <QGraphicsScene>
#include <QKeyEvent>
#include <QList>
#include <QGuiApplication>


Drunk::Drunk(int boardData[12][16], int x, int y)
{
    QPixmap bottleImage(":assets/images/Whiskey.png");

    int screenWidth = QGuiApplication::primaryScreen()->availableSize().width();
    int screenHeight = QGuiApplication::primaryScreen()->availableSize().height();
    int unitWidth = qMin(screenWidth, screenHeight) / 13;
    int unitHeight = qMin(screenWidth, screenHeight) / 13;

    bottleImage = bottleImage.scaledToWidth(unitWidth/1.3);
    bottleImage = bottleImage.scaledToHeight(unitHeight/1.3);

    setPixmap(bottleImage);

    this->x = x;
    this->y = y;

    setPos(unitWidth + y * unitWidth, unitHeight + x * unitHeight);
}
