#ifndef ENQUIRY_H
#define ENQUIRY_H

#include <QWidget>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QSqlQueryModel>
namespace Ui {
class enquiry;
}

class enquiry : public QWidget
{
    Q_OBJECT

public:
    explicit enquiry(QWidget *parent = 0);
    ~enquiry();
    bool conn();
    void disconn();
    bool checkacc_no(QString);
    bool checkname(QString);

private slots:
    void on_enquiry_back_clicked();

    void on_enquiry_search_clicked();

    void on_enquiry_maintenance_clicked();

    void on_enquiry_statement_clicked();

private:
    Ui::enquiry *ui;
    QSqlDatabase mydb;
};

#endif // ENQUIRY_H
