#include "level3.h"
#include "gamemanager.h"
#include "flyingbullet.h"
#include <QGuiApplication>
#include <QFile>
#include <QGraphicsProxyWidget>
#include <QPushButton>

level3::level3(void *gameManager, QGraphicsScene *scene)
{
    this->gameManager = gameManager;
    this->scene = scene;
    qDebug() << scene;
}

void level3::add_board_images()
{
    int screenWidth = QGuiApplication::primaryScreen()->availableSize().width();
    int screenHeight = QGuiApplication::primaryScreen()->availableSize().height();
    int unitWidth = qMin(screenWidth, screenHeight) / 13;
    int unitHeight = qMin(screenWidth, screenHeight) / 13;

    QPixmap blankImage(":assets/images/blank.png");

    blankImage = blankImage.scaledToWidth(unitWidth);
    blankImage = blankImage.scaledToHeight(unitHeight);

    QPixmap brick1Image(":assets/images/car up.png");
    brick1Image = brick1Image.scaledToWidth(unitWidth);
    brick1Image = brick1Image.scaledToHeight(unitWidth);

    QPixmap brick2Image(":assets/images/water.png");
    brick2Image = brick2Image.scaledToWidth(unitWidth);
    brick2Image = brick2Image.scaledToHeight(unitWidth);

    QPixmap brick3Image(":assets/images/car bottom.png");
    brick3Image = brick3Image.scaledToWidth(unitWidth);
    brick3Image = brick3Image.scaledToHeight(unitWidth);

    QPixmap brick4Image(":assets/images/car right.png");
    brick4Image = brick4Image.scaledToWidth(unitWidth);
    brick4Image = brick4Image.scaledToHeight(unitWidth);

    QPixmap brick5Image(":assets/images/Tree.png");
    brick5Image = brick5Image.scaledToWidth(unitWidth);
    brick5Image = brick5Image.scaledToHeight(unitWidth);

    QPixmap brick6Image(":assets/images/house.png");
    brick6Image = brick6Image.scaledToWidth(unitWidth);
    brick6Image = brick6Image.scaledToHeight(unitWidth);

    QPixmap brick7Image(":assets/images/Bodygard.png");
    brick7Image = brick7Image.scaledToWidth(unitWidth);
    brick7Image = brick7Image.scaledToHeight(unitWidth);

    QPixmap homeImage(":assets/images/Home.png");
    homeImage = homeImage.scaledToWidth(unitWidth);
    homeImage = homeImage.scaledToHeight(unitWidth);

    QPixmap arrowImage(":assets/images/arrow.png");
    arrowImage = arrowImage.scaledToWidth(unitWidth);
    arrowImage = arrowImage.scaledToHeight(unitWidth);

    QPixmap VertRoadImage(":assets/images/vert.png"); // aadded for test
    VertRoadImage = VertRoadImage.scaledToWidth(unitWidth);
    VertRoadImage = VertRoadImage.scaledToHeight(unitWidth);

    QPixmap HorRoadImage(":assets/images/horz.png"); // aadded for test
    HorRoadImage = HorRoadImage.scaledToWidth(unitWidth);
    HorRoadImage = HorRoadImage.scaledToHeight(unitWidth);

    QPixmap toleft_RoadImage(":assets/images/2left.png"); // aadded
    toleft_RoadImage = toleft_RoadImage.scaledToWidth(unitWidth);
    toleft_RoadImage = toleft_RoadImage.scaledToHeight(unitWidth);

    QPixmap toright_RoadImage(":assets/images/2right.png"); // aadded
    toright_RoadImage = toright_RoadImage.scaledToWidth(unitWidth);
    toright_RoadImage = toright_RoadImage.scaledToHeight(unitWidth);

    QPixmap toleft_RoadImage2(":assets/images/2left2.png"); // aadded
    toleft_RoadImage2 = toleft_RoadImage2.scaledToWidth(unitWidth);
    toleft_RoadImage2 = toleft_RoadImage2.scaledToHeight(unitWidth);

    QPixmap toright_RoadImage2(":assets/images/2right2.png"); // aadded
    toright_RoadImage2 = toright_RoadImage2.scaledToWidth(unitWidth);
    toright_RoadImage2 = toright_RoadImage2.scaledToHeight(unitWidth);

    QPixmap TUImage(":assets/images/T Up.png"); // aadded
    TUImage = TUImage.scaledToWidth(unitWidth);
    TUImage = TUImage.scaledToHeight(unitWidth);

    QPixmap TDImage(":assets/images/T Down.png"); // aadded
    TDImage = TDImage.scaledToWidth(unitWidth);
    TDImage = TDImage.scaledToHeight(unitWidth);

    QPixmap TLImage(":assets/images/T Left.png"); // aadded
    TLImage = TLImage.scaledToWidth(unitWidth);
    TLImage = TLImage.scaledToHeight(unitWidth);

    QPixmap TRImage(":assets/images/T Right.png"); // aadded
    TRImage = TRImage.scaledToWidth(unitWidth);
    TRImage = TRImage.scaledToHeight(unitWidth);

    QPixmap CrossImage(":assets/images/cross road.png"); // aadded
    CrossImage = CrossImage.scaledToWidth(unitWidth);
    CrossImage = CrossImage.scaledToHeight(unitWidth);

    // create 2d dynamic array of type QGraphicsPixmapItem, with 12 rows and 16 columns
    boardItems = new QGraphicsPixmapItem *[12];
    for (int i = 0; i < 12; i++)
    {
        boardItems[i] = new QGraphicsPixmapItem[16];
    }

    for (int i = 0; i < 12; i++)
        for (int j = 0; j < 16; j++)
        {
            // Set Image
            if (boardData[i][j] == -1)
                boardItems[i][j].setPixmap(brick1Image);
            else if (boardData[i][j] == -2)
                boardItems[i][j].setPixmap(brick2Image);
            else if (boardData[i][j] == -3)
                boardItems[i][j].setPixmap(brick3Image);
            else if (boardData[i][j] == -4)
                boardItems[i][j].setPixmap(brick4Image);
            else if (boardData[i][j] == -5)
                boardItems[i][j].setPixmap(brick5Image);
            else if (boardData[i][j] == -6)
                boardItems[i][j].setPixmap(brick6Image);
            else if (boardData[i][j] == -7)
                boardItems[i][j].setPixmap(brick7Image);
            else if (boardData[i][j] == 20)
                boardItems[i][j].setPixmap(homeImage);
            else if (boardData[i][j] == 50)
                boardItems[i][j].setPixmap(blankImage);
            else if (boardData[i][j] == -50)
                boardItems[i][j].setPixmap(blankImage);
            else if (boardData[i][j] == 4)
                boardItems[i][j].setPixmap(VertRoadImage);
            else if (boardData[i][j] == 2)
                boardItems[i][j].setPixmap(HorRoadImage);
            else if (boardData[i][j] == 7)
                boardItems[i][j].setPixmap(toright_RoadImage);
            else if (boardData[i][j] == 8)
                boardItems[i][j].setPixmap(toright_RoadImage2);
            else if (boardData[i][j] == 9)
                boardItems[i][j].setPixmap(toleft_RoadImage);
            else if (boardData[i][j] == 3)
                boardItems[i][j].setPixmap(toleft_RoadImage2);
            else if (boardData[i][j] == 13)
                boardItems[i][j].setPixmap(TRImage);
            else if (boardData[i][j] == 14)
                boardItems[i][j].setPixmap(TLImage);
            else if (boardData[i][j] == 12)
                boardItems[i][j].setPixmap(TDImage);
            else if (boardData[i][j] == 11)
                boardItems[i][j].setPixmap(TUImage);
            else if (boardData[i][j] == 15)
                boardItems[i][j].setPixmap(CrossImage);
            else
                boardItems[i][j].setPixmap(blankImage);

            // Set Position
            boardItems[i][j].setPos(unitWidth + j * unitWidth, unitHeight + i * unitHeight);
            // Add to the Scene
            scene->addItem(&boardItems[i][j]);
        }
}

