#ifndef HOMEPAGE_H
#define HOMEPAGE_H

#include <QMainWindow>
#include "gamemanager.h"
#include <QGraphicsScene.h>
#include <QGraphicsView>

namespace Ui {
class homepage;
}

class homepage : public QMainWindow
{
    Q_OBJECT
private:
    GameManager *gameManager;


public:
    explicit homepage(GameManager *gameManager, QGraphicsScene *scene);
    ~homepage();

private slots:
     void exit();

private:
    Ui::homepage *ui;
};

#endif // HOMEPAGE_H
