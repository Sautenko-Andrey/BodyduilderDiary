#include "mainwindow.h"
#include "./ui_mainwindow.h"

#include <QScreen>
#include <QDebug>
#include <QDir>
#include <QFile>
#include <QMessageBox>
#include "exercise.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // Creating all tables for the proper work
    if(!db_manager.prepare()){
        QMessageBox::warning(this,
                             "Database error",
                             "Couldn't prepare the databse.");
        exit(1);
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}


/*
    Method calls AddUser class
*/
void MainWindow::on_actionAdd_user_triggered()
{
    m_ptr_add_user = std::make_unique<AddUser>(this);

    m_ptr_add_user->setWindowTitle("Adding a new customer");

    m_ptr_add_user->show();
}


/*
    Method calls FinsdUser class
*/
void MainWindow::on_actionFind_a_customer_triggered()
{
    m_ptr_find_user = std::make_unique<Find>(FindType::Customer, this);

    m_ptr_find_user->setWindowTitle("Searching a customer");

    m_ptr_find_user->show();
}


/*
    Method calls EditCustomer class
*/
void MainWindow::on_actionEdit_customer_customers_triggered()
{
    m_ptr_edit_user = std::make_unique<EditCustomer>(this);
    m_ptr_edit_user->setWindowTitle("Editing a customer");
    m_ptr_edit_user->show();
}


/*
    Method calls DeleteCustomer class
*/
void MainWindow::on_actionDelete_a_customer_triggered()
{
    m_ptr_delete_customer = std::make_unique<DeleteCustomer>(this);
    m_ptr_delete_customer->setWindowTitle("Deleting a customer");
    m_ptr_delete_customer->show();
}


/*
    Method calls AddExercise class
*/
void MainWindow::on_actionAdd_a_new_exercise_triggered()
{
    m_ptr_add_exercise = std::make_unique<AddExercise>(this);
    m_ptr_add_exercise->setWindowTitle("Adding a new exercise");
    m_ptr_add_exercise->show();
}


/*
    Method calls EditExercise class
*/
void MainWindow::on_actionEdit_exercise_exercises_triggered()
{

}


/*
    Method calls FindExercise class
*/
void MainWindow::on_actionFind_an_exercise_triggered()
{
    m_ptr_find_exercise = std::make_unique<Find>(FindType::Exercise, this);
    m_ptr_find_exercise->setWindowTitle("Seeking an exercise");
    m_ptr_find_exercise->show();
}


/*
    Method calls DeleteExercise class
*/
void MainWindow::on_actionDelete_exercise_triggered()
{

}