void level3::create_board()
{
    QFile file(":Board 3.txt");
    file.open(QIODevice::ReadOnly);
    QTextStream stream(&file);
    QString temp;
    for (int i = 0; i < 12; i++)
        for (int j = 0; j < 16; j++)
        {
            stream >> temp;
            boardData[i][j] = temp.toInt();
        }
}

void level3::create_player()
{
    franklin = new Franklin(boardData, this);
    scene->addItem(franklin);

    timer = new QTimer();
    QObject::connect(timer, &QTimer::timeout, franklin, &Franklin::focus_player);
    timer->start(300);
}

void level3::create_enemies()
{
    int screenWidth = QGuiApplication::primaryScreen()->availableSize().width();
    int screenHeight = QGuiApplication::primaryScreen()->availableSize().height();
    int unitWidth = qMin(screenWidth, screenHeight) / 13;
    int unitHeight = qMin(screenWidth, screenHeight) / 13;
    enemy1 = new class dog (boardData, this, unitWidth, unitHeight);
    scene->addItem(enemy1);

    enemy2 = new class car(boardData, this, unitWidth, unitHeight);
    scene->addItem(enemy2);

    timer2 = new QTimer();
    timer3 = new QTimer();
    QObject::connect(timer2, &QTimer::timeout, enemy1, &dog::move);
    QObject::connect(timer3, &QTimer::timeout, enemy2, &car::move);
    timer2->start(500);
    timer3->start(300);
}

