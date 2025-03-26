#ifndef FIND_H
#define FIND_H

#include <QDialog>
#include <QMap>
#include "customer.h"


namespace Ui {
class FindCustomer;
}

enum class FindType { Customer, Exercise };

class Find : public QDialog
{
    Q_OBJECT

public:
    Find(FindType find_type, QWidget *parent = nullptr);
    ~Find();

private slots:
    void onUserDoubleClicked();

    void textEdited();

    void searchCustomer();

    void on_clearAllButton_clicked();

    void on_showUsersListButton_clicked();

private:
    Ui::FindCustomer *ui;

    QMap<QString, std::shared_ptr<Customer>> m_data;

    void fillListWidget();
};

#endif // FIND_H
