#include "onlineflyingbullet.h"

#include <QGraphicsScene>
#include <QKeyEvent>
#include <QList>
#include <QGuiApplication>
#include <QTimer>
#include "enemy1.h"
#include "onlinelevel.h"
#include "gamemanager.h"
#include "onlineplayer.h"

OnlineFlyingBullet::OnlineFlyingBullet(int boardData[12][16], int x, int y, int direction, void *manager, QString source_player, QString currPlayer)
{
    QPixmap bulletImageu(":assets/images/bullet.png");
    QPixmap bulletImager(":assets/images/bulletR.png");
    QPixmap bulletImagel(":assets/images/bulletL.png");
    QPixmap bulletImaged(":assets/images/bulletD.png");

    this->source_player = source_player;
    this->currPLayer = currPlayer;

    int screenWidth = QGuiApplication::primaryScreen()->availableSize().width();
    int screenHeight = QGuiApplication::primaryScreen()->availableSize().height();
    int unitWidth = qMin(screenWidth, screenHeight) / 13;
    int unitHeight = qMin(screenWidth, screenHeight) / 13;
    int unitHeight2 = qMin(screenWidth, screenHeight) / 17;

    bulletImageu = bulletImageu.scaledToWidth(unitHeight2);
    bulletImageu = bulletImageu.scaledToHeight(unitHeight2);

    bulletImaged = bulletImaged.scaledToWidth(unitHeight2);
    bulletImaged = bulletImaged.scaledToHeight(unitHeight2);

    bulletImager = bulletImager.scaledToWidth(unitHeight2);
    bulletImager = bulletImager.scaledToHeight(unitHeight2);

    bulletImagel = bulletImagel.scaledToWidth(unitHeight2);
    bulletImagel = bulletImagel.scaledToHeight(unitHeight2);

    if (direction == 0)
    {
        setPixmap(bulletImager);
    }
    else if (direction == 1)
    {
        setPixmap(bulletImagel);
    }
    else if (direction == 2)
    {
        setPixmap(bulletImageu);
    }
    else if (direction == 3)
    {
        setPixmap(bulletImaged);
    }

    this->x = x;
    this->y = y;
    this->direction = direction;
    this->manager = manager;

    setPos(unitWidth + y * unitWidth, unitHeight + x * unitHeight);

    for (int i = 0; i < 12; i++)
    {
        for (int j = 0; j < 16; j++)
        {
            this->boardData[i][j] = boardData[i][j];
        }
    }

    timer = new QTimer();
    QObject::connect(timer, &QTimer::timeout, this, &OnlineFlyingBullet::move);
    timer->start(50);

    move();
}

void OnlineFlyingBullet::move()
{
    // move bullet depending on direction
    if (direction == 0)
    {
        y++;
    }
    else if (direction == 1)
    {
        y--;
    }
    else if (direction == 2)
    {
        x--;
    }
    else if (direction == 3)
    {
        x++;
    }

    QList<QGraphicsItem *> colliding_items = collidingItems();
    OnlineLevel *manager2 = static_cast<OnlineLevel *>(manager);

    for (int i = 0; i < colliding_items.size(); i++)
    {
        if (typeid(*colliding_items[i]) == typeid(OnlinePlayer))
        {
            OnlinePlayer * player = static_cast<OnlinePlayer *>(colliding_items[i]);
            qDebug() << "hit 1 " <<  player->id << source_player;

            if(player->id != source_player) {
                qDebug() << "hit 2 " << player->id << currPLayer;

                if( player->id == currPLayer) {
                    qDebug()<< " hit 3 ";
                    player->hit();
                    manager2->player_hit(player->health);
                }
                if(scene() != nullptr) {
                    scene()->removeItem(this);
                    delete this;
                }
                return;
            }
        }
    }

    // check if bullet is out of bounds
    if (x < 0 || x > 11 || y < 0 || y > 15)
    {
        if(scene() != nullptr) {
            scene()->removeItem(this);
            delete this;
        }
        return;
    }

    // check if bullet hit a wall
    if (boardData[x][y] < 0)
    {
        if(scene() != nullptr) {
            scene()->removeItem(this);
            delete this;
        }
        return;
    }

    // move bullet
    int screenWidth = QGuiApplication::primaryScreen()->availableSize().width();
    int screenHeight = QGuiApplication::primaryScreen()->availableSize().height();
    int unitWidth = qMin(screenWidth, screenHeight) / 13;
    int unitHeight = qMin(screenWidth, screenHeight) / 13;

    setPos(unitWidth + y * unitWidth, unitHeight + x * unitHeight);
}

OnlineFlyingBullet::~OnlineFlyingBullet()
{
    if (timer != nullptr)
        delete timer;
}
