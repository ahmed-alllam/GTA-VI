#include "dog.h"
#include "franklin.h"
#include <QGraphicsScene>
#include <QKeyEvent>
#include <QList>
#include <QGuiApplication>
#include <QTimer>
#include "gamemanager.h"
#include "level.h"
#define INF 9999


dog::dog(int boardData[12][16], void * gameManager, int w, int h):
unitWidth(w),
unitHeight(h)
{
    this->currentLevel = gameManager;
    while(!bossPath.empty())
    {bossPath.pop_back();}

    QPixmap enemy4LImage(":assets/images/dog4L.png");
    enemy4LImage = enemy4LImage.scaledToWidth(unitWidth);
    enemy4LImage = enemy4LImage.scaledToHeight(unitHeight);

    setPixmap(enemy4LImage);
    health = 4;
    x = 1;
    y = 1;
    direction = 0;

    setPos(unitWidth + y * unitWidth, unitHeight + x * unitHeight);

    for(int i = 0; i < 12; i++){
        for(int j = 0; j < 16; j++){
            this->boardData[i][j] = boardData[i][j];
        }
    }
}

void dog::move()
{
    checkCollision();
    if(!bossPath.empty())
            {
              if(x==bossPath[bossPath.size()-1].first&&y+1==bossPath[bossPath.size()-1].second)
              {
                 checkCollision();
                 if(health == 4)
                 {
                     QPixmap enemy4RImage(":assets/images/dog4R.png");
                     enemy4RImage = enemy4RImage.scaledToWidth(unitWidth);
                     enemy4RImage = enemy4RImage.scaledToHeight(unitHeight);
                     setPixmap(enemy4RImage);
                 }
                 else if(health == 3)
                 {
                     QPixmap enemy3RImage(":assets/images/dog3R.png");
                     enemy3RImage = enemy3RImage.scaledToWidth(unitWidth);
                     enemy3RImage = enemy3RImage.scaledToHeight(unitHeight);
                     setPixmap(enemy3RImage);
                 }
                 else if(health == 2)
                 {
                     QPixmap enemy2RImage(":assets/images/dog2R.png");
                     enemy2RImage = enemy2RImage.scaledToWidth(unitWidth);
                     enemy2RImage = enemy2RImage.scaledToHeight(unitHeight);
                     setPixmap(enemy2RImage);
                 }
                 else if(health == 1)
                 {
                     QPixmap enemy1RImage(":assets/images/dog1R.png");
                     enemy1RImage = enemy1RImage.scaledToWidth(unitWidth);
                     enemy1RImage = enemy1RImage.scaledToHeight(unitHeight);
                     setPixmap(enemy1RImage);
                 }
              }
              else if(x==bossPath[bossPath.size()-1].first&&y-1==bossPath[bossPath.size()-1].second)
              {
                  checkCollision();
                  if(health == 4)
                  {
                      QPixmap enemy4LImage(":assets/images/dog4L.png");
                      enemy4LImage = enemy4LImage.scaledToWidth(unitWidth);
                      enemy4LImage = enemy4LImage.scaledToHeight(unitHeight);
                      setPixmap(enemy4LImage);
                  }
                  else if(health == 3)
                  {
                      QPixmap enemy3LImage(":assets/images/dog3L.png");
                      enemy3LImage = enemy3LImage.scaledToWidth(unitWidth);
                      enemy3LImage = enemy3LImage.scaledToHeight(unitHeight);
                      setPixmap(enemy3LImage);
                  }
                  else if(health == 2)
                  {
                      QPixmap enemy2LImage(":assets/images/dog2L.png");
                      enemy2LImage = enemy2LImage.scaledToWidth(unitWidth);
                      enemy2LImage = enemy2LImage.scaledToHeight(unitHeight);
                      setPixmap(enemy2LImage);
                  }
                  else if(health == 1)
                  {
                      QPixmap enemy1LImage(":assets/images/dog1L.png");
                      enemy1LImage = enemy1LImage.scaledToWidth(unitWidth);
                      enemy1LImage = enemy1LImage.scaledToHeight(unitHeight);
                      setPixmap(enemy1LImage);
                  }
              }
              bossPosition.first=bossPath[bossPath.size()-1].first;
              bossPosition.second=bossPath[bossPath.size()-1].second;
              bossPath.pop_back();
              setXandY(bossPosition.first, bossPosition.second);
              checkCollision();
              return;
            }
    else
            bossPath = aStarSearch();
}

void dog::checkCollision()
{
    QList<QGraphicsItem *> colliding_items = collidingItems();
    for (int i = 0, n = colliding_items.size(); i < n; ++i)
    {
        if (typeid(*(colliding_items[i])) == typeid(Franklin))
        {
            while(!bossPath.empty())
            {bossPath.pop_back();}
            level *manager = static_cast<level *>(currentLevel);
            manager->player_hit();
            bossPath = aStarSearch();
        }
    }
}

