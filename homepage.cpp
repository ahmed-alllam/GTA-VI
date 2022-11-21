#include "homepage.h"
#include "ui_homepage.h"
#include "log_in.h"
#include <QFile>
#include <QObject>
#include <QSaveFile>

homepage::homepage(GameManager *gameManager, QGraphicsScene *scene)
{
    ui = new Ui::homepage;
    ui->setupUi(this);

    QFile acc("Accounts.txt");
    acc.open(QIODevice::ReadOnly);
    QTextStream stream(&acc);
    QString u;
    QString p;
    while(!stream.atEnd())
    {
         stream >> u;
         stream >> p;
         qDebug() << u;
         user.append(u);
         pass.append(p);
    }
    ui->pass->setEchoMode(QLineEdit::Password);
    ui->OnlineButton->setVisible(false);
//    ui->pushButton->setVisible(false);
    ui->errorLabel->setVisible(false);
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



    this->gameManager = gameManager;
    QObject::connect(ui->pushButton, SIGNAL(clicked()), this, SLOT(exit()), Qt::QueuedConnection);
}

homepage::~homepage()
{
    delete ui;
}

void homepage::exit()
{
    if (this->gameManager != nullptr)
        this->gameManager->launch_game();
}

void homepage::on_Log_clicked()
{
    Log_in dialog(this, &user, &pass);
    dialog.setModal(true);
    dialog.exec();
}


void homepage::on_Sign_clicked()
{
    ui->errorLabel->setVisible(false);
    bool flag = true;
    QString username = ui->user->text();
    QString password = ui->pass->text();
    if(username == "")
    {
        ui->errorLabel->setText("Please enter your username");
        ui->errorLabel->setVisible(true);
    }
    else if(password == "")
    {
        ui->errorLabel->setText("Please enter the password");
        ui->errorLabel->setVisible(true);
    }
    else
    {
    for (int i = 0; i < user.length(); i++) {
        if (user[i] == username) {
            flag = false;
            if (pass[i] == password) {
                ui->OnlineButton->setVisible(true);
                ui->pushButton->setVisible(true);
                ui->errorLabel->setText("Welcome " + username + ",");
                ui->errorLabel->setVisible(true);
                } else {
                ui->errorLabel->setText("Incorrect password");
                ui->errorLabel->setVisible(true);
                }
            }
        }
        if (flag)
        {
        ui->errorLabel->setText("User not found");
        ui->errorLabel->setVisible(true);
        }
    }
    ui->user->setText("");
    ui->pass->setText("");
}

