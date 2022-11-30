#ifndef ONLINEGAMEMANAGER_H
#define ONLINEGAMEMANAGER_H

#include <QGraphicsScene>
#include <QObject>


class OnlineGameManager: public QObject
{
private:
    QGraphicsScene *scene;
public:
    OnlineGameManager(QGraphicsScene *scene);
    void create_game_id_panel();
};

#endif // ONLINEGAMEMANAGER_H
