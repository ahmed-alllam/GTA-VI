#include "payment_info.h"
#include "ui_payment_info.h"
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

payment_info::payment_info(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::payment_info)
{
    ui->setupUi(this);
    ui->warning->setText("");
}

payment_info::~payment_info()
{
    delete ui;
}

void payment_info::on_pay_clicked()
{
    qDebug() << ui->card_numb->text();
    if(((ui->CVV)->text()).toInt()<100 ||((ui->CVV)->text()).toInt()>999 )
       ui->warning->setText("not valid CVV");
    else if(((ui->card_numb)->text()).toLongLong()<1000000000000000 ||((ui->card_numb)->text()).toLongLong()>9999999999999999 )
         ui->warning->setText("not valid card number");
     else
     {
          ui->warning->setText("payment done");
          // close the window
            this->close();
     }

}


void payment_info::on_cancel_clicked()
{
    this->close();
}

