#ifndef DOG_H
#define DOG_H

#include <QObject>
#include <set>
#include <QPair>
#include <utility>
#include<stack>
#include <QGraphicsPixmapItem>
struct  cell3  //used in A_star
{
    int parent_i, parent_j;
    float f, g, h; // f=g+h
};
typedef std::pair<int, int> Pair;
typedef std::pair<int, std::pair<int, int>> pPair;

class dog : public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
private:
    int direction;
    int x;
    int y;
    int health;
    int boardData[12][16];
    void * currentLevel;
    cell3 cellDetails[12][16];
    bool closedList[12][16];
    const int unitWidth;
    const int unitHeight;
    QPixmap enemy4LImage;
    QPixmap enemy4RImage;
    QPixmap enemy3LImage;
    QPixmap enemy3RImage;
    QPixmap enemy2LImage;
    QPixmap enemy2RImage;
    QPixmap enemy1LImage;
    QPixmap enemy1RImage;
public:
    dog(int boardData[12][16], void * gameManager, int w, int h);
    void move();
    int getX();
    int getY();
    void setXandY(int x, int y);
    void reduceHealth();
    void checkCollision();
    int getHealth();
    std::pair<int,int>bossPosition;
    std::vector<Pair> bossPath;
    int H_Calculation(int r, int col);
    std::vector<Pair> getPath();

signals:

};

#endif // DOG_H
