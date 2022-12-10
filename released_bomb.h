#ifndef RELEASED_BOMB_H
#define RELEASED_BOMB_H
#include <QObject>
#include <QTimer>
#include <QGraphicsPixmapItem>

class released_bomb: public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
private:

    int boardData[12][16];
    QTimer *timer;
    void * manager;
public:
    released_bomb(int boardData[12][16], int x, int y,int direction,void *manager );
    int x;
    int y;  //temporarily
};

#endif // RELEASED_BOMB_H
