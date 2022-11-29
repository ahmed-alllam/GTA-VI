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
    int health;
    int boardData[12][16];
    void * currentLevel;
public:
    enemy1(int boardData[12][16], void * currentLevel);
    void move();
    int getX();
    int getY();
    void setXandY(int x, int y);
    void reduceHealth();
    void checkCollision();

signals:

};

#endif // ENEMY1_H
