#ifndef BOMB_H
#define BOMB_H


#include <QObject>
#include <QGraphicsPixmapItem>

class bomb: public QObject, public QGraphicsPixmapItem
{
private:
    int x;
    int y;
    int boardData[12][16];
public:
    bomb(int boardData[12][16], int x, int y);


};

#endif // BOMB_H
