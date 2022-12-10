#ifndef ONLINEGAMEMANAGER_H
#define ONLINEGAMEMANAGER_H

#include <QGraphicsScene>
#include <QLabel>
#include <QLineEdit>
#include <QObject>
#include <QWebSocket>
#include "onlinelevel.h"
#include <QJsonObject>

class OnlineGameManager: public QObject
{
private:
    QGraphicsScene *scene;
    QLabel *label;
    QLineEdit *idLine;
    QString token;
    QString username;
    QString game_id;
    QWebSocket *socket;
    QString state;
    OnlineLevel *level;
public:
    QGraphicsTextItem * txt;
    QGraphicsTextItem * bulletsCounter;
    QGraphicsTextItem * coinsCounter;
    QGraphicsPixmapItem* hearts;
    OnlineGameManager(QGraphicsScene *scene, QString token, QString username);
    void create_game_id_panel();
    void join_game();
    void shoot(int x, int y, int direction);
    void create_healthbar();   // to create and display the pellet
    void create_new_game();
    void exit();
    void game_over();
    void playerDied(QString id);
    void gameWon();
    void player_hit(int health);
    void remove_heart(int health);
    void create_game_waiting_panel();
    void shoot_another_bullet(int x, int y, int direction);
    void gameStarted(QJsonObject game);
    void gameUpdated(QJsonObject json);
    void anotherPlayerJoined(QJsonObject json);
    void updatePosition(int x, int y, int direction);
    void remove_bullet(int x, int y);
    void remove_pellet(int x, int y);
    void updateBullet(int bullets);
    void updateScore(int score);
    void onConnected();
    void onDisconnected();
    void onTextMessageReceived(QString message);
    void create_sound();

};

#endif // ONLINEGAMEMANAGER_H
