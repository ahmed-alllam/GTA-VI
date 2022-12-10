#include "enemy1.h"
#include "franklin.h"
#include <QGraphicsScene>
#include <QKeyEvent>
#include <QList>
#include <QGuiApplication>
#include <QTimer>
#include "gamemanager.h"
#include "level.h"
#include"bomb.h"
#include"released_bomb.h"
#include <queue>
#define INF 9999

using namespace std;

enemy1::enemy1(int boardData[12][16], void *currentLevel, int w, int h):
unitWidth(w),
unitHeight(h)
{
    bossPath = vector<pair<int,int>>();
    qDebug() << bossPath.max_size() <<'\n';
    this->currentLevel = currentLevel;
    while(!bossPath.empty())
    {bossPath.pop_back();}

    QPixmap enemy1FLImage(":assets/images/GangsterFL.png");
//    QPixmap enemy1FRImage(":assets/images/GangsterFR.png");
//    QPixmap enemy1HLImage(":assets/images/GangsterHL.png");
//    QPixmap enemy1HRImage(":assets/images/GangsterHR.png");

    enemy1FLImage = enemy1FLImage.scaledToWidth(unitWidth);
    enemy1FLImage = enemy1FLImage.scaledToHeight(unitHeight);

//    enemy1FRImage = enemy1FRImage.scaledToWidth(unitWidth);
//    enemy1FRImage = enemy1FRImage.scaledToHeight(unitHeight);

//    enemy1HLImage = enemy1HLImage.scaledToWidth(unitWidth);
//    enemy1HLImage = enemy1HLImage.scaledToHeight(unitHeight);

//    enemy1HRImage = enemy1HRImage.scaledToWidth(unitWidth);
//    enemy1HRImage = enemy1HRImage.scaledToHeight(unitHeight);

    setPixmap(enemy1FLImage);
    health = 2;
    x = 10;
    y = 12;
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
              if(x==bossPath[bossPath.size()-1].first&&y+1==bossPath[bossPath.size()-1].second)
              {
                 checkCollision();
                 direction = 1;
              }
              else if(x==bossPath[bossPath.size()-1].first&&y-1==bossPath[bossPath.size()-1].second)
              {
                  checkCollision();
                  direction = 0;
              }
              if (direction == 0)
              {

                  if(health == 2)
                  {
                      QPixmap enemy1FLImage(":assets/images/GangsterFL.png");
                      enemy1FLImage = enemy1FLImage.scaledToWidth(unitWidth);
                      enemy1FLImage = enemy1FLImage.scaledToHeight(unitHeight);
                      setPixmap(enemy1FLImage);
                  }
                  else if(health == 1)
                  {
                      QPixmap enemy1HLImage(":assets/images/GangsterHL.png");
                      enemy1HLImage = enemy1HLImage.scaledToWidth(unitWidth);
                      enemy1HLImage = enemy1HLImage.scaledToHeight(unitHeight);
                      setPixmap(enemy1HLImage);
                  }
              }
              else if (direction == 1)
              {

                  if(health == 2)
                  {
                      QPixmap enemy1FRImage(":assets/images/GangsterFR.png");
                      enemy1FRImage = enemy1FRImage.scaledToWidth(unitWidth);
                      enemy1FRImage = enemy1FRImage.scaledToHeight(unitHeight);
                      setPixmap(enemy1FRImage);
                  }
                  else if(health == 1)
                  {
                      QPixmap enemy1HRImage(":assets/images/GangsterHR.png");
                      enemy1HRImage = enemy1HRImage.scaledToWidth(unitWidth);
                      enemy1HRImage = enemy1HRImage.scaledToHeight(unitHeight);
                      setPixmap(enemy1HRImage);
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
    {
        bossPath = getPath();
    }
}

void enemy1::checkCollision()
{
    QList<QGraphicsItem *> colliding_items = collidingItems();
    for (int i = 0, n = colliding_items.size(); i < n; ++i)
    {
        if (typeid(*(colliding_items[i])) == typeid(Franklin))
        {
            while(!bossPath.empty())
            {bossPath.pop_back();}

            QMediaPlayer *player = new QMediaPlayer;
            QAudioOutput *audioOutput = new QAudioOutput;
            player->setAudioOutput(audioOutput);
            player->setSource(QUrl("qrc:/assets/sounds/Evil Laugh.mp3"));
            player->play();

            level *manager = static_cast<level *>(currentLevel);
            manager->player_hit();
            bossPath = getPath();
        }
        if(typeid(*(colliding_items[i]))== typeid(released_bomb))    //when colliding with the bomb
        {
            level *manager = static_cast<level *>(currentLevel);
            level *manager2 = static_cast<level *>(manager);

            QMediaPlayer *player = new QMediaPlayer;
            QAudioOutput *audioOutput = new QAudioOutput;
            player->setAudioOutput(audioOutput);
            player->setSource(QUrl("qrc:/assets/sounds/Hurt.mp3"));
            player->play();

            manager->enemy_hit(this);
            manager->delete_released_bomb(getX(),getY());
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

vector<pair<int, int>> enemy1::getPath() {
    int playerX = 0;
    int playerY = 0;

    level *manager = static_cast<level *>(currentLevel);
    manager->getDest(playerX, playerY);

    vector<vector<int>> distance(12, vector<int>(16, 0));
    vector<vector<int>> parent(12, vector<int>(16, 0));
    vector<vector<bool>> visited(12, vector<bool>(16, false));

    for (int i = 0; i < 12; i++) {
        for (int j = 0; j < 16; j++) {
            distance[i][j] = 1000000;
        }
    }

    distance[x][y] = 0;
    parent[x][y] = -1;

    priority_queue<pair<int, pair<int, int>>, vector<pair<int, pair<int, int>>>, greater<pair<int, pair<int, int>>>> pq;
    pq.push({0, {x, y}});

    while (!pq.empty()) {
        pair<int, pair<int, int>> current = pq.top();
        pq.pop();

        int currentX = current.second.first;
        int currentY = current.second.second;

        if (visited[currentX][currentY]) {
            continue;
        }

        visited[currentX][currentY] = true;

        if (currentX == playerX && currentY == playerY) {
            break;
        }

        int dx[4] = {-1, 1, 0, 0};
        int dy[4] = {0, 0, -1, 1};

        for (int i = 0; i < 4; i++) {
            int newX = currentX + dx[i];
            int newY = currentY + dy[i];

            if (newX >= 0 && newX < 12 && newY >= 0 && newY < 16 && !visited[newX][newY] && boardData[newX][newY] > 0) {
                if (distance[newX][newY] > distance[currentX][currentY] + 1) {
                    distance[newX][newY] = distance[currentX][currentY] + 1;
                    parent[newX][newY] = i + 1;
                    pq.push({distance[newX][newY] + H_Calculation(newX, newY), {newX, newY}});
                }
            }
        }


    }

    vector<pair<int, int>> path;
    int currentX = playerX;
    int currentY = playerY;

    while (parent[currentX][currentY] != -1) {
        path.push_back({currentX, currentY});
        if (parent[currentX][currentY] == 1) {
            currentX++;
        } else if (parent[currentX][currentY] == 2) {
            currentX--;
        } else if (parent[currentX][currentY] == 3) {
            currentY++;
        } else if (parent[currentX][currentY] == 4) {
            currentY--;
        }
    }

    path.push_back({currentX, currentY});
    return path;
}

int enemy1::H_Calculation(int x, int y)
{
    int playerX = 0;
    int playerY = 0;

    level *manager = static_cast<level *>(currentLevel);
    manager->getDest(playerX, playerY);

    return abs(x - playerX) + abs(y - playerY);
}
