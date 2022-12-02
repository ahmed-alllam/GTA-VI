#include "enemy1.h"
#include "franklin.h"
#include <QGraphicsScene>
#include <QKeyEvent>
#include <QList>
#include <QGuiApplication>
#include <QTimer>
#include "gamemanager.h"
#include "level.h"
#define INF 9999

enemy1::enemy1(int boardData[12][16], void *currentLevel)
{
    this->currentLevel = currentLevel;
    while(!bossPath.empty())
    {bossPath.pop();}
    int screenWidth = QGuiApplication::primaryScreen()->availableSize().width();
    int screenHeight = QGuiApplication::primaryScreen()->availableSize().height();
    unitWidth = qMin(screenWidth, screenHeight) / 12;
    unitHeight = qMin(screenWidth, screenHeight) / 12;

    QPixmap enemy1FLImage(":assets/images/GangsterFL.png");
    QPixmap enemy1FRImage(":assets/images/GangsterFR.png");
    QPixmap enemy1HLImage(":assets/images/GangsterHL.png");
    QPixmap enemy1HRImage(":assets/images/GangsterHR.png");

    enemy1FLImage = enemy1FLImage.scaledToWidth(unitWidth);
    enemy1FLImage = enemy1FLImage.scaledToHeight(unitHeight);

    enemy1FRImage = enemy1FRImage.scaledToWidth(unitWidth);
    enemy1FRImage = enemy1FRImage.scaledToHeight(unitHeight);

    enemy1HLImage = enemy1HLImage.scaledToWidth(unitWidth);
    enemy1HLImage = enemy1HLImage.scaledToHeight(unitHeight);

    enemy1HRImage = enemy1HRImage.scaledToWidth(unitWidth);
    enemy1HRImage = enemy1HRImage.scaledToHeight(unitHeight);

    setPixmap(enemy1FLImage);
    health = 2;
    x = 9;
    y = 8;
    direction = 0;

    setPos(unitWidth + y * unitWidth, unitHeight + x * unitHeight);

    for (int i = 0; i < 12; i++)
    {
        for (int j = 0; j < 16; j++)
        {
            this->boardData[i][j] = boardData[i][j];
        }
    }
}

void enemy1::move()
{
    if(!bossPath.empty())
            {
              if(x==bossPath.top().first&&y+1==bossPath.top().second)
              {
                 checkCollision();
                 if(health == 2)
                 {
                     setPixmap(enemy1FRImage);
                 }
                 else if(health == 1)
                 {
                     setPixmap(enemy1HRImage);
                 }
              }
              else if(x==bossPath.top().first&&y-1==bossPath.top().second)
              {
                  checkCollision();
                  if(health == 2)
                  {
                      setPixmap(enemy1FLImage);
                  }
                  else if(health == 1)
                  {
                      setPixmap(enemy1HLImage);
                  }
              }
              bossPosition.first=bossPath.top().first;
              bossPosition.second=bossPath.top().second;
              bossPath.pop();
              setXandY(bossPosition.first, bossPosition.second);
              checkCollision();
              return;
            }
    else
            aStarSearch();
}

void enemy1::checkCollision()
{
    QList<QGraphicsItem *> colliding_items = collidingItems();
    for (int i = 0, n = colliding_items.size(); i < n; ++i)
    {
        if (typeid(*(colliding_items[i])) == typeid(Franklin))
        {
            while(!bossPath.empty())
            {bossPath.pop();}
            level *manager = static_cast<level *>(currentLevel);
            manager->player_hit();
        }
    }
}

int enemy1::getX()
{
    return this->x;
}

int enemy1::getY()
{
    return this->y;
}

int enemy1::getHealth()
{
    return this->health;
}

void enemy1::setXandY(int x, int y)
{
    this->x = x;
    this->y = y;
    setPos(unitWidth + y * unitWidth, unitHeight + x * unitHeight);
}

void enemy1::reduceHealth()
{
    this->health--;
}

void enemy1::aStarSearch()
{
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


//    // Put the starting cell on the open list and set its'f' as 0
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
                tracePath( dest);
                foundOpst = true;
                return;
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
                tracePath(dest);
                foundOpst = true;
                return;
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
                tracePath(dest);
                foundOpst = true;
                return;
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
                tracePath( dest);
                foundOpst = true;
                return;
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
    return;
}

bool enemy1:: isValid(int r, int col) // in the range of the data
{
    return ((r < 12) && (col < 16));
}

//// if the cell is block +we might use it depends on the enemy lma netfeq
bool enemy1:: isBlock(int r, int col)
{
    return (boardData[r][col] <0);
}


int enemy1::H_Calculation(int r, int col, Pair destn) // return the estimation distance using the rule of difference between two points
{
    return (sqrt((r - destn.first) * (r - destn.first) + (col - destn.second) * (col - destn.second)));
}
// // will be changed and make the boss move according to the sequence of steps

void enemy1:: tracePath( Pair destn)
{
    int r = destn.first;
    int col = destn.second;
    while(!bossPath.empty())
            bossPath.pop();
    while (!(cellDetails[r][col].parent_i == r && cellDetails[r][col].parent_j == col))
    {
            bossPath.push(std::make_pair(r, col));
            int temp_row = cellDetails[r][col].parent_i;
            int temp_col = cellDetails[r][col].parent_j;
            r = temp_row;
            col = temp_col;
    }
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
    return;
}

bool enemy1::isDestination(int r, int col, Pair destn) // to check whether enemy reached (its destination) the player or not
{
 return (r == destn.first && col == destn.second); // collision
}
