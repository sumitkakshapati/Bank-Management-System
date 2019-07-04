#ifndef TWODAYLIST_H
#define TWODAYLIST_H

#include <QWidget>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QSqlQueryModel>

namespace Ui {
class twodaylist;
}

class twodaylist : public QWidget
{
    Q_OBJECT

public:
    explicit twodaylist(QWidget *parent = 0);
    ~twodaylist();
    void getdata(QString);
    bool conn();
    void disconn();
    void get_transaction_list();
    void get_acc_holder_list();

private slots:
    void on_twodaylist_show_clicked();

    void on_twodaylist_back_clicked();

private:
    Ui::twodaylist *ui;
    QSqlDatabase mydb;
};

#endif // TWODAYLIST_H
