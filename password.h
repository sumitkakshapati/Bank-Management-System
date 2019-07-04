#ifndef PASSWORD_H
#define PASSWORD_H

#include <QWidget>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>

namespace Ui {
class Password;
}

class Password : public QWidget
{
    Q_OBJECT

public:
    explicit Password(QWidget *parent = 0);
    ~Password();
    void setdata(QString,QString);
    bool conn();
    void disconn();
    void cleardata();

private slots:
    void on_password_back_clicked();

    void on_password_account_no_returnPressed();

    void on_password_push_clicked();

    void on_password_account_no_textChanged(const QString &arg1);

private:
    Ui::Password *ui;
    QSqlDatabase mydb;
};

#endif // PASSWORD_H
