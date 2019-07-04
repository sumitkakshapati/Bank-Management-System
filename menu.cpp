#include "menu.h"
#include "ui_menu.h"
#include <QMessageBox>
#include "account_open.h"
#include "enquiry.h"
#include "statement.h"
#include "password.h"
#include "maintenance.h"
#include "ratelimit.h"
#include "deposit.h"
#include "onedaylist.h"
#include "twodaylist.h"
#include "multipleentry.h"

menu::menu(QWidget *parent) :
    QTabWidget(parent),
    ui(new Ui::menu)
{
    ui->setupUi(this);
    QStringList account_list,transaction_list,report_list;
    account_list<<"1. Account Open"<<"2. Enquiry"<<"3. Statement"<<"4. Password"<<"5. Maintenance"<<"6. Account Close";
    transaction_list<<"1. Single Entry"<<"2. Multiple Entry"<<"3. Transaction List";
    report_list<<"1. Account Opening List"<<"2. Account Holder Detail"<<"3. Transaction List Datewise"<<"4. Account Holder Detail Datewise";
    ui->account_list->addItems(account_list);
    ui->transection_list->addItems(transaction_list);
    ui->report_list->addItems(report_list);
    setCurrentIndex(0);
    QPixmap pic(":/new/Resource/Login.png");
    ui->account_show->setPixmap(pic.scaled(150,135,Qt::KeepAspectRatio));
    ui->transection_show->setPixmap(pic.scaled(150,135,Qt::KeepAspectRatio));
    ui->report_show->setPixmap(pic.scaled(150,135,Qt::KeepAspectRatio));
}

menu::~menu()
{
    delete ui;
}

//Account Next Button

void menu::on_account_next_clicked()
{
    QString select=ui->account_list->currentItem()->text();
    if(select=="1. Account Open"){
        account_open *win=new account_open;
        win->setdata("Account Open","Create Account","Back",true);
        win->setacc_no();
        this->hide();
        win->show();
    }
    else if(select=="2. Enquiry"){
        enquiry *win=new enquiry;
        this->hide();
        win->show();
    }
    else if(select=="3. Statement"){
        statement *win=new statement;
        this->hide();
        win->show();
    }
    else if(select=="4. Password"){
        Password *win=new Password;
        win->setdata("Password","Set Password");
        this->hide();
        win->show();
    }
    else if(select=="5. Maintenance"){
        maintenance *win=new maintenance;
        win->setdata("Maintenance","General","Rate/Limit");
        if(win->exec()){
            if(win->check()==1){
                account_open *win1=new account_open;
                win1->setdata("Maintenance","Update Account","Back",false);
                win1->setoff();
                this->hide();
                win1->show();
            }
            else{
                ratelimit *win2=new ratelimit;
                this->hide();
                win2->show();
            }
        }
    }
    else if(select=="6. Account Close"){
        Password *win=new Password;
        win->setdata("Account Close","Deactive Account");
        this->hide();
        win->show();
    }
    else{
        QMessageBox::warning(this,"Warning","Nothing Selected!!");
    }

}

//Current Text Changed

void menu::on_account_list_currentTextChanged(const QString &currentText)
{
    if(currentText=="1. Account Open"){
        QPixmap pic(":/new/Resource/add account.png");
        ui->account_show->setPixmap(pic.scaled(ui->account_show->height(),ui->account_show->width(),Qt::KeepAspectRatio));
    }
    else if(currentText=="2. Enquiry"){
        QPixmap pic(":/new/Resource/search account.png");
        ui->account_show->setPixmap(pic.scaled(ui->account_show->height(),ui->account_show->width(),Qt::KeepAspectRatio));
    }
    else if(currentText=="3. Statement"){
        QPixmap pic(":/new/Resource/statement.png");
        ui->account_show->setPixmap(pic.scaled(ui->account_show->height(),ui->account_show->width(),Qt::KeepAspectRatio));
    }
    else if(currentText=="4. Password"){
        QPixmap pic(":/new/Resource/password.png");
        ui->account_show->setPixmap(pic.scaled(ui->account_show->height(),ui->account_show->width(),Qt::KeepAspectRatio));
    }
    else if(currentText=="5. Maintenance"){
        QPixmap pic(":/new/Resource/maintenance.png");
        ui->account_show->setPixmap(pic.scaled(ui->account_show->height(),ui->account_show->width(),Qt::KeepAspectRatio));
    }
    else if(currentText=="6. Account Close"){
        QPixmap pic(":/new/Resource/delete account.png");
        ui->account_show->setPixmap(pic.scaled(ui->account_show->height(),ui->account_show->width(),Qt::KeepAspectRatio));
    }
    else{
        QPixmap pic(":/new/Resource/Login.png");
        ui->account_show->setPixmap(pic.scaled(ui->account_show->height(),ui->account_show->width(),Qt::KeepAspectRatio));
    }
}

