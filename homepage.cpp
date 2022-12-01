#include "homepage.h"
#include "ui_homepage.h"
#include "log_in.h"
#include <QFile>
#include <QObject>
#include <QSaveFile>

#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QUrl>
#include <QUrlQuery>
#include <QJsonDocument>
#include <QJsonObject>
#include <QByteArray>

#include "gamemanager.h"
#include "onlinegamemanager.h"


homepage::homepage(QGraphicsScene *scene)
{
    ui = new Ui::homepage;
    ui->setupUi(this);

    this->scene = scene;

    ui->pass->setEchoMode(QLineEdit::Password);
    ui->OnlineButton->setVisible(false);
    ui->pushButton->setVisible(false);
    ui->errorLabel->setVisible(false);
    ui->marketButton->setVisible(false);
    QGraphicsScene *scene1 = new QGraphicsScene();
    QGraphicsScene *scene2 = new QGraphicsScene();
    QGraphicsScene *scene3 = new QGraphicsScene();
    QPixmap k(":assets/images/kiro.png");
    k = k.scaledToWidth(200);
    k = k.scaledToHeight(200);
    QPixmap a(":assets/images/allam.png");
    a = a.scaledToWidth(200);
    a = a.scaledToHeight(200);
    QPixmap t(":assets/images/tawfiq.png");
    t = t.scaledToWidth(200);
    t = t.scaledToHeight(200);
    scene1->addPixmap(k);
    ui->graphicsView->setScene(scene1);
    scene2->addPixmap(a);
    ui->graphicsView_2->setScene(scene2);
    scene3->addPixmap(t);
    ui->graphicsView_3->setScene(scene3);

    QObject::connect(ui->pushButton, SIGNAL(clicked()), this, SLOT(start_story_mode()), Qt::QueuedConnection);
    QObject::connect(ui->OnlineButton, SIGNAL(clicked()), this, SLOT(start_online_mode()), Qt::QueuedConnection);

}

homepage::~homepage()
{
    delete ui;
}

void homepage::start_story_mode()
{
    GameManager * manager = new GameManager(scene);
    deleteLater();
    manager->launch_game();
}

void homepage::start_online_mode() {
    OnlineGameManager * manager = new OnlineGameManager(scene, token, username);
    deleteLater();
//    manager->launch_game();
}

void homepage::on_Log_clicked()
{
    Log_in dialog(this);
    dialog.setModal(true);
    dialog.exec();
}

void homepage::on_Sign_clicked()
{
    ui->errorLabel->setVisible(false);
    bool flag = true;
    QString username = ui->user->text();
    QString password = ui->pass->text();
    if (username == "")
    {
        ui->errorLabel->setText("Please enter your username");
        ui->errorLabel->setVisible(true);
    }
    else if (password == "")
    {
        ui->errorLabel->setText("Please enter the password");
        ui->errorLabel->setVisible(true);
    }
    else
    {
        // for (int i = 0; i < user.length(); i++)
        // {
        //     if (user[i] == username)
        //     {
        //         flag = false;
        //         if (pass[i] == password)
        //         {
        //             ui->OnlineButton->setVisible(true);
        //             ui->marketButton->setVisible(true);
        //             ui->pushButton->setVisible(true);
        //             ui->errorLabel->setText("Welcome " + username + ",");
        //             ui->errorLabel->setVisible(true);
        //         }
        //         else
        //         {
        //             ui->errorLabel->setText("Incorrect password");
        //             ui->errorLabel->setVisible(true);
        //         }
        //     }
        // }
        // if (flag)
        // {
        //     ui->errorLabel->setText("User not found");
        //     ui->errorLabel->setVisible(true);
        // }
    
        // now, connect to the server with base url https://gta-vi-backend1.onrender.com
        // and send a post request to /signin with username and password as json
        // if the response is 200, then the user is signed in
        // if the response is 401, then the user is not signed in

        // start coding the QT networking code here
        // use the following code to send a post request
        ui->errorLabel->setText("Loading...");
        ui->errorLabel->setVisible(true);

        QNetworkAccessManager *manager = new QNetworkAccessManager(this);
        QNetworkRequest request;
        request.setUrl(QUrl("https://gta-vi-backend1.onrender.com/signin"));
        request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");
        QJsonObject json;
        json["username"] = username;
        json["password"] = password;
        QJsonDocument doc(json);
        QByteArray bytes = doc.toJson();
        QNetworkReply *reply = manager->post(request, bytes);
        connect(reply, &QNetworkReply::finished, this, [=]() {
            qDebug() << reply->error();
            // get status code
            int status_code = reply->attribute(QNetworkRequest::HttpStatusCodeAttribute).toInt();
            if (reply->error() == QNetworkReply::NoError && status_code == 200)
            {
                // the user is signed in
                ui->OnlineButton->setVisible(true);
                ui->marketButton->setVisible(true);
                ui->pushButton->setVisible(true);
                ui->errorLabel->setText("Welcome " + username + ",");
                ui->errorLabel->setVisible(true);

                // take the JWT token from the response and store it in a variable
                // so that you can use it in the online game manager
                // you can use the following code to get the JWT token
                QByteArray response_data = reply->readAll();
                QJsonDocument json_doc = QJsonDocument::fromJson(response_data);
                QJsonObject json_obj = json_doc.object();
                QString jwt_token = json_obj["token"].toString();
                qDebug() << jwt_token;
                this->token = jwt_token;
                this->username = username;
            }
            else if (status_code == 401 || status_code == 400) {
                ui->errorLabel->setText("Incorrect credentials");
                ui->errorLabel->setVisible(true);
            }
            else
            {
                ui->errorLabel->setText("Network error occured");
                ui->errorLabel->setVisible(true);
            }
        });

        // print loading message in errorLabel

        // end of networking code
    }
    ui->user->setText("");
    ui->pass->setText("");
}
