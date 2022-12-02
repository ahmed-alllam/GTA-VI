#ifndef ONLINEPLAYER_H
#define ONLINEPLAYER_H

#include <QObject>
#include <QPixmap>
#include <QGraphicsPixmapItem>

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
    QPixmap franklinImagel1;
    QPixmap franklinImagel2;
    QPixmap franklinImageu1;
    QPixmap franklinImageu2;
    QPixmap franklinImaged1;
    QPixmap franklinImaged2;
    QPixmap franklinImager1;
    QPixmap franklinImager2;
    QPixmap franklinImagel;
    QPixmap franklinImager;
    QPixmap franklinImageu;
    QPixmap franklinImaged;
    QPixmap franklinImagell;
    QPixmap franklinImagerr;
    int unitWidth;
    int unitHeight;
public:
    explicit OnlinePlayer(int boardData[12][16], void *currentLevel, QString username);
    void setCoordinates(int x, int y, int direction);
    void focus_player();
public slots:
    void keyPressEvent(QKeyEvent * event);

signals:

};

#endif // ONLINEPLAYER_H
