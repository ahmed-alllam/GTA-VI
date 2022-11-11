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

    // qDebug() << "here"; // You can use this for tracing

    view.setFixedSize(600, 600);
    view.setWindowTitle("Maze Game");
    QBrush brush(Qt::black);
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

    QPixmap grassImage(":Grass.png");

    grassImage = grassImage.scaledToWidth(50);
    grassImage = grassImage.scaledToHeight(50);

    QPixmap bricksImage(":Bricks.png");
    bricksImage = bricksImage.scaledToWidth(50);
    bricksImage = bricksImage.scaledToHeight(50);

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
            boardItems[i][j].setPos(50 + j * 50, 50 + i * 50);

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
