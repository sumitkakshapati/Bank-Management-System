#include "deposit.h"
#include "ui_deposit.h"
#include "menu.h"
#include <QMessageBox>

//Set Data To dialog box

void deposit::setdata(QString title,QString push){
    setWindowTitle(title);
    ui->deposit_push->setText(push);
}

deposit::deposit(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::deposit)
{
    ui->setupUi(this);
    ui->deposit_detail->hide();
    ui->deposit_name->setReadOnly(true);
    ui->deposit_address->setReadOnly(true);
    ui->deposit_balance->setReadOnly(true);
    ui->deposit_password->setReadOnly(true);
    ui->deposit_date->setReadOnly(true);
    ui->deposit_date->setDate(QDate::currentDate());
}

deposit::~deposit()
{
    delete ui;
}

//Check NULL

bool deposit::check_null(){
    if(ui->deposit_balance->text()==NULL || ui->deposit_narration->text()==NULL){
        return true;
    }
    return false;
}

void deposit::cleardetail(){
    ui->deposit_name->clear();
    ui->deposit_address->clear();
    ui->deposit_balance->clear();
    ui->deposit_password->clear();
    ui->deposit_detail->hide();
}

void deposit::resetdata(){
    deposit::cleardetail();
    ui->deposit_narration->clear();
    ui->deposit_amount->clear();
    ui->deposit_acc_no->clear();
}

//Database Connect

bool deposit::conn(){
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

void deposit::disconn(){
    mydb.close();
    mydb.removeDatabase(QSqlDatabase::defaultConnection);
}

single_entry_data deposit::getdata(){
    single_entry_data k;
    k.setacc_no(ui->deposit_acc_no->text());
    k.name.setname(ui->deposit_name->text());
    k.setaddress(ui->deposit_address->text());
    k.dates.setdate(ui->deposit_date->date());
    k.setnaration(ui->deposit_narration->text());
    k.setamount(ui->deposit_amount->text());
    k.setbalance(ui->deposit_balance->text());
    return k;
}

bool deposit::save_depo_statement(single_entry_data k){
    deposit::conn();
    bool flag=false;
    QSqlQuery query;
    query.prepare("INSERT INTO statement ([Account No],[Name],[Address],[Date],[Particulars],[Credit Amount],[Balance],[Time])" "VALUES(:acc_no,:name,:address,:date,:particulars,:cr_amt,:balance,:time)");
    query.bindValue(":acc_no",k.getacc_no());
    query.bindValue(":name",k.name.getname());
    query.bindValue(":address",k.getaddress());
    query.bindValue(":date",k.dates.getdate());
    query.bindValue(":particulars",k.getnaration());
    query.bindValue(":cr_amt",k.getamount());
    query.bindValue(":balance",k.getbalance().toInt()+k.getamount().toInt());
    query.bindValue(":time",QTime::currentTime());
    if(query.exec()){
        flag=true;
    }
    else{
        QMessageBox::warning(this,"Transaction",query.lastError().text());
    }
    deposit::disconn();
    return flag;
}

//Update Account Database

bool deposit::update_account(single_entry_data k){
    deposit::conn();
    QSqlQuery query;
    query.prepare("UPDATE account SET [Balance]='"+k.getbalance()+"' WHERE [Account No]='"+k.getacc_no()+"'");
    if(query.exec()){
     deposit::disconn();
     return true;
    }
    deposit::disconn();
    return false;
}

bool deposit::save_with_statement(single_entry_data k){
    deposit::conn();
    bool flag=false;
    QSqlQuery query;
    query.prepare("INSERT INTO statement ([Account No],[Name],[Address],[Date],[Particulars],[Debit Amount],[Balance],[Time])" "VALUES(:acc_no,:name,:address,:date,:particulars,:dr_amt,:balance,:time)");
    query.bindValue(":acc_no",k.getacc_no());
    query.bindValue(":name",k.name.getname());
    query.bindValue(":address",k.getaddress());
    query.bindValue(":date",k.dates.getdate());
    query.bindValue(":particulars",k.getnaration());
    query.bindValue(":dr_amt",k.getamount());
    query.bindValue(":balance",k.getbalance().toInt()-k.getamount().toInt());
    query.bindValue(":time",QTime::currentTime());
    if(query.exec()){
        flag=true;
    }
    else{
        QMessageBox::warning(this,"Transaction",query.lastError().text());
    }
    deposit::disconn();
    return flag;
}

//Get Account Detial

void deposit::getdetail(QString acc_no){
    deposit::conn();
    QSqlQuery query;
    query.prepare("SELECT [Name],[Address],[Balance],[Password] FROM account WHERE [Account No]='"+acc_no+"' AND [Status]='"+QString::number(true)+"'");
    query.exec();
    while(query.next()){
        ui->deposit_name->setText(query.value(0).toString());
        ui->deposit_address->setText(query.value(1).toString());
        ui->deposit_balance->setText(query.value(2).toString());
        ui->deposit_password->setText(query.value(3).toString());
    }
    deposit::disconn();
}

//When Account No is Pressed

void deposit::on_deposit_acc_no_returnPressed()
{
    QString acc_no=ui->deposit_acc_no->text();
    if(obj.checkacc_no(acc_no)){
        ui->deposit_detail->show();
        deposit::getdetail(acc_no);
    }
    else{
        deposit::cleardetail();
    }
}

void deposit::on_deposit_acc_no_editingFinished()
{
    deposit::on_deposit_acc_no_returnPressed();
}

void deposit::on_deposit_cancel_clicked()
{
    menu *win=new menu;
    this->hide();
    win->show();
}

void deposit::on_deposit_push_clicked()
{
    if(deposit::check_null()){
        QMessageBox::warning(this,"Transaction Error","Please Enter All The Data!!");
    }
    else{
        if(ui->deposit_push->text()=="Deposit"){
            single_entry_data k=deposit::getdata();
            if(deposit::save_depo_statement(k)){
                k.setbalance(QString::number(k.getbalance().toInt()+k.getamount().toInt()));
                if(deposit::update_account(k)){
                    QMessageBox::information(this,"Transaction","Deposit Succesfull");
                    deposit::resetdata();
                }
            }
        }
        else{
            single_entry_data k=deposit::getdata();
            if(obj2.checklimit(k.getacc_no(),k.getamount())){
                QMessageBox::warning(this,"Transaction","Limit Exceed!!");
            }
            else{
                if(k.getbalance().toInt()>=k.getamount().toInt()){
                    if(deposit::save_with_statement(k)){
                        k.setbalance(QString::number(k.getbalance().toInt()-k.getamount().toInt()));
                        if(deposit::update_account(k)){
                            QMessageBox::information(this,"Transaction","Withdraw Succesfull");
                            deposit::resetdata();
                        }
                    }
                }
                else{
                    QMessageBox::warning(this,"Transaction Error","Not Enough Balance!!");
                }
            }
        }
    }
}

void deposit::on_deposit_acc_no_textChanged(const QString &arg1)
{
    deposit::cleardetail();
}
