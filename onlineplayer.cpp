#include "onlineplayer.h"
#include "QtGui/qevent.h"
#include "QtGui/qscreen.h"
#include <QGuiApplication>
#include "onlinelevel.h"
#include <QKeyEvent>

OnlinePlayer::OnlinePlayer(int boardData[12][16], void *currentLevel, QString username)
{
    qDebug () << "online player created with username: "<< username;

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
}


void OnlinePlayer::add_id() {
    idText = new QGraphicsTextItem(id);
    idText->setDefaultTextColor(Qt::white);
//    idText->setFont(QFont("Arial", 20));
    idText->setZValue(1);
    scene()->addItem(idText);
    qDebug () << "id is "<< id;
    qDebug () << scene();

    if(idText != nullptr) {
        idText->setPos(unitWidth + y * unitWidth + 20, unitHeight + x * unitHeight - 25);
    }
}

void OnlinePlayer::setCoordinates(int x, int y, int direction)
{
    this->x = x;
    this->y = y;
    this->direction = direction;

    if (direction == 0)
    {
        setPixmap(franklinImager);
        if(idText != nullptr) {
            idText->setPos(unitWidth + y * unitWidth + 20, unitHeight + x * unitHeight - 25);
            // rotate the text
            idText->setRotation(0);
        }
//        timer->stop();
    }
    else if (direction == 1)
    {
        setPixmap(franklinImagel);
        if(idText != nullptr) {
            idText->setPos(unitWidth + y * unitWidth + 20, unitHeight + x * unitHeight - 25);
            idText->setRotation(0);

        }
//        timer->stop();
    }
    else if (direction == 2)
    {
        setPixmap(franklinImageu);
        if(idText != nullptr) {
            idText->setPos(unitWidth + y * unitWidth + 90, unitHeight + x * unitHeight + 20);
            idText->setRotation(90);
        }
//        timer->stop();
    }
    else
    {
        setPixmap(franklinImaged);
        if(idText != nullptr) {
            idText->setPos(unitWidth + y * unitWidth + 90, unitHeight + x * unitHeight + 20);
            idText->setRotation(90);
        }
//        timer->stop();
    }

    qDebug() << "in set coordinates "<< x << y;

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
            if(idText != nullptr) {
                idText->setPos(unitWidth + y * unitWidth + 90, unitHeight + x * unitHeight + 20);
                idText->setRotation(90);
            }
        }
        else if (event->key() == Qt::Key_Down && boardData[x + 1][y] >= 0)
        {
            x++;
            direction = 3;
            setPixmap(franklinImaged);
            if(idText != nullptr) {
                idText->setPos(unitWidth + y * unitWidth + 90, unitHeight + x * unitHeight + 20);
                idText->setRotation(90);
            }
        }
        else if (event->key() == Qt::Key_Right && boardData[x][y + 1] >= 0)
        {
            y++;
            direction = 0;
            setPixmap(franklinImager);
            if(idText != nullptr) {
                idText->setPos(unitWidth + y * unitWidth + 20, unitHeight + x * unitHeight - 25);
                idText->setRotation(0);
            }
        }
        else if (event->key() == Qt::Key_Left && boardData[x][y - 1] >= 0)
        {
            y--;
            direction = 1;
            setPixmap(franklinImagel);
            if(idText != nullptr) {
                idText->setPos(unitWidth + y * unitWidth + 20, unitHeight + x * unitHeight - 25);
                idText->setRotation(0);
            }
        }

        if (event->key() == Qt::Key_Space)
        {
            // shoot();
        }

        setPos(unitWidth + y * unitWidth, unitHeight + x * unitHeight);

        checkCollision();
        // if (x == 9 && y == 15)
        // {
        //     manager->win();
        // }

        manager->updatePosition(x, y, direction);
    }
}

void OnlinePlayer::checkCollision() {
    OnlineLevel *manager = static_cast<OnlineLevel *>(currentLevel);
    QList<QGraphicsItem *> collision = collidingItems();

    for (int i = 0; i < collision.size(); i++)
    {
        if (typeid(*(collision[i])) == typeid(bullet))
        {
            // cast the item to a bullet
            bullet *bullet = dynamic_cast<class bullet *>(collision[i]);
            manager->remove_bullet(bullet->x, bullet->y);
            bullets++;
            manager->updateBullet(bullets);
        } else if (typeid(*(collision[i])) == typeid(pellet))
        {
            pellet *pellet = dynamic_cast<class pellet *>(collision[i]);
            manager->remove_pellet(pellet->x, pellet->y);
            score++;
            manager->updateScore(score);
        } 
    }

}
