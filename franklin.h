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
    int bullets;
    int boardData[12][16];
    void * currentLevel;
    QPixmap franklinImagel1;
    QPixmap franklinImagel2;
    QPixmap franklinImageu1;
    QPixmap franklinImageu2;
    QPixmap franklinImaged1;
    QPixmap franklinImaged2;
    QPixmap franklinImager1;
    QPixmap franklinImager2;
    QPixmap franklinImagel;
    QPixmap franklinImager;
    QPixmap franklinImageu;
    QPixmap franklinImaged;
    QPixmap franklinImagell;
    QPixmap franklinImagerr;
    int unitWidth;
    int unitHeight;

public:
    Franklin(int boardData[12][16], void *currentLevel);
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
    void shoot();
    void Move();
    void hit();
    int getBulletsCount();
    int getCoinsCount();
    void editboard(int x);
    QTimer *timer = new QTimer(this);
public slots:
    void keyPressEvent(QKeyEvent * event);
};

#endif // FRANKLIN_H
