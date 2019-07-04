#ifndef DEPOSIT_H
#define DEPOSIT_H

#include <QWidget>
#include "enquiry.h"
#include "account.h"
#include <multipleentry.h>
namespace Ui {
class deposit;
}

class deposit : public QWidget
{
    Q_OBJECT

public:
    explicit deposit(QWidget *parent = 0);
    ~deposit();
    void setdata(QString,QString);
    void getdetail(QString);
    bool conn();
    void disconn();
    bool check_null();
    single_entry_data getdata();
    bool save_depo_statement(single_entry_data);
    bool save_with_statement(single_entry_data);
    bool update_account(single_entry_data);
    void cleardetail();
    void resetdata();


private slots:
    void on_deposit_acc_no_returnPressed();

    void on_deposit_acc_no_editingFinished();

    void on_deposit_cancel_clicked();

    void on_deposit_push_clicked();

    void on_deposit_acc_no_textChanged(const QString &arg1);

private:
    Ui::deposit *ui;
    enquiry obj;
    QSqlDatabase mydb;
    multipleentry obj2;
};

#endif // DEPOSIT_H
