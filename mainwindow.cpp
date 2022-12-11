#include "mainwindow.h"
#include "ui_mainwindow.h"
#include"bomb.h"
#include"powerful_bullet.h"
#include"extra_life.h"
#include "payment_info.h"
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    this->setWindowFlags(Qt::FramelessWindowHint);
    //set window background color to transparent
    this-> setAttribute(Qt::WA_TranslucentBackground);

    ui->setupUi(this);
   ui->label->setText("1500");
   coins = 1500;
   ui->label_2->setVisible(false);

    ui->ExitButton->setIcon( QIcon(":/assets/images/button.png"));
    ui->ExitButton->setIconSize(QSize(65, 65));

    ui->bomb_label->setPixmap( QPixmap(":/assets/images/time-bomb.png"));
    ui->bomb_label->setScaledContents(true);

    ui->pwerfulbullet_label->setPixmap(QPixmap(":/assets/images/powerfull-bulletsU.png"));
    ui->pwerfulbullet_label->setScaledContents(true);

    ui->coins_image->setPixmap( QPixmap(":/assets/images/coins.png"));
    ui->coins_image->setScaledContents(true);

    ui->health_image->setPixmap( QPixmap(":/assets/images/extra-health.png"));

    ui->health_image->setScaledContents(true);
    ui->drink_image->setPixmap( QPixmap(":/assets/images/energy-drink.png"));

    ui->drink_image->setScaledContents(true);
    ui->drink_image->setPixmap( QPixmap(":/assets/images/energy-drink.png"));

    ui->drink_image->setScaledContents(true);

    ui->coins_image1->setPixmap( QPixmap(":/assets/images/coins.png"));
    ui->coins_image1->setScaledContents(true);

   }

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_ExitButton_clicked()
{
    this->close();
}


void MainWindow::on_Buy_bomb_clicked()
{
    if(coins >= 500)
    {
        bomb::make_available();
        ui->label_2->setVisible(false);
        coins -= 500;
        ui->label->setText(QString::number(coins));
    }
    else
    {
        ui->label_2->setVisible(true);
    }
}


void MainWindow::on_Buy_powerfulbullet_clicked()
{
    if(coins >= 400)
    {
    powerful_bullet::make_available();
    ui->label_2->setVisible(false);
    coins -= 400;
    ui->label->setText(QString::number(coins));
    }
    else
    {
        ui->label_2->setVisible(true);
    }
}


void MainWindow::on_Buy_health_clicked()
{
    if(coins >= 500)
    {
        extra_life::make_available();
        coins -= 500;
        ui->label_2->setVisible(false);
        ui->label->setText(QString::number(coins));
    }
    else
    {
        ui->label_2->setVisible(true);
    }
}


void MainWindow::on_Buy_bomb_3_clicked()
{
    payment_info dialog(this);
    dialog.setModal(true);
    dialog.exec();
    coins += 500;
    ui->label->setText(QString::number(coins));
    ui->label_2->setVisible(false);
}

