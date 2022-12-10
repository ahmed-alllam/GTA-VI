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
    bool taken;
public:
    bullet(int boardData[12][16], int x, int y);
signals:

};

#endif // BULLET_H
