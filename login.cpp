#include "login.h"
#include "ui_login.h"
#include <QMessageBox>
#include <menu.h>
login::login(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::login)
{
    ui->setupUi(this);
}

void login::on_pushButton_2_clicked()
{}

login::~login()
{
    delete ui;
}

//Login Database Connection

bool login::login_conn(){
    mydb=QSqlDatabase::addDatabase("QSQLITE");
    mydb.setDatabaseName("F:/project/final/finalfinalproject/logindata.db");
    if(mydb.open()){
        return true;
    }
    else{
        return false;
    }
}

//Login Database Disconnect

void login::login_disconn(){
    mydb.close();
    mydb.removeDatabase(QSqlDatabase::defaultConnection);
}

//Login Push Button

void login::on_login_push_clicked()
{
    if(ui->login_userid->text()==NULL || ui->login_password->text()==NULL){
        QMessageBox::warning(this,"Login Error","Please Enter All The Data");
    }
    else{
        login::login_conn();
        QSqlQuery query;
        QString username=ui->login_userid->text();
        QString password=ui->login_password->text();
        query.prepare("SELECT * FROM login WHERE username='"+username+"' and password='"+password+"'");
        query.exec();
        if(query.next()){
            menu *win=new menu;
            this->hide();
            win->show();
        }
        else{
            QMessageBox::information(this,"Login","Wrong ID/Passowrd");
        }
        login::login_disconn();
    }
}

void login::on_login_userid_returnPressed()
{
    login::on_login_push_clicked();
}

void login::on_login_password_returnPressed()
{
    login::on_login_push_clicked();
}
