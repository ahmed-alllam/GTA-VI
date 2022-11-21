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
#include <QTimer>

class Franklin: public QObject, public QGraphicsPixmapItem{
    Q_OBJECT
private:
    int health;
    int score;
    bool drunk;
    int direction;
    bool isPowerful;
    int x;
    int y;
    int boardData[12][16];
    void * gameManager;
    QPixmap franklinImagel1;
    QPixmap franklinImagel2;
    QPixmap franklinImager1;
    QPixmap franklinImager2;
    QPixmap franklinImagel;
    QPixmap franklinImager;
    QPixmap franklinImagell;
    QPixmap franklinImagerr;
    int unitWidth;
    int unitHeight;

public:
    Franklin(int boardData[12][16], void *gameManager);
    void focus_player();
    void checkCollision();
    bool getIsPowerful();
    bool getIsDrunk();
    void setIsDrunk(bool);
    void setPowerful(bool);
    void setPowerful2False();
    void setDrunk2False();
    int getX();
    int getY();
    int getHealth();
    void Move();
    void hit();
    QTimer *timer = new QTimer(this);
public slots:
    void keyPressEvent(QKeyEvent * event);
};

#endif // FRANKLIN_H
