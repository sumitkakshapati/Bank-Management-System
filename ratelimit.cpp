#include "ratelimit.h"
#include "ui_ratelimit.h"
#include <QMessageBox>
#include "menu.h"

//Reset Rate/Limit Data

void ratelimit::resetdata(){
    ui->rate_acc_no->clear();
    ui->rate_name->clear();
    ui->rate_address->clear();
    ui->rate_rate->clear();
    ui->rate_limit->clear();
    ui->rate_push->setDisabled(true);
    ui->rate_name->setReadOnly(true);
    ui->rate_address->setReadOnly(true);
    ui->rate_limit->setReadOnly(true);
    ui->rate_rate->setReadOnly(true);
}

ratelimit::ratelimit(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ratelimit)
{
    ui->setupUi(this);
    ratelimit::resetdata();
}

ratelimit::~ratelimit()
{
    delete ui;
}


//DataBase Connection

bool ratelimit::conn(){
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

void ratelimit::disconn(){
    mydb.close();
    mydb.removeDatabase(QSqlDatabase::defaultConnection);
}

void ratelimit::on_rate_acc_no_returnPressed()
{
    if(obj.checkacc_no(ui->rate_acc_no->text())){
        ratelimit::conn();
        QSqlQuery query;
        QString name,address,rate,limit;
        query.prepare("SELECT [Name],[Address],[Rate],[Limit] FROM account WHERE [Account No]='"+ui->rate_acc_no->text()+"'");
        query.exec();
        while(query.next()){
            name=query.value(0).toString();
            address=query.value(1).toString();
            rate=query.value(2).toString();
            limit=query.value(3).toString();
        }
        ui->rate_name->setText(name);
        ui->rate_address->setText(address);
        ui->rate_rate->setText(rate);
        ui->rate_limit->setText(limit);
        ui->rate_rate->setReadOnly(false);
        ui->rate_limit->setReadOnly(false);
        ui->rate_push->setEnabled(true);
    }
    else{
        QMessageBox::warning(this,"Rate/Limit Error","No Account Found");
        ratelimit::resetdata();

    }
}

void ratelimit::on_rate_push_clicked()
{
    ratelimit::conn();
    QSqlQuery query;
    query.prepare("UPDATE account SET [Rate]=:r , [Limit]=:l WHERE [Account No]=:acc");
    query.bindValue(":acc",ui->rate_acc_no->text());
    query.bindValue(":r",ui->rate_rate->text());
    query.bindValue(":l",ui->rate_limit->text());
    if(query.exec()){
        QMessageBox::information(this," ","Rate/Limit Updated");
        ratelimit::resetdata();
    }
    else{
        QMessageBox::information(this,"Password",query.lastError().text());
    }
}

void ratelimit::on_rate_back_clicked()
{
    menu *win=new menu;
    this->hide();
    win->show();
}
