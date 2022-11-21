#include "mainwindow.h"

#include <QApplication>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QFile>
#include <QTextStream>
#include <QGraphicsPixmapItem>
#include "gamemanager.h"
#include <QDir>
#include <QTimer>
#include <QDebug>
#include <QApplication>
#include <QGuiApplication>
//#include <QAudioFormat>
//#include <QMediaPlayer>
//#include <QAudioOutput>


int main(int argc, char *argv[])
{
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

    GameManager gameManager(scene);

    view.setScene(scene);

    view.show();
    return a.exec();
}

