#ifndef EDITCUSTOMER_H
#define EDITCUSTOMER_H

#include <QDialog>

#include "customer.h"

namespace Ui {
class EditCustomer;
}

class EditCustomer : public QDialog
{
    Q_OBJECT

public:
    explicit EditCustomer(QWidget *parent = nullptr);
    ~EditCustomer();

private slots:

    void searchCustomer();

    void textEdited();

private:
    Ui::EditCustomer *ui;

    QMultiMap<QString, std::shared_ptr<Customer>> m_data;

    QString m_customer_name;

    void hideDataWidgets();

    void showDataWidgets();
};

#endif // EDITCUSTOMER_H
