#include "released_bomb.h"
#include <QGraphicsScene>
#include <QKeyEvent>
#include <QList>
#include <QGuiApplication>
#include <QTimer>
#include "enemy1.h"
#include "level.h"
#include "gamemanager.h"
released_bomb::released_bomb(int boardData[12][16], int x, int y,int direction, void *manager)
{

   QPixmap bombimage(":/assets/images/time-bomb.png");

    int screenWidth = QGuiApplication::primaryScreen()->availableSize().width();
    int screenHeight = QGuiApplication::primaryScreen()->availableSize().height();
    int unitWidth = qMin(screenWidth, screenHeight) / 13;
  int unitHeight = qMin(screenWidth, screenHeight) / 13;
  int unitHeight2 = qMin(screenWidth, screenHeight) / 17;

    bombimage = bombimage.scaledToWidth(unitHeight2);
    bombimage = bombimage.scaledToHeight(unitHeight2);

    setPixmap(bombimage);// that line causes an issue in the counter of bombs

    this->x = x;
    this->y = y;
    this->manager= manager;
//    if (direction == 0 /*&& boardData[y+1][x]>0*/)  //should  check if there is a block
//    {
//        y++;
//    }
//    else if (direction == 1 /*&& boardData[y-1][x]>0*/)
//    {
//        y--;
//    }
//    else if (direction == 2 /*&& boardData[y][x+1]>0*/)
//    {
//      x--;
//    }
//    else /*if(direction==3 /*&& boardData[y][x-1]>0)*/
//    {
//      x++;
//    }

    setPos( unitWidth + y * unitWidth, unitHeight + x * unitHeight);
    for (int i = 0; i < 12; i++)
    {
        for (int j = 0; j < 16; j++)
        {
            this->boardData[i][j] = boardData[i][j];
        }
    }
}
