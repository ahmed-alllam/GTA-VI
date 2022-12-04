#ifndef ENEMY1_H
#define ENEMY1_H

#include <QObject>
#include <set>
#include <QPair>
#include <utility>
#include<vector>
#include <QGraphicsPixmapItem>
struct  cell1  //used in A_star
{
    int parent_i, parent_j;
    float f, g, h; // f=g+h
};
typedef std::pair<int, int> Pair;
typedef std::pair<int, std::pair<int, int>> pPair;

class enemy1 : public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
private:
    int direction;
    int x;
    int y;
    int health;
    int boardData[12][16];
    void * currentLevel;
    cell1 cellDetails[12][16];
    bool closedList[12][16];
    const int unitWidth;
    const int unitHeight;
    QPixmap enemy1FLImage;
    QPixmap enemy1FRImage;
    QPixmap enemy1HLImage;
    QPixmap enemy1HRImage;
public:
    enemy1(int boardData[12][16], void * currentLevel, int w, int h);
    void move();
    int getX();
    int getY();
    void setXandY(int x, int y);
    void reduceHealth();
    void checkCollision();
    int getHealth();
    std::pair<int,int>bossPosition;
    std::pair<int, int> dest;
    std::vector<Pair> bossPath;
    std::set<pPair> openList;
    bool isValid(int r, int col);
    bool isBlock(int r, int col);
    int H_Calculation(int r, int col, Pair destn);
    void tracePath(Pair destn);
    bool isDestination(int r, int col, Pair destn);
    void aStarSearch();

signals:

};

#endif // ENEMY1_H
