#include "log_in.h"
#include "ui_log_in.h"
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


Log_in::Log_in(QWidget *parent) : QDialog(parent),
                                  ui(new Ui::Log_in)
{
    ui->setupUi(this);
    ui->pass->setEchoMode(QLineEdit::Password);
}

Log_in::~Log_in()
{
    delete ui;
}

void Log_in::on_Log_clicked()
{
    ui->errorLabel->setVisible(false);
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
        // now we need to send request to server to sign up the user
        // and then we need to receive the response from server
        // and then we need to check if the response is 200
        // base url: https://gta-vi-backend1.onrender.com
        // post request: /signup

        QNetworkAccessManager *manager = new QNetworkAccessManager(this);
        QNetworkRequest request;
        request.setUrl(QUrl("https://gta-vi-backend1.onrender.com/signup"));
        request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");

        QJsonObject json;
        json["username"] = username;
        json["password"] = password;

        QJsonDocument doc(json);
        QByteArray data = doc.toJson();

        QNetworkReply *reply = manager->post(request, data);

        // now we need to connect the reply to a function
        // so that we can receive the response from server
        // and then we can check if the response is 200

        ui->errorLabel->setText("Loading...");
        ui->errorLabel->setVisible(true);

        connect(reply, &QNetworkReply::finished, [=]() {
            int status = reply->attribute(QNetworkRequest::HttpStatusCodeAttribute).toInt();

            if (reply->error() || status != 201)
            {
                ui->errorLabel->setVisible(true);

                if(status == 409) {
                    ui->errorLabel->setText("User already exists");
                } else {
                    ui->errorLabel->setText("Network error");
                }
            }
            else
            {
                ui->errorLabel->setText("User created successfully");
                ui->errorLabel->setVisible(true);
            }
        });
    }

    ui->user->setText("");
    ui->pass->setText("");
}