int dog::getX()
{
    return this->x;
}

int dog::getY()
{
    return this->y;
}

int dog::getHealth()
{
    return this->health;
}

void dog::setXandY(int x, int y)
{
    this->x = x;
    this->y = y;
    setPos(unitWidth + y * unitWidth, unitHeight + x * unitHeight);
}

void dog::reduceHealth()
{
    this->health--;
}

std::vector<Pair> dog::aStarSearch()
{
    while(!bossPath.empty())
    {bossPath.pop_back();}
//  initialize closed list (2D array)
    for(int i=0;i<12;i++)
    {
        for(int j=0;j<16;j++)
        {
            closedList[i][j]=0;
        }
    }

//    // Declare a 2D array of structure to hold the details
    int i, j;

    for (int k = 0; k < 12; k++)
    {
        for (int a = 0; a < 16; a++)
        {
            cellDetails[k][a].f = INF;
            cellDetails[k][a].g = INF;
            cellDetails[k][a].h = INF;
            cellDetails[k][a].parent_i = -1;
            cellDetails[k][a].parent_j = -1;
        }
    }
    i = x;
    j = y;
    level *manager = static_cast<level *>(currentLevel);
    manager->getDest(dest.first, dest.second);
    cellDetails[i][j].f = 0;
    cellDetails[i][j].g = 0;
    cellDetails[i][j].h = 0;
    cellDetails[i][j].parent_i = i;
    cellDetails[i][j].parent_j = j;


////    // Put the starting cell on the open list and set its'f' as 0
    openList.insert(make_pair(0, std::make_pair(i, j)));
    bool foundOpst = false; // the destination is not reached.
    while (!openList.empty())
    {
        pPair p = *openList.begin(); // Remove this vertex from the open list
        openList.erase(openList.begin());
        i = p.second.first;
        j = p.second.second;
        closedList[i][j] = true; // Add this vertex to the closed list

        // Cell-->Popped Cell (i, j)
        //(4 directions ) N -->  North (i-1, j) S -->  South (i+1, j) E -->  East (i, j+1) W -->  West (i, j-1)
        int gNew, hNew, fNew; // To store the 'g', 'h' and 'f' of the 4 successors

        if (isValid(i - 1, j) == true) // north
        {
            if (isDestination(i - 1, j, dest) == true)
            {
                cellDetails[i - 1][j].parent_i = i; // Set the Parent of the destination cell
                cellDetails[i - 1][j].parent_j = j;
                bossPath = tracePath( dest);
                foundOpst = true;
                return bossPath;
            }
            else if (!(closedList[i - 1][j]) && !(isBlock( i - 1, j)))
            {
                gNew = cellDetails[i][j].g + 1;
                hNew = H_Calculation(i - 1, j, dest);
                fNew = gNew + hNew;
                if (cellDetails[i - 1][j].f == INF || cellDetails[i - 1][j].f > fNew)
                {
                    openList.insert(make_pair(fNew, std::make_pair(i - 1, j)));

                    // Update the details of this cell
                    cellDetails[i - 1][j].f = fNew;
                    cellDetails[i - 1][j].g = gNew;
                    cellDetails[i - 1][j].h = hNew;
                    cellDetails[i - 1][j].parent_i = i;
                    cellDetails[i - 1][j].parent_j = j;
                }
            }
        }
        if (isValid(i + 1, j) == true) //(South)
        {
            // If the destination cell is the same as the  current successor
            if (isDestination(i + 1, j, dest) == true)
            {
                // Set the Parent of the destination cell
                cellDetails[i + 1][j].parent_i = i;
                cellDetails[i + 1][j].parent_j = j;
                bossPath = tracePath(dest);
                foundOpst = true;
                return bossPath;
            }

            else if (!closedList[i + 1][j] && !isBlock( i + 1, j))
            {
                gNew = cellDetails[i][j].g + 1;
                hNew = H_Calculation(i + 1, j, dest);
                fNew = gNew + hNew;

                if (cellDetails[i + 1][j].f == INF || cellDetails[i + 1][j].f > fNew)
                {
                    openList.insert(make_pair(
                        fNew, std::make_pair(i + 1, j)));
                    // Update the details of this cell
                    cellDetails[i + 1][j].f = fNew;
                    cellDetails[i + 1][j].g = gNew;
                    cellDetails[i + 1][j].h = hNew;
                    cellDetails[i + 1][j].parent_i = i;
                    cellDetails[i + 1][j].parent_j = j;
                }
            }
        }

        if (isValid(i, j + 1) == true) // east
        {
            if (isDestination(i, j + 1, dest) == true) // Set the Parent of the destination cell

            {
                cellDetails[i][j + 1].parent_i = i;
                cellDetails[i][j + 1].parent_j = j;
                bossPath = tracePath(dest);
                foundOpst = true;
                return bossPath;
            }

            else if (!closedList[i][j + 1] && !isBlock(i, j + 1))
            {
                gNew = cellDetails[i][j].g + 1;
                hNew = H_Calculation(i, j + 1, dest);
                fNew = gNew + hNew;
                if (cellDetails[i][j + 1].f == INF || cellDetails[i][j + 1].f > fNew)
                {
                    openList.insert(make_pair(
                        fNew, std::make_pair(i, j + 1)));
                    // Update the details of this cell
                    cellDetails[i][j + 1].f = fNew;
                    cellDetails[i][j + 1].g = gNew;
                    cellDetails[i][j + 1].h = hNew;
                    cellDetails[i][j + 1].parent_i = i;
                    cellDetails[i][j + 1].parent_j = j;
                }
            }
        }

        if (isValid(i, j - 1) == true) // west
        {
            if (isDestination(i, j - 1, dest) == true)
            {
                // Set the Parent of the destination cell
                cellDetails[i][j - 1].parent_i = i;
                cellDetails[i][j - 1].parent_j = j;
                bossPath = tracePath( dest);
                foundOpst = true;
                return bossPath;
            }
            else if (!closedList[i][j - 1] && !isBlock( i, j - 1) == true)
            {
                gNew = cellDetails[i][j].g + 1;
                hNew = H_Calculation(i, j - 1, dest);
                fNew = gNew + hNew;
                if (cellDetails[i][j - 1].f == INF || cellDetails[i][j - 1].f > fNew)
                {
                    openList.insert(std::make_pair(
                        fNew, std::make_pair(i, j - 1)));

                    cellDetails[i][j - 1].f = fNew;
                    cellDetails[i][j - 1].g = gNew;
                    cellDetails[i][j - 1].h = hNew;
                    cellDetails[i][j - 1].parent_i = i;
                    cellDetails[i][j - 1].parent_j = j;
                }
            }
        }
    }
    return bossPath;
}



