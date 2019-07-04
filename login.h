#ifndef LOGIN_H
#define LOGIN_H

#include <QWidget>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
namespace Ui {
class login;
}

class login : public QWidget
{
    Q_OBJECT

public:
    explicit login(QWidget *parent = 0);
    ~login();
    bool login_conn();
    void login_disconn();

private slots:
    void on_pushButton_2_clicked();

    void on_login_push_clicked();

    void on_login_userid_returnPressed();

    void on_login_password_returnPressed();

private:
    Ui::login *ui;
    QSqlDatabase mydb;
};

#endif // LOGIN_H
