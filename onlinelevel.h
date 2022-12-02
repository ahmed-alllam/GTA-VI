#ifndef ONLINELEVEL_H
#define ONLINELEVEL_H

#include <QGraphicsScene>
#include <QGraphicsPixmapItem>
#include <QTimer>
#include <QList>
#include <bullet.h>
#include <pellet.h>
#include "onlineplayer.h"


class OnlineLevel
{
private:
    QTimer *timer;
    QTimer *timer2;
    QGraphicsScene *scene;
    void * gameManager;
    QList<OnlinePlayer*> players;
    QList<bullet*> bullets;
    QList<pellet*> pellets;
    QString username;
    QString game_id;
    int boardData[12][16];
    QGraphicsPixmapItem **boardItems;
public:
    OnlineLevel(void * gameManager, QGraphicsScene *scene, QString username, QString game_id);
    void create_board();
    void add_board_images();
    void create_players(QJsonArray players);
    void update_player_position(QString playerId, int x, int y, int direction);
    void updatePosition(int x, int y, int direction);
    void add_bullet(int x, int y);
    void add_pellet(int x, int y);
    void create_bullets();
    void create_pellets();
    void create_healthbar();
    void remove_bullets();
    void updateCounters();
    void restart_game();
    void updateModeTxt();
    void player_hit();
    void win();
};

#endif // ONLINELEVEL_H