#include "adduser.h"
#include "ui_adduser.h"
#include <QMessageBox>
#include <QSqlQuery>

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
    : QDialog(parent)
    , ui(new Ui::AddUser)
{
    ui->setupUi(this);

    // Prepare database manager
    //db_manager.prepare();

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


    // Save data into the databse
    //QSqlQuery query(db_manager.getDatabase());




    // Close the dialog window
    this->accept();
}



