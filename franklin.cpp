// make the class for the franklin

#include "franklin.h"
#include <QGraphicsScene>
#include <QKeyEvent>
#include <QList>

Franklin::Franklin(int boardData[10][10]){

    QPixmap franklinImage(":assets/images/Franklin.png");

    franklinImage = franklinImage.scaledToWidth(50);
    franklinImage = franklinImage.scaledToHeight(50);

    setPixmap(franklinImage);
    
    health = 100;
    score = 0;
    ammo = 100;
    speed = 10;
    direction = 0;
    x = 4;
    y = 4;

    setPos((x+1)*50, (y+1)*50);
    
    for(int i = 0; i < 10; i++){
        for(int j = 0; j < 10; j++){
            this->boardData[i][j] = boardData[i][j];
        }
    }
}

void Franklin::keyPressEvent(QKeyEvent * event){
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
    setPos(50 + y * 50, 50 + x * 50);
}
