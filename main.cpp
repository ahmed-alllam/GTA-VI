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


<<<<<<< HEAD
    view.setWindowState(Qt::WindowMaximized);
    view.fitInView(scene.sceneRect(), Qt::IgnoreAspectRatio);
    view.setWindowTitle("GTA VI");
    view.setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    view.setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    QBrush brush(Qt::gray);
=======
    view.setFixedSize(600, 600);
    view.setWindowTitle("GTA VI");
    QBrush brush(Qt::black);
>>>>>>> db2464d960dfcc25d0c23926b84a62c8237bfd65
    view.setBackgroundBrush(brush);

    QFile file(":Maze.txt");
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

<<<<<<< HEAD
    QPixmap bricksImage(":assets/images/gees-def_still_2x.png");
    bricksImage = bricksImage.scaledToWidth(unitWidth);
    bricksImage = bricksImage.scaledToHeight(unitHeight);
=======
    QPixmap brick1Image(":assets/images/car up.png");
    brick1Image = brick1Image.scaledToWidth(50);
    brick1Image = brick1Image.scaledToHeight(50);

    QPixmap brick2Image(":assets/images/car left.png");
    brick2Image = brick2Image.scaledToWidth(50);
    brick2Image = brick2Image.scaledToHeight(50);

    QPixmap brick3Image(":assets/images/car bottom.png");
    brick3Image = brick3Image.scaledToWidth(50);
    brick3Image = brick3Image.scaledToHeight(50);

    QPixmap brick4Image(":assets/images/car right.png");
    brick4Image = brick4Image.scaledToWidth(50);
    brick4Image = brick4Image.scaledToHeight(50);

    QPixmap brick5Image(":assets/images/Tree.png");
    brick5Image = brick5Image.scaledToWidth(50);
    brick5Image = brick5Image.scaledToHeight(50);

    QPixmap brick6Image(":assets/images/house.png");
    brick6Image = brick6Image.scaledToWidth(50);
    brick6Image = brick6Image.scaledToHeight(50);

    QPixmap homeImage(":assets/images/Home.png");
    homeImage = homeImage.scaledToWidth(50);
    homeImage = homeImage.scaledToHeight(50);

    QPixmap arrowImage(":assets/images/arrow.png");
    arrowImage = arrowImage.scaledToWidth(50);
    arrowImage = arrowImage.scaledToHeight(50);
>>>>>>> db2464d960dfcc25d0c23926b84a62c8237bfd65

    QGraphicsPixmapItem boardItems[10][10];
    for (int i = 0; i < 10; i++)
        for (int j = 0; j < 10; j++)
        {
            // Set Image
            if (boardData[i][j] == -1)
                boardItems[i][j].setPixmap(brick1Image);
            else if (boardData[i][j] == -2)
                boardItems[i][j].setPixmap(brick2Image);
            else if (boardData[i][j] == -3)
                boardItems[i][j].setPixmap(brick3Image);
            else if (boardData[i][j] == -4)
                boardItems[i][j].setPixmap(brick4Image);
            else if (boardData[i][j] == -5)
                boardItems[i][j].setPixmap(brick5Image);
            else if (boardData[i][j] == -6)
                boardItems[i][j].setPixmap(brick6Image);
            else if (boardData[i][j] == 20)
                boardItems[i][j].setPixmap(homeImage);
            else if (boardData[i][j] == 43)
                boardItems[i][j].setPixmap(arrowImage);
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
