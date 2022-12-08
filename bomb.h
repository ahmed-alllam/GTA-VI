#ifndef BOMB_H
#define BOMB_H


#include <QObject>
#include <QTimer>
#include <QGraphicsPixmapItem>

class bomb: public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
private:
    int x;
    int y;
    int boardData[12][16];
    QTimer *timer;
    void * manager;
    //static bool available; //buyed or not
public:
    bomb(int boardData[12][16], int x, int y);
    bomb(int boardData[12][16], int x, int y,void *manager );
    //static bool is_available();
    void waiting_to_bomb();
    //virtual ~bomb() {};

};

#endif // BOMB_H
