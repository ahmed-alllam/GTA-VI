// create qt class for class QObject, public QGraphicsPixmapItem
// the class is for the player character Franklin

#ifndef FRANKLIN_H
#define FRANKLIN_H
#include"bomb.h"
#include"released_bomb.h"
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
    int powerful_bullets;
    int bombs;
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
    QPixmap franklinImagepr;
    QPixmap franklinImagepl;
    QPixmap franklinImagepu;
    QPixmap franklinImagepd;
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
    void BOMB();
    void Move();
    void hit();
    int getBulletsCount();
    int getBombsCount(); // added
    int getCoinsCount();
    int getPowerfullBullets();
    void editboard(int x);
    QTimer *timer = new QTimer(this);
    QList<released_bomb*> released_bombs;
    bool extra_consumed=false;  //check if he used the extra  life before

    void delete_released_bomb(int,int);
    void powerful_shoot();
public slots:
    void keyPressEvent(QKeyEvent * event);

};

#endif // FRANKLIN_H
