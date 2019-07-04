#include "account.h"

//Customer Class Implementation

void customer::setname(QString n){
    name=n;
}

QString customer::getname(){
    return name;
}

//Date Class Implementation

QDate date::getdate(){
    return dates;
}

void date::setdate(QDate k){
    dates=k;
}


//Account Class Implementation

void account::setaccount_no(QString a){
    acc_no=a;
}

void account::setaccount_type(QString b){
    acc_type=b;
}

void account::setbalance(QString c){
    balance=c;
}

QString account::getaccount_no(){
    return acc_no;
}

QString account::getaccount_type(){
    return acc_type;
}

QString account::getbalance(){
    return balance;
}

bool account::getstatus(){
    return status;
}

void account::setstatus(bool s){
    status=s;
}

//Password Class Implementation

void password::setpassword(QString z){
    pass=z;
}

QString password::getpassword(){
    return pass;
}

//Personal Class Implementation

void personal::setmobileno(QString a){
    mob_no=a;
}

void personal::setgender(QString b){
    gender=b;
}

void personal::setaddress(QString c){
    address=c;
}

void personal::setnationality(QString n){
    nationality=n;
}

QString personal::getnationality(){
    return nationality;
}

QString personal::getmobileno(){
    return mob_no;
}

QString personal::getgender(){
    return gender;
}

QString personal::getaddress(){
    return address;
}

//Saving Account Implementation

void saving_account::setrate(double k){
    rate=k;
}

double saving_account::getrate(){
    return rate;
}


//Deposit Data Implementation

void deposit_data::setmode(QString a){
    mode=a;
}

void deposit_data::setchequeno(QString b){
    cheque_no=b;
}

void deposit_data::setbankname(QString c){
    bank_name=c;
}

QString deposit_data::getmode(){
    return mode;
}

QString deposit_data::getchequeno(){
    return cheque_no;
}

QString deposit_data::getbankname(){
    return bank_name;
}

//Single Entry Data Implementation

void single_entry_data::setacc_no(QString a){
    acc_no=a;
}

void single_entry_data::setaddress(QString a){
    address=a;
}

void single_entry_data::setnaration(QString n){
    naration=n;
}

void single_entry_data::setamount(QString a){
    amt=a;
}

void single_entry_data::setbalance(QString b){
    balance=b;
}

QString single_entry_data::getacc_no(){
    return acc_no;
}

QString single_entry_data::getaddress(){
    return address;
}

QString single_entry_data::getnaration(){
    return naration;
}

QString single_entry_data::getamount(){
    return amt;
}

QString single_entry_data::getbalance(){
    return balance;
}
