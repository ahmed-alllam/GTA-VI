#ifndef PELLET_H
#define PELLET_H

#include <QObject>
#include <QGraphicsPixmapItem>

class pellet : public QObject, QGraphicsPixmapItem
{
    Q_OBJECT
private:
    int x;
    int y;
    int boardData[12][16];
public:
    pellet(int boardData[12][16]);
signals:

};

#endif // PELLET_H
