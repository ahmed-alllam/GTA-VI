#include "extra_life.h"
#include <QGraphicsScene>
#include <QKeyEvent>
#include <QList>
#include <QGuiApplication>
#include <QTimer>
#include <QtGlobal>
bool extra_life::available=false;

extra_life::extra_life(int boardData[12][16], int x, int y)
{


    QPixmap bombimage(":/assets/images/extra-health.png");

    int screenWidth = QGuiApplication::primaryScreen()->availableSize().width();
    int screenHeight = QGuiApplication::primaryScreen()->availableSize().height();
    int unitWidth = qMin(screenWidth, screenHeight) / 13;
    int unitHeight = qMin(screenWidth, screenHeight) / 13;

    bombimage = bombimage.scaledToWidth(unitWidth);
    bombimage = bombimage.scaledToHeight(unitHeight);

    setPixmap(bombimage);

    this->x = x;
    this->y = y;

    setPos(unitWidth + y * unitWidth, unitHeight + x * unitHeight);

}

bool extra_life::is_available()
{
    return available;
}

void extra_life::make_available()
{
    available = true;
}

