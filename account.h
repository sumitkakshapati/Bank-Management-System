#ifndef ACCOUNT_H
#define ACCOUNT_H

#include <QString>
#include <QDate>

//Customer Class

class customer{
    QString name;
public:
    void setname(QString);
    QString getname();
};

//Date Class

class date{
    QDate dates;
public:
    QDate getdate();
    void setdate(QDate);
};

//Account Class

class account{
    QString acc_no;
    QString acc_type;
    QString balance;
    bool status;
public:
    void setaccount_no(QString);
    void setaccount_type(QString);
    void setbalance(QString);
    bool getstatus();
    void setstatus(bool);
    QString getaccount_no();
    QString getaccount_type();
    QString getbalance();
};

//Password class

class password{
    QString pass;
public:
    void setpassword(QString);
    QString getpassword();
};

//Personal class

class personal{
    QString mob_no;
    QString gender;
    QString nationality;
    QString address;
public:
    void setmobileno(QString);
    void setgender(QString);
    void setaddress(QString);
    void setnationality(QString);
    QString getnationality();
    QString getmobileno();
    QString getgender();
    QString getaddress();
    date birth;
};

//Saving Account Class

class saving_account{
private:
    double rate;
public:
    void setrate(double);
    double getrate();
    customer name;
    customer father;
    customer grandfather;
    account saving;
    personal info;
    password pin;
    date account_created;
    date account_expire;
};

//Current Account Class

class current_account{
public:
    customer name;
    customer father;
    customer grandfather;
    account current;
    personal info;
    password pin;
    date account_created;
    date account_expire;
};

//Withdraw Data Class

class withdraw_data{
public:
    customer name;
    date withdraw;
    password pin;
    account data;
};

//Deposit Data Class

class deposit_data{
private:
    QString mode;
    QString cheque_no;
    QString bank_name;
public:
    account data;
    customer holder;
    customer by;
    date deposit;
    void setmode(QString);
    void setchequeno(QString);
    void setbankname(QString);
    QString getmode();
    QString getchequeno();
    QString getbankname();
};

//Single Entry Data

class single_entry_data{
private:
    QString acc_no,address,naration,amt,balance;
public:
    customer name;
    date dates;
    void setacc_no(QString);
    void setaddress(QString);
    void setnaration(QString);
    void setamount(QString);
    void setbalance(QString);
    QString getacc_no();
    QString getaddress();
    QString getnaration();
    QString getamount();
    QString getbalance();

};

#endif // ACCOUNT_H
