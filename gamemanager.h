#ifndef GAMEMANAGER_H
#define GAMEMANAGER_H

#include <QString>
#include <QTimer>
#include <QGraphicsScene>

#include "franklin.h"
#include "enemy1.h"
#include "bullet.h"
#include "pellet.h"

class GameManager
{

private:
    int boardData[12][16];

    QTimer *timer;  // game over checker
    QTimer *timer2; // the last stage checker
    QTimer *timer3; // win checker
    QGraphicsScene *scene;
public:
    static Franklin *franklin;
    static enemy1 *enemy1;
    static bullet *bullet1;
    static bullet *bullet2;
    static bullet *bullet3;
    static bullet *bullet4;
    static pellet *pellet1;
    static pellet *pellet2;
    //QGraphicsItem* temp2;      //in process
    GameManager(QGraphicsScene *scene);
    void create_player();    // create and dispaly players
    void create_enemies();   // to create and dispaly enemies
    void add_board_images(); // to create and display the board
    void create_board();     // to create and display the board
    void create_sound();     // to create and display the sound
    void create_bullets();   // to create and display the bullets
    void create_pellets();   // to create and display the pellet
    void create_healthbar();   // to create and display the pellet
   // void remove_heart(int);  // in process

};

#endif // GAMEMANAGER_H
