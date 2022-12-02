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
        level->update_player_position(playerId, x, y, direction);
    }
}

void OnlineGameManager::anotherPlayerJoined(QJsonObject game)
{
    QJsonArray players = game["players"].toArray();
    level->create_players(players);
}

void OnlineGameManager::updatePosition(int x, int y, int direction)
{
    // send the server the new position
    socket->sendTextMessage(QString("{\"type\":\"updatePosition\",\"game\":{\"gameId\":\"%1\"},\"playerId\":\"%2\", \"player\":{\"x\":%3,\"y\":%4,\"direction\":%5}}").arg(game_id).arg(username).arg(x).arg(y).arg(direction));
}

void OnlineGameManager::onConnected()
{
    qDebug() << "Connected";
}

void OnlineGameManager::onDisconnected()
{
    qDebug() << "Disconnected";
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
            emit gameStarted(json);
        }
        else
        {
            emit anotherPlayerJoined(json);
        }
    }
    else if (type == "gameUpdated")
    {
        emit gameUpdated(json);
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
    player->play();
}
