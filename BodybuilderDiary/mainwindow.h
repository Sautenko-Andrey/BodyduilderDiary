#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include "adduser.h"

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

private:
    Ui::MainWindow *ui;

    // Pointer on AddUser widget
    std::unique_ptr<AddUser> m_ptr_add_user{nullptr};

};
#endif // MAINWINDOW_H
