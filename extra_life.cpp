#include "extra_life.h"
#include <QGraphicsScene>
#include <QKeyEvent>
#include <QList>
#include <QGuiApplication>
#include <QTimer>
#include <QtGlobal>
#include <cstdlib>
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

 /*   this->x = x;
    this->y = y;*/ //useless
    for (int i = 0; i < 12; i++)
    {
        for (int j = 0; j < 16; j++)
        {
            this->boardData[i][j] = boardData[i][j];
        }
    }
    srand(time(0));
    int a=rand()%12, b=rand()%16;
    while(this->boardData[a][b]<0 || (a== 1&& b==1 )|| (a== 1 && b==14 )|| (a== 10&& b==1 )|| (a== 10&& b==14 )|| (a== 8&& b==1)|| (a== 5&& b==11 ))
    {
        a=rand()%12;
        b=rand()%16;
    }

    //setPos(unitWidth + y * unitWidth, unitHeight + x * unitHeight);
    setPos(unitWidth + b * unitWidth, unitHeight + a * unitHeight);

}

bool extra_life::is_available()
{
    return available;
}

void extra_life::make_available()
{
    available = true;
}

