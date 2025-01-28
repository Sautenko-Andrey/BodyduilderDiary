#ifndef FINDCUSTOMER_H
#define FINDCUSTOMER_H

#include <QDialog>
#include <QMap>
#include "customer.h"

namespace Ui {
class FindCustomer;
}

class FindCustomer : public QDialog
{
    Q_OBJECT

public:
    explicit FindCustomer(QWidget *parent = nullptr);
    ~FindCustomer();

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

#endif // FINDCUSTOMER_H