void level3::create_bullets()
{
    bullet *bullet1 = new class bullet(boardData, 1, 1);
    bullet *bullet2 = new class bullet(boardData, 10, 14);
    bullet *bullet3 = new class bullet(boardData, 10, 1);
    bullet *bullet4 = new class bullet(boardData, 1, 14);

    bullets.clear();
    bullets.push_back(bullet1);
    bullets.push_back(bullet2);
    bullets.push_back(bullet3);
    bullets.push_back(bullet4);

    if(powerful_bullet::is_available())//if he buyied powerful bullet, put it in the map
    {
        powerful_bullet *powerful= new class powerful_bullet(boardData,2,14);
        powerful_bullets.clear();
        powerful_bullets.push_back(powerful);
    }

    for (int i = 0; i < bullets.size(); i++)
    {
        scene->addItem(bullets[i]);
    }
    for (int i = 0; i < powerful_bullets.size(); i++)
    {
        scene->addItem(powerful_bullets[i]);
    }
}

void level3::remove_bullets()
{
    for (int i = 0; i < bullets.size(); i++)
    {
        if (bullets[i] != nullptr)
        {
            scene->removeItem(bullets[i]);
            delete bullets[i];
            bullets[i] = nullptr;
        }
    }
    for (int i = 0; i < powerful_bullets.size(); i++)
    {
        if (powerful_bullets[i] != nullptr)
        {
            scene->removeItem(powerful_bullets[i]);
            delete powerful_bullets[i];
            powerful_bullets[i] = nullptr;
        }
    }
}

void level3::create_pellets()
{
    pellet *pellet1 = new class pellet(boardData, 9, 1);
    pellet *pellet2 = new class pellet(boardData, 4, 14);

    pellets.push_back(pellet1);
    pellets.push_back(pellet2);

    drunk = new class Drunk(boardData, 2, 1);

    for (int i = 0; i < pellets.size(); i++)
    {
        scene->addItem(pellets[i]);
    }
    scene->addItem(drunk);
}

