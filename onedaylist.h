#ifndef ONEDAYLIST_H
#define ONEDAYLIST_H

#include <QWidget>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QSqlQueryModel>

namespace Ui {
class onedaylist;
}

class onedaylist : public QWidget
{
    Q_OBJECT

public:
    explicit onedaylist(QWidget *parent = 0);
    ~onedaylist();
    void setdata(QString);
    bool conn();
    void disconn();
    void getstatement();
    void today_acc_open();
    void today_acc_holder_detail();
private slots:
    void on_onedaylist_back_clicked();

private:
    Ui::onedaylist *ui;
    QSqlDatabase mydb;
};

#endif // ONEDAYLIST_H
