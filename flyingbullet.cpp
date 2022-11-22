#include "flyingbullet.h"

#include <QGraphicsScene>
#include <QKeyEvent>
#include <QList>
#include <QGuiApplication>
#include <QTimer>
#include "enemy1.h"
#include "enemy2.h"
#include "gamemanager.h"

FlyingBullet::FlyingBullet(int boardData[12][16], int x, int y, int direction, void * manager)
{
    QPixmap bulletImage(":assets/images/bullet.png");

    int screenWidth = QGuiApplication::primaryScreen()->availableSize().width();
    int screenHeight = QGuiApplication::primaryScreen()->availableSize().height();
    int unitWidth = qMin(screenWidth, screenHeight) / 12;
    int unitHeight = qMin(screenWidth, screenHeight) / 12;
    int unitHeight2 = qMin(screenWidth, screenHeight) / 17;


    bulletImage = bulletImage.scaledToWidth(unitHeight2);
    bulletImage = bulletImage.scaledToHeight(unitHeight2);

    setPixmap(bulletImage);

    this->x = x;
    this->y = y;
    this->direction = direction;
    this->manager = manager;

    setPos(unitWidth + y * unitWidth, unitHeight + x * unitHeight);

    for(int i = 0; i < 12; i++){
        for(int j = 0; j < 16; j++){
            this->boardData[i][j] = boardData[i][j];
        }
    }

    timer = new QTimer();
    QObject::connect(timer, &QTimer::timeout, this, &FlyingBullet::move);
    timer->start(50);
}

void FlyingBullet::move() {
    // move bullet depending on direction
    if(direction == 0){
        y++;
    } else if(direction == 1){
        y--;
    }

    // check if bullet hit an enemy
    QList<QGraphicsItem *> colliding_items = collidingItems();
    GameManager * manager2 = static_cast<GameManager *>(manager);

    for(int i = 0; i < colliding_items.size(); i++){
        if(colliding_items[i] == manager2->enemy1){
            scene()->removeItem(this);
            delete this;
            manager2->enemy1->reduceHealth();
            return;
        } else if(colliding_items[i] == manager2->enemy2) {
            scene()->removeItem(this);
            delete this;
            manager2->enemy2->reduceHealth();
            return;
        }
    }

    // check if bullet is out of bounds
    if(x < 0 || x > 11 || y < 0 || y > 15){
        scene()->removeItem(this);
        delete this;
        return;
    }

    // check if bullet hit a wall
    if(boardData[x][y] < 0){
        scene()->removeItem(this);
        delete this;
        return;
    }

    // move bullet
    int screenWidth = QGuiApplication::primaryScreen()->availableSize().width();
    int screenHeight = QGuiApplication::primaryScreen()->availableSize().height();
    int unitWidth = qMin(screenWidth, screenHeight) / 12;
    int unitHeight = qMin(screenWidth, screenHeight) / 12;

    setPos(unitWidth + y * unitWidth, unitHeight + x * unitHeight);
}

FlyingBullet::~FlyingBullet() {
    if(timer != nullptr)
        delete timer;
}