void level3::updateModeTxt()
{
    GameManager *manager = static_cast<GameManager *>(gameManager);

    if (manager->txt != nullptr && franklin != nullptr)
    {
        if (franklin->getIsPowerful() && franklin->getIsDrunk())
        {
            manager->txt->setPlainText("Powerful and Drunk");
        }
        else if (franklin->getIsPowerful())
        {
            manager->txt->setPlainText("Powerful Mode");
        }
        else if (franklin->getIsDrunk())
        {
            manager->txt->setPlainText("Drunk Mode");
        }
        else
        {
            manager->txt->setPlainText("Normal Mode");
        }
    }
}

void level3::open_gate()
{
    boardData[10][15] = 50;
    franklin->editboard(50);
    GameManager *manager = static_cast<GameManager *>(gameManager);
    manager->open_gate();
}

void level3::close_gate()
{
    boardData[10][15] = -50;
    franklin->editboard(-50);
}

void level3::updateCounters()
{
    GameManager *manager = static_cast<GameManager *>(gameManager);
    qDebug() << "in update counters bullets "<< manager->bulletsCounter << " " << QString::number(franklin->getBulletsCount());
    qDebug() << "in update counters bombs " << manager->bombsCounter << " " << QString::number(franklin->getBombsCount());
    qDebug() << "in update counters coins "<< manager->coinsCounter << " " << QString::number(franklin->getCoinsCount());

    if (manager->bulletsCounter != nullptr)
        manager->bulletsCounter->setPlainText(QString::number(franklin->getBulletsCount()));
    if(manager->pwoerfull_sign==nullptr && powerful_bullet::is_available() && franklin->getPowerfullBullets()>0)
    {
        manager->pwoerfull_sign = new QGraphicsPixmapItem;
        QPixmap blankImage(":/assets/images/bullet_icon.png");
        blankImage = blankImage.scaledToWidth(25);
        blankImage = blankImage.scaledToHeight(25);
        manager->pwoerfull_sign->setPixmap(blankImage);
        manager->pwoerfull_sign->setPos(335, 8);
        scene->addItem(manager->pwoerfull_sign);

    }
    if(manager->pwoerfull_sign!=nullptr  && franklin->getPowerfullBullets()==0)
    {

        scene->removeItem(manager->pwoerfull_sign);
        delete manager->pwoerfull_sign;
        manager->pwoerfull_sign=nullptr;

    }

    if (manager->bombsCounter != nullptr)
        manager->bombsCounter->setPlainText(QString::number(franklin->getBombsCount()));

    if (manager->coinsCounter != nullptr)
        manager->coinsCounter->setPlainText(QString::number(franklin->getCoinsCount()));
}

void level3::remove_heart()
{
    GameManager *manager = static_cast<GameManager *>(gameManager);
    int health = franklin->getHealth();

    if (health >= 0)
    {
        scene->removeItem(&(manager->hearts[health]));
    }

    if (health == 0)
    {

        manager->game_over();
        timer2->stop();
        timer3->stop();
    }
}

void level3::restart_game()
{

    QList<QGraphicsItem *> items = scene->items();

    franklin = nullptr;
    enemy2 = nullptr;
    enemy1 = nullptr;

    // remove bullets
    bullets.clear();
    powerful_bullets.clear();
    //remove bombs
    bombs.clear();
    // remove pellets
    pellets.clear();
    drunk = nullptr;

    for (int i = 0; i < items.size(); i++)
    {
        if (typeid(*items[i]) == typeid(QGraphicsProxyWidget) || typeid(*items[i]) == typeid(QGraphicsTextItem) || typeid(*items[i]) == typeid(QPushButton) || typeid(*items[i]) == typeid(QGraphicsRectItem) || typeid(*items[i]) == typeid(bullet) || typeid(*items[i]) == typeid(powerful_bullet)|| typeid(*items[i]) == typeid(bomb)|| typeid(*items[i]) == typeid(extra_life) || typeid(*items[i]) == typeid(class Franklin) || typeid(*items[i]) == typeid(class Drunk) || typeid(*items[i]) == typeid(class pellet) || typeid(*items[i]) == typeid(class FlyingBullet) || typeid(*items[i]) == typeid(class dog))
        {
            scene->removeItem(items[i]);
            delete items[i];
        }
    }

    // delete boardItems (2d dynamic array) from memory and scene
    for (int i = 0; i < 12; i++)
    {
        for (int j = 0; j < 16; j++)
        {
            if ((boardItems[i]+j) != nullptr)
            {
                scene->removeItem((boardItems[i]+j));
            }
        }

        delete[] boardItems[i];
        boardItems[i] = nullptr;
     }

    timer->stop();
    timer2->stop();
    timer3->stop();
}

