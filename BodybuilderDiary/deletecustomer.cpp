#include "deletecustomer.h"
#include "ui_deletecustomer.h"
#include "databasemanager.h"
#include "query_messages.h"

#include <QMessageBox>
#include <QCompleter>
#include <QTextStream>
#include <QDebug>

enum class Size{
    WidgetWidth = 482,
    RegularModeHeight = 488,
    HideModeHeight = 120
};

DeleteCustomer::DeleteCustomer(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::DeleteCustomer)
{
    ui->setupUi(this);

    // Search line settings
    ui->searchLine->setPlaceholderText("Type here customer's name");

    // Hide plain text edit widget
    ui->plainTextEdit->hide();

    // Make size for hide mode
    this->resize(
        static_cast<int>(Size::WidgetWidth),
        static_cast<int>(Size::HideModeHeight)
    );

    // Get all customers names
    DataBaseManager &ref_db_manager = DataBaseManager::getInstance();

    auto res =
        ref_db_manager.readRequestToDB(CustomQuery::read_customers_query_all,
                                       m_data,
                                       Customer::getFieldsNum());

    if(!res){
        QMessageBox::warning(this, "Database error",
                             "Couldn't read customers data");
        return;
    }

    // Signals and slots
    // User types something in the searching line
    connect(ui->searchLine, &QLineEdit::textEdited,
            this, &DeleteCustomer::textEdited);

    // User press Enter
    connect(ui->searchLine, &QLineEdit::returnPressed,
            this, &DeleteCustomer::enterPressed);

}

DeleteCustomer::~DeleteCustomer()
{
    delete ui;
}



/*
    Method make searching process much easy for the user.
    It gives hints while user types target name.
*/
void DeleteCustomer::textEdited()
{
    // Get all customers names

    for(auto it = m_data.cbegin(); it != m_data.cend(); ++it){
        m_customers_names << (*it)->getName();
    }

    QStringList names = QStringList(m_customers_names.begin(),
                                    m_customers_names.end());

    // Set up QCompliter for auto completer(for user's conveniece)
    QCompleter *completer = new QCompleter(names, this);

    // Register independency
    completer->setCaseSensitivity(Qt::CaseInsensitive);
    ui->searchLine->setCompleter(completer);
}


/*
    When user confirms deleting
*/
void DeleteCustomer::on_deleteButton_clicked()
{
    // Make a delete query to DB

    const QString delete_user_query = "DELETE "
                                      "FROM customers "
                                      "WHERE full_name = :i_full_name";

    DataBaseManager &ref_db_manager = DataBaseManager::getInstance();

    auto res = ref_db_manager.writeRequestToDB(delete_user_query,
                                               {
                                                {":i_full_name", m_name}
                                               });

    if(!res){
        QMessageBox::warning(this, "Report",
                             "Couldn't delete the customer");
        return;
    }

    QMessageBox::information(this, "Report",
                             "The customer has been deleted");

    // Make size for hide mode
    this->resize(
        static_cast<int>(Size::WidgetWidth),
        static_cast<int>(Size::HideModeHeight)
    );

    ui->plainTextEdit->hide();
    ui->searchLine->clear();

    // Get all updated customers names

    m_data.clear();

    // Read data from the database and save it into QMultiMap
    auto update_res = ref_db_manager.readRequestToDB(CustomQuery::read_customers_query_all,
                                                     m_data, Customer::getFieldsNum());

    if(!update_res){
        QMessageBox::warning(this, "Database error",
                             "Couldn't read updated customers data");
        return;
    }

    m_customers_names.clear();

    for(auto it = m_data.cbegin(); it != m_data.cend(); ++it){
        m_customers_names << (*it)->getName();
    }
}




void DeleteCustomer::enterPressed()
{
    /*
        When user presses Enter method begines searching a
        customer by name.
    */

    // If search line is empty ignore command
    if(ui->searchLine->text().isEmpty()){
        return;
    }

    // Make size for regular mode
    this->resize(
        static_cast<int>(Size::WidgetWidth),
        static_cast<int>(Size::RegularModeHeight)
    );

    // Show text plain edit again
    ui->plainTextEdit->show();

    // Get name from QLinedEdit
    m_name = ui->searchLine->text();

    // Find this user and get its data
    auto res = m_data.find(m_name);

    if(res == m_data.end()){
        QMessageBox::warning(this, "Report", "Customer doesn't exist");
        return;
    }

    // Fill text plain edit widget with customer's data
    QString info;
    QTextStream stream(&info);

    stream << "Name:\t" << (*res)->getName()
           << "\n\nAge:\t" << (*res)->getAge()
           << "\n\nHeight:\t" << (*res)->getHeight()
           << "\n\nWeight:\t" << (*res)->getWeight()
           << "\n\nNotice:\t" << (*res)->getNotice();

    ui->plainTextEdit->setPlainText(info);

    // Make info widget disable
    ui->plainTextEdit->setDisabled(true);

}

