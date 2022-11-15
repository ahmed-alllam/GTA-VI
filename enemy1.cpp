#include "enemy1.h"
#include <QGraphicsScene>
#include <QKeyEvent>
#include <QList>
#include <QGuiApplication>

enemy1::enemy1(int boardData[12][16])
{
    QPixmap enemy1Image(":assets/images/Gangster-Wars-2D-Game-Kit14.png");

    int screenWidth = QGuiApplication::primaryScreen()->availableSize().width();
    int screenHeight = QGuiApplication::primaryScreen()->availableSize().height();
    int unitWidth = qMin(screenWidth, screenHeight) / 12;
    int unitHeight = qMin(screenWidth, screenHeight) / 12;

    enemy1Image = enemy1Image.scaledToWidth(unitWidth);
    enemy1Image = enemy1Image.scaledToHeight(unitHeight);

    setPixmap(enemy1Image);

    x = 3;
    y = 7;

    setPos(unitWidth + y * unitWidth, unitHeight + x * unitHeight);

    for(int i = 0; i < 12; i++){
        for(int j = 0; j < 16; j++){
            this->boardData[i][j] = boardData[i][j];
        }
    }
}

void enemy1::move(){
    int screenWidth = QGuiApplication::primaryScreen()->availableSize().width();
    int screenHeight = QGuiApplication::primaryScreen()->availableSize().height();
    int unitWidth = qMin(screenWidth, screenHeight) / 12;
    int unitHeight = qMin(screenWidth, screenHeight) / 12;

    int direction = rand() % 4;

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

    setPos(unitWidth + y * unitWidth, unitHeight + x * unitHeight);
}