#ifndef GAMEMANAGER_H
#define GAMEMANAGER_H

#include <QString>
#include <QTimer>
#include <QGraphicsScene>
#include<QObject>

#include "franklin.h"
#include "enemy1.h"
#include "enemy2.h"
#include "bullet.h"
#include "pellet.h"
#include "Drunk.h"
#include "qobjectdefs.h"

class GameManager: public QObject
{

private:
    int boardData[12][16];

    QTimer *timer;  // game over checker
    QTimer *timer2; // the last stage checker
    QTimer *timer3; // win checker
public slots:

void restart_game();
void exit();

public:
    QGraphicsScene *scene;
    static Franklin *franklin;
    static enemy1 *enemy1;
    static enemy2 *enemy2;
    static bullet *bullet1;
    static bullet *bullet2;
    static bullet *bullet3;
    QGraphicsRectItem **panels;
    static bullet *bullet4;
    static pellet *pellet1;
    static pellet *pellet2;
    QGraphicsTextItem * txt;
    QGraphicsTextItem * bulletsCounter;
    QGraphicsTextItem * coinsCounter;
    QGraphicsPixmapItem* hearts;
    Drunk *drunk;
    QMovie *gate;// added
    QMovie* movie; // added
    GameManager(QGraphicsScene *scene);
    void launch_game();
    void create_player();    // create and dispaly players
    void create_enemies();   // to create and dispaly enemies
    void add_board_images(); // to create and display the board
    void create_board();     // to create and display the board
    void updateModeTxt();
    void create_sound();     // to create and display the sound
    void create_bullets();   // to create and display the bullets
    void remove_bullets();
    void create_pellets();   // to create and display the pellet
    void create_healthbar();   // to create and display the pellet
    void remove_heart();
    void franklin_hit();
    void updateCounters();
    void Win();
    QGraphicsRectItem* drawPanel(int x, int y, int width, int height, QColor color, double opacity);
//    void restart_game();
    void game_over();
    void activate_mode();
    void open_gate();
    void close_gate();
    class enemy1* retenemy1();
    class enemy2* retenemy2();

};

#endif // GAMEMANAGER_H