bool dog:: isValid(int r, int col) // in the range of the data
{
    return ((r < 12) && (col < 16));
}

//// if the cell is block +we might use it depends on the enemy lma netfeq
bool dog:: isBlock(int r, int col)
{
    return (boardData[r][col] <0);
}


int dog::H_Calculation(int r, int col, Pair destn) // return the estimation distance using the rule of difference between two points
{
    return (sqrt((r - destn.first) * (r - destn.first) + (col - destn.second) * (col - destn.second)));
}
// // will be changed and make the boss move according to the sequence of steps

std::vector<Pair> dog:: tracePath( Pair destn)
{
    int r = destn.first;
    int col = destn.second;
    while(!bossPath.empty())
            bossPath.pop_back();
    Pair next_node;
    next_node.first = cellDetails[r][col].parent_i;
    next_node.second = cellDetails[r][col].parent_j;
    do {
        bossPath.push_back(next_node);
        if(cellDetails[r][col].parent_i<0||cellDetails[r][col].parent_j<0)
             break;
        if(cellDetails[r][col].parent_i>20||cellDetails[r][col].parent_j>20)
             break;
        if(cellDetails[cellDetails[r][col].parent_i][cellDetails[r][col].parent_j].parent_i==r&&cellDetails[cellDetails[r][col].parent_i][cellDetails[r][col].parent_j].parent_j==col)
             break;
            next_node.first = cellDetails[r][col].parent_i;
            next_node.second = cellDetails[r][col].parent_j;
            int temp_row = cellDetails[r][col].parent_i;
            int temp_col = cellDetails[r][col].parent_j;
            r = temp_row;
            col = temp_col;
    }while (!(cellDetails[r][col].parent_i == r && cellDetails[r][col].parent_j == col));
//    while (!((cellDetails[r][col].parent_i == r && cellDetails[r][col].parent_j == col)))
//    {
//        bossPath.push(std::make_pair(r, col));
//        if(cellDetails[r][col].parent_i==-1||cellDetails[r][col].parent_j==-1)
//            break;
//        if(cellDetails[cellDetails[r][col].parent_i][cellDetails[r][col].parent_j].parent_i==r&&cellDetails[cellDetails[r][col].parent_i][cellDetails[r][col].parent_j].parent_j==col)
//            break;
//        int temp_r = cellDetails[r][col].parent_i;
//        int temp_col = cellDetails[r][col].parent_j;
//        r = temp_r;
//        col = temp_col;
//    }
    return bossPath;
}

bool dog::isDestination(int r, int col, Pair destn) // to check whether enemy reached (its destination) the player or not
{
 return (r == destn.first && col == destn.second); // collision
}
