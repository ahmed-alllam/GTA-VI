#include "mainwindow.h"
#include "ui_mainwindow.h"
#include"bomb.h"
#include"powerful_bullet.h"
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    
    ui->setupUi(this);
   ui->label->setText("300");

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
    qDebug()<<"status: "<<bomb::is_available();
    bomb::make_available();
    qDebug()<<"status: "<<bomb::is_available();

}


void MainWindow::on_Buy_powerfulbullet_clicked()
{
    qDebug()<<"status: "<<powerful_bullet::is_available();
    powerful_bullet::make_available();
    qDebug()<<"status: "<<powerful_bullet::is_available();
}

