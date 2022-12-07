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
public:
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
    void update_player_position(QString playerId, int x, int y, int direction, int score, int bullets, int health);
    void updatePosition(int x, int y, int direction);
    void add_bullet(int x, int y);
    void add_pellet(int x, int y);
    void remove_bullet(int x, int y);
    void remove_pellet(int x, int y);
    void updateBullet(int bullets);
    void updateScore(int score);
    void clear_bullets(QJsonArray bullets);
    void shoot(int x, int y, int direction);
    void clear_pellets(QJsonArray pellets);
    void create_bullets();
    void create_pellets();
    void create_healthbar();
    void remove_bullets();
    void remove_player(QString id);
    void updateCounters();
    void restart_game();
    void updateModeTxt();
    void player_hit(int health);
    void win();
};

#endif // ONLINELEVEL_H
