#include "onlinelevel.h"
#include "QtCore/qjsonarray.h"
#include "onlinegamemanager.h"
#include "QtGui/qscreen.h"

//#include "flyingbullet.h"
#include <QGuiApplication>
#include <QFile>

OnlineLevel::OnlineLevel(void *gameManager, QGraphicsScene *scene, QString username, QString game_id)
{
    this->gameManager = gameManager;
    this->scene = scene;
    this->username = username;
    this->game_id = game_id;


    // display the game id on the right side of the screen
    QGraphicsTextItem *game_id_text = new QGraphicsTextItem();
    game_id_text->setPlainText("Game ID: " + game_id);
    // font big
    // make the text white
    game_id_text->setDefaultTextColor(Qt::white);
    QFont fonty("Arial", 20, QFont::StyleNormal);
    game_id_text->setZValue(1);
    game_id_text->setPos(540, 20);
    game_id_text->setFont(fonty);
    scene->addItem(game_id_text);
}

void OnlineLevel::add_board_images()
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

void OnlineLevel::create_board()
{
    QFile file(":Maze online.txt");
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

void OnlineLevel::create_players(QJsonArray playersJSON)
{
    qDebug () << "creating players "<< playersJSON << playersJSON.size();

    for (int i = 0; i < playersJSON.size(); i++)
    {
        QJsonObject player = playersJSON[i].toObject();
        QString id = player["id"].toString("");

        bool found = false;
        for (int j = 0; j < players.size(); j++)
        {
            if (players[j]->id == id)
            {
                found = true;
                break;
            }
        }

        if (found)
            continue;

        int x = player["x"].toInt();
        int y = player["y"].toInt();
        // int score = player["score"].toInt();
        int direction = player["direction"].toInt();

        OnlinePlayer *onlinePlayer = new OnlinePlayer(boardData, this, id);
        onlinePlayer->setCoordinates(x, y, direction);
        scene->addItem(onlinePlayer);
        players.append(onlinePlayer);
        onlinePlayer->add_id();
        onlinePlayer->add_health_bar();
        // display the player id above the player image

        if (id == this->username)
        {
            onlinePlayer->currPlayer = true;

            timer = new QTimer();
            QObject::connect(timer, &QTimer::timeout, onlinePlayer, &OnlinePlayer::focus_player);
            timer->start(350);
        }
    }
}

void OnlineLevel::update_player_position(QString playerId, int x, int y, int direction, int score, int bullets, int health)
{
    for (int i = 0; i < players.size(); i++)
    {
        if (players[i]->id == playerId && playerId != this->username)
        {
            qDebug() << "updating pos " <<players[i]->id << " curr health " << players[i]->health << " " << health;
            players[i]->setCoordinates(x, y, direction);
            players[i]->score = score;
            players[i]->bullets = bullets;
            players[i]->health = health;
            players[i]->healthBar->setValue(health);
        }
    }
}

void OnlineLevel::updatePosition(int x, int y, int direction)
{
    OnlineGameManager *manager = static_cast<OnlineGameManager *>(gameManager);
    manager->updatePosition(x, y, direction);
}

void OnlineLevel::add_bullet(int x, int y)
{
    for (int i = 0; i < bullets.size(); i++)
    {
        if (bullets[i]->x == x && bullets[i]->y == y)
            return;
    }

    bullet *bullet = new class bullet(boardData, x, y);
    scene->addItem(bullet);
    bullets.append(bullet);
}

void OnlineLevel::add_pellet(int x, int y)
{
    for (int i = 0; i < pellets.size(); i++)
    {
        if (pellets[i]->x == x && pellets[i]->y == y)
            return;
    }

    pellet *pellet = new class pellet(boardData, x, y);
    scene->addItem(pellet);
    pellets.append(pellet);
}

void OnlineLevel::remove_bullet(int x, int y)
{
    for (int i = 0; i < bullets.size(); i++)
    {
        if (bullets[i]->x == x && bullets[i]->y == y)
        {
//            scene->removeItem(bullets[i]);
//            bullets.removeAt(i);

            // emit bullet removal to server
            OnlineGameManager *manager = static_cast<OnlineGameManager *>(gameManager);
            manager->remove_bullet(x, y);
            return;
        }
    }
}

// same as above but for pellets
void OnlineLevel::remove_pellet(int x, int y)
{
    for (int i = 0; i < pellets.size(); i++)
    {
        if (pellets[i]->x == x && pellets[i]->y == y)
        {
//            scene->removeItem(pellets[i]);
//            pellets.removeAt(i);

            // emit pellet removal to server
            OnlineGameManager *manager = static_cast<OnlineGameManager *>(gameManager);
            manager->remove_pellet(x, y);
            return;
        }
    }
}

void OnlineLevel::updateBullet(int bullets) {
    // emit signal to update the number of bullets
    OnlineGameManager *manager = static_cast<OnlineGameManager *>(gameManager);
    manager->updateBullet(bullets);
}

void OnlineLevel::updateScore(int pellets) {
    // emit signal to update the number of pellets
    OnlineGameManager *manager = static_cast<OnlineGameManager *>(gameManager);
    manager->updateScore(pellets);
}

void OnlineLevel::clear_bullets(QJsonArray bullets)
{
    // if the bullet is not in the array, remove it from the scene
    for (int i = 0; i < this->bullets.size(); i++)
    {
        bool found = false;
        for (int j = 0; j < bullets.size(); j++)
        {
            QJsonObject bullet = bullets[j].toObject();
            int x = bullet["x"].toInt();
            int y = bullet["y"].toInt();

            if (this->bullets[i]->x == x && this->bullets[i]->y == y)
            {
                found = true;
                break;
            }
        }

        if (!found)
        {
            scene->removeItem(this->bullets[i]);
            this->bullets.removeAt(i);
        }
    }
}

void OnlineLevel::clear_pellets(QJsonArray pellets)
{
    // same as above but for pellets
    for (int i = 0; i < this->pellets.size(); i++)
    {
        bool found = false;
        for (int j = 0; j < pellets.size(); j++)
        {
            QJsonObject pellet = pellets[j].toObject();
            int x = pellet["x"].toInt();
            int y = pellet["y"].toInt();

            if (this->pellets[i]->x == x && this->pellets[i]->y == y)
            {
                found = true;
                break;
            }
        }

        if (!found)
        {
            scene->removeItem(this->pellets[i]);
            this->pellets.removeAt(i);
        }
    }
}

void OnlineLevel::remove_player(QString id) {
    for (int i = 0; i < players.size(); i++)
    {
        if (players[i]->id == id)
        {
            scene->removeItem(players[i]);
            players[i]->healthBar->setVisible(false);
            scene->removeItem(players[i]->idText);
            players.removeAt(i);
            break;
        }
    }
}

void OnlineLevel::shoot(int x, int y, int direction)
{
    // emit signal to server to add bullet
    OnlineGameManager *manager = static_cast<OnlineGameManager *>(gameManager);
    manager->shoot(x, y, direction);
}


void OnlineLevel::player_hit(int health) {
    OnlineGameManager *manager = static_cast<OnlineGameManager *>(gameManager);
    manager->player_hit(health);
    manager->remove_heart(health);
}
