#include "statement.h"
#include "ui_statement.h"
#include "menu.h"
#include <QDate>
void statement::resetdata(){
    ui->statement_name->clear();
    ui->statement_address->clear();
    ui->statement_from->clear();
    ui->statement_to->clear();
    ui->statement_name->setReadOnly(true);
    ui->statement_address->setReadOnly(true);
    ui->statement_from->setMaximumDate(QDate::currentDate());
    ui->statement_date->setDisabled(true);
    ui->statement_table->setDisabled(true);
    ui->statement_show->setDisabled(true);
    ui->statement_to->setDate(QDate::currentDate());
    ui->statement_to->setMaximumDate(QDate::currentDate());
}

void statement::setstatus(QString back_button,bool acc_status){
    ui->statement_back->setText("Close");
    ui->statement_acc_no->setReadOnly(acc_status);
}

void statement::loaddata(QString acc_no){
    statement::conn();
    QSqlQuery query;
    query.prepare("SELECT [Name],[Address],[Account Created] FROM account WHERE [Account No]='"+acc_no+"'");
    query.exec();
    while(query.next()){
        ui->statement_acc_no->setText(acc_no);
        ui->statement_name->setText(query.value(0).toString());
        ui->statement_address->setText(query.value(1).toString());
        ui->statement_from->setDate(query.value(2).toDate());
        ui->statement_from->setMinimumDate(query.value(2).toDate());
        ui->statement_to->setMinimumDate(query.value(2).toDate());
        ui->statement_date->setEnabled(true);
        ui->statement_show->setEnabled(true);
    }
    statement::disconn();
}

statement::statement(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::statement)
{
    ui->setupUi(this);
    statement::resetdata();
    //ui->statement_acc_no->setInputMask("999999");
    //ui->statement_acc_no->clear();
}

statement::~statement()
{
    delete ui;
}

//DataBase Connection

bool statement::conn(){
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

void statement::disconn(){
    mydb.close();
    mydb.removeDatabase(QSqlDatabase::defaultConnection);
}

void statement::on_statement_back_clicked()
{
    if(ui->statement_back->text()=="Close"){
        close();
    }
    else{
        menu *win=new menu;
        this->hide();
        win->show();
    }
}

void statement::on_statement_acc_no_returnPressed()
{
       if(obj.checkacc_no(ui->statement_acc_no->text())){
           statement::loaddata(ui->statement_acc_no->text());
       }
       else{
           QMessageBox::warning(this,"Statement Error","No Account Found!!");
       }
}

void statement::on_statement_show_clicked()
{
    statement::conn();
    QSqlQueryModel *modal=new QSqlQueryModel;
    QSqlQuery *query=new QSqlQuery(mydb);
    query->prepare("SELECT [Date],[Time],[Particulars],[Debit Amount],[Credit Amount],[Balance] FROM statement WHERE [Account No]='"+ui->statement_acc_no->text()+"' AND [Date]>=:from AND [Date]<=:to");
    query->bindValue(":from",ui->statement_from->date());
    query->bindValue(":to",ui->statement_to->date());
    query->exec();
    modal->setQuery(*query);
    ui->statement_table->setModel(modal);
    statement::disconn();
    ui->statement_table->setEnabled(true);
}

void statement::on_statement_acc_no_textChanged(const QString &arg1)
{
    statement::resetdata();
}
