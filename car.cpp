#include "car.h"
#include "franklin.h"
#include <QGraphicsScene>
#include <QKeyEvent>
#include <QList>
#include <QGuiApplication>
#include <QTimer>
#include "gamemanager.h"
#include "level.h"
#include <vector>
#include <queue>

#define INF 9999

using namespace std;

car::car(int boardData[12][16], void * gameManager, int w, int h):
unitWidth(w),
unitHeight(h)
{
    bossPath = vector<pair<int,int>>();

    this->currentLevel = gameManager;
    while(!bossPath.empty())
    {bossPath.pop_back();}

    QPixmap enemy4LImage(":assets/images/car4L.png");
    enemy4LImage = enemy4LImage.scaledToWidth(unitWidth);
    enemy4LImage = enemy4LImage.scaledToHeight(unitHeight);

    setPixmap(enemy4LImage);
    health = 4;
    x = 6;
    y = 1;
    direction = 0;

    setPos(unitWidth + y * unitWidth, unitHeight + x * unitHeight);

    for(int i = 0; i < 12; i++){
        for(int j = 0; j < 16; j++){
            this->boardData[i][j] = boardData[i][j];
        }
    }
}

void car::move()
{
    checkCollision();
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
              if(direction == 1)
              {
                 if(health == 4)
                 {
                     QPixmap enemy4RImage(":assets/images/car4R.png");
                     enemy4RImage = enemy4RImage.scaledToWidth(unitWidth);
                     enemy4RImage = enemy4RImage.scaledToHeight(unitHeight);
                     setPixmap(enemy4RImage);
                 }
                 else if(health == 3)
                 {
                     QPixmap enemy3RImage(":assets/images/car3R.png");
                     enemy3RImage = enemy3RImage.scaledToWidth(unitWidth);
                     enemy3RImage = enemy3RImage.scaledToHeight(unitHeight);
                     setPixmap(enemy3RImage);
                 }
                 else if(health == 2)
                 {
                     QPixmap enemy2RImage(":assets/images/car2R.png");
                     enemy2RImage = enemy2RImage.scaledToWidth(unitWidth);
                     enemy2RImage = enemy2RImage.scaledToHeight(unitHeight);
                     setPixmap(enemy2RImage);
                 }
                 else if(health == 1)
                 {
                     QPixmap enemy1RImage(":assets/images/car1R.png");
                     enemy1RImage = enemy1RImage.scaledToWidth(unitWidth);
                     enemy1RImage = enemy1RImage.scaledToHeight(unitHeight);
                     setPixmap(enemy1RImage);
                 }
              }
              else if (direction == 0)
              {
                  if(health == 4)
                  {
                      QPixmap enemy4LImage(":assets/images/car4L.png");
                      enemy4LImage = enemy4LImage.scaledToWidth(unitWidth);
                      enemy4LImage = enemy4LImage.scaledToHeight(unitHeight);
                      setPixmap(enemy4LImage);
                  }
                  else if(health == 3)
                  {
                      QPixmap enemy3LImage(":assets/images/car3L.png");
                      enemy3LImage = enemy3LImage.scaledToWidth(unitWidth);
                      enemy3LImage = enemy3LImage.scaledToHeight(unitHeight);
                      setPixmap(enemy3LImage);
                  }
                  else if(health == 2)
                  {
                      QPixmap enemy2LImage(":assets/images/car2L.png");
                      enemy2LImage = enemy2LImage.scaledToWidth(unitWidth);
                      enemy2LImage = enemy2LImage.scaledToHeight(unitHeight);
                      setPixmap(enemy2LImage);
                  }
                  else if(health == 1)
                  {
                      QPixmap enemy1LImage(":assets/images/car1L.png");
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
    {
        bossPath = getPath();
    }
}

void car::checkCollision()
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
            player->setSource(QUrl("qrc:/assets/sounds/car crash.mp3"));
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
            player->setSource(QUrl("qrc:/assets/sounds/car shot.mp3"));
            player->play();

            manager->enemy_hit(this);
            manager->delete_released_bomb(getX(),getY());
        }
    }
}

int car::getX()
{
    return this->x;
}

int car::getY()
{
    return this->y;
}

int car::getHealth()
{
    return this->health;
}

void car::setXandY(int x, int y)
{
    this->x = x;
    this->y = y;
    setPos(unitWidth + y * unitWidth, unitHeight + x * unitHeight);
}

void car::reduceHealth()
{
    this->health--;
}

int car::H_Calculation(int x, int y)
{
    int playerX = 0;
    int playerY = 0;

    level *manager = static_cast<level *>(currentLevel);
    manager->getDest(playerX, playerY);

    return abs(x - playerX) + abs(y - playerY);
}


vector<pair<int, int>> car::getPath() {
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

