#include "password.h"
#include "ui_password.h"
#include "menu.h"
#include <QMessageBox>
#include <QDate>
#include <QTime>
void Password::setdata(QString title,QString button_name){
    setWindowTitle(title);
    ui->password_push->setText(button_name);
}

void Password::cleardata(){
    ui->password_name->clear();
    ui->password_address->clear();
    ui->password_pass->clear();
    ui->password_name->setReadOnly(true);
    ui->password_address->setReadOnly(true);
    ui->password_pass->setDisabled(true);
    ui->password_push->setDisabled(true);
}

Password::Password(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Password)
{
    ui->setupUi(this);
    Password::cleardata();
}

Password::~Password()
{
    delete ui;
}

//DataBase Connection

bool Password::conn(){
    mydb=QSqlDatabase::addDatabase("QSQLITE");
    mydb.setDatabaseName("F:/project/final/finalfinalproject/accountdata.db");
    if(mydb.open()){
        return true;
    }
    else{
        return false;
    }
}

//DataBase Disconnect

void Password::disconn(){
    mydb.close();
    mydb.removeDatabase(QSqlDatabase::defaultConnection);
}


void Password::on_password_back_clicked()
{
    menu *win=new menu;
    this->hide();
    win->show();
}

void Password::on_password_account_no_returnPressed()
{
    QString acc_no=ui->password_account_no->text();
    Password::conn();
    QSqlQuery query;
    QString name,address,pass;
    bool flag=false;
    query.prepare("SELECT [Name],[Address],[Password] FROM account WHERE [Account No]='"+acc_no+"' AND [Status]='"+QString::number(true)+"'");
    query.exec();
    while(query.next()){
        flag=true;
        name=query.value(0).toString();
        address=query.value(1).toString();
        pass=query.value(2).toString();
    }
    if(flag==true){
        ui->password_name->setText(name);
        ui->password_address->setText(address);
        ui->password_pass->setEnabled(true);
        ui->password_pass->setText(pass);
        ui->password_push->setEnabled(true);
    }
    else{
       Password::cleardata();
    }
    Password::disconn();
}

void Password::on_password_push_clicked()
{
    if(ui->password_pass->text()!=NULL){
        QString pass=ui->password_pass->text();
        Password::conn();
        QSqlQuery query;
        if(ui->password_push->text()=="Set Password"){
            query.prepare("UPDATE account SET [Password]='"+pass+"' WHERE [Account No]='"+ui->password_account_no->text()+"'");
            if(query.exec()){
                QMessageBox::information(this," ","Password Updated");
                Password::cleardata();
                ui->password_account_no->clear();
            }
            else{
                QMessageBox::information(this,"Password",query.lastError().text());
            }
        }
        else{
            query.prepare("UPDATE account SET [Status]='"+QString::number(false)+"',[Account Expired]=:ae,[Account Expired Time]=:aet WHERE [Account No]='"+ui->password_account_no->text()+"'");
            query.bindValue(":ae",QDate::currentDate());
            query.bindValue(":aet",QTime::currentTime());
            if(query.exec()){
                QMessageBox::information(this," ","Account Deactivated");
                Password::cleardata();
                ui->password_account_no->clear();
            }
            else{
                QMessageBox::information(this,"Password",query.lastError().text());
            }
        }

        Password::disconn();
    }
    else{
        QMessageBox::warning(this,"Password","Please Enter Password!!");
    }
}

void Password::on_password_account_no_textChanged(const QString &arg1)
{
    Password::cleardata();
}
