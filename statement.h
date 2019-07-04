#ifndef STATEMENT_H
#define STATEMENT_H

#include <QWidget>
#include <QMessageBox>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QSqlQueryModel>
#include "enquiry.h"
namespace Ui {
class statement;
}

class statement : public QWidget
{
    Q_OBJECT

public:
    explicit statement(QWidget *parent = 0);
    ~statement();
    bool conn();
    void disconn();
    void resetdata();
    void setstatus(QString,bool);
    void loaddata(QString);

private slots:
    void on_statement_back_clicked();

    void on_statement_acc_no_returnPressed();

    void on_statement_show_clicked();

    void on_statement_acc_no_textChanged(const QString &arg1);

private:
    Ui::statement *ui;
    QSqlDatabase mydb;
    enquiry obj;
};

#endif // STATEMENT_H
