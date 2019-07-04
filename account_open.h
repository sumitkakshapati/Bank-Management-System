#ifndef ACCOUNT_OPEN_H
#define ACCOUNT_OPEN_H

#include <QWidget>
#include "account.h"
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <cstdlib>
#include <ctime>
#include <enquiry.h>

namespace Ui {
class account_open;
}

class account_open : public QWidget
{
    Q_OBJECT

public:
    explicit account_open(QWidget *parent = 0);
    ~account_open();
    void setdata(QString, QString, QString, bool);
    bool checknull();
    bool conn();
    void disconn();
    saving_account getsavingdata();
    current_account getcurrentdata();
    bool check_account_no(int);
    int get_account_no();
    double getrate(QString);
    void cleardata();
    void sa_to_database(saving_account);
    void ca_to_database(current_account);
    void setacc_no();
    void setoff();
    void seton();
    saving_account getupdatedata();
    bool updatedata(saving_account);
    void load_data(QString);

private slots:
    void on_ao_back_clicked();

    void on_ao_push_clicked();

    void on_ao_acc_no_returnPressed();

private:
    Ui::account_open *ui;
    QSqlDatabase mydb;
    enquiry obj;
};

#endif // ACCOUNT_OPEN_H
