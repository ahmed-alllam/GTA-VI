#ifndef GAMEMANAGER_H
#define GAMEMANAGER_H

#include <QString>
#include <QTimer>
#include <QGraphicsScene>
#include<QObject>

#include "qobjectdefs.h"
#include "level.h"

class GameManager: public QObject
{

private:
    level *currentLevel;
    QTimer *timer;  // game over checker
    QTimer *timer2; // the last stage checker
    QTimer *timer3; // win checker
public slots:

void restart_game();
void exit();

public:
    QGraphicsScene *scene;
    QGraphicsRectItem **panels;
    QGraphicsTextItem * txt;
    QGraphicsTextItem * bulletsCounter;
    QGraphicsTextItem * coinsCounter;
    QGraphicsPixmapItem* hearts;
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
