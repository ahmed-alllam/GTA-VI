#ifndef FLYINGBULLET_H
#define FLYINGBULLET_H

#include <QObject>
#include <QTimer>
#include <QGraphicsPixmapItem>

class FlyingBullet : public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
private:
    int x;
    int y;
    int direction;
    void * manager;
    int boardData[12][16];
    QTimer *timer;
public:
    FlyingBullet(int boardData[12][16], int x, int y, int direction, void *manager);
   //FlyingBullet(int boardData[12][16], int x, int y, int direction, void *manager, QString type);
    ~FlyingBullet();
    void move();
};

#endif // FLYINGBULLET_H
