#ifndef DELETECUSTOMER_H
#define DELETECUSTOMER_H

#include <QDialog>
#include <QMap>
#include <QSet>
#include "customer.h"

namespace Ui {
class DeleteCustomer;
}

class DeleteCustomer : public QDialog
{
    Q_OBJECT

public:
    explicit DeleteCustomer(QWidget *parent = nullptr);
    ~DeleteCustomer();

private slots:
    void textEdited();

    void on_deleteButton_clicked();

    void enterPressed();

private:
    Ui::DeleteCustomer *ui;

    QMap<QString, std::shared_ptr<Customer>> m_data;

    QSet<QString> m_customers_names;

    QString m_name;

};

#endif // DELETECUSTOMER_H
