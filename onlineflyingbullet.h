#ifndef ONLINEFLYINGBULLET_H
#define ONLINEFLYINGBULLET_H

#include <QObject>
#include <QTimer>
#include <QGraphicsPixmapItem>

class OnlineFlyingBullet : public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT

private:
    int x;
    int y;
    int direction;
    void * manager;
    int boardData[12][16];
    QTimer *timer;
    QString source_player;
    QString currPLayer;
public:
    OnlineFlyingBullet(int boardData[12][16], int x, int y, int direction, void *manager, QString source_player, QString currPlayer);
    ~OnlineFlyingBullet();
    void move();
signals:

};

#endif // ONLINEFLYINGBULLET_H
