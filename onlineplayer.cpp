#include "onlineplayer.h"
#include "QtGui/qevent.h"
#include "QtGui/qscreen.h"
#include <QGuiApplication>
#include "onlinelevel.h"
#include <QKeyEvent>
#include <QMessageBox>
#include <QSoundEffect>
#include <QAudioFormat>
#include <QMediaPlayer>
#include <QAudioOutput>
#include "level.h"
#include "onlineflyingbullet.h"

OnlinePlayer::OnlinePlayer(int boardData[12][16], void *currentLevel, QString username)
{
    qDebug() << "online player created with username: " << username;

    this->currentLevel = currentLevel;
    this->id = username;
    this->currPlayer = false;
    this->idText = nullptr;

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
    unitWidth = qMin(screenWidth, screenHeight) / 13;
    unitHeight = qMin(screenWidth, screenHeight) / 13;

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

    //    QMediaPlayer *player = new QMediaPlayer;
    //    QAudioOutput *audioOutput = new QAudioOutput;
    //    player->setAudioOutput(audioOutput);
    //    player->setSource(QUrl("qrc:/assets/sounds/Ah Shit Here We Go Again.mp3"));
    //    player->play();

    health = 3;
    score = 0;
    direction = 0;
    isPowerful = 0;
    drunk = 0;
    bullets = 0;
    x = 0;
    y = 0;

    for (int i = 0; i < 12; i++)
    {
        for (int j = 0; j < 16; j++)
        {
            this->boardData[i][j] = boardData[i][j];
        }
    }

    // display a health bar above each player
    // the health bar is a QProgressBar
    // it should have a value synchronized with the player's health
    // it should be displayed above the player's head
}

void OnlinePlayer::add_id()
{
    idText = new QGraphicsTextItem(id);
    idText->setDefaultTextColor(Qt::white);
    //    idText->setFont(QFont("Arial", 20));
//    idText->setZValue(1);
    scene()->addItem(idText);
    qDebug() << "id is " << id;
    qDebug() << scene();

    if (idText != nullptr)
    {
        idText->setPos(unitWidth + y * unitWidth + 20, unitHeight + x * unitHeight - 25);
    }
}

void OnlinePlayer::add_health_bar() {
    healthBar = new QProgressBar();
    healthBar->setMaximum(this->health);
    healthBar->setMinimum(0);
    healthBar->setValue(3);
    healthBar->setGeometry(unitWidth + y * unitWidth + 20, unitHeight + x * unitHeight - 35, 50, 10);
    // make the chunk of the health bar that is filled in red
    // add nice border radius to the health bar
    // make the chunck of the health bar take its full width and height
    // and lastly, make the health bar transparent
    // also make the chuck begin at the right side of the health bar

    healthBar->setStyleSheet("QProgressBar::chunk {background-color: red; border-radius: 5px;}"
                             "QProgressBar {border: 1px solid grey; border-radius: 5px; background-color: transparent;}");

//    healthBar->setAlignment(Qt::AlignCenter);
    healthBar->setFormat("");
    scene()->addWidget(healthBar);
}

void OnlinePlayer::setCoordinates(int x, int y, int direction)
{
    this->x = x;
    this->y = y;
    this->direction = direction;

    if (direction == 0)
    {
        setPixmap(franklinImager);
        if (idText != nullptr)
        {
            idText->setPos(unitWidth + y * unitWidth + 20, unitHeight + x * unitHeight - 25);
            // rotate the text
            idText->setRotation(0);

            healthBar->setOrientation(Qt::Horizontal);
            healthBar->setGeometry(unitWidth + y * unitWidth + 20, unitHeight + x * unitHeight - 35, 50, 10);
        }
        //        timer->stop();
    }
    else if (direction == 1)
    {
        setPixmap(franklinImagel);
        if (idText != nullptr)
        {
            idText->setPos(unitWidth + y * unitWidth + 20, unitHeight + x * unitHeight - 25);
            idText->setRotation(0);

            healthBar->setOrientation(Qt::Horizontal);
            healthBar->setGeometry(unitWidth + y * unitWidth + 20, unitHeight + x * unitHeight - 35, 50, 10);
        }
        //        timer->stop();
    }
    else if (direction == 2)
    {
        setPixmap(franklinImageu);
        if (idText != nullptr)
        {
            idText->setPos(unitWidth + y * unitWidth + 90, unitHeight + x * unitHeight + 20);
            idText->setRotation(90);

            healthBar->setOrientation(Qt::Vertical);
                healthBar->setGeometry(unitWidth + y * unitWidth + 90, unitHeight + x * unitHeight + 20, 10, 50);
        }
        //        timer->stop();
    }
    else
    {
        setPixmap(franklinImaged);
        if (idText != nullptr)
        {
            idText->setPos(unitWidth + y * unitWidth + 90, unitHeight + x * unitHeight + 20);
            idText->setRotation(90);

            healthBar->setOrientation(Qt::Vertical);
                healthBar->setGeometry(unitWidth + y * unitWidth + 90, unitHeight + x * unitHeight + 20, 10, 50);
        }
        //        timer->stop();
    }

    qDebug() << "in set coordinates " << x << y;

    setPos(unitWidth + y * unitWidth, unitHeight + x * unitHeight);
}

