#include "onlinegamemanager.h"

#include <QGraphicsScene>
#include <QPushButton>
#include <QGraphicsRectItem>
#include <QGuiApplication>
#include <QGraphicsTextItem>
#include <QObject>
#include <QLineEdit>
#include <QtUiTools>

#include <QtCore/QJsonObject>
#include <QtCore/QJsonArray>
#include <QtCore/QDebug>

#include <QNetworkAccessManager>
#include <QJsonArray>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QUrl>
#include <QUrlQuery>
#include <QJsonDocument>
#include <QJsonObject>
#include <QByteArray>

#include <QAudioFormat>
#include <QMediaPlayer>
#include <QAudioOutput>
#include <QLabel>
#include <QPushButton>
#include <QProgressBar>
#include <QMessageBox>
#include <QGraphicsRectItem>
#include <QGraphicsProxyWidget>
#include <qprocess.h>
#include <qmovie.h>
#include <QMovie>

#include "onlineflyingbullet.h"

OnlineGameManager::OnlineGameManager(QGraphicsScene *scene, QString token, QString username)
{
    this->token = token;
    this->username = username;
    this->scene = scene;
    create_game_id_panel();

    state = "init";

    QUrl url("https://gta-vi-backend1.onrender.com");
    url.setScheme("wss");
    url.setPath("/");
    socket = new QWebSocket();
    socket->open(url);
    connect(socket, &QWebSocket::connected, this, &OnlineGameManager::onConnected);
    connect(socket, &QWebSocket::disconnected, this, &OnlineGameManager::onDisconnected);
    connect(socket, &QWebSocket::textMessageReceived, this, &OnlineGameManager::onTextMessageReceived);
}

void OnlineGameManager::create_game_id_panel()
{
    QFile file(":/forms/onlinegameid.ui");
    file.open(QIODevice::ReadOnly);

    QUiLoader loader;
    QWidget *layout = loader.load(&file, nullptr);
    scene->addWidget(layout);

    QPushButton *newGameButton = layout->findChild<QPushButton *>("createNew");
    QPushButton *joinButton = layout->findChild<QPushButton *>("join");
    idLine = layout->findChild<QLineEdit *>("lineEdit");
    label = layout->findChild<QLabel *>("errorLabel");

    QObject::connect(
        newGameButton, &QPushButton::clicked, layout, [this]()
        {
        label->setText("Loading...");
        create_new_game(); },
        Qt::QueuedConnection);

    QObject::connect(
        joinButton, &QPushButton::clicked, layout, [this]()
        {
        game_id = idLine->text();
        join_game(); },
        Qt::QueuedConnection);
}

void OnlineGameManager::create_new_game()
{
    QNetworkAccessManager *manager = new QNetworkAccessManager(this);
    QNetworkRequest request(QUrl("https://gta-vi-backend1.onrender.com/create"));
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");
    request.setRawHeader("Authorization", "JWT " + token.toUtf8());

    QNetworkReply *reply = manager->post(request, QByteArray());
    QObject::connect(reply, &QNetworkReply::finished, this, [this, reply]()
                     {
                        if (reply->error() == QNetworkReply::NoError)
                        {
                            QByteArray bytes = reply->readAll();
                            QJsonDocument doc = QJsonDocument::fromJson(bytes);
                            QJsonObject json = doc.object();
                           QJsonObject game = json["game"].toObject();
                           game_id = game["id"].toString();
                           qDebug() << "created game id is " << game_id;
                           join_game();
                        }
                        else
                        {
                            label->setText("Error creating game");
                        } });
}

void OnlineGameManager::join_game()
{
    qDebug() << "joinging game...";
    label->setText("Joining game...");
    socket->sendTextMessage(QString("{\"type\":\"joinGame\",\"game\":{\"gameId\":\"%1\"},\"playerId\":\"%2\"}").arg(game_id).arg(username));
}

void OnlineGameManager::create_game_waiting_panel()
{
    QFile file(":/forms/onlinegamewaiting.ui");
    file.open(QIODevice::ReadOnly);

    QUiLoader loader;
    QWidget *layout = loader.load(&file, nullptr);
    scene->addWidget(layout);
    QLabel *labelID = layout->findChild<QLabel *>("gameId");
    labelID->setText(game_id);
}

void OnlineGameManager::gameStarted(QJsonObject game)
{
    scene->clear();
    level = new OnlineLevel(this, scene, username, game_id);
    level->create_board();
    level->add_board_images();
    QJsonArray players = game["players"].toArray();
    level->create_players(players);
    create_healthbar();
    gameUpdated(game);
    create_sound();
}

