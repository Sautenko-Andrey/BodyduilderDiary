#include "editcustomer.h"
#include "ui_editcustomer.h"

EditCustomer::EditCustomer(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::EditCustomer)
{
    ui->setupUi(this);

    // Search line settings
    ui->searchLine->setPlaceholderText("Type here customer's name");
}

EditCustomer::~EditCustomer()
{
    delete ui;
}
