#ifndef LEVEL3_H
#define LEVEL3_H

#include <QGraphicsScene>
#include <QTimer>

#include "level.h"
#include "franklin.h"
#include "enemy1.h"
#include "dog.h"
#include "bullet.h"
#include "pellet.h"
#include "Drunk.h"
#include <QObject>

class level3 : public level
{
public:
    level3(void * gameManager, QGraphicsScene *scene);
    virtual void create_board()=0;
    virtual void add_board_images()=0;
    virtual void create_player()=0;
    virtual void create_enemies()=0;
    virtual void create_bullets()=0;
    virtual void create_pellets()=0;
    virtual void create_healthbar()=0;
    virtual void remove_bullets()=0;
    virtual void open_gate()=0;
    virtual void close_gate()=0;
    virtual void updateCounters()=0;
    virtual void restart_game()=0;
    virtual void updateModeTxt()=0;
    virtual void remove_heart()=0;
    virtual void player_hit()=0;
    virtual void enemy_hit(QGraphicsItem * enemy)=0;
    virtual void win()=0;
    virtual void getData(int data[12][16])=0;
    virtual void getDest(int& i, int& j)=0;

private:
    QTimer *timer;
    QTimer *timer2;
    QGraphicsScene *scene;
    void * gameManager;
    Franklin *franklin;
    dog *enemy1;
    class enemy1 *enemy2;
    QList<bullet*> bullets;
    QList<pellet*> pellets;
    Drunk *drunk;
    int boardData[12][16];
    QGraphicsPixmapItem **boardItems;

};

#endif // LEVEL3_H
