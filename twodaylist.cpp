#include "twodaylist.h"
#include "ui_twodaylist.h"

void twodaylist::getdata(QString title){
    setWindowTitle(title);
}

twodaylist::twodaylist(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::twodaylist)
{
    ui->setupUi(this);
    QDate min;
    min.setDate(2017,01,01);
    ui->twodaylist_to->setDate(QDate::currentDate());
    ui->twodaylist_to->setMaximumDate(QDate::currentDate());
    ui->twodaylist_to->setMinimumDate(min);
    ui->twodaylist_from->setMinimumDate(min);
    ui->twodaylist_from->setMaximumDate(QDate::currentDate());
}

twodaylist::~twodaylist()
{
    delete ui;
}

//Database Connect

bool twodaylist::conn(){
    mydb=QSqlDatabase::addDatabase("QSQLITE");
    mydb.setDatabaseName("F:/project/final/finalfinalproject/accountdata.db");
    if(mydb.open()){
        return true;
    }
    else{
        return false;
    }
}

//Disconnect With Database

void twodaylist::disconn(){
    mydb.close();
    mydb.removeDatabase(QSqlDatabase::defaultConnection);
}

void twodaylist::get_transaction_list(){
    twodaylist::conn();
    QSqlQueryModel *modal=new QSqlQueryModel;
    QSqlQuery *query=new QSqlQuery(mydb);
    query->prepare("SELECT [Date],[Time],[Particulars],[Debit Amount],[Credit Amount],[Balance] FROM statement WHERE [Date]>=:from AND [Date]<=:to");
    query->bindValue(":from",ui->twodaylist_from->date());
    query->bindValue(":to",ui->twodaylist_to->date());
    query->exec();
    modal->setQuery(*query);
    ui->twodaylist_table->setModel(modal);
    setFixedWidth(670);
    twodaylist::disconn();
}

void twodaylist::get_acc_holder_list(){
    twodaylist::conn();
    QSqlQueryModel *modal=new QSqlQueryModel;
    QSqlQuery *query=new QSqlQuery(mydb);
    query->prepare("SELECT [Account No],[Account Type],[Name],[Date of Birth],[Gender],[Mobile No],[Nationality],[Address],[Father Name],[Grand Father Name],[Rate],[Balance] FROM account WHERE [Account Created]>=:from AND [Account Created]<=:to");
    query->bindValue(":from",ui->twodaylist_from->date());
    query->bindValue(":to",ui->twodaylist_to->date());
    query->exec();
    modal->setQuery(*query);
    ui->twodaylist_table->setModel(modal);
    twodaylist::disconn();
}

void twodaylist::on_twodaylist_show_clicked()
{
    if(windowTitle()=="Transaction List")  {
        twodaylist::get_transaction_list();
    }
    else{
        twodaylist::get_acc_holder_list();
    }
}

void twodaylist::on_twodaylist_back_clicked()
{
    close();
}
