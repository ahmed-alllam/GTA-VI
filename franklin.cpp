// make the class for the franklin

#include "franklin.h"
#include <QGraphicsScene>
#include <QKeyEvent>
#include <QList>
#include <QGuiApplication>
#include <enemy1.h>
#include <pellet.h>
#include <bullet.h>
#include <Drunk.h>
#include <QTimer>
#include <QMessageBox>
//#include <QSoundEffect>
//#include <QAudioFormat>
//#include <QMediaPlayer>
//#include <QAudioOutput>
Franklin::Franklin(int boardData[12][16])
{
    QPixmap franklinImagel1(":assets/images/Franklin model 2 m3.png");
    QPixmap franklinImagel2(":assets/images/Franklin model 2 m2.png");
    QPixmap franklinImager1(":assets/images/Franklin model 2 m4.png");
    QPixmap franklinImager2(":assets/images/Franklin model 2 m1.png");

    int screenWidth = QGuiApplication::primaryScreen()->availableSize().width();
    int screenHeight = QGuiApplication::primaryScreen()->availableSize().height();
    int unitWidth = qMin(screenWidth, screenHeight) / 12;
    int unitHeight = qMin(screenWidth, screenHeight) / 12;

    franklinImagel1 = franklinImagel1.scaledToWidth(unitWidth);
    franklinImagel1 = franklinImagel1.scaledToHeight(unitHeight);

    franklinImagel2 = franklinImagel2.scaledToWidth(unitWidth);
    franklinImagel2 = franklinImagel2.scaledToHeight(unitHeight);

    franklinImager1 = franklinImager1.scaledToWidth(unitWidth);
    franklinImager1 = franklinImager1.scaledToHeight(unitHeight);

    franklinImager2 = franklinImager2.scaledToWidth(unitWidth);
    franklinImager2 = franklinImager2.scaledToHeight(unitHeight);

    setPixmap(franklinImagel1);

    //    QMediaPlayer *player = new QMediaPlayer;
    //    QAudioOutput * audioOutput = new QAudioOutput;
    //    player->setAudioOutput(audioOutput);
    //    player->setSource(QUrl("qrc:/assets/sounds/Ah Shit Here We Go Again.mp3"));
    //    player->play();


    health = 3;
    score = 0;
    direction = 0;
    isPowerful = 0;
    drunk = 0;
    x = 5;
    y = 7;

    setPos(unitWidth + y * unitWidth, unitHeight + x * unitHeight);
    for (int i = 0; i < 12; i++)
    {
        for (int j = 0; j < 16; j++)
        {
            this->boardData[i][j] = boardData[i][j];
        }
    }
}

