// create qt class for class QObject, public QGraphicsPixmapItem
// the class is for the player character Franklin

#ifndef FRANKLIN_H
#define FRANKLIN_H

#include <QObject>
#include <QGraphicsPixmapItem>
#include <QGraphicsItem>
#include <QGraphicsScene>
#include <QKeyEvent>
#include <QList>

class Franklin: public QObject, public QGraphicsPixmapItem{
    Q_OBJECT
private:
    int health;
    int score;
    int ammo;
    int speed;
    int direction;
    int x;
    int y;
    int boardData[12][16];
public:
    Franklin(int boardData[12][16]);
public slots:
    void keyPressEvent(QKeyEvent * event);
};

#endif // FRANKLIN_H