void OnlineGameManager::gameUpdated(QJsonObject game)
{
    QJsonArray players = game["players"].toArray();
    for (int i = 0; i < players.size(); i++)
    {
        QJsonObject player = players[i].toObject();
        QString playerId = player["id"].toString();
        int x = player["x"].toInt();
        int y = player["y"].toInt();
        int direction = player["direction"].toInt();
        int score = player["score"].toInt();
        int health = player["health"].toInt();
        int bullets = player["bullets"].toInt();
        level->update_player_position(playerId, x, y, direction, score, bullets, health);

        if (playerId == username)
        {
            // change bulletsCounter, and coinsCounter
            bulletsCounter->setPlainText(QString::number(bullets));
            coinsCounter->setPlainText(QString::number(score));

            // todo: change number of hearts
        }
    }

    QJsonArray bullets = game["bullets"].toArray();
    for (int i = 0; i < bullets.size(); i++)
    {
        QJsonObject bullet = bullets[i].toObject();
        int x = bullet["x"].toInt();
        int y = bullet["y"].toInt();
        level->add_bullet(x, y);
    }
    // if the level has a bullet that is not in the bullets list then remove it
    level->clear_bullets(bullets);

    QJsonArray pellets = game["pellets"].toArray();
    for (int i = 0; i < pellets.size(); i++)
    {
        QJsonObject pellet = pellets[i].toObject();
        int x = pellet["x"].toInt();
        int y = pellet["y"].toInt();
        level->add_pellet(x, y);
    }
    level->clear_pellets(pellets);
}

void OnlineGameManager::shoot(int x, int y, int direction)
{
    socket->sendTextMessage(QString("{\"type\":\"shoot\",\"game\":{\"gameId\":\"%1\"},\"playerId\":\"%2\",\"x\":%3,\"y\":%4,\"direction\":%5}").arg(game_id).arg(username).arg(x).arg(y).arg(direction));
    bulletsCounter->setPlainText(QString::number(bulletsCounter->toPlainText().toInt() - 1));
}


void OnlineGameManager::player_hit(int health) {
    // emit the new health of the player to the socket
    socket->sendTextMessage(QString("{\"type\":\"playerHit\",\"game\":{\"gameId\":\"%1\"},\"playerId\":\"%2\"}").arg(game_id).arg(username));
}

void OnlineGameManager::remove_heart(int health) {
    if (health >= 0)
    {
        scene->removeItem(&(hearts[health]));
    }

    if (health == 0)
    {
       game_over();
    }
}

void OnlineGameManager::game_over()
{
    qDebug() << "Game Over";
    state = "gameOver";

    // close after 0.1 
    QTimer::singleShot(100, this, [this]()
    {
        socket->close();
    });

    int screenWidth = QGuiApplication::primaryScreen()->availableSize().width();
    int screenHeight = QGuiApplication::primaryScreen()->availableSize().height();
    for (size_t i = 0, n = scene->items().size(); i < n; i++)
    {
        scene->items()[i]->setEnabled(false);
    }

    drawPanel(screenWidth / 3 - 20, screenHeight / 3 - 20, 400, 400, Qt::lightGray, 1);

    /* Gmae Over Text*/
    QGraphicsTextItem *overText = new QGraphicsTextItem("Game Over");
    QFont fonty("Arial", 20, QFont::StyleNormal);
    overText->setPos(screenWidth / 3 + 100, screenHeight / 3 + 80);
    overText->setFont(fonty);
    scene->addItem(overText);

    QPushButton *quit;
    quit = new QPushButton("Restart again");
    quit->setGeometry(screenWidth / 3 + 100, screenHeight / 3 + 250, 100, 50);
    scene->addWidget(quit);

    QObject::connect(quit, &QPushButton::clicked, [=]()
                     { exit(); });
}

void OnlineGameManager::anotherPlayerJoined(QJsonObject game)
{
    QJsonArray players = game["players"].toArray();
    level->create_players(players);
}

void OnlineGameManager::shoot_another_bullet(int x, int y, int direction)
{
    QMediaPlayer *player = new QMediaPlayer;
    QAudioOutput *audioOutput = new QAudioOutput;
    player->setAudioOutput(audioOutput);
    player->setSource(QUrl("qrc:/assets/sounds/shot.mp3"));
    player->play();

    OnlineFlyingBullet *bullet = new OnlineFlyingBullet(level->boardData, x, y, direction, level, "", username);
    scene->addItem(bullet);
}

void OnlineGameManager::updatePosition(int x, int y, int direction)
{
    // send the server the new position
    qDebug() << "emitting move with user name " << username << " x: " << x << " y: " << y;
    socket->sendTextMessage(QString("{\"type\":\"move\",\"game\":{\"gameId\":\"%1\"},\"playerId\":\"%2\", \"player\":{\"x\":%3,\"y\":%4,\"direction\":%5}}").arg(game_id).arg(username).arg(x).arg(y).arg(direction));
}

