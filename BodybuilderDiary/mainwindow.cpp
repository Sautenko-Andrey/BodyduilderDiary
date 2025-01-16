#include "mainwindow.h"
#include "./ui_mainwindow.h"

#include <QScreen>
#include <QDebug>
#include <QDir>
#include <QFile>
#include <QMessageBox>


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // Creating all tables for the proper work
    //db_manager.createDB(query_msgs);
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
    m_ptr_find_user = std::make_unique<FindCustomer>(this);

    m_ptr_find_user->setWindowTitle("Searching a customer");

    m_ptr_find_user->show();
}