void Franklin::keyPressEvent(QKeyEvent *event)
{
    int screenWidth = QGuiApplication::primaryScreen()->availableSize().width();
    int screenHeight = QGuiApplication::primaryScreen()->availableSize().height();
    int unitWidth = qMin(screenWidth, screenHeight) / 12;
    int unitHeight = qMin(screenWidth, screenHeight) / 12;

    QPixmap franklinImagel1(":assets/images/Franklin model 2 m3.png");
    QPixmap franklinImagel2(":assets/images/Franklin model 2 m2.png");
    QPixmap franklinImager1(":assets/images/Franklin model 2 m4.png");
    QPixmap franklinImager2(":assets/images/Franklin model 2 m1.png");

    franklinImagel1 = franklinImagel1.scaledToWidth(unitWidth);
    franklinImagel1 = franklinImagel1.scaledToHeight(unitHeight);

    franklinImagel2 = franklinImagel2.scaledToWidth(unitWidth);
    franklinImagel2 = franklinImagel2.scaledToHeight(unitHeight);

    franklinImager1 = franklinImager1.scaledToWidth(unitWidth);
    franklinImager1 = franklinImager1.scaledToHeight(unitHeight);

    franklinImager2 = franklinImager2.scaledToWidth(unitWidth);
    franklinImager2 = franklinImager2.scaledToHeight(unitHeight);

    QPixmap franklinImagel(":assets/images/Franklin model 2 protected 2.png"); // change  the image
    QPixmap franklinImager(":assets/images/Franklin model 2 protected.png"); // change  the image

    franklinImagel = franklinImagel.scaledToWidth(unitWidth);
    franklinImagel = franklinImagel.scaledToHeight(unitHeight);

    franklinImager = franklinImager.scaledToWidth(unitWidth);
    franklinImager = franklinImager.scaledToHeight(unitHeight);

    if (!getIsPowerful()){
        if(!drunk){
            if (event->key() == Qt::Key_Up && boardData[x - 1][y] >= 0)
            {
                x--;
            }
            else if (event->key() == Qt::Key_Down && boardData[x + 1][y] >= 0)
            {
                x++;
            }
            else if (event->key() == Qt::Key_Right && boardData[x][y + 1] >= 0)
            {
                QTimer::singleShot(1000, this, SLOT(Move(2)));
                QTimer::singleShot(2000, this, SLOT(Move(3)));
                y++;
                direction = 0;
            }
            else if (event->key() == Qt::Key_Left && boardData[x][y - 1] >= 0)
            {
                QTimer::singleShot(1000, this, SLOT(Move(0)));
                QTimer::singleShot(2000, this, SLOT(Move(1)));
                y--;
                direction = 1;
            }
        }
        else{
            if (event->key() == Qt::Key_Up && boardData[x + 1][y] >= 0)
            {
                x++;
            }
            else if (event->key() == Qt::Key_Down && boardData[x - 1][y] >= 0)
            {
                x--;
            }
            else if (event->key() == Qt::Key_Left && boardData[x][y + 1] >= 0)
            {
                QTimer::singleShot(1000, this, SLOT(Move(2)));
                QTimer::singleShot(2000, this, SLOT(Move(3)));
                y++;
                direction = 0;
            }
            else if (event->key() == Qt::Key_Right && boardData[x][y - 1] >= 0)
            {
                QTimer::singleShot(1000, this, SLOT(Move(0)));
                QTimer::singleShot(2000, this, SLOT(Move(1)));
                y--;
                direction = 1;
            }
        }
    }
    else {
        if(!drunk){
            if (event->key() == Qt::Key_Up && boardData[x - 1][y] >= 0)
            {
                x--;
            }
            else if (event->key() == Qt::Key_Down && boardData[x + 1][y] >= 0)
            {
                x++;
            }
            else if (event->key() == Qt::Key_Right && boardData[x][y + 1] >= 0)
            {
                setPixmap(franklinImager);
                y++;
                direction = 0;
            }
            else if (event->key() == Qt::Key_Left && boardData[x][y - 1] >= 0)
            {
                setPixmap(franklinImagel);
                y--;
                direction = 1;
            }
        }
        else{
            if (event->key() == Qt::Key_Up && boardData[x + 1][y] >= 0)
            {
                x++;
            }
            else if (event->key() == Qt::Key_Down && boardData[x - 1][y] >= 0)
            {
                x--;
            }
            else if (event->key() == Qt::Key_Left && boardData[x][y + 1] >= 0)
            {
                setPixmap(franklinImager);
                y++;
                direction = 0;
            }
            else if (event->key() == Qt::Key_Right && boardData[x][y - 1] >= 0)
            {
                setPixmap(franklinImagel);
                y--;
                direction = 1;
            }
        }
    }

    setPos(unitWidth + y * unitWidth, unitHeight + x * unitHeight);
    checkCollision();
}

void Franklin::Move(int a)
{
    int screenWidth = QGuiApplication::primaryScreen()->availableSize().width();
    int screenHeight = QGuiApplication::primaryScreen()->availableSize().height();
    int unitWidth = qMin(screenWidth, screenHeight) / 12;
    int unitHeight = qMin(screenWidth, screenHeight) / 12;

    QPixmap franklinImagel1(":assets/images/Franklin model 2 m3.png");
    QPixmap franklinImagel2(":assets/images/Franklin model 2 m2.png");
    QPixmap franklinImager1(":assets/images/Franklin model 2 m4.png");
    QPixmap franklinImager2(":assets/images/Franklin model 2 m1.png");

    franklinImagel1 = franklinImagel1.scaledToWidth(unitWidth);
    franklinImagel1 = franklinImagel1.scaledToHeight(unitHeight);

    franklinImagel2 = franklinImagel2.scaledToWidth(unitWidth);
    franklinImagel2 = franklinImagel2.scaledToHeight(unitHeight);

    franklinImager1 = franklinImager1.scaledToWidth(unitWidth);
    franklinImager1 = franklinImager1.scaledToHeight(unitHeight);

    franklinImager2 = franklinImager2.scaledToWidth(unitWidth);
    franklinImager2 = franklinImager2.scaledToHeight(unitHeight);

    if(a == 0)
    {
        setPixmap(franklinImager1);
    }
    else if(a == 1)
    {
        setPixmap(franklinImager2);
    }
    else if(a == 2)
    {
        setPixmap(franklinImagel1);
    }
    else
    {
        setPixmap(franklinImagel2);
    }
}

