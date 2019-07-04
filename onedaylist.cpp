#include "onedaylist.h"
#include "ui_onedaylist.h"

void onedaylist::setdata(QString title){
    setWindowTitle(title);
}

onedaylist::onedaylist(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::onedaylist)
{
    ui->setupUi(this);
    ui->onedaylist_date->setDate(QDate::currentDate());
    ui->onedaylist_date->setReadOnly(true);
}

onedaylist::~onedaylist()
{
    delete ui;
}

//DataBase Connection

bool onedaylist::conn(){
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

void onedaylist::disconn(){
    mydb.close();
    mydb.removeDatabase(QSqlDatabase::defaultConnection);
}

void onedaylist::getstatement(){
    onedaylist::conn();
    QSqlQueryModel *modal=new QSqlQueryModel;
    QSqlQuery *query=new QSqlQuery(mydb);
    query->prepare("SELECT * FROM statement WHERE [Date]=Date(:date)");
    query->bindValue(":date",QDate::currentDate());
    query->exec();
    modal->setQuery(*query);
    ui->onedaylist_table->setModel(modal);
    onedaylist::disconn();
}

void onedaylist::today_acc_open(){
    onedaylist::conn();
    setFixedWidth(350);
    QSqlQueryModel *modal=new QSqlQueryModel;
    QSqlQuery *query=new QSqlQuery(mydb);
    query->prepare("SELECT [Account No],[Account Type],[Name] FROM account WHERE [Account Created]=Date(:date)");
    query->bindValue(":date",QDate::currentDate());
    query->exec();
    modal->setQuery(*query);
    ui->onedaylist_table->setModel(modal);
    onedaylist::disconn();
}

void onedaylist::today_acc_holder_detail(){
    onedaylist::conn();
    QSqlQueryModel *modal=new QSqlQueryModel;
    QSqlQuery *query=new QSqlQuery(mydb);
    query->prepare("SELECT [Account No],[Account Type],[Name],[Date of Birth],[Gender],[Mobile No],[Nationality],[Address],[Father Name],[Grand Father Name],[Rate],[Balance] FROM account WHERE [Account Created]=Date(:date)");
    query->bindValue(":date",QDate::currentDate());
    query->exec();
    modal->setQuery(*query);
    ui->onedaylist_table->setModel(modal);
    onedaylist::disconn();
}

void onedaylist::on_onedaylist_back_clicked()
{
    this->close();
}
