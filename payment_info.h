#ifndef PAYMENT_INFO_H
#define PAYMENT_INFO_H

#include <QDialog>

namespace Ui {
class payment_info;
}

class payment_info : public QDialog
{
    Q_OBJECT

public:
    explicit payment_info(QWidget *parent = nullptr);
    ~payment_info();

private slots:
    void on_pay_clicked();

    void on_cancel_clicked();

private:
    Ui::payment_info *ui;
};

#endif // PAYMENT_INFO_H
