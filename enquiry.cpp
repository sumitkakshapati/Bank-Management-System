#include "enquiry.h"
#include "ui_enquiry.h"
#include "menu.h"
#include <QMessageBox>
#include "account_open.h"
#include "statement.h"
enquiry::enquiry(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::enquiry)
{
    ui->setupUi(this);
    ui->enquiry_account_detail->hide();
    ui->enquiry_acc_no->setInputMask("999999");
    ui->enquiry_acc_no->clear();
}

enquiry::~enquiry()
{
    delete ui;
}

//DataBase Connection

bool enquiry::conn(){
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

void enquiry::disconn(){
    mydb.close();
    mydb.removeDatabase(QSqlDatabase::defaultConnection);
}

//Check Account No In DataBase

bool enquiry::checkacc_no(QString a){
    enquiry::conn();
    QSqlQuery *query=new QSqlQuery(mydb);
    query->prepare("SELECT * FROM account WHERE [Account No]='"+a+"' AND [Status]='"+QString::number(true)+"'");
    query->exec();
    while(query->next()){
        enquiry::disconn();
        return true;
    }
    enquiry::disconn();
    return false;
}

//Check Name In DataBase

bool enquiry::checkname(QString n){
    enquiry::conn();
    QSqlQuery *query=new QSqlQuery(mydb);
    query->prepare("SELECT * FROM account WHERE UPPER([Name])=UPPER('"+n+"') AND [Status]='"+QString::number(true)+"'");
    query->exec();
    while(query->next()){
        enquiry::disconn();
        return true;
    }
    enquiry::disconn();
    return false;
}

void enquiry::on_enquiry_back_clicked()
{
    menu *win=new menu;
    this->hide();
    win->show();
}

void enquiry::on_enquiry_search_clicked()
{
    if(ui->enquiry_acc_no->text()==NULL && ui->enquiry_name->text()==NULL){
        QMessageBox::warning(this,"Enquiry Error","Please Fill The Account No/Name!!");
    }
    else if(ui->enquiry_acc_no->text()!=NULL && ui->enquiry_name->text()==NULL){
        QString acc_no=ui->enquiry_acc_no->text();
        if(enquiry::checkacc_no(acc_no)){
            enquiry::conn();
            QSqlQueryModel *modal=new QSqlQueryModel;
            QSqlQuery *query=new QSqlQuery(mydb);
            query->prepare("SELECT [Account No],[Name],[Account Type],[Address],[Balance] FROM account WHERE [Account No]='"+acc_no+"'");
            query->exec();
            modal->setQuery(*query);
            ui->enquiry_table->setModel(modal);
            ui->enquiry_account_detail->show();
            enquiry::disconn();
        }
        else{
            ui->enquiry_account_detail->hide();
            QMessageBox::information(this,"Enquiry Error","No Account Found!!");
        }
    }
    else if(ui->enquiry_acc_no->text()==NULL && ui->enquiry_name->text()!=NULL){
        QString name=ui->enquiry_name->text();
        if(enquiry::checkname(name)){
            enquiry::conn();
            QSqlQueryModel *modal=new QSqlQueryModel;
            QSqlQuery *query=new QSqlQuery(mydb);
            query->prepare("SELECT [Account No],[Name],[Account Type],[Address],[Balance] FROM account WHERE UPPER([Name])=UPPER('"+name+"')");
            query->exec();
            modal->setQuery(*query);
            ui->enquiry_table->setModel(modal);
            ui->enquiry_account_detail->show();
            enquiry::disconn();
        }
        else{
            ui->enquiry_account_detail->hide();
            QMessageBox::information(this,"Enquiry Error","No Account Found!!");
        }
    }
    else{
        QMessageBox::warning(this,"Enquiry Information","Please Enter Any One Data!![Account No/Name]");
    }
}

void enquiry::on_enquiry_maintenance_clicked()
{
    QString value=ui->enquiry_table->model()->data(ui->enquiry_table->currentIndex()).toString();
    enquiry::conn();
    account_open *wins=new account_open;
    QSqlQuery query;
    query.prepare("SELECT * FROM account WHERE [Account No]='"+value+"'");
    query.exec();
    if(query.next()){
        wins->setdata("Maintenance","Update Account","Close",true);
        wins->cleardata();
        wins->setoff();
        wins->load_data(value);
        wins->show();
    }
    else{
        QMessageBox::warning(this,"Account","Please Select Account No!!");
    }
    enquiry::disconn();
}

void enquiry::on_enquiry_statement_clicked()
{
    QString value=ui->enquiry_table->model()->data(ui->enquiry_table->currentIndex()).toString();
    enquiry::conn();
    statement *win1=new statement;
    QSqlQuery query;
    query.prepare("SELECT * FROM account WHERE [Account No]='"+value+"'");
    query.exec();
    if(query.next()){
        win1->resetdata();
        win1->setstatus("Close",true);
        win1->loaddata(value);
        win1->show();
    }
    else{
        QMessageBox::warning(this,"Account","Please Select Account No!!");
    }
    enquiry::disconn();
}
