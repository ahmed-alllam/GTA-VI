#ifndef LEVEL1_H
#define LEVEL1_H

#include <QGraphicsScene>
#include <QTimer>

#include "level.h"
#include "franklin.h"
#include "enemy1.h"
#include "dog.h"
#include "bullet.h"
#include "pellet.h"
#include "Drunk.h"
#include"bomb.h"
#include"extra_life.h"
#include"powerful_bullet.h"
#include <QObject>

class level1 : public level
{
private:
    QTimer *timer;
    QTimer *timer2;
    QTimer *timer3;
    QGraphicsScene *scene;
    void * gameManager;
    Franklin *franklin;
    enemy1 *enemy1;
    dog *enemy2;
    QList<bullet*> bullets;
    QList<powerful_bullet*> powerful_bullets;
    QList<pellet*> pellets;
    QList<bomb*> bombs; //adding bombs
    Drunk *drunk;
    int boardData[12][16];
    QGraphicsPixmapItem **boardItems;
public:

    level1(void * gameManager, QGraphicsScene *scene);
    virtual void create_board();
    virtual void add_board_images();
    virtual void create_player();
    virtual void create_enemies();
    virtual void create_bullets();
    virtual void create_bombs(); //creating bombs
    virtual void create_pellets();
    virtual void create_healthbar();
    virtual void remove_bullets();
    virtual void remove_bombs(); //removing bombs
    virtual void open_gate();
    virtual void close_gate();
    virtual void updateCounters();
    virtual void restart_game();
    virtual void updateModeTxt();
    virtual void remove_heart();
    virtual void player_hit();
    virtual void enemy_hit(QGraphicsItem * enemy);
    virtual void win();

    virtual void getData(int data[12][16]);
    virtual void getDest(int& i, int& j);

    virtual void delete_released_bomb(int,int); // added
    virtual void create_extra_life();
    virtual void new_heart();
    virtual void activate_mode();

};

#endif // LEVEL1_H
