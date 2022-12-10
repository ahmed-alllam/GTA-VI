#ifndef PELLET_H
#define PELLET_H

#include <QObject>
#include <QGraphicsPixmapItem>

class pellet : public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
public:
    int x;
    int y;
    int boardData[12][16];
    bool taken;
public:
    pellet(int boardData[12][16], int x, int y);
signals:

};

#endif // PELLET_H
