#include "onlinegamemanager.h"

#include <QGraphicsScene>
#include <QPushButton>
#include <QGraphicsRectItem>
#include <QGuiApplication>
#include <QGraphicsTextItem>
#include <QObject>
#include <QLineEdit>
#include <QtUiTools>

#include <QNetworkAccessManager>
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
        join_game(idLine->text()); },
        Qt::QueuedConnection);
}

void OnlineGameManager::create_new_game()
{
    // here we send a post request to the server to create a new game
    // the base url is https://gta-vi-backend1.onrender.com
    // the endpoint is /create
    // the body is empty 
    // attach the token in the header

    // the response will be a json with the game id
    // if the response is 200, then the game is created
    // if the response is 401, then the user is not signed in
    // if the response is 500, then the game could not be created

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
                             QString game_id = json["game_id"].toString();
                             label->setText("Game created with id " + game_id);
                             idLine->setText(game_id);
                         }
                         else
                         {
                            // print status code int
                            qDebug() << QString::number(reply->attribute(QNetworkRequest::HttpStatusCodeAttribute).toInt());

                            qDebug() << reply->errorString();
                             label->setText("Error creating game");
                         }
                     });
}

void OnlineGameManager::join_game(QString id)
{
}

void OnlineGameManager::create_game_waiting_panel()
{
    QFile file(":/forms/onlinegamewaiting.ui");
    file.open(QIODevice::ReadOnly);

    QUiLoader loader;
    QWidget *layout = loader.load(&file, nullptr);
    scene->addWidget(layout);
}