//Transaction Next Button

void menu::on_transection_next_clicked()
{
    QString select=ui->transection_list->currentItem()->text();
    if(select=="1. Single Entry"){
        maintenance *win=new maintenance;
        win->setdata("Single Entry","Cash Deposit","Cash Withdraw");
        if(win->exec()){
            deposit *win1=new deposit;
            if(win->check()==1){
                win1->setdata("Cash Deposit","Deposit");
                this->hide();
                win1->show();
            }
            else{
                win1->setdata("Cash Withdraw","Withdraw");
                this->hide();
                win1->show();
            }
        }
    }
    else if(select=="2. Multiple Entry"){
        multipleentry *win=new multipleentry;
        this->hide();
        win->show();
    }
    else if(select=="3. Transaction List"){
        onedaylist *win=new onedaylist;
        win->setdata("Transaction List");
        win->getstatement();
        win->show();
    }
    else{
        QMessageBox::warning(this,"Warning","Nothing Selected!!");
    }
}

//Useless

void menu::on_account_list_entered(const QModelIndex &index)
{

}

//Report Next

void menu::on_report_next_clicked()
{
    QString select=ui->report_list->currentItem()->text();
    if(select=="1. Account Opening List"){
        onedaylist *win=new onedaylist;
        win->setdata("Account Opening List");
        win->today_acc_open();
        win->show();
    }
    else if(select=="2. Account Holder Detail"){
        onedaylist *win=new onedaylist;
        win->setdata("Account Holder Detail");
        win->today_acc_holder_detail();
        win->show();
    }
    else if(select=="3. Transaction List Datewise"){
        twodaylist *win=new twodaylist;
        win->getdata("Transaction List");
        win->show();
    }
    else if(select=="4. Account Holder Detail Datewise"){
        twodaylist *win=new twodaylist;
        win->getdata("Account Holder Detail");
        win->show();
    }

    else{
        QMessageBox::warning(this,"Warning","Nothing Selected!!");
    }
}

void menu::on_transection_list_currentTextChanged(const QString &currentText)
{
    if(currentText=="1. Single Entry"){
        QPixmap pic(":/new/Resource/single entry s.png");
        ui->transection_show->setPixmap(pic.scaled(ui->account_show->height(),ui->account_show->width(),Qt::KeepAspectRatio));
    }
    else if(currentText=="2. Multiple Entry"){
        QPixmap pic(":/new/Resource/multiple entry.png");
        ui->transection_show->setPixmap(pic.scaled(ui->account_show->height(),ui->account_show->width(),Qt::KeepAspectRatio));
    }
    else if(currentText=="3. Transaction List"){
        QPixmap pic(":/new/Resource/statement.png");
        ui->transection_show->setPixmap(pic.scaled(ui->account_show->height(),ui->account_show->width(),Qt::KeepAspectRatio));
    }
    else{
        QPixmap pic(":/new/Resource/Login.png");
        ui->transection_show->setPixmap(pic.scaled(ui->account_show->height(),ui->account_show->width(),Qt::KeepAspectRatio));
    }
}

void menu::on_report_list_currentTextChanged(const QString &currentText)
{
    if(currentText=="1. Account Opening List"){
        QPixmap pic(":/new/Resource/account open.png");
        ui->report_show->setPixmap(pic.scaled(ui->account_show->height(),ui->account_show->width(),Qt::KeepAspectRatio));
    }
    else if(currentText=="2. Account Holder Detail"){
        QPixmap pic(":/new/Resource/account holder.png");
        ui->report_show->setPixmap(pic.scaled(ui->account_show->height(),ui->account_show->width(),Qt::KeepAspectRatio));
    }
    else if(currentText=="3. Transaction List Datewise"){
        QPixmap pic(":/new/Resource/statement.png");
        ui->report_show->setPixmap(pic.scaled(ui->account_show->height(),ui->account_show->width(),Qt::KeepAspectRatio));
    }
    else if(currentText=="4. Account Holder Detail Datewise"){
        QPixmap pic(":/new/Resource/account holder.png");
        ui->report_show->setPixmap(pic.scaled(ui->account_show->height(),ui->account_show->width(),Qt::KeepAspectRatio));
    }
    else{
        QPixmap pic(":/new/Resource/Login.png");
        ui->report_show->setPixmap(pic.scaled(ui->account_show->height(),ui->account_show->width(),Qt::KeepAspectRatio));
    }
}
