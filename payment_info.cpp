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
}

payment_info::~payment_info()
{
    delete ui;
}

void payment_info::on_pay_clicked()
{
    if(((ui->CVV)->text()).toInt()<100 ||((ui->CVV)->text()).toInt()>999 )
       ui->warning->setText("not valid CVV");


}

