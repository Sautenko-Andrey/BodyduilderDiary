#include "findcustomer.h"
#include "ui_findcustomer.h"
#include "query_messages.h"

#include <QMessageBox>
#include <QDebug>
#include <QPushButton>
#include <algorithm>
#include <QTextStream>

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
        exit(1);
    }

    // Fill the list widget with customers names
    std::for_each(m_data.cbegin(), m_data.cend(), [this](const auto &el){

        auto &name = el->getName();

        ui->InfoListWidget->addItem(name);
    });


    // Signals and slots
    connect(ui->InfoListWidget, &QListWidget::doubleClicked,
            this, &FindCustomer::onUserDoubleClicked);


}

FindCustomer::~FindCustomer()
{
    delete ui;
}

void FindCustomer::onUserDoubleClicked()
{
    // what row was selected?
    int &&row = ui->InfoListWidget->currentRow();

    // Search a customer by key(id)
    auto it = m_data.find(row + 1);

    if(it != m_data.end()){
        // Make info string
        QString info;
        QTextStream stream(&info);

        stream << "Age: " << (*it)->getAge()
               << "\nHeight: " << (*it)->getHeight()
               << "\nWeight: " << (*it)->getWeight()
               << "\nNotes: " << (*it)->getNotice();

        QMessageBox::information(this, (*it)->getName(), info);
        return;
    }
}
