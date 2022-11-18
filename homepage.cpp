#include "homepage.h"
#include "ui_homepage.h"
#include <QObject>

homepage::homepage(GameManager *gameManager, QGraphicsScene *scene)
{
    ui = new Ui::homepage;
    ui->setupUi(this);

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
