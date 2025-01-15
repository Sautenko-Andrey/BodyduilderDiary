#include "findcustomer.h"
#include "ui_findcustomer.h"
#include "databasemanager.h"
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

    constexpr int columns_in_table{5};
    auto res = ref_db_manager.readRequestToDB(read_customers_query,
                                users_data, columns_in_table,
                                {"Name", "Age", "Sex", "Height", "Weight"});

    if(!res){
        QMessageBox::warning(this, "Database error",
                             "Couldn't read customers data");
        return;
    }
    else{
        for(const auto &user : users_data){
            QPushButton *user_btn = new QPushButton(user, this);

            // Save pointer on button
            users_ptrs_list.push_back(user_btn);

            QListWidgetItem *item = new QListWidgetItem(ui->InfoListWidget);

            ui->InfoListWidget->setItemWidget(item, user_btn);
        }
    }
}

FindCustomer::~FindCustomer()
{
    delete ui;
}