void Franklin::focus_player()
{
    setFlag(QGraphicsPixmapItem::ItemIsFocusable);
    setFocus();
}

void Franklin::checkCollision()
{
    int screenWidth = QGuiApplication::primaryScreen()->availableSize().width();
    int screenHeight = QGuiApplication::primaryScreen()->availableSize().height();
    int unitWidth = qMin(screenWidth, screenHeight) / 12;
    int unitHeight = qMin(screenWidth, screenHeight) / 12;
    QList<QGraphicsItem *> collision = collidingItems();
    for (int i = 0; i < collision.size(); i++)
    {
        if (typeid(*(collision[i])) == typeid(enemy1))
        {
                if(!getIsPowerful())
                {
                this->health--;
                    //remove_heart from the game manger
                if(health == 0){
                    QMessageBox msgBox;
                    msgBox.setText("Game Over!!!!");
                    msgBox.exec();
                }
                this->x = 5;
                this->y = 7;
                setPos(unitWidth + y * unitWidth, unitHeight + x * unitHeight);
                //    QMediaPlayer *player = new QMediaPlayer;
                //    QAudioOutput * audioOutput = new QAudioOutput;
                //    player->setAudioOutput(audioOutput);
                //    player->setSource(QUrl("qrc:/assets/sounds/Ah Shit Here We Go Again.mp3"));
                //    player->play();
                }
                else
                {
                    setPowerful(false);
                }
        }
        else if(typeid(*(collision[i])) == typeid(bullet)) {
            QPixmap franklinImagel(":assets/images/Franklin model 2 powered 2.png"); // change  the image
            QPixmap franklinImager(":assets/images/Franklin model 2 powered.png"); // change  the image

            franklinImagel = franklinImagel.scaledToWidth(unitWidth);
            franklinImagel = franklinImagel.scaledToHeight(unitHeight);

            franklinImager = franklinImager.scaledToWidth(unitWidth);
            franklinImager = franklinImager.scaledToHeight(unitHeight);
            if(direction == 1)
            {
                setPixmap(franklinImagel);
            }
            else
            {
               setPixmap(franklinImager);
            }
            (collision[i])->setVisible(false);

        }
        else if(typeid(*(collision[i])) == typeid(pellet)) {
            QPixmap franklinImagel(":assets/images/Franklin model 2 protected 2.png"); // change  the image
            QPixmap franklinImager(":assets/images/Franklin model 2 protected.png"); // change  the image

            franklinImagel = franklinImagel.scaledToWidth(unitWidth);
            franklinImagel = franklinImagel.scaledToHeight(unitHeight);

            franklinImager = franklinImager.scaledToWidth(unitWidth);
            franklinImager = franklinImager.scaledToHeight(unitHeight);
            if(direction == 1)
            {
                setPixmap(franklinImagel);
            }
            else
            {
               setPixmap(franklinImager);
            }

            setPowerful(true);
            (collision[i])->setVisible(false);

        }
        else if(typeid(*(collision[i])) == typeid(Drunk)) {

            setIsDrunk(true);
            (collision[i])->setVisible(false);


        }
        // add qtimer to reverse it after 1 sec
    }
    QTimer::singleShot(1000, this, SLOT(checkCollision()));
}
void Franklin::setPowerful(bool isPowerful)
{
    this->isPowerful = isPowerful;
}

bool Franklin::getIsPowerful()
{
    return isPowerful;
}

int Franklin::getHealth()
{
    return this->health;
}

bool Franklin::getIsDrunk()
{
    return this->drunk;
}

void Franklin::setIsDrunk(bool a = 0)
{
    this->drunk = a;
}
