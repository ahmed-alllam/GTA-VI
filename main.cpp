#include "mainwindow.h"
#include <QApplication>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QFile>
#include <QTextStream>
#include <QGraphicsPixmapItem>
#include "homepage.h"
#include <QDir>
#include <QTimer>
#include <QDebug>
#include <QApplication>
#include <QGuiApplication>


int main(int argc, char *argv[])
{
    try {

    QApplication a(argc, argv);
    QGraphicsView view;
    QGraphicsScene *scene = new QGraphicsScene();

    view.setWindowState(Qt::WindowMaximized);
    view.fitInView(scene->sceneRect(), Qt::IgnoreAspectRatio);
    view.setWindowTitle("GTA VI");
    view.setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    view.setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    view.setFixedSize(1920, 1080);

    QBrush brush(QColor(0x335f3f));
    view.setBackgroundBrush(brush);


    homepage *home = new homepage(scene);
    scene->addWidget(home);

    view.setScene(scene);

    view.show();
    a.exec();

    } catch (std::exception &e) {
        qDebug() << e.what();
    }
    return 0;
}

