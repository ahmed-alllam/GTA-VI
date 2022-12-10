#ifndef LEVEL_H
#define LEVEL_H

#include <QObject>
#include <QGraphicsItem>

class level
{
public:
    level();
    virtual void create_board() = 0;
    virtual void add_board_images() = 0;
    virtual void create_player() = 0;
    virtual void create_enemies() = 0;
    virtual void create_bullets() = 0;
    virtual void create_bombs() = 0;
    virtual void create_pellets() = 0;
    virtual void create_healthbar() = 0;
    virtual void remove_bullets() = 0;
    virtual void remove_bombs() = 0;
    virtual void open_gate() = 0;
    virtual void close_gate() = 0;
    virtual void updateCounters() = 0;
    virtual void restart_game() = 0;
    virtual void updateModeTxt() = 0;
    virtual void remove_heart() = 0;
    virtual void player_hit() = 0;
    virtual void enemy_hit(QGraphicsItem * enemy) = 0;
    virtual void win() = 0;
    virtual void getData(int data[12][16]) = 0;
    virtual void getDest(int& i, int& j) = 0;
virtual void  delete_released_bomb(int,int)=0; // added
    virtual void create_extra_life()=0;
    virtual void new_heart()=0;
    virtual void activate_mode()=0;

};

#endif // LEVEL_H
