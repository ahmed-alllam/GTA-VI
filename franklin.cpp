// make the class for the franklin

#include "franklin.h"
#include <QGraphicsScene>
#include <QKeyEvent>
#include <QList>

Franklin::Franklin(int boardData[10][10]){

    QPixmap franklinImage(":assets/images/Franklin.png");

    int unitWidth = 100;
    int unitHeight = 100;

    franklinImage = franklinImage.scaledToWidth(unitWidth);
    franklinImage = franklinImage.scaledToHeight(unitHeight);

    setPixmap(franklinImage);
    
    health = 100;
    score = 0;
    ammo = 100;
    speed = 10;
    direction = 0;
    x = 1;
    y = 1;

    setPos((x+1)*unitWidth, (y+1)*unitHeight);
    
    for(int i = 0; i < 10; i++){
        for(int j = 0; j < 10; j++){
            this->boardData[i][j] = boardData[i][j];
        }
    }
}

void Franklin::keyPressEvent(QKeyEvent * event){
    int unitWidth = 100;
    int unitHeight = 100;

    if (event->key() == Qt::Key_Up && boardData[x - 1][y] >= 0)
    {
        x--;
    }
    else if (event->key() == Qt::Key_Down && boardData[x + 1][y] >= 0)
    {
        x++;
    }
    else if (event->key() == Qt::Key_Right && boardData[x][y + 1] >= 0)
    {
        y++;
    }
    else if (event->key() == Qt::Key_Left && boardData[x][y - 1] >= 0)
    {
        y--;
    }
    setPos(unitWidth + y * unitWidth, unitHeight + x * unitHeight);
}
