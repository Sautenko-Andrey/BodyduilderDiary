#ifndef FINDCUSTOMER_H
#define FINDCUSTOMER_H

#include <QDialog>


namespace Ui {
class FindCustomer;
}

class FindCustomer : public QDialog
{
    Q_OBJECT

public:
    explicit FindCustomer(QWidget *parent = nullptr);
    ~FindCustomer();

private:
    Ui::FindCustomer *ui;

    QList<QString> users_data;

    QList<QPushButton *> users_ptrs_list;
};

#endif // FINDCUSTOMER_H
