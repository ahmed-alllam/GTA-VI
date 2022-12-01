#ifndef ONLINEGAMEMANAGER_H
#define ONLINEGAMEMANAGER_H

#include <QGraphicsScene>
#include <QLabel>
#include <QLineEdit>
#include <QObject>


class OnlineGameManager: public QObject
{
private:
    QGraphicsScene *scene;
    QLabel *label;
    QLineEdit *idLine;
    QString token;
    QString username;
public:
    OnlineGameManager(QGraphicsScene *scene, QString token, QString username);
    void create_game_id_panel();
    void join_game(QString id);
    void create_new_game();
    void create_game_waiting_panel();
};

#endif // ONLINEGAMEMANAGER_H
