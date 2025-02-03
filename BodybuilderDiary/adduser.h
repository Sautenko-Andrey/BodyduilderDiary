#ifndef ADDUSER_H
#define ADDUSER_H

#include <QDialog>
#include <deque>

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

    void changeText();

private:
    Ui::AddUser *ui;

    std::deque<QString> m_customers_names;

    // Validation functions
    bool checkFullName() const;

};

#endif // ADDUSER_H
