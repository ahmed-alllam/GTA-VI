#ifndef DRUNK_H
#define DRUNK_H

#include <QObject>
#include <QGraphicsPixmapItem>

class Drunk : public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
private:
    int x;
    int y;
    int boardData[12][16];
public:
    Drunk(int boardData[12][16], int x, int y);
signals:

};

#endif
