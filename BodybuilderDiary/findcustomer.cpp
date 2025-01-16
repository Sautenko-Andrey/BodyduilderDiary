#include "findcustomer.h"
#include "ui_findcustomer.h"
#include "query_messages.h"

#include <QMessageBox>
#include <QDebug>
#include <QPushButton>

FindCustomer::FindCustomer(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::FindCustomer)
{

    ui->setupUi(this);

    // Showing all customers in the block
    DataBaseManager &ref_db_manager = DataBaseManager::getInstance();

    // Read data from the database and save it into QMap
    auto res = ref_db_manager.readRequestToDB(read_customers_query_all,
                                              m_data, Customer::getFieldsNum());

    if(!res){
        QMessageBox::warning(this, "Database error",
                                 "Couldn't read customers data");
        return;
    }
    else{
        QMessageBox::information(this, "Test", "Success!");
    }

}

FindCustomer::~FindCustomer()
{
    delete ui;
}
