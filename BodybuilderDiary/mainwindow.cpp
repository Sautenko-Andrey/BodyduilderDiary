#include "mainwindow.h"
#include "./ui_mainwindow.h"

#include <QScreen>
#include <QDebug>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
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


