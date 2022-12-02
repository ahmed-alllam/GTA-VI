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
    int unitWidth;
    int unitHeight;
    QPixmap enemy4LImage;
    QPixmap enemy4RImage;
    QPixmap enemy3LImage;
    QPixmap enemy3RImage;
    QPixmap enemy2LImage;
    QPixmap enemy2RImage;
    QPixmap enemy1LImage;
    QPixmap enemy1RImage;
public:
    dog(int boardData[12][16], void * gameManager);
    void move();
    int getX();
    int getY();
    void setXandY(int x, int y);
    void reduceHealth();
    void checkCollision();
    int getHealth();
    std::pair<int,int>bossPosition;
    std::pair<int, int> dest;
    std::stack<Pair> bossPath;
    std::set<pPair> openList;
    bool isValid(int r, int col);
    bool isBlock(int r, int col);
    int H_Calculation(int r, int col, Pair destn);
    void tracePath(Pair destn);
    bool isDestination(int r, int col, Pair destn);
    void aStarSearch();

signals:

};

#endif // DOG_H
