#ifndef EDITCUSTOMER_H
#define EDITCUSTOMER_H

#include <QDialog>

namespace Ui {
class EditCustomer;
}

class EditCustomer : public QDialog
{
    Q_OBJECT

public:
    explicit EditCustomer(QWidget *parent = nullptr);
    ~EditCustomer();

private:
    Ui::EditCustomer *ui;
};

#endif // EDITCUSTOMER_H
