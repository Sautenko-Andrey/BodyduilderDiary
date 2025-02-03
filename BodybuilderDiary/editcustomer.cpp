#include "editcustomer.h"
#include "ui_editcustomer.h"
#include "databasemanager.h"
#include "query_messages.h"

#include <QMessageBox>
#include <QCompleter>

enum class Size{
    MaxAge = 100,
    MaxHeight = 250,
    MaxWeight = 300,
    WidgetWidth = 482,
    RegularModeHeight = 488,
    HideModeHeight = 120
};

EditCustomer::EditCustomer(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::EditCustomer)
{
    ui->setupUi(this);

    // Main widget settings
    this->resize(
        static_cast<int>(Size::WidgetWidth),
        static_cast<int>(Size::HideModeHeight)
    );

    // Search line settings
    ui->searchLine->setPlaceholderText("Type here customer's name");

    // Age spin box settings
    ui->ageSpinBox->setMaximum(static_cast<int>(Size::MaxAge));

    // Height and weight spin boxes settings
    ui->heightSpinBox->setMaximum(static_cast<int>(Size::MaxHeight));
    ui->weightSpinBox->setMaximum(static_cast<int>(Size::MaxWeight));

    // Hide empty widgets
    hideDataWidgets();

    // Get referenct on databse
    auto &ref_db_manager = DataBaseManager::getInstance();

    // Read data from the database and save it into QMultiMap
    auto res = ref_db_manager.readRequestToDB(CustomQuery::read_customers_query_all,
                                              m_data, Customer::getFieldsNum());

    if(!res){
        QMessageBox::warning(this, "Database error",
                             "Couldn't read customers data");
        return;
    }

    // Signals and slots
    // Search customers via Completer
    connect(ui->searchLine, &QLineEdit::returnPressed,
            this, &EditCustomer::searchCustomer);

    // User types something in the searching line
    connect(ui->searchLine, &QLineEdit::textEdited,
            this, &EditCustomer::textEdited);

}

EditCustomer::~EditCustomer()
{
    delete ui;
}

void EditCustomer::searchCustomer()
{
    // If search line is empty ignore command
    if(ui->searchLine->text().isEmpty()){
        return;
    }

    // Resize widget
    this->resize(
        static_cast<int>(Size::WidgetWidth),
        static_cast<int>(Size::RegularModeHeight)
    );

    // Make all widgets visible and disable
    showDataWidgets();


    // Get target name
    m_customer_name = ui->searchLine->text();

    // Show user in the database
    auto itr = m_data.find(m_customer_name);

    if(itr != m_data.end()){
        // Name found
        // Fill widgets with user's data
        // Name
        ui->fullNameLine->setText((*itr)->getName());
        // Age
        ui->ageSpinBox->setValue((*itr)->getAge());
        // Gender
        (*itr)->getGender() ?
            ui->maleRadioButton->setChecked(true) :
            ui->femaleRadioButton->setChecked(true);
        // Height
        ui->heightSpinBox->setValue((*itr)->getHeight());
        // Weight
        ui->weightSpinBox->setValue((*itr)->getWeight());
        // Notes
        ui->notesTextEdit->setText((*itr)->getNotice());
    }


}

/*
    Method make searching process much easy for the user.
    It gives hints while user types target name.
*/
void EditCustomer::textEdited()
{
    // Get all customers names

    for(auto it = m_data.cbegin(); it != m_data.cend(); ++it){
        m_customers_names << (*it)->getName();
    }

    QStringList names = QStringList(m_customers_names.begin(), m_customers_names.end());

    // Set up QCompliter for auto completer(for user's conveniece)
    QCompleter *completer = new QCompleter(names, this);

    // Register independency
    completer->setCaseSensitivity(Qt::CaseInsensitive);
    ui->searchLine->setCompleter(completer);
}

void EditCustomer::hideDataWidgets()
{
    // Hide empty widgets
    ui->fullNameLabel->hide();
    ui->fullNameLine->hide();
    ui->sexLabel->hide();
    ui->maleRadioButton->hide();
    ui->femaleRadioButton->hide();
    ui->ageLabel->hide();
    ui->ageSpinBox->hide();
    ui->heightLabel->hide();
    ui->heightSpinBox->hide();
    ui->weightLabel->hide();
    ui->weightSpinBox->hide();
    ui->notesLabel->hide();
    ui->notesTextEdit->hide();
    ui->editButton->hide();
}

void EditCustomer::showDataWidgets()
{
    // Make all widgets visible
    ui->fullNameLabel->show();
    ui->fullNameLine->show();
    ui->sexLabel->show();
    ui->maleRadioButton->show();
    ui->femaleRadioButton->show();
    ui->ageLabel->show();
    ui->ageSpinBox->show();
    ui->heightLabel->show();
    ui->heightSpinBox->show();
    ui->weightLabel->show();
    ui->weightSpinBox->show();
    ui->notesLabel->show();
    ui->notesTextEdit->show();
    ui->editButton->show();
}


void EditCustomer::on_editButton_clicked()
{
    // make an update query to db
    auto &ref_db_manager = DataBaseManager::getInstance();

    auto gender{1};

    if(ui->femaleRadioButton->isChecked()){
        gender = 0;
    }

    auto result = ref_db_manager.writeRequestToDB(CustomQuery::update_user_query,
                            {
                             {":i_new_name", ui->fullNameLine->text()},
                             {":i_full_name", m_customer_name},
                             {":i_age", ui->ageSpinBox->value()},
                             {":i_sex", gender},
                             {":i_height", ui->heightSpinBox->value()},
                             {":i_weight", ui->weightSpinBox->value()},
                             {":i_notes", ui->notesTextEdit->toPlainText()}
                            });

    if (!result){
        QMessageBox::warning(this, "Database error",
                             "Couldn't save changes");
        return;
    }

    QMessageBox::information(this, "Edit report",
                             "Changes have been saved!");

    // Clean searching line, hide info widgets and resize dialog widget
    ui->searchLine->clear();

    hideDataWidgets();

    this->resize(
        static_cast<int>(Size::WidgetWidth),
        static_cast<int>(Size::HideModeHeight));

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

