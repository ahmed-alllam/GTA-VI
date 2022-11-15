#include "mainwindow.h"

#include <QApplication>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QFile>
#include <QTextStream>
#include <QGraphicsPixmapItem>
#include "franklin.h"
#include "enemy1.h""
#include <QDir>
#include <QTimer>
#include <QDebug>
#include <QApplication>
#include <QGuiApplication>


Franklin * franklinMain = nullptr;
enemy1 * enemy11Main = nullptr;

void focus_player()
{
    if(franklinMain != nullptr) {
        franklinMain->focus_player();
    }
}

void enemy1_move()
{
    if(enemy11Main != nullptr) {
        enemy11Main->move();
    }
}

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

    view.setFixedSize(1920, 1080);

    QBrush brush(Qt::gray);

    view.setBackgroundBrush(brush);

    QFile file(":Maze.txt");
    file.open(QIODevice::ReadOnly);
    QTextStream stream(&file);
    int boardData[12][16];
    QString temp;
    for (int i = 0; i < 12; i++)
        for (int j = 0; j < 16; j++)
        {
            stream >> temp;
            boardData[i][j] = temp.toInt();
        }

    // calculate the size of the the unit square depending on the size of the window
    int screenWidth = QGuiApplication::primaryScreen()->availableSize().width();
    int screenHeight = QGuiApplication::primaryScreen()->availableSize().height();
    int unitWidth = qMin(screenWidth, screenHeight) / 12;
    int unitHeight = qMin(screenWidth, screenHeight) / 12;

    QPixmap blankImage(":assets/images/blank.png");

    blankImage = blankImage.scaledToWidth(unitWidth);
    blankImage = blankImage.scaledToHeight(unitHeight);

    QPixmap brick1Image(":assets/images/car up.png");
    brick1Image = brick1Image.scaledToWidth(unitWidth);
    brick1Image = brick1Image.scaledToHeight(unitWidth);

    QPixmap brick2Image(":assets/images/water.png");
    brick2Image = brick2Image.scaledToWidth(unitWidth);
    brick2Image = brick2Image.scaledToHeight(unitWidth);

    QPixmap brick3Image(":assets/images/car bottom.png");
    brick3Image = brick3Image.scaledToWidth(unitWidth);
    brick3Image = brick3Image.scaledToHeight(unitWidth);

    QPixmap brick4Image(":assets/images/car right.png");
    brick4Image = brick4Image.scaledToWidth(unitWidth);
    brick4Image = brick4Image.scaledToHeight(unitWidth);

    QPixmap brick5Image(":assets/images/Tree.png");
    brick5Image = brick5Image.scaledToWidth(unitWidth);
    brick5Image = brick5Image.scaledToHeight(unitWidth);

    QPixmap brick6Image(":assets/images/house.png");
    brick6Image = brick6Image.scaledToWidth(unitWidth);
    brick6Image = brick6Image.scaledToHeight(unitWidth);

    QPixmap brick7Image(":assets/images/Bodygard.png");
    brick7Image = brick7Image.scaledToWidth(unitWidth);
    brick7Image = brick7Image.scaledToHeight(unitWidth);

    QPixmap homeImage(":assets/images/Home.png");
    homeImage = homeImage.scaledToWidth(unitWidth);
    homeImage = homeImage.scaledToHeight(unitWidth);

    QPixmap arrowImage(":assets/images/arrow.png");
    arrowImage = arrowImage.scaledToWidth(unitWidth);
    arrowImage = arrowImage.scaledToHeight(unitWidth);

    QPixmap VertRoadImage(":assets/images/vert.png"); // aadded for test
    VertRoadImage = VertRoadImage.scaledToWidth(unitWidth);
    VertRoadImage = VertRoadImage.scaledToHeight(unitWidth);

    QPixmap HorRoadImage(":assets/images/horz.png"); // aadded for test
    HorRoadImage = HorRoadImage.scaledToWidth(unitWidth);
    HorRoadImage = HorRoadImage.scaledToHeight(unitWidth);

    QPixmap toleft_RoadImage(":assets/images/2left.png"); // aadded
    toleft_RoadImage = toleft_RoadImage.scaledToWidth(unitWidth);
    toleft_RoadImage = toleft_RoadImage.scaledToHeight(unitWidth);

    QPixmap toright_RoadImage(":assets/images/2right.png"); // aadded
    toright_RoadImage = toright_RoadImage.scaledToWidth(unitWidth);
    toright_RoadImage = toright_RoadImage.scaledToHeight(unitWidth);

    QPixmap toleft_RoadImage2(":assets/images/2left2.png"); // aadded
    toleft_RoadImage2 = toleft_RoadImage2.scaledToWidth(unitWidth);
    toleft_RoadImage2 = toleft_RoadImage2.scaledToHeight(unitWidth);

    QPixmap toright_RoadImage2(":assets/images/2right2.png"); // aadded
    toright_RoadImage2 = toright_RoadImage2.scaledToWidth(unitWidth);
    toright_RoadImage2 = toright_RoadImage2.scaledToHeight(unitWidth);

    QPixmap TUImage(":assets/images/T Up.png"); // aadded
    TUImage = TUImage.scaledToWidth(unitWidth);
    TUImage = TUImage.scaledToHeight(unitWidth);

    QPixmap TDImage(":assets/images/T Down.png"); // aadded
    TDImage = TDImage.scaledToWidth(unitWidth);
    TDImage = TDImage.scaledToHeight(unitWidth);

    QPixmap TLImage(":assets/images/T Left.png"); // aadded
    TLImage = TLImage.scaledToWidth(unitWidth);
    TLImage = TLImage.scaledToHeight(unitWidth);

    QPixmap TRImage(":assets/images/T Right.png"); // aadded
    TRImage = TRImage.scaledToWidth(unitWidth);
    TRImage = TRImage.scaledToHeight(unitWidth);

    QPixmap CrossImage(":assets/images/cross road.png"); // aadded
    CrossImage = CrossImage.scaledToWidth(unitWidth);
    CrossImage = CrossImage.scaledToHeight(unitWidth);

    QGraphicsPixmapItem boardItems[12][16];
    for (int i = 0; i < 12; i++)
        for (int j = 0; j < 16; j++)
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
            else if (boardData[i][j] == -7)
                boardItems[i][j].setPixmap(brick7Image);
            else if (boardData[i][j] == 20)
                boardItems[i][j].setPixmap(homeImage);
            else if (boardData[i][j] == 50)
                boardItems[i][j].setPixmap(arrowImage);
            else if (boardData[i][j] == 4)
                boardItems[i][j].setPixmap(VertRoadImage);
            else if (boardData[i][j] == 2)
                boardItems[i][j].setPixmap(HorRoadImage);
            else if (boardData[i][j] == 7)
                boardItems[i][j].setPixmap(toright_RoadImage);
            else if (boardData[i][j] == 8)
                boardItems[i][j].setPixmap(toright_RoadImage2);
            else if (boardData[i][j] == 9)
                boardItems[i][j].setPixmap(toleft_RoadImage);
            else if (boardData[i][j] == 3)
                boardItems[i][j].setPixmap(toleft_RoadImage2);
            else if (boardData[i][j] == 13)
                boardItems[i][j].setPixmap(TRImage);
            else if (boardData[i][j] == 14)
                boardItems[i][j].setPixmap(TLImage);
            else if (boardData[i][j] == 12)
                boardItems[i][j].setPixmap(TDImage);
            else if (boardData[i][j] == 11)
                boardItems[i][j].setPixmap(TUImage);
            else if (boardData[i][j] == 15)
                boardItems[i][j].setPixmap(CrossImage);
            else
                boardItems[i][j].setPixmap(blankImage);

            // Set Position
            boardItems[i][j].setPos(unitWidth + j * unitWidth, unitHeight + i * unitHeight);

            // Add to the Scene
            scene.addItem(&boardItems[i][j]);
        }

    Franklin franklin(boardData);
    scene.addItem(&franklin);
    franklinMain = &franklin;

    enemy1 enemy11(boardData);
    scene.addItem(&enemy11);
    enemy11Main = &enemy11;

    QTimer* timer = new QTimer();
    QObject::connect(timer, &QTimer::timeout, focus_player);
    timer->start(350);
    
    QTimer* timer2 = new QTimer();
    QObject::connect(timer2, &QTimer::timeout, enemy1_move);
    timer2->start(800);


    view.setScene(&scene);
    view.show();
    return a.exec();
}

