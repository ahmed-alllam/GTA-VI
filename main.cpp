#include "mainwindow.h"

#include <QApplication>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QFile>
#include <QTextStream>
#include <QGraphicsPixmapItem>
#include "franklin.h"
#include <QDir>
#include <QDebug>
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QGraphicsView view;
    QGraphicsScene scene;


    view.setWindowState(Qt::WindowMaximized);
    view.fitInView(scene.sceneRect(), Qt::IgnoreAspectRatio);
    view.setWindowTitle("GTA VI");
    view.setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    view.setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    QBrush brush(Qt::gray);
    view.setBackgroundBrush(brush);

    QFile file(":Board.txt");
    file.open(QIODevice::ReadOnly);
    QTextStream stream(&file);
    int boardData[10][10];
    QString temp;
    for (int i = 0; i < 10; i++)
        for (int j = 0; j < 10; j++)
        {
            stream >> temp;
            boardData[i][j] = temp.toInt();
        }

    int unitWidth = 100;
    int unitHeight = 100;

    QPixmap grassImage(":assets/images/blank.png");

    grassImage = grassImage.scaledToWidth(unitWidth);
    grassImage = grassImage.scaledToHeight(unitHeight);

    QPixmap bricksImage(":assets/images/gees-def_still_2x.png");
    bricksImage = bricksImage.scaledToWidth(unitWidth);
    bricksImage = bricksImage.scaledToHeight(unitHeight);

    QGraphicsPixmapItem boardItems[10][10];
    for (int i = 0; i < 10; i++)
        for (int j = 0; j < 10; j++)
        {
            // Set Image
            if (boardData[i][j] < 0)
                boardItems[i][j].setPixmap(bricksImage);
            else
                boardItems[i][j].setPixmap(grassImage);

            // Set Position
            boardItems[i][j].setPos(unitWidth + j * unitWidth, unitHeight + i * unitHeight);

            // Add to the Scene
            scene.addItem(&boardItems[i][j]);
        }

    Franklin franklin(boardData);
    scene.addItem(&franklin);

    franklin.setFlag(QGraphicsPixmapItem::ItemIsFocusable);
    franklin.setFocus();

    view.setScene(&scene);
    view.show();
    return a.exec();
}
