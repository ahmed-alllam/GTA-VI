#ifndef LEVEL1_H
#define LEVEL1_H

#include <QGraphicsScene>
#include <QTimer>

#include "level.h"
#include "franklin.h"
#include "enemy1.h"
#include "enemy2.h"
#include "bullet.h"
#include "pellet.h"
#include "Drunk.h"
#include <QObject>

class level1 : public level
{
private:
    QTimer *timer;
    QTimer *timer2;
    QGraphicsScene *scene;
    void * gameManager;
    Franklin *franklin;
    enemy1 *enemy1;
    enemy2 *enemy2;
    QList<bullet*> bullets;
    QList<pellet*> pellets;
    Drunk *drunk;
    int boardData[12][16];
public:
    level1(void * gameManager, QGraphicsScene *scene);
    virtual void create_board();
    virtual void add_board_images();
    virtual void create_player();
    virtual void create_enemies();
    virtual void create_bullets();
    virtual void create_pellets();
    virtual void create_healthbar();
    virtual void remove_bullets();
    virtual void open_gate();
    virtual void close_gate();
    virtual void updateCounters();
    virtual void restart_game();
    virtual void updateModeTxt();
    virtual void remove_heart();
    virtual void player_hit();
    virtual void enemy_hit();
};

#endif // LEVEL1_H
