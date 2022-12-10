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
    static bool available ; //buyed or not
public:
    bomb(int boardData[12][16], int x, int y);
    static bool is_available();
    static void make_available();


};

#endif // BOMB_H
