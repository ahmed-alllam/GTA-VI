#ifndef GAMEMANAGER_H
#define GAMEMANAGER_H

#include <QString>
#include <QTimer>
#include <QGraphicsScene>
#include<QObject>
#include "qobjectdefs.h"
#include "level.h"
#include <QAudioFormat>
#include <QMediaPlayer>
#include <QAudioOutput>
class GameManager: public QObject
{

private:
    level *currentLevel;
    int levelNum;
    bool win;
    QTimer *timer;  // game over checker
    QTimer *timer2; // the last stage checker
    QTimer *timer3; // win checker
    QMediaPlayer *player = new QMediaPlayer;
    QAudioOutput *audioOutput = new QAudioOutput;
public slots:

void restart_game();
void exit();

public:
    QGraphicsScene *scene;
    QGraphicsRectItem **panels;
    QGraphicsTextItem * txt;
    QGraphicsTextItem * bulletsCounter;
    QGraphicsTextItem * coinsCounter;
    QGraphicsTextItem * bombsCounter;//bombs
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
    void updateCounters();
    void Win();
//    void Next_level();
    void create_bombs();
    void remove_bombs();
    QGraphicsRectItem* drawPanel(int x, int y, int width, int height, QColor color, double opacity);
//    void restart_game();
    void game_over();
    void activate_mode();
    void open_gate();
    void close_gate();
    void delete_released_bomb(int,int);
};

#endif // GAMEMANAGER_H
