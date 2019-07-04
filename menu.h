#ifndef MENU_H
#define MENU_H

#include <QTabWidget>

namespace Ui {
class menu;
}

class menu : public QTabWidget
{
    Q_OBJECT

public:
    explicit menu(QWidget *parent = 0);
    ~menu();

private slots:
    void on_account_next_clicked();

    void on_account_list_currentTextChanged(const QString &currentText);

    void on_transection_next_clicked();

    void on_account_list_entered(const QModelIndex &index);

    void on_report_next_clicked();

    void on_transection_list_currentTextChanged(const QString &currentText);

    void on_report_list_currentTextChanged(const QString &currentText);

private:
    Ui::menu *ui;
};

#endif // MENU_H
