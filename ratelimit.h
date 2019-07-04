#ifndef RATELIMIT_H
#define RATELIMIT_H

#include <QWidget>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QSqlQueryModel>
#include "enquiry.h"

namespace Ui {
class ratelimit;
}

class ratelimit : public QWidget
{
    Q_OBJECT

public:
    explicit ratelimit(QWidget *parent = 0);
    ~ratelimit();
    bool conn();
    void disconn();
    void resetdata();

private slots:
    void on_rate_acc_no_returnPressed();

    void on_rate_push_clicked();

    void on_rate_back_clicked();

private:
    Ui::ratelimit *ui;
    enquiry obj;
    QSqlDatabase mydb;
};

#endif // RATELIMIT_H
