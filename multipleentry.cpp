#include "multipleentry.h"
#include "ui_multipleentry.h"
#include "menu.h"
#include <QMessageBox>
multipleentry::multipleentry(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::multipleentry)
{
    ui->setupUi(this);
    ui->multipleentry_name_from->setReadOnly(true);
    ui->multipleentry_name_to->setReadOnly(true);
    ui->multipleentry_address_from->setReadOnly(true);
    ui->multipleentry_address_to->setReadOnly(true);
    ui->multipleentry_date->setDate(QDate::currentDate());
    ui->multipleentry_date->setReadOnly(true);
    ui->multipleentry_password_from->setReadOnly(true);
    ui->multipleentry_balance_from->setReadOnly(true);
    ui->multipleentry_balance_to->setReadOnly(true);
}

//DataBase Connection

bool multipleentry::conn(){
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

void multipleentry::disconn(){
    mydb.close();
    mydb.removeDatabase(QSqlDatabase::defaultConnection);
}

bool multipleentry::writestatement(){
    multipleentry::conn();
    QSqlQuery query;
    query.prepare("INSERT INTO statement ([Account No],[Name],[Address],[Date],[Particulars],[Credit Amount],[Balance],[Time])" "VALUES(:acc_no,:name,:address,:date,:particulars,:cr_amt,:balance,:time)");
    query.bindValue(":acc_no",ui->multipleentry_acc_no_to->text());
    query.bindValue(":name",ui->multipleentry_name_to->text());
    query.bindValue(":address",ui->multipleentry_address_to->text());
    query.bindValue(":date",ui->multipleentry_date->date());
    query.bindValue(":particulars",ui->multipleentry_narration->text());
    query.bindValue(":cr_amt",ui->multipleentry_amount->text());
    query.bindValue(":balance",ui->multipleentry_balance_to->text().toDouble()+ui->multipleentry_amount->text().toDouble());
    query.bindValue(":time",QTime::currentTime());
    if(query.exec()){
        multipleentry::disconn();
        return true;
    }
    else{
        QMessageBox::warning(this,"Transaction",query.lastError().text());
    }
    multipleentry::disconn();
    return false;
}

void multipleentry::getfromdata(){
    multipleentry::conn();
    QSqlQuery query;
    query.prepare("SELECT [Name],[Address],[Password],[Balance] FROM account WHERE [Account No]='"+ui->multipleentry_acc_no_from->text()+"'");
    query.exec();
    while(query.next()){
        ui->multipleentry_name_from->setText(query.value(0).toString());
        ui->multipleentry_address_from->setText(query.value(1).toString());
        ui->multipleentry_password_from->setText(query.value(2).toString());
        ui->multipleentry_balance_from->setText(query.value(3).toString());
    }
    multipleentry::disconn();
}

void multipleentry::gettodata(){
    multipleentry::conn();
    QSqlQuery query;
    query.prepare("SELECT [Name],[Address],[Balance] FROM account WHERE [Account No]='"+ui->multipleentry_acc_no_to->text()+"' AND [Status]='"+QString::number(true)+"'");
    query.exec();
    while(query.next()){
        ui->multipleentry_name_to->setText(query.value(0).toString());
        ui->multipleentry_address_to->setText(query.value(1).toString());
        ui->multipleentry_balance_to->setText(query.value(2).toString());
    }
    multipleentry::disconn();
}

multipleentry::~multipleentry()
{
    delete ui;
}

bool multipleentry::checknull(){
    if(ui->multipleentry_acc_no_from->text()==NULL || ui->multipleentry_acc_no_to->text()==NULL || ui->multipleentry_name_from->text()==NULL || ui->multipleentry_name_to->text()==NULL || ui->multipleentry_amount->text()==NULL || ui->multipleentry_narration->text()==NULL){
        return true;
    }
    return false;
}

void multipleentry::resetdata(){
    ui->multipleentry_name_from->clear();
    ui->multipleentry_address_from->clear();
    ui->multipleentry_password_from->clear();
    ui->multipleentry_balance_from->clear();
    ui->multipleentry_name_to->clear();
    ui->multipleentry_address_to->clear();
    ui->multipleentry_balance_to->clear();
    ui->multipleentry_acc_no_from->clear();
    ui->multipleentry_acc_no_to->clear();
    ui->multipleentry_amount->clear();
    ui->multipleentry_narration->clear();
}

bool multipleentry::checklimit(QString acc_no,QString amt)
{
       multipleentry::conn();
       QSqlQuery query;
       query.prepare("SELECT * FROM account WHERE [Account No]='"+acc_no+"' AND [Limit] IS NULL");
       query.exec();
       while(query.next()){
           multipleentry::disconn();
           return false;
       }
       query.prepare("SELECT [Limit] FROM account WHERE [Account No]='"+acc_no+"'");
       query.exec();
       while(query.next()){
           if(amt.toDouble()>query.value(0).toDouble()){
               multipleentry::disconn();
               return true;
           }
       }
       multipleentry::disconn();
       return false;
}

void multipleentry::on_multipleentry_acc_no_from_returnPressed()
{
    if(obj.checkacc_no(ui->multipleentry_acc_no_from->text())){
        multipleentry::getfromdata();
    }
    else{
        QMessageBox::warning(this,"Multiple Entry","No Account Found!!");
    }
}


void multipleentry::on_multipleentry_acc_no_to_returnPressed()
{
    if(obj.checkacc_no(ui->multipleentry_acc_no_to->text())){
        multipleentry::gettodata();
    }
    else{
        QMessageBox::warning(this,"Multiple Entry","No Account Found!!");
    }
}

void multipleentry::on_multipleentry_acc_no_from_textChanged(const QString &arg1)
{
    ui->multipleentry_name_from->clear();
    ui->multipleentry_address_from->clear();
    ui->multipleentry_password_from->clear();
    ui->multipleentry_balance_from->clear();
}

void multipleentry::on_multipleentry_acc_no_to_textChanged(const QString &arg1)
{
    ui->multipleentry_name_to->clear();
    ui->multipleentry_address_to->clear();
    ui->multipleentry_balance_to->clear();
}

void multipleentry::on_multipleentry_back_clicked()
{
    menu *win=new menu;
    this->hide();
    win->show();
}

void multipleentry::on_multipleentry_deposit_clicked()
{
    if(multipleentry::checknull()){
        QMessageBox::warning(this,"Transaction","Please Enter All The Data!!");
    }
    else{
        if(multipleentry::checklimit(ui->multipleentry_acc_no_from->text(),ui->multipleentry_amount->text())){
            QMessageBox::warning(this,"Transaction","Withdraw Limit Exceed!!");
        }
        else if(ui->multipleentry_amount->text().toDouble()>ui->multipleentry_balance_from->text().toDouble()){
            QMessageBox::warning(this,"Transaction","Not Enough Balance!!");
        }

        else{
            multipleentry::conn();
            QSqlQuery query;
            query.prepare("UPDATE account SET [Balance]=:blnc WHERE [Account No]='"+ui->multipleentry_acc_no_from->text()+"'");
            query.bindValue(":blnc",ui->multipleentry_balance_from->text().toDouble()-ui->multipleentry_amount->text().toDouble());
            if(query.exec()){
                query.prepare("UPDATE account SET [Balance]=:blnc WHERE [Account No]='"+ui->multipleentry_acc_no_to->text()+"'");
                query.bindValue(":blnc",ui->multipleentry_balance_to->text().toDouble()+ui->multipleentry_amount->text().toDouble());
                if(query.exec()){
                    if(multipleentry::writestatement()){
                        QMessageBox::information(this,"Transaction","Balance Transfered!!");
                        multipleentry::resetdata();
                    }
                }
            }
            multipleentry::disconn();
        }
    }
}


//Useless Function

void multipleentry::on_multipleentry_to_returnPressed()
{

}


