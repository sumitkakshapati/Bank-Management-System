#ifndef MULTIPLEENTRY_H
#define MULTIPLEENTRY_H

#include <QWidget>
#include <enquiry.h>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QSqlQueryModel>

namespace Ui {
class multipleentry;
}

class multipleentry : public QWidget
{
    Q_OBJECT

public:
    explicit multipleentry(QWidget *parent = 0);
    ~multipleentry();
    bool conn();
    void disconn();
    void getfromdata();
    void gettodata();
    bool checknull();
    bool checklimit(QString,QString);
    void resetdata();
    bool writestatement();

private slots:
    void on_multipleentry_acc_no_from_returnPressed();

    void on_multipleentry_to_returnPressed();

    void on_multipleentry_acc_no_from_textChanged(const QString &arg1);

    void on_multipleentry_acc_no_to_textChanged(const QString &arg1);

    void on_multipleentry_back_clicked();

    void on_multipleentry_acc_no_to_returnPressed();

    void on_multipleentry_deposit_clicked();

private:
    Ui::multipleentry *ui;
    enquiry obj;
    QSqlDatabase mydb;
};

#endif // MULTIPLEENTRY_H
