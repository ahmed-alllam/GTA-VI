#ifndef ENEMY2_H
#define ENEMY2_H

#include <QObject>
#include <QGraphicsPixmapItem>

class enemy2 : public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
private:
    int direction;
    int x;
    int y;
    int health;
    int boardData[12][16];
    void * gameManager;
public:
    enemy2(int boardData[12][16], void * gameManager);
    void move();
    int getX();
    int getY();
    void reduceHealth();
    void checkCollision();

signals:

};

#endif // ENEMY2_H
