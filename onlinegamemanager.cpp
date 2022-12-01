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

OnlineGameManager::OnlineGameManager(QGraphicsScene *scene, QString token, QString username)
{
    this->token = token;
    this->username = username;
    this->scene = scene;
    create_game_id_panel();

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
        label->setText("Loading...");
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
                            create_game_waiting_panel();
                        }
                        else
                        {
                            label->setText("Error creating game");
                        } });
}

void OnlineGameManager::join_game()
{
    qDebug() << "joinging game...";
    socket->sendTextMessage(QString("{\"event\":\"joinGame\",\"gameId\":\"%1\",\"playerId\":\"%2\"}").arg(game_id).arg(username));
}

void OnlineGameManager::create_game_waiting_panel()
{
    QFile file(":/forms/onlinegamewaiting.ui");
    file.open(QIODevice::ReadOnly);

    QUiLoader loader;
    QWidget *layout = loader.load(&file, nullptr);
    scene->addWidget(layout);
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
}
