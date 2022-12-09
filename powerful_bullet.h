#ifndef POWERFUL_BULLET_H
#define POWERFUL_BULLET_H


#include <QObject>
#include <QGraphicsPixmapItem>

class powerful_bullet : public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
public:
    int x;
    int y;
    int boardData[12][16];
    static bool available ; //buyed or not
public:
    powerful_bullet(int boardData[12][16], int x, int y);
   static bool is_available();
   static void make_available();
signals:

};


#endif // POWERFUL_BULLET_H
