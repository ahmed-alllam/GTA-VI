#ifndef FLYING_POWERFUL_BULLET_H
#define FLYING_POWERFUL_BULLET_H

#include <QObject>
#include <QTimer>
#include <QGraphicsPixmapItem>

class flying_powerful_bullet : public QObject, public QGraphicsPixmapItem
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
    flying_powerful_bullet(int boardData[12][16], int x, int y, int direction, void *manager);
    void move();
    ~flying_powerful_bullet();
};

#endif // FLYING_POWERFUL_BULLET_H