void OnlineGameManager::remove_bullet(int x, int y)
{
    socket->sendTextMessage(QString("{\"type\":\"removeBullet\",\"game\":{\"gameId\":\"%1\"},\"playerId\":\"%2\", \"bullet\":{\"x\":%3,\"y\":%4}}").arg(game_id).arg(username).arg(x).arg(y));
}

void OnlineGameManager::remove_pellet(int x, int y)
{
    socket->sendTextMessage(QString("{\"type\":\"removePellet\",\"game\":{\"gameId\":\"%1\"},\"playerId\":\"%2\", \"pellet\":{\"x\":%3,\"y\":%4}}").arg(game_id).arg(username).arg(x).arg(y));
}

void OnlineGameManager::updateBullet(int bullets)
{
    socket->sendTextMessage(QString("{\"type\":\"updateBullets\",\"game\":{\"gameId\":\"%1\"},\"playerId\":\"%2\", \"player\":{\"bullets\":%3}}").arg(game_id).arg(username).arg(bullets));
}

void OnlineGameManager::updateScore(int score)
{
    socket->sendTextMessage(QString("{\"type\":\"updateScore\",\"game\":{\"gameId\":\"%1\"},\"playerId\":\"%2\", \"player\":{\"score\":%3}}").arg(game_id).arg(username).arg(score));
}

void OnlineGameManager::onConnected()
{
    qDebug() << "Connected";
}

void OnlineGameManager::onDisconnected()
{
    qDebug() << "Disconnected";

    if(state == "gameOver" || state == "gameWon")
          return;

    int screenWidth = QGuiApplication::primaryScreen()->availableSize().width();
    int screenHeight = QGuiApplication::primaryScreen()->availableSize().height();
    for (size_t i = 0, n = scene->items().size(); i < n; i++)
    {
        scene->items()[i]->setEnabled(false);
    }

    drawPanel(screenWidth / 3 - 20, screenHeight / 3 - 20, 400, 400, Qt::lightGray, 1);

    /* Gmae Over Text*/
    QGraphicsTextItem *overText = new QGraphicsTextItem("Network Error, Please Try and Join Again");
    QFont fonty("Arial", 20, QFont::StyleNormal);
    overText->setPos(screenWidth / 3 + 100, screenHeight / 3 + 80);
    overText->setFont(fonty);
    scene->addItem(overText);

    QPushButton *quit;
    quit = new QPushButton("Quit");
    quit->setGeometry(screenWidth / 3 + 100, screenHeight / 3 + 250, 100, 50);
    scene->addWidget(quit);

    QObject::connect(quit, &QPushButton::clicked, [=]()
                     { exit(); });
}

void OnlineGameManager::exit()
{
    QString program = qApp->arguments()[0];
    QStringList arguments = qApp->arguments().mid(1);
    qApp->quit();
    QProcess::startDetached(program, arguments);
}

QGraphicsRectItem *OnlineGameManager::drawPanel(int x, int y, int width, int height, QColor color, double opacity)
{
    // draws a panel at the specified location with the specified properties

    QGraphicsRectItem *panel = new QGraphicsRectItem(x, y, width, height);
    QBrush brush;
    brush.setStyle(Qt::SolidPattern);
    brush.setColor(color);
    panel->setBrush(brush);
    panel->setOpacity(opacity);
    scene->addItem(panel);

    return panel;
}

void OnlineGameManager::gameWon() {
    state = "gameWon";

    // close after 0.1 
    QTimer::singleShot(100, this, [this]()
    {
        socket->close();
    });

    int screenWidth = QGuiApplication::primaryScreen()->availableSize().width();
    int screenHeight = QGuiApplication::primaryScreen()->availableSize().height();
    for (size_t i = 0, n = scene->items().size(); i < n; i++)
    {
        scene->items()[i]->setEnabled(false);
    }

    drawPanel(screenWidth / 3 - 20, screenHeight / 3 - 20, 400, 400, Qt::lightGray, 1);

    /* Gmae Over Text*/
    QGraphicsTextItem *overText = new QGraphicsTextItem("You Won!");
    QFont fonty("Arial", 20, QFont::StyleNormal);
    overText->setPos(screenWidth / 3 + 100, screenHeight / 3 + 80);
    overText->setFont(fonty);
    scene->addItem(overText);

    QPushButton *quit;
    quit = new QPushButton("Play again");
    quit->setGeometry(screenWidth / 3 + 100, screenHeight / 3 + 250, 100, 50);
    scene->addWidget(quit);

    QObject::connect(quit, &QPushButton::clicked, [=]()
                     { exit(); });
}

