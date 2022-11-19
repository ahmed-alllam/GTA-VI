#ifndef ENEMY1_H
#define ENEMY1_H

#include <QObject>
#include <QGraphicsPixmapItem>

class enemy1 : public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
private:
    int direction;
    int x;
    int y;
    int boardData[12][16];
    void * gameManager;
public:
    enemy1(int boardData[12][16], void * gameManager);
    void move();
    void checkCollision();

signals:

};

#endif // ENEMY1_H
