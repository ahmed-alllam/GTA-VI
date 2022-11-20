#include "log_in.h"
#include "ui_log_in.h"
#include <QFile>
#include <QObject>
#include <QSaveFile>

Log_in::Log_in(QWidget *parent, QList<QString> *u, QList<QString> *p) :
    QDialog(parent),
    user(u),
    pass(p),
    ui(new Ui::Log_in)
{
    ui->setupUi(this);
    ui->pass->setEchoMode(QLineEdit::Password);
    ui->pass_2->setEchoMode(QLineEdit::Password);
}

Log_in::~Log_in()
{
    delete ui;
}

void Log_in::on_Log_clicked()
{
    ui->errorLabel->setVisible(false);
    bool flag = true;
    QString username = ui->user->text();
    QString password = ui->pass->text();
    QString conf_password = ui->pass_2->text();
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
    else if(conf_password == "")
    {
        ui->errorLabel->setText("Please enter the confirmation for password");
        ui->errorLabel->setVisible(true);
    }
    else
    {
    for (int i = 0; i < user->length(); i++) {
        if (user->at(i) == username) {
            flag = false;
            ui->errorLabel->setText("This user already exist");
            ui->errorLabel->setVisible(true);
        }
    }
    if(flag)
    {
        if (password == conf_password)
        {
        user->append(username);
        pass->append(password);
        QFile acc("Accounts.txt");
        acc.open(QIODevice::WriteOnly);
        QTextStream stream(&acc);
        stream << username << "\n";
        stream << password;
        acc.close();

        ui->errorLabel->setText("This user is added, now you can log in");
        ui->errorLabel->setVisible(true);
        }
        else
        {
            ui->errorLabel->setText("The two passwords does not match");
            ui->errorLabel->setVisible(true);
        }
    }
    }
    ui->user->setText("");
    ui->pass->setText("");
}