void OnlineGameManager::playerDied(QString id) {
    // remove the player with the same id from the level
    level->remove_player(id);
}

void OnlineGameManager::onTextMessageReceived(QString message)
{
    qDebug() << "Message received:" << message;

    // Parse the message
    QJsonDocument doc = QJsonDocument::fromJson(message.toUtf8());
    QJsonObject json = doc.object();
    QString type = json["type"].toString();

    if (type == "gameJoined")
    {
        qDebug() << "Game joined";
        create_game_waiting_panel();
        state = "gameJoined";
    }
    else if (type == "gameStarted")
    {
        qDebug() << "Game started";
        if (state != "gameStarted")
        {
            state = "gameStarted";
            emit gameStarted(json["game"].toObject());
        }
        else
        {
            emit anotherPlayerJoined(json["game"].toObject());
        }
    }
    else if (type == "gameUpdated")
    {
        emit gameUpdated(json["game"].toObject());
    }
    else if (type == "shoot")
    {
        emit shoot_another_bullet(json["x"].toInt(), json["y"].toInt(), json["direction"].toInt());
    } else if (type == "playerDied") {
        emit playerDied(json["player"].toString());
    } else if(type == "gameWon") {
        emit gameWon();
    }
    else if (type == "error")
    {
        qDebug() << "Error";
        if (state == "init")
        {
            label->setText("Error joining game");
        }
    }
}

void OnlineGameManager::create_sound()
{
    QMediaPlayer *player = new QMediaPlayer;
    QAudioOutput *audioOutput = new QAudioOutput;
    player->setAudioOutput(audioOutput);
    player->setLoops(QMediaPlayer::Infinite);
    player->setSource(QUrl("qrc:/assets/sounds/backsound.mp3"));
    //    player->play();
}

void OnlineGameManager::create_healthbar()
{
    int screenWidth = QGuiApplication::primaryScreen()->availableSize().width();
    int screenHeight = QGuiApplication::primaryScreen()->availableSize().height();
    int unitWidth = qMin(screenWidth, screenHeight) / 17;
    int unitHeight = qMin(screenWidth, screenHeight) / 17;

    QGraphicsRectItem *panel = new QGraphicsRectItem(65, 0, 1130, 70);
    QBrush *brush = new QBrush();
    brush->setColor(Qt::darkGray);
    brush->setStyle(Qt::SolidPattern);
    panel->setBrush(*brush);
    scene->addItem(panel);

    txt = new QGraphicsTextItem("NORMAL MODE");
    QFont fonty("Arial", 20, QFont::StyleNormal);
    txt->setPos(540, 20);
    txt->setFont(fonty);
    txt->setDefaultTextColor(Qt::white);
    scene->addItem(txt);

    /* Creating Hearts */
    hearts = new QGraphicsPixmapItem[3];

    QPixmap blankImage(":assets/images/extra.png");

    blankImage = blankImage.scaledToWidth(unitWidth);
    blankImage = blankImage.scaledToHeight(unitHeight);
    for (int i = 0; i < 3; i++)
    {
        hearts[i].setPixmap(blankImage);
        hearts[i].setPos(80 * (i + 1), 15);
        scene->addItem(&hearts[i]);
    }

    QPixmap bulletImage(":assets/images/bullet.png");
    bulletImage = bulletImage.scaledToWidth(unitWidth);
    bulletImage = bulletImage.scaledToHeight(unitHeight);

    QGraphicsPixmapItem *bulletItem = new QGraphicsPixmapItem();
    bulletItem->setPos(300, 15);
    bulletItem->setPixmap(bulletImage);
    scene->addItem(bulletItem);

    bulletsCounter = new QGraphicsTextItem("0");
    bulletsCounter->setPos(360, 20);
    bulletsCounter->setFont(fonty);
    bulletsCounter->setDefaultTextColor(Qt::white);
    scene->addItem(bulletsCounter);

    QPixmap coinImage(":assets/images/coin.png");

    coinImage = coinImage.scaledToWidth(unitWidth);
    coinImage = coinImage.scaledToHeight(unitHeight);

    QGraphicsPixmapItem *coinItem = new QGraphicsPixmapItem();
    coinItem->setPos(400, 15);
    coinItem->setPixmap(coinImage);
    scene->addItem(coinItem);

    coinsCounter = new QGraphicsTextItem("0");
    coinsCounter->setPos(460, 20);
    coinsCounter->setFont(fonty);
    coinsCounter->setDefaultTextColor(Qt::white);
    scene->addItem(coinsCounter);
}
