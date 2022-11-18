#include "homepage.h"
#include "ui_homepage.h"
#include <QObject>

homepage::homepage(GameManager *gameManager, QGraphicsScene *scene)
{
    ui = new Ui::homepage;
    ui->setupUi(this);
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
