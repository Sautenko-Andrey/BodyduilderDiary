#ifndef ADDUSER_H
#define ADDUSER_H

#include <QDialog>
#include "databasemanager.h"

namespace Ui {
class AddUser;
}

class AddUser : public QDialog
{
    Q_OBJECT

public:
    explicit AddUser(QWidget *parent = nullptr);
    ~AddUser();

private slots:
    void on_saveButton_clicked();

private:
    Ui::AddUser *ui;

    // Validation functions
    bool checkFullName() const;

    DataBaseManager &db_manager = DataBaseManager::getInstance();
};

#endif // ADDUSER_H
