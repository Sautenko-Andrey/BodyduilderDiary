#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include "adduser.h"
#include "databasemanager.h"
#include "findcustomer.h"
#include "editcustomer.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_actionAdd_user_triggered();

    void on_actionFind_a_customer_triggered();

    void on_actionEdit_customer_customers_triggered();

private:
    Ui::MainWindow *ui;

    // Pointer on AddUser widget
    std::unique_ptr<AddUser> m_ptr_add_user{nullptr};

    // Pointer on FindCustomer widget
    std::unique_ptr<FindCustomer> m_ptr_find_user{nullptr};

    // Pointer on EditCustomer widget
    std::unique_ptr<EditCustomer> m_ptr_edit_user{nullptr};

    DataBaseManager &db_manager = DataBaseManager::getInstance();

};
#endif // MAINWINDOW_H
