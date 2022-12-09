#ifndef BULLET_H
#define BULLET_H

#include <QObject>
#include <QGraphicsPixmapItem>

class bullet : public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
public:
    int x;
    int y;
    int boardData[12][16];
    static bool available ; //buyed or not
    bool powerful =false;
public:
    bullet(int boardData[12][16], int x, int y);
   bullet(int boardData[12][16], int x, int y, QString type); //powerful
   static bool is_available();
   static void make_available();
   bool is_powerful();
signals:

};

#endif // BULLET_H
