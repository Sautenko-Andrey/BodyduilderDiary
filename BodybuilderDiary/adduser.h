#ifndef ADDUSER_H
#define ADDUSER_H

#include <QDialog>
#include <QSqlDatabase>

namespace Ui {
class AddUser;
}

class AddUser : public QDialog
{
    Q_OBJECT

public:
    explicit AddUser(QSqlDatabase &databse, QWidget *parent = nullptr);
    ~AddUser();

private slots:
    void on_saveButton_clicked();

private:
    Ui::AddUser *ui;

    // Validation functions
    bool checkFullName() const;

    QSqlDatabase *m_databse{nullptr};
};

#endif // ADDUSER_H
