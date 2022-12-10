#ifndef EXTRA_LIFE_H
#define EXTRA_LIFE_H

#include <QObject>
#include <QTimer>
#include <QGraphicsPixmapItem>

class extra_life: public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
private:
//    int x;
//    int y;
    int boardData[12][16];
    static bool available ; //buyed or not
public:
    extra_life(int boardData[12][16], int x, int y);
    static bool is_available();
    static void make_available();
};

#endif // EXTRA_LIFE_H
