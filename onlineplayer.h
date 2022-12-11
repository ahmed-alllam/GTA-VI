#ifndef ONLINEPLAYER_H
#define ONLINEPLAYER_H

#include <QObject>
#include <QPixmap>
#include <QGraphicsPixmapItem>
#include <QGraphicsTextItem>
#include <QProgressBar>

class OnlinePlayer : public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
public:
    int health;
    int score;
    bool drunk;
    int direction;
    bool isPowerful;
    int x;
    int y;
    QString id;
    bool currPlayer;
    int bullets;
    int boardData[12][16];
    void * currentLevel;
    QProgressBar *healthBar;
    QGraphicsTextItem *idText;
    QPixmap franklinImagel;
    QPixmap franklinImageu;
    QPixmap franklinImaged;
    QPixmap franklinImager;
    QPixmap franklinImagepr;
    QPixmap franklinImagepl;
    QPixmap franklinImagepu;
    QPixmap franklinImagepd;
    int unitWidth;
    int unitHeight;
public:
    explicit OnlinePlayer(int boardData[12][16], void *currentLevel, QString username);
    void setCoordinates(int x, int y, int direction);
    void focus_player();
    void checkCollision();
    void shoot();
    void add_id();
    void hit();
    void add_health_bar();
public slots:
    void keyPressEvent(QKeyEvent * event);

signals:

};

#endif // ONLINEPLAYER_H