void OnlinePlayer::focus_player()
{
    setFlag(QGraphicsPixmapItem::ItemIsFocusable);
    setFocus();
}

void OnlinePlayer::keyPressEvent(QKeyEvent *event)
{
    if (currPlayer == true)
    {
        OnlineLevel *manager = static_cast<OnlineLevel *>(currentLevel);

        if (event->key() == Qt::Key_Up && boardData[x - 1][y] >= 0)
        {
            x--;
            direction = 2;
            setPixmap(franklinImageu);
            if (idText != nullptr)
            {
                idText->setPos(unitWidth + y * unitWidth + 90, unitHeight + x * unitHeight + 20);
                idText->setRotation(90);

                healthBar->setOrientation(Qt::Vertical);

                healthBar->setGeometry(unitWidth + y * unitWidth + 90, unitHeight + x * unitHeight + 20, 10, 50);

            }
        }
        else if (event->key() == Qt::Key_Down && boardData[x + 1][y] >= 0)
        {
            x++;
            direction = 3;
            setPixmap(franklinImaged);
            if (idText != nullptr)
            {
                idText->setPos(unitWidth + y * unitWidth + 90, unitHeight + x * unitHeight + 20);
                idText->setRotation(90);

                healthBar->setOrientation(Qt::Vertical);

                healthBar->setGeometry(unitWidth + y * unitWidth + 90, unitHeight + x * unitHeight + 20, 10, 50);

            }
        }
        else if (event->key() == Qt::Key_Right && boardData[x][y + 1] >= 0)
        {
            y++;
            direction = 0;
            setPixmap(franklinImager);
            if (idText != nullptr)
            {
                idText->setPos(unitWidth + y * unitWidth + 20, unitHeight + x * unitHeight - 25);
                idText->setRotation(0);

                healthBar->setOrientation(Qt::Horizontal);

            healthBar->setGeometry(unitWidth + y * unitWidth + 20, unitHeight + x * unitHeight - 35, 50, 10);
            }
        }
        else if (event->key() == Qt::Key_Left && boardData[x][y - 1] >= 0)
        {
            y--;
            direction = 1;
            setPixmap(franklinImagel);
            if (idText != nullptr)
            {
                idText->setPos(unitWidth + y * unitWidth + 20, unitHeight + x * unitHeight - 25);
                idText->setRotation(0);

                healthBar->setOrientation(Qt::Horizontal);

            healthBar->setGeometry(unitWidth + y * unitWidth + 20, unitHeight + x * unitHeight - 35, 50, 10);
            }
        }

        if (event->key() == Qt::Key_Space)
        {
            shoot();
        }

        setPos(unitWidth + y * unitWidth, unitHeight + x * unitHeight);

        manager->updatePosition(x, y, direction);
        checkCollision();
        // if (x == 9 && y == 15)
        // {
        //     manager->win();
        // }
    }
}

void OnlinePlayer::checkCollision()
{
    QList<QGraphicsItem *> collision = collidingItems();

    for (int i = 0; i < collision.size(); i++)
    {
        if (typeid(*(collision[i])) == typeid(bullet))
        {
            // cast the item to a bullet
            bullet *bullet = dynamic_cast<class bullet *>(collision[i]);

                OnlineLevel *manager = static_cast<OnlineLevel *>(currentLevel);
                manager->remove_bullet(bullet->x, bullet->y);
                bullets++;
                manager->updateBullet(bullets);
        }
        else if (typeid(*(collision[i])) == typeid(pellet))
        {
            pellet *pellet = dynamic_cast<class pellet *>(collision[i]);

                OnlineLevel *manager = static_cast<OnlineLevel *>(currentLevel);
                manager->remove_pellet(pellet->x, pellet->y);

                score++;
            manager->updateScore(score);
        }
    }
}

void OnlinePlayer::shoot()
{
    if (bullets > 0)
    {
        bullets--;

        OnlineLevel *manager = static_cast<OnlineLevel *>(currentLevel);
        manager->shoot(x, y, direction);

        QMediaPlayer *player = new QMediaPlayer;
        QAudioOutput *audioOutput = new QAudioOutput;
        player->setAudioOutput(audioOutput);
        player->setSource(QUrl("qrc:/assets/sounds/shot.mp3"));
        player->play();

        OnlineFlyingBullet *bullet = new OnlineFlyingBullet(boardData, x, y, direction, manager, this->id, this->id);
        scene()->addItem(bullet);
    }
}

void OnlinePlayer::hit() {
    health--;
    healthBar->setValue(health);
}
