#ifndef FINDCUSTOMER_H
#define FINDCUSTOMER_H

#include <QDialog>
#include "databasemanager.h"
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

private:
    Ui::FindCustomer *ui;

    //MapStruct m_data;
    QMap<int, std::shared_ptr<Customer>> m_data;

};

#endif // FINDCUSTOMER_H
