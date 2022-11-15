#ifndef ENEMY2_H
#define ENEMY2_H

#include <QObject>
#include <QGraphicsPixmapItem>

class enemy2 : public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
private:
    int x;
    int y;
    int boardData[12][16];
public:
    enemy2(int boardData[12][16]);

signals:

};

#endif // ENEMY2_H
