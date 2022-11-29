#ifndef LEVEL1_H
#define LEVEL1_H

#include <QGraphicsScene>
#include <vector>

#include "level.h"
#include "franklin.h"
#include "enemy1.h"
#include "enemy2.h"
#include "bullet.h"
#include "pellet.h"
#include "Drunk.h"

using namespace std;

class level1 : public level
{
private:
    QGraphicsScene *scene;
    void * gameManager;
    Franklin *franklin;
    enemy1 *enemy1;
    enemy2 *enemy2;
    vector<bullet> bullets;
    vector<pellet> pellets;
    Drunk *drunk;
    int boardData[12][16];
public:
    level1(void * gameManager, QGraphicsScene *scene);

};

#endif // LEVEL1_H
