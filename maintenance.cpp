#include "maintenance.h"
#include "ui_maintenance.h"

void maintenance::setdata(QString title,QString one,QString two){
    setWindowTitle(title);
    ui->maintenance_general->setText(one);
    ui->maintenance_rate->setText(two);
}

maintenance::maintenance(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::maintenance)
{
    ui->setupUi(this);
    ui->maintenance_general->setChecked(true);
}

maintenance::~maintenance()
{
    delete ui;
}

int maintenance::check(){
    if(ui->maintenance_general->isChecked()){
        return 1;
    }
    return 2;
}
