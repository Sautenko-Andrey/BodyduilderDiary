#include "adduser.h"
#include "ui_adduser.h"
#include <QMessageBox>
#include <QSqlQuery>
#include "databasemanager.h"
#include "query_messages.h"

enum class UserData {

    MinAge = 4,
    MaxAge = 100,
    DefaultAge = 18,
    MinWeight = 20,
    MaxWeight = 250,
    DefaultWeight = 50,
    MinHeight = 120,
    MaxHeight = 250,
    DefaultHeight = 175

};


AddUser::AddUser(QWidget *parent)
    : QDialog(parent),
      ui(new Ui::AddUser)
{
    ui->setupUi(this);

    // Make all labels bold and with font 12
    // Using lambda-function
    auto makeLabelBold = (
        [this](QLabel *label) -> void {

        label->setAlignment(Qt::AlignCenter);

        QFont font = label->font();

        font.setBold(true);
        font.setPointSize(12);

        label->setFont(font);
    });

    makeLabelBold(ui->fullNameLabel);
    makeLabelBold(ui->ageLabel);
    makeLabelBold(ui->weightLabel);
    makeLabelBold(ui->heightLabel);
    makeLabelBold(ui->notesLabel);
    makeLabelBold(ui->genderLabel);

    // Widget settings

    // Start focus
    ui->fullNameLineEdit->setFocus();

    // Age
    ui->ageSpinBox->setMaximum(static_cast<int>(UserData::MaxAge));
    ui->ageSpinBox->setMinimum(static_cast<int>(UserData::MinAge));
    ui->ageSpinBox->setValue(static_cast<int>(UserData::DefaultAge));

    //Gender
    ui->maleRadioButton->setChecked(true);

    //Height
    ui->heightSpinBox->setMaximum(static_cast<int>(UserData::MaxHeight));
    ui->heightSpinBox->setMinimum(static_cast<int>(UserData::MinHeight));
    ui->heightSpinBox->setValue(static_cast<int>(UserData::DefaultHeight));

    //Weight
    ui->weightSpinBox->setMaximum(static_cast<int>(UserData::MaxWeight));
    ui->weightSpinBox->setMinimum(static_cast<int>(UserData::MinWeight));
    ui->weightSpinBox->setValue(static_cast<int>(UserData::DefaultWeight));


}

AddUser::~AddUser()
{
    delete ui;
}


/*
    Function checks full name.
    It must has two words: first name and last name.
    If it doesn't satisfy it shows user warning message.
*/
bool AddUser::checkFullName() const {

    const QString &full_name = ui->fullNameLineEdit->text();

    // Delete unwated spaces from the full name line
    const QString clear_full_name = full_name.trimmed();

    int spaces_amount = clear_full_name.count(" ");

    constexpr int max_spaces{1};

    return (spaces_amount != max_spaces) ? false : true;
}


/*
    Private slot checks all input data and save it in a database
*/
void AddUser::on_saveButton_clicked()
{
    // Checking input data
    if(!checkFullName()){
        QMessageBox::warning(this, "Full name error",
                             "Type first name and last name separetly");
    }

    // Checking notes text lenght
    const QString &notes_text = ui->notesTextEdit->placeholderText();

    constexpr int max_notes_symbols{200};

    if(notes_text.size() > max_notes_symbols){
        QMessageBox::warning(this, "Notes error",
                             "Too long notes text");
    }

    // Create a new databse for all customers
    // Save data into the databse
    auto &ref_db_manager = DataBaseManager::getInstance();

    auto res_1 = ref_db_manager.writeRequestToDB(customers_query);


    // Define customers gender
    int gender{0};
    if(ui->maleRadioButton->isChecked()){
        gender = 1;
    }

    auto res_2 = ref_db_manager.writeRequestToDB(new_customer_query,
                {
                    {":i_full_name", ui->fullNameLineEdit->text()},
                    {":i_age", ui->ageSpinBox->value()},
                    {":i_sex", gender},
                    {":i_height", ui->heightSpinBox->value()},
                    {":i_weight", ui->weightSpinBox->value()},
                    {":i_notes", ui->notesTextEdit->toPlainText()}

                });

    if(!res_1 || !res_2){
        QMessageBox::warning(this, "Database error",
                             "Couldn't save a new customer");
    }
    else{
        QMessageBox::information(this, "Adding a new customer", "Done!");
    }

    // Close the dialog window
    this->accept();
}