void level3::player_hit()
{
    if (enemy1 != nullptr)
    {
        enemy1->setXandY(1, 2);
        enemy1->bossPath.clear();
        enemy1->getPath();
    }
    else
    {
        timer2->stop();
    }
    if (enemy2 != nullptr)
    {
        enemy2->setXandY(6, 1);
        enemy1->bossPath.clear();
        enemy2->getPath();
    }
    else
    {
        timer3->stop();
    }

    franklin->hit();
}

void level3::enemy_hit(QGraphicsItem *enemy)
{

    if (typeid(*enemy) == typeid(dog) && enemy1 != nullptr)
    {
        enemy1->reduceHealth();
        if (enemy1->getHealth() == 0)
        {
            if (enemy2 == nullptr)
            {
                open_gate();
                timer3->stop();
            }
            timer2->stop();
            scene->removeItem(enemy1);
            enemy1 = nullptr;
            delete enemy1;
        }
    }
    else if (typeid(*enemy) == typeid(class car) && enemy2 != nullptr)
    {
        enemy2->reduceHealth();
        if (enemy2->getHealth() == 0)
        {
            if (enemy1 == nullptr)
            {
                open_gate();
                timer2->stop();
            }
            timer3->stop();
            scene->removeItem(enemy2);
            enemy2 = nullptr;
            delete enemy2;
        }
    }
}

void level3::create_healthbar()
{
}

void level3::win()
{
    GameManager *manager = static_cast<GameManager *>(gameManager);
    manager->Win();
    timer2->stop();
}

void level3::getData(int data[12][16])
{
    data = boardData;
}

void level3::getDest(int& i, int& j)
{
    i = franklin->getX();
    j = franklin->getY();
}

void level3::remove_bombs()
{
    for (int i = 0; i < bombs.size(); i++)
    {
        if (bombs[i] != nullptr)
        {
            scene->removeItem(bombs[i]);
            delete bombs[i];
            bombs[i] = nullptr;
        }
    }
}

void level3::create_bombs()
{
    bomb *bomb1 = new class bomb(boardData, 8, 1);
   bomb *bomb2 = new class bomb(boardData, 3,12 );
   bombs.clear();
   bombs.push_back(bomb1);
  bombs.push_back(bomb2);
   scene->addItem(bombs[0]);
   scene->addItem(bombs[1]);


}
void level3::delete_released_bomb(int x, int y)
{
franklin->delete_released_bomb(x,y);

}

void level3::create_extra_life()
{
    GameManager *manager = static_cast<GameManager *>(gameManager);
    int health = franklin->getHealth()-1;
    if (health >= 0)
    {
        scene->addItem(&(manager->hearts[health]));
    }
}

void level3::new_heart()
{
    extra_life *extra= new extra_life(boardData,6,1);
    scene->addItem(extra);
}

void level3::activate_mode()
{
    GameManager *manager = static_cast<GameManager *>(gameManager);
    manager->activate_mode(franklin->getIsDrunk(), franklin->getIsPowerful());
//    if(franklin->getIsPowerful())
//    {
//        manager->set_counter(30);
//        manager->activate_mode();
//    }
//    else if(franklin->getIsDrunk())
//    {
//        manager->set_counter(15);
//        manager->activate_mode();
//    }
}
