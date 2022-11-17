// make the class for the franklin

#include "franklin.h"
#include <QGraphicsScene>
#include <QKeyEvent>
#include <QList>
#include <QGuiApplication>
#include <enemy1.h>
#include <pellet.h>
#include <bullet.h>
//#include <QSoundEffect>
//#include <QAudioFormat>
//#include <QMediaPlayer>
//#include <QAudioOutput>

Franklin::Franklin(int boardData[12][16])
{

    QPixmap franklinImage(":assets/images/Franklin.png");

    int screenWidth = QGuiApplication::primaryScreen()->availableSize().width();
    int screenHeight = QGuiApplication::primaryScreen()->availableSize().height();
    int unitWidth = qMin(screenWidth, screenHeight) / 12;
    int unitHeight = qMin(screenWidth, screenHeight) / 12;

    franklinImage = franklinImage.scaledToWidth(unitWidth);
    franklinImage = franklinImage.scaledToHeight(unitHeight);

    setPixmap(franklinImage);

    //    QMediaPlayer *player = new QMediaPlayer;
    //    QAudioOutput * audioOutput = new QAudioOutput;
    //    player->setAudioOutput(audioOutput);
    //    player->setSource(QUrl("qrc:/assets/sounds/Ah Shit Here We Go Again.mp3"));
    //    player->play();

    health = 100;
    score = 0;
    direction = 0;
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
        y++;
    }
    else if (event->key() == Qt::Key_Left && boardData[x][y - 1] >= 0)
    {
        y--;
    }
    setPos(unitWidth + y * unitWidth, unitHeight + x * unitHeight);
    checkCollision();
}

void Franklin::focus_player()
{
    setFlag(QGraphicsPixmapItem::ItemIsFocusable);
    setFocus();
}

void Franklin::checkCollision()
{
    QList<QGraphicsItem *> collision = collidingItems();
    for (int i = 0; i < collision.size(); i++)
    {
        if (typeid(*(collision[i])) == typeid(enemy1))
        {
            qDebug() << "collisions!!";
        }
        else if(typeid(*(collision[i])) == typeid(bullet)) {

        }
        else if(typeid(*(collision[i])) == typeid(pellet)) {

        }
    }
}

void Franklin::setPowerful(bool isPowerful)
{
    this->isPowerful = isPowerful;
}

bool Franklin::getIsPowerful()
{
    return isPowerful;
}
