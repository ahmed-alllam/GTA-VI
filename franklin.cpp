// make the class for the franklin

#include "franklin.h"
#include <QGraphicsScene>
#include <QKeyEvent>
#include <QList>
#include <QGuiApplication>
#include <enemy1.h>
#include <enemy2.h>
#include <pellet.h>
#include <bullet.h>
#include <Drunk.h>
#include <QMessageBox>
#include <QSoundEffect>
#include <QAudioFormat>
#include <QMediaPlayer>
#include <QAudioOutput>
#include "level.h"
#include "flyingbullet.h"

Franklin::Franklin(int boardData[12][16], void *currentLevel)
{

    this->currentLevel = currentLevel;

    franklinImagel1 = QPixmap(":assets/images/Franklin model 2 m3.png");
    franklinImagel2 = QPixmap(":assets/images/Franklin model 2 m2.png");
    franklinImager1 = QPixmap(":assets/images/Franklin model 2 m4.png");
    franklinImager2 = QPixmap(":assets/images/Franklin model 2 m1.png");
    franklinImaged1 = QPixmap(":assets/images/Franklin D m1.png");
    franklinImaged2 = QPixmap(":assets/images/Franklin D m2.png");
    franklinImageu1 = QPixmap(":assets/images/Franklin U m1.png");
    franklinImageu2 = QPixmap(":assets/images/Franklin U m2.png");
    franklinImageu = QPixmap(":assets/images/Franklin U protected.png");
    franklinImaged = QPixmap(":assets/images/Franklin D protected.png");

    int screenWidth = QGuiApplication::primaryScreen()->availableSize().width();
    int screenHeight = QGuiApplication::primaryScreen()->availableSize().height();
    unitWidth = qMin(screenWidth, screenHeight) / 12;
    unitHeight = qMin(screenWidth, screenHeight) / 12;

    franklinImagel1 = franklinImagel1.scaledToWidth(unitWidth);
    franklinImagel1 = franklinImagel1.scaledToHeight(unitHeight);

    franklinImagel2 = franklinImagel2.scaledToWidth(unitWidth);
    franklinImagel2 = franklinImagel2.scaledToHeight(unitHeight);

    franklinImager1 = franklinImager1.scaledToWidth(unitWidth);
    franklinImager1 = franklinImager1.scaledToHeight(unitHeight);

    franklinImager2 = franklinImager2.scaledToWidth(unitWidth);
    franklinImager2 = franklinImager2.scaledToHeight(unitHeight);

    franklinImaged1 = franklinImaged1.scaledToWidth(unitWidth);
    franklinImaged1 = franklinImaged1.scaledToHeight(unitHeight);

    franklinImaged2 = franklinImaged2.scaledToWidth(unitWidth);
    franklinImaged2 = franklinImaged2.scaledToHeight(unitHeight);

    franklinImageu1 = franklinImageu1.scaledToWidth(unitWidth);
    franklinImageu1 = franklinImageu1.scaledToHeight(unitHeight);

    franklinImageu2 = franklinImageu2.scaledToWidth(unitWidth);
    franklinImageu2 = franklinImageu2.scaledToHeight(unitHeight);

    franklinImaged = franklinImaged.scaledToWidth(unitWidth);
    franklinImaged = franklinImaged.scaledToHeight(unitHeight);

    franklinImageu = franklinImageu.scaledToWidth(unitWidth);
    franklinImageu = franklinImageu.scaledToHeight(unitHeight);

    franklinImagel = QPixmap(":assets/images/Franklin model 2 protected 2.png"); // change  the image
    franklinImager = QPixmap(":assets/images/Franklin model 2 protected.png");   // change  the image

    franklinImagel = franklinImagel.scaledToWidth(unitWidth);
    franklinImagel = franklinImagel.scaledToHeight(unitHeight);

    franklinImager = franklinImager.scaledToWidth(unitWidth);
    franklinImager = franklinImager.scaledToHeight(unitHeight);

    franklinImagell = QPixmap(":assets/images/Franklin model 2 powered 2.png"); // change  the image
    franklinImagerr = QPixmap(":assets/images/Franklin model 2 powered.png");   // change  the image

    franklinImagell = franklinImagell.scaledToWidth(unitWidth);
    franklinImagell = franklinImagell.scaledToHeight(unitHeight);

    franklinImagerr = franklinImagerr.scaledToWidth(unitWidth);
    franklinImagerr = franklinImagerr.scaledToHeight(unitHeight);

    setPixmap(franklinImagel1);

    QMediaPlayer *player = new QMediaPlayer;
    QAudioOutput *audioOutput = new QAudioOutput;
    player->setAudioOutput(audioOutput);
    player->setSource(QUrl("qrc:/assets/sounds/Ah Shit Here We Go Again.mp3"));
    player->play();

    health = 3;
    score = 0;
    direction = 0;
    isPowerful = 0;
    drunk = 0;
    bullets = 0;
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
    level *manager = static_cast<level *>(currentLevel);

    if (!getIsPowerful())
    {
        if (!drunk)
        {
            if (event->key() == Qt::Key_Up && boardData[x - 1][y] >= 0)
            {
                x--;
                direction = 2;
                setPixmap(franklinImageu1);

                connect(timer, &QTimer::timeout, this, &Franklin::Move);
                timer->start(5);
            }
            else if (event->key() == Qt::Key_Down && boardData[x + 1][y] >= 0)
            {
                x++;
                direction = 3;
                setPixmap(franklinImaged1);

                connect(timer, &QTimer::timeout, this, &Franklin::Move);
                timer->start(5);
            }
            else if (event->key() == Qt::Key_Right && boardData[x][y + 1] >= 0)
            {
                y++;
                direction = 0;
                setPixmap(franklinImager1);

                connect(timer, &QTimer::timeout, this, &Franklin::Move);
                timer->start(5);
                //                QTimer::singleShot(2000, this, SLOT(Move()));
            }
            else if (event->key() == Qt::Key_Left && boardData[x][y - 1] >= 0)
            {
                y--;
                direction = 1;
                setPixmap(franklinImagel1);

                connect(timer, &QTimer::timeout, this, &Franklin::Move);
                timer->start(5);
                //                QTimer::singleShot(2000, this, SLOT(Move()));
            }
        }
        else
        {
            if (event->key() == Qt::Key_Up && boardData[x + 1][y] >= 0)
            {
                x++;
                direction = 3;
                setPixmap(franklinImaged1);

                connect(timer, &QTimer::timeout, this, &Franklin::Move);
                timer->start(5);
            }
            else if (event->key() == Qt::Key_Down && boardData[x - 1][y] >= 0)
            {
                x--;
                direction = 2;
                setPixmap(franklinImageu1);

                connect(timer, &QTimer::timeout, this, &Franklin::Move);
                timer->start(5);
            }
            else if (event->key() == Qt::Key_Left && boardData[x][y + 1] >= 0)
            {
                y++;
                direction = 0;
                setPixmap(franklinImager1);

                connect(timer, &QTimer::timeout, this, &Franklin::Move);
                timer->start(5);
                //                QTimer::singleShot(2000, this, SLOT(Move()));
            }
            else if (event->key() == Qt::Key_Right && boardData[x][y - 1] >= 0)
            {
                y--;
                direction = 1;
                setPixmap(franklinImagel1);

                connect(timer, &QTimer::timeout, this, &Franklin::Move);
                timer->start(5);
                //                QTimer::singleShot(2000, this, SLOT(Move()));
            }
        }
    }
    else
    {
        if (!drunk)
        {
            if (event->key() == Qt::Key_Up && boardData[x - 1][y] >= 0)
            {
                x--;
                direction = 2;
                setPixmap(franklinImageu);
            }
            else if (event->key() == Qt::Key_Down && boardData[x + 1][y] >= 0)
            {
                x++;
                direction = 3;
                setPixmap(franklinImaged);
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
        else
        {
            if (event->key() == Qt::Key_Up && boardData[x + 1][y] >= 0)
            {
                x++;
                direction = 3;
                setPixmap(franklinImaged);
            }
            else if (event->key() == Qt::Key_Down && boardData[x - 1][y] >= 0)
            {
                x--;
                direction = 2;
                setPixmap(franklinImageu);
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

    if (event->key() == Qt::Key_Space)
    {
        shoot();
    }

    setPos(unitWidth + y * unitWidth, unitHeight + x * unitHeight);
    checkCollision();
    if (x == 9 && y == 15)
    {
        manager->win();
    }
}

void Franklin::Move()
{
    if (!getIsPowerful())
    {

        if (direction == 0)
        {
            setPixmap(franklinImager2);
            timer->stop();
        }
        else if (direction == 1)
        {
            setPixmap(franklinImagel2);
            timer->stop();
        }
        else if (direction == 2)
        {
            setPixmap(franklinImageu2);
            timer->stop();
        }
        else
        {
            setPixmap(franklinImaged2);
            timer->stop();
        }
    }
    else
    {
        if (direction == 0)
        {
            setPixmap(franklinImager);
            timer->stop();
        }
        else if (direction == 1)
        {
            setPixmap(franklinImagel);
            timer->stop();
        }
        else if (direction == 2)
        {
            setPixmap(franklinImageu);
            timer->stop();
        }
        else
        {
            setPixmap(franklinImaged);
            timer->stop();
        }
    }
}

void Franklin::focus_player()
{
    setFlag(QGraphicsPixmapItem::ItemIsFocusable);
    setFocus();
}

void Franklin::shoot()
{
    if (bullets > 0)
    {
        if (bullets == 1)
        {
            // change image to normal
        }

        bullets--;

        QMediaPlayer *player = new QMediaPlayer;
        QAudioOutput *audioOutput = new QAudioOutput;
        player->setAudioOutput(audioOutput);
        player->setSource(QUrl("qrc:/assets/sounds/shot.mp3"));
        player->play();

        level *manager = static_cast<level *>(currentLevel);
        manager->updateCounters();

        FlyingBullet *bullet = new FlyingBullet(boardData, x, y, direction, manager);
        scene()->addItem(bullet);
    }
}

void Franklin::checkCollision()
{
    level *manager = static_cast<level *>(currentLevel);
    QList<QGraphicsItem *> collision = collidingItems();
    for (int i = 0; i < collision.size(); i++)
    {
        if (typeid(*(collision[i])) == typeid(enemy1))
        {
            manager->player_hit();
        }
        else if (typeid(*(collision[i])) == typeid(enemy2))
        {
            manager->player_hit();
        }
        else if (typeid(*(collision[i])) == typeid(bullet))
        {

            if (direction == 1)
            {
                setPixmap(franklinImagell);
                connect(timer, &QTimer::timeout, this, &Franklin::Move);
                timer->start(1000);
            }
            else
            {
                setPixmap(franklinImagerr);
                connect(timer, &QTimer::timeout, this, &Franklin::Move);
                timer->start(1000);
            }
            bullets++;
            manager->updateCounters();
            (collision[i])->setVisible(false);
        }
        else if (typeid(*(collision[i])) == typeid(pellet))
        {
            if (direction == 1)
            {
                setPixmap(franklinImagel);
            }
            else
            {
                setPixmap(franklinImager);
            }

            setPowerful(true);
            score++;
            manager->updateCounters();
            manager->updateModeTxt();
            // manager->activate_mode();   //displaying the progress bar

            connect(timer, &QTimer::timeout, this, &Franklin::setPowerful2False);
            timer->start(120000);
            //            QTimer::singleShot(10000, this, SLOT(setPowerful(false)));
            (collision[i])->setVisible(false);
        }
        else if (typeid(*(collision[i])) == typeid(Drunk))
        {

            setIsDrunk(true);

            manager->updateModeTxt();
            //   manager->activate_mode();   //displaying the progress bar

            connect(timer, &QTimer::timeout, this, &Franklin::setDrunk2False);
            timer->start(60000);
            //            QTimer::singleShot(10000, this, SLOT(setIsDrunk(false)));
            (collision[i])->setVisible(false);
        }
        // add qtimer to reverse it after 1 sec
    }
}

void Franklin::hit()
{
    level *manager = static_cast<level *>(currentLevel);

    if (!getIsPowerful())
    {
        this->health--;
        manager->remove_heart();
        this->x = 5;
        this->y = 7;
        bullets = 0;
        manager->remove_bullets();
        manager->create_bullets();
        manager->updateCounters();
        setPos(unitWidth + y * unitWidth, unitHeight + x * unitHeight);
        QMediaPlayer *player = new QMediaPlayer;
        QAudioOutput *audioOutput = new QAudioOutput;
        player->setAudioOutput(audioOutput);
        player->setSource(QUrl("qrc:/assets/sounds/Ah Shit Here We Go Again.mp3"));
        player->play();
    }
    else
    {
        setPowerful(false);
        manager->updateModeTxt();
        Move();
    }
}

int Franklin::getCoinsCount()
{
    return this->score;
}

int Franklin::getBulletsCount()
{
    return this->bullets;
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
    timer->stop();
}

void Franklin::setDrunk2False()
{
    this->drunk = false;
    level *manager = static_cast<level *>(currentLevel);
    manager->updateModeTxt();
    this->Move();
    timer->stop();
}

void Franklin::setPowerful2False()
{
    this->isPowerful = false;
    level *manager = static_cast<level *>(currentLevel);
    manager->updateModeTxt();
    this->Move();
    timer->stop();
}

int Franklin::getX()
{
    return this->x;
}

int Franklin::getY()
{
    return this->y;
}

void Franklin::editboard(int x)
{
    boardData[9][15] = x;
}
