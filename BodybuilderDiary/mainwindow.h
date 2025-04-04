#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include "adduser.h"
#include "databasemanager.h"
//#include "find.h"
#include "editcustomer.h"
#include "deletecustomer.h"
#include "addexercise.h"
#include "searchcustomer.h"
#include "searchexercise.h"
#include "editexrcise.h"


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

    void on_actionDelete_a_customer_triggered();

    void on_actionAdd_a_new_exercise_triggered();

    void on_actionEdit_exercise_exercises_triggered();

    void on_actionFind_an_exercise_triggered();

    void on_actionDelete_exercise_triggered();

private:
    Ui::MainWindow *ui;

    // Pointer on AddUser widget
    std::unique_ptr<AddUser> m_ptr_add_user{nullptr};

    // Pointer on FindCustomer widget
    //std::unique_ptr<Find> m_ptr_find_user{nullptr};  // Remove it!

    // Pointer on SearchCustomer
    std::unique_ptr<SearchCustomer> m_ptr_search_customer{nullptr};

    // Pointer on SearchExercise
    std::unique_ptr<SearchExercise> m_ptr_search_exercise{nullptr};

    // Pointer on EditCustomer widget
    std::unique_ptr<EditCustomer> m_ptr_edit_user{nullptr};

    // Pointer on DeleteCustomer widget
    std::unique_ptr<DeleteCustomer> m_ptr_delete_customer{nullptr};

    // Pointer on AddExercise widget
    std::unique_ptr<AddExercise> m_ptr_add_exercise{nullptr};

    // For seeking an exercise
    //std::unique_ptr<Find> m_ptr_find_exercise{nullptr};

    // Pointer in EditExercise widget
    std::unique_ptr<EditExrcise> m_ptr_edit_exercise{nullptr};

    DataBaseManager &db_manager = DataBaseManager::getInstance();

};
#endif // MAINWINDOW_H
