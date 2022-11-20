#ifndef LOG_IN_H
#define LOG_IN_H

#include <QDialog>

namespace Ui {
class Log_in;
}

class Log_in : public QDialog
{
    Q_OBJECT

public:
    explicit Log_in(QWidget *parent = nullptr, QList<QString> *u = nullptr, QList<QString> *p = nullptr);
    ~Log_in();

private slots:
    void on_Log_clicked();

private:
    Ui::Log_in *ui;
    QList<QString> *user;
    QList<QString> *pass;
};

#endif // LOG_IN_H
