#include "onlinegamemanager.h"

#include <QGraphicsScene>
#include <QPushButton>
#include <QGraphicsRectItem>
#include <QGuiApplication>
#include <QGraphicsTextItem>
#include <QObject>
#include <QtUiTools>

OnlineGameManager::OnlineGameManager(QGraphicsScene *scene)
{
    this->scene = scene;
    create_game_id_panel();
}

void OnlineGameManager::create_game_id_panel() {
    QFile file(":/forms/onlinegameid.ui");
    file.open(QIODevice::ReadOnly);

    QUiLoader loader;
    scene->addWidget(loader.load(&file, nullptr));
}

