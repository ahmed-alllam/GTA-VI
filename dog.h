#ifndef DOG_H
#define DOG_H

#include <QObject>
#include <QGraphicsPixmapItem>

class dog : public QObject, public QGraphicsPixmapItem
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
    dog(int boardData[12][16], void * gameManager);
    void move();
    int getX();
    int getY();
    void reduceHealth();
    void checkCollision();

signals:

};

#endif // DOG_H
