#ifndef ONLINEGAMEMANAGER_H
#define ONLINEGAMEMANAGER_H

#include <QGraphicsScene>
#include <QLabel>
#include <QLineEdit>
#include <QObject>
#include <QWebSocket>

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
public:
    OnlineGameManager(QGraphicsScene *scene, QString token, QString username);
    void create_game_id_panel();
    void join_game();
    void create_new_game();
    void create_game_waiting_panel();
    void gameStarted();
    void onConnected();
    void onDisconnected();
    void onTextMessageReceived(QString message);
};

#endif // ONLINEGAMEMANAGER_H
