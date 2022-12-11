#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_ExitButton_clicked();
    void on_Buy_bomb_clicked();

    void on_Buy_powerfulbullet_clicked();

    void on_Buy_health_clicked();

    void on_Buy_bomb_3_clicked();

private:
    Ui::MainWindow *ui;
    int coins;
};
#endif // MAINWINDOW_H
